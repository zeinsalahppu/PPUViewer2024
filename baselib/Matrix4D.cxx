// Matrix4D.ccc
//
// GDV II-Uebung Nr.3, SS 2000
//
// 4x4 Matrix4D. Im Augenblick noch elementar. Kann erweitert werden
//
// 16.5.00
//
// copyright 2000 WSI/GRIS, University of Tuebingen

#include "Matrix4D.h"
#include <math.h>

using namespace gris;

Matrix4D::Matrix4D(double  v0, double  v1, double  v2, double  v3,
				   double  v4, double  v5, double  v6, double  v7,
				   double  v8, double  v9, double v10, double v11,
				   double v12, double v13, double v14, double v15)
{
	val[0]  = v0;	val[1] = v1;	val[2] = v2;	val[3] = v3;
	val[4]  = v4;	val[5] = v5;	val[6] = v6;	val[7] = v7;
	val[8]  = v8;	val[9] = v9;	val[10] = v10;	val[11] = v11;
	val[12] = v12;	val[13] = v13;	val[14] = v14;	val[15] = v15;
}

Matrix4D::Matrix4D(const Matrix4D &m)
{
	for (int i=0; i<16; ++i)
	{
		val[i] = m.val[i];
	}
}

void Matrix4D::operator=(const Matrix4D &m)
{
	for (int i=0; i<16; ++i)
	{
		val[i] = m.val[i];
	}
}

Matrix4D Matrix4D::Scale(double s0, double s1, double s2)
{
	return Matrix4D(s0,  0,  0, 0,
					 0, s1,  0, 0,
					 0,  0, s2, 0,
					 0,  0,  0, 1);
}

Matrix4D Matrix4D::Translate(const Vector3D &t)
{
	return Matrix4D(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					t.x(), t.y(), t.z(), 1);
}

Matrix4D Matrix4D::Rotate(const Vector3D &axis, double angle)
{
  double cosA = cos(angle),
		 sinA = sin(angle),
		 invCosA = 1.0-cosA;

  return Matrix4D(invCosA*axis[0]*axis[0] + cosA, 
				  invCosA*axis[0]*axis[1] - sinA*axis[2], 
				  invCosA*axis[0]*axis[2] + sinA*axis[1],
				  0,
				  invCosA*axis[0]*axis[1] + sinA*axis[2],
				  invCosA*axis[1]*axis[1] + cosA,
				  invCosA*axis[1]*axis[2] - sinA*axis[0],
				  0,
				  invCosA*axis[0]*axis[2] - sinA*axis[1],
				  invCosA*axis[1]*axis[2] + sinA*axis[0],
				  invCosA*axis[2]*axis[2] + cosA);
}

Point3D Matrix4D::operator*(const Point3D &p) const
{
	Point3D result;

	for (int i=0; i<3; ++i)
	{
		for (int j=0; j<3; ++j)
		{
			result[i] += val[j*4+i]*p[j];
		}
		result[i] += val[12+i];
	}

	double w=0;
	for (int j=0; j<3; ++j)
	{
		w += val[j*4+3]*p[j];
	}
	w += val[15];

	if (w != 0)
	{
		for (int k=0; k<3; ++k)
		{
			result[k] /= w;
		}
	}

	return result;
}

Vector3D Matrix4D::operator*(const Vector3D &v) const
{
	Vector3D result;

	for (int i=0; i<3; ++i)
	{
		for (int j=0; j<3; ++j)
		{
			result[i] += val[j*4+i]*v[j];
		}
	}

	return result;
}

Matrix4D Matrix4D::operator*(const Matrix4D &m) const
{
	Matrix4D result;

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			result.val[i*4+j] = 0;
			for (int s=0; s<4; ++s)
			{
				result.val[i*4+j] += val[i*4+s] * m.val[s*4+j];
			}
		}
	}

	return result;
}

Matrix4D &Matrix4D::operator*=(const Matrix4D &m)
{
	double help[4][4];

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			help[i][j] = 0;
			for (int s=0; s<4; ++s)
			{
				help[i][j] += val[i*4+s] * m.val[s*4+j];
			}
		}
	}

	for (int k=0; k<4; ++k)
	{
		for (int j=0; j<4; ++j)
		{
			val[k*4+j] = help[k][j];
		}
	}

	return *this;
}

void Matrix4D::invert()
{
	double help[4][4];
	int i;

	// Initialisierung 
	for (i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			help[i][j] = val[i*4+j];
		}
	}

	int row[4],
		col[4];
	for (int k=0; k<4; ++k)  
	{
		row[k] = 
		col[k] = k;
        }

	// Austauschverfahren
	int pr,
	    ps,
	    j;
	for (j=0; j<4; ++j)  
	{
		// suche Pivot help[row[pr]][col[ps]]
		pr = j;
		ps = j;

		for (int r=j; r<4; ++r) 
		{
			for (int s=j; s<4; ++s)  
			{
				if (fabs(help[row[r]][col[s]]) > fabs(help[row[pr]][col[ps]]))
				{
					pr = r;   
					ps = s;
				}
			}
		}

		// tausche die Zeilen j,r und die Spalten j,s 
		if (pr > j)
		{
			int temp = row[j];   
			row[j] = row[pr];   
			row[pr] = temp;
		}

		if (ps > j)
		{
			int temp = col[j];   
			col[j] = col[ps];   
			col[ps] = temp;
		}
	  
		// im Rest der j-Schleife passiert der eigentliche Austausch 
		// zwischen der j-ten Zeile und der j-ten Spalte           

		int rowj = row[j],
			colj = col[j];
		double Pivot = help[rowj][colj];

		int i;
		// 1. Schritt: Rechteckregel
		for (i=0; i<4; ++i)  
		{
			if (i != rowj)
			{
				for (int k=0; k<4; ++k) 
				{
					if (k != colj)
					{
						help[i][k] -= (help[i][colj] * help[rowj][k] / Pivot);
					}
				}
			}
		}

	  	// 2. Schritt: Pivotzeile durch negativen Pivot teilen 
		for (int k=0; k<4; ++k)  
		{
			if (k != colj)
			{
				help[rowj][k] /= -Pivot;
			}
		}

		// 3. Schritt: Pivotspalte durch positiven Pivot teilen 
		for (i=0; i<4; ++i)  
		{
			if (i != rowj)
			{
				help[i][colj] /= Pivot;
			}
		}

		// 4. Schritt: Pivot durch sein Inverses ersetzen
		help[rowj][colj] = 1.0 / Pivot;
	} // for j 

	// inverse Matrix4D wieder nach val schreiben 
	for (i=0; i<4; ++i)  
	{
		for (int k=0; k<4; ++k)  
		{
			val[col[i]*4+row[k]] = help[row[i]][col[k]];
		}
	}
}

Matrix4D::MatrixRow Matrix4D::operator[](int i)
{
	assert(0<=i && i<4);

	return MatrixRow(val+i*4);
}

Matrix4D::MatrixRow Matrix4D::operator[](int i) const
{
	assert(0<=i && i<4);

	return MatrixRow(((double *) val)+i*4);
}
