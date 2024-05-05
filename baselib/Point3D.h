#ifndef POINT3D_H
#define POINT3D_H

// Point.h
//
// GDV II-Uebung Nr.3, SS 2000
//
// Elementarer Datentyp fuer Vektorrechnung. Ortsvektor mit
// passenden Operationen.
//
// 16.5.00
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

class Vector3D;

class Point3D
{   
public:
	//! constructor.
	Point3D(double x=0, double y=0, double z=0);
	//! copyconstructor
	Point3D(const Point3D &p);
    //! cast onstructor
//	Point3D(const Vector3D &v);
	//! assignment operator
	void operator=(const Point3D &p);

	//! cerate vector which points to position represented 
	Vector3D getVector() const;

	//! access to particular members
	double x() const;
	double y() const;
	double z() const;
	double operator[](int i) const;

	double& x();
	double& y();
	double& z(); 
	double& operator[](int i);

	//! comparison operator  
	bool operator==(const Point3D &p) const;
	//! comparison operator  
	bool operator!=(const Point3D &p) const;

	//! addition/subtraction
	Point3D operator+(const Vector3D &v) const;
	Point3D operator-(const Vector3D &v) const;
	Vector3D operator-(const Point3D &p) const;
   
    Point3D &operator+=(const Vector3D &v);
    Point3D &operator-=(const Vector3D &v);

	// scalar operations
	Point3D operator*(double s) const;
	Point3D operator/(double s) const;
	Point3D &operator*=(double s);
	Point3D &operator/=(double s);
	friend Point3D operator*(double s,const Point3D &p);

	//! calc distance between two points
	friend double dist(const Point3D &p0, const Point3D &p1);

	//! epsilon for comparison
	static double epsilon;

   //! liefert Zeiger auf Vektoreinträge, nützlich für Argumente
   //! von OpenGl Befehlen (z.B. glVertex3dv())
   inline operator double*() {
      return &((*this)[0]);
   }

private:
	double val[3];
};

// Zusaetzliche Funktionen ====================================================
#ifdef WIN32
std::iostream &operator<<(std::iostream &os, const Point3D &p);
#else
ostream &operator<<(ostream &os, const Point3D &p);
#endif

// Inline-Methoden ============================================================

inline
Point3D::Point3D(double x, double y, double z) 
{
	val[0] = x;
	val[1] = y;
	val[2] = z;
}

inline
Point3D::Point3D(const Point3D &p) 
{ 
	for (int i=0; i<3; ++i)
	{
		val[i] = p.val[i];
	}
}

//inline
//Point3D::Point3D(const Vector3D &vv) 
//{ 
//	val[0] = vv.x();
//	val[1] = vv.y();
//	val[2] = vv.z();
//}

inline
void Point3D::operator=(const Point3D& p)
{
	for (int i=0; i<3; ++i)
	{
		val[i] = p.val[i];
	}
}

inline
double Point3D::x() const
{
	return val[0];
}

inline
double Point3D::y() const
{
	return val[1];
}

inline
double Point3D::z() const
{
	return val[2];
}

inline
double Point3D::operator[](int i) const
{
	assert(0<=i && i<3);

	return val[i];
}

inline
double &Point3D::x()
{
	return val[0];
}

inline
double &Point3D::y()
{
	return val[1];
}

inline
double &Point3D::z()
{
	return val[2];
}

inline
double &Point3D::operator[](int i) 
{
	assert(0<=i && i<3);

	return val[i];
}

inline
bool Point3D::operator==(const Point3D &p) const
{
	return (fabs(val[0] - p.val[0]) < epsilon 
		&&  fabs(val[1] - p.val[1]) < epsilon
		&&  fabs(val[2] - p.val[2]) < epsilon);
}

inline
bool Point3D::operator!=(const Point3D &p) const
{
	return ! (*this == p);
}

inline
Point3D Point3D::operator*(double s) const
{
	return Point3D(val[0]*s, val[1]*s, val[2]*s);
}

inline
Point3D Point3D::operator/(double s) const
{
	return Point3D(val[0]/s, val[1]/s, val[2]/s);
}

inline
Point3D &Point3D::operator*=(double s)
{
	for (int i=0; i<3; ++i)
	{
		val[i] *= s;
	}
		
	return *this;
}

inline
Point3D &Point3D::operator/=(double s)
{
	for (int i=0; i<3; ++i)
	{
		val[i] /= s;
	}
		
	return *this;
}

// friends ====================================================================

inline
Point3D operator*(double s, const Point3D &p)
{
	return Point3D(p.val[0]*s, p.val[1]*s, p.val[2]*s);
}

inline
double dist(const Point3D &p0, const Point3D &p1)
{
	return sqrt((p0.val[0]-p1.val[0])*(p0.val[0]-p1.val[0]) +
				(p0.val[1]-p1.val[1])*(p0.val[1]-p1.val[1]) +
				(p0.val[2]-p1.val[2])*(p0.val[2]-p1.val[2]));
}

} // namespace gris

#endif
