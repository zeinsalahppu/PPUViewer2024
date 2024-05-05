#ifndef VECTOR3D_H
#define VECTOR3D_H

// Vector3D.h
//
// GDV II-Uebung Nr.3, SS 2000
//
// Elementarer Datentyp fuer Vektorrechnung. Richtungsvektor mit
// passenden Operationen.
//
// 18.5.00
//
// copyright 2000 WSI/GRIS, University of Tuebingen

#include <assert.h>
#include <math.h>
#ifdef WIN32
#include <iostream>
#else
#include <iostream.h>
#endif

namespace gris
{

class Point3D;

class Vector3D
{
public:
	// Konstruktoren
	Vector3D(double x=0, double y=0, double z=0);
	// Copykonstruktor
	Vector3D(const Vector3D &v);
	// Zuweisung
	void operator=(const Vector3D &v);

	Point3D getPoint() const;

	// Zugriffsmethoden
	double x() const;
	double y() const;
	double z() const;
	double operator[](int i) const;

	double &x();
	double &y();
	double &z();
	double &operator[](int i);

	// Vergleichsoperatoren  
	bool operator==(const Vector3D &v) const;
	bool operator!=(const Vector3D &v) const;

	// Addition/Subtraktion
	Vector3D operator+(const Vector3D &v) const;
	Vector3D operator-(const Vector3D &v) const;
	Vector3D operator-() const;
	Point3D operator+(const Point3D &p) const;
	Point3D operator-(const Point3D &p) const;

	Vector3D &operator+=(const Vector3D &v);
	Vector3D &operator-=(const Vector3D &v);

	// Skalaroperationen
	Vector3D operator*(double s) const;
	Vector3D &operator*=(double s);
	Vector3D operator/(double s) const;
	Vector3D &operator/=(double s);
	friend Vector3D operator*(double s, const Vector3D &v);

	//! inner product
	double operator*(const Vector3D &v) const;
	//! vector product
	Vector3D operator^(const Vector3D &v) const;

	// Normierung
	double norm() const;
	Vector3D getNormalized() const;
	double normalize();

   //! liefert Zeiger auf Vektoreinträge, nützlich für Argumente
   //! von OpenGl Befehlen (z.B. glNormal3dv())
   inline operator double*() {
      return &((*this)[0]);
   }

	static double epsilon;

private:
	double val[3];
};

// Zusaetzliche Funktionen ====================================================
#ifdef WIN32
std::iostream &operator<<(std::iostream &os, const Vector3D &v);
#else
ostream &operator<<(ostream &os, const Vector3D &v);
#endif

// Inline-Methoden ============================================================

inline
Vector3D::Vector3D(double x, double y, double z) 
{
	val[0] = x;
	val[1] = y;
	val[2] = z;
}

inline
Vector3D::Vector3D(const Vector3D &v) 
{ 
	for (int i=0; i<3; ++i)
	{
		val[i] = v.val[i];
	}
}

inline
void Vector3D::operator=(const Vector3D& v)
{
	for (int i=0; i<3; ++i)
	{
		val[i] = v.val[i];
	}
}

inline
double Vector3D::x() const
{
	return val[0];
}

inline
double Vector3D::y() const
{
	return val[1];
}

inline
double Vector3D::z() const
{
	return val[2];
}

inline
double Vector3D::operator[](int i) const
{
	assert(0<=i && i<3);

	return val[i];
}

inline
double &Vector3D::x()
{
	return val[0];
}

inline
double &Vector3D::y()
{
	return val[1];
}

inline
double &Vector3D::z()
{
	return val[2];
}

inline
double &Vector3D::operator[](int i) 
{
	assert(0<=i && i<3);

	return val[i];
}

inline
bool Vector3D::operator==(const Vector3D &p) const
{
	return (fabs(val[0] - p.val[0]) < epsilon 
		&&  fabs(val[1] - p.val[1]) < epsilon
		&&  fabs(val[2] - p.val[2]) < epsilon);
}

inline
bool Vector3D::operator!=(const Vector3D &p) const
{
	return ! (*this == p);
}

inline
Vector3D Vector3D::operator+(const Vector3D &v) const
{
	return Vector3D(val[0]+v[0], val[1]+v[1], val[2]+v[2]);
}

inline
Vector3D Vector3D::operator-(const Vector3D &v) const
{
	return Vector3D(val[0]-v[0], val[1]-v[1], val[2]-v[2]);
}

inline
Vector3D Vector3D::operator-() const
{
	return Vector3D(-val[0], -val[1], -val[2]);
}

inline
Vector3D Vector3D::operator*(double s) const
{
	return Vector3D(val[0]*s, val[1]*s, val[2]*s);
}

inline
Vector3D Vector3D::operator/(double s) const
{
	return Vector3D(val[0]/s, val[1]/s, val[2]/s);
}

inline
Vector3D &Vector3D::operator*=(double s)
{
	for (int i=0; i<3; ++i)
	{
		val[i] *= s;
	}
		
	return *this;
}

inline
Vector3D &Vector3D::operator/=(double s)
{
	for (int i=0; i<3; ++i)
	{
		val[i] /= s;
	}
		
	return *this;
}

inline
double Vector3D::operator*(const Vector3D &v) const
{
	return val[0]*v.val[0] + val[1]*v.val[1] + val[2]*v.val[2];
}

inline
Vector3D Vector3D::operator^(const Vector3D &v) const
{
	return Vector3D(val[1]*v.val[2] - val[2]*v.val[1],
				    val[2]*v.val[0] - val[0]*v.val[2],
				    val[0]*v.val[1] - val[1]*v.val[0]);
}

inline
double Vector3D::norm() const
{
	return sqrt(val[0]*val[0] + val[1]*val[1] + val[2]*val[2]); 
}

inline
double Vector3D::normalize()
{
	double n = norm();
	if (n>=epsilon)
	{
		for (int i=0; i<3; ++i)
		{
			val[i] /= n;
		}
	}

	return n;
}

inline
Vector3D Vector3D::getNormalized() const
{
	Vector3D result(*this);
	result.normalize();

	return result;
}

// friends ====================================================================

inline
Vector3D operator*(double s, const Vector3D &v)
{
	return Vector3D(v.val[0]*s, v.val[1]*s, v.val[2]*s);
}

} // namespace gris

#endif
