#ifndef MATRIX4D_H
#define MATRIX4D_H

// Matrix4D.h
//
// GDV II-Uebung Nr.3, SS 2000
//
// 4x4 Matrix. Im Augenblick noch elementar. Kann erweitert werden
//
// 16.5.00
//
// copyright 2000 WSI/GRIS, University of Tuebingen

#include <assert.h>
#include "Vector3D.h"
#include "Point3D.h"

namespace gris
{

class Matrix4D
{
private:
	// Proxyclass fuer wahlfreien Zugriff auf einzelen Elemente
	class MatrixRow
	{
	public:
		MatrixRow(double *v);

		double operator[](int i) const;
		double &operator[](int i);

	private:
		// Zeiger auf 4 doubles in Array
		double *val;
	};

public:
	//! construktor.
	Matrix4D(double  v0=1, double  v1=0, double  v2=0, double  v3=0,
		     double  v4=0, double  v5=1, double  v6=0, double  v7=0,
			 double  v8=0, double  v9=0, double v10=1, double v11=0,
			 double v12=0, double v13=0, double v14=0, double v15=1);
	// Copykonstruktor
	Matrix4D(const Matrix4D &m);
	// Zuweisung
	void operator=(const Matrix4D &m);

	//! Generate a scaling matrix
	static Matrix4D Scale(double s0, double s1, double s2);
	//! Generate a translation matrix
	static Matrix4D Translate(const Vector3D &t); 
	//! Generate a translation matrix
	static Matrix4D Rotate(const Vector3D &axis, double angle); 

	// Zugriffsoperator
	MatrixRow operator[](int i);
	MatrixRow operator[](int i) const;

	Point3D operator*(const Point3D &p) const;
	Vector3D operator*(const Vector3D &v) const;
	Matrix4D operator*(const Matrix4D &m) const;
	Matrix4D &operator*=(const Matrix4D &m);

	// Matrix4D invertieren
	void invert();

   //! liefert Zeiger auf Matrizeneinträge, nützlich für Argumente
   //! von OpenGl Befehlen (z.B. glMultMatrixd())
   inline operator double*() {
      return &((*this)[0][0]);
   }

private:
	// Matrixwerte
	double val[16];
};

inline
Matrix4D::MatrixRow::MatrixRow(double *v)
{
	val = v;
}

inline
double Matrix4D::MatrixRow::operator[](int i) const
{
	assert(0<=i && i<4);

	return val[i];
}

inline
double &Matrix4D::MatrixRow::operator[](int i)
{
	assert(0<=i && i<4);

	return val[i];
}

} // namespace gris

#endif // MATRIX4D_H
