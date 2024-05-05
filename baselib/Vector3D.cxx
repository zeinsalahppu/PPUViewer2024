// Vector3D.cxx
//
// GDV II-Uebung Nr.3, SS 2000
//
// Elementarer Datentyp fuer Vektorrechnung. Richtungsvektor mit
// passenden Operationen.
//
// 18.5.00
//
// copyright 2000 WSI/GRIS, University of Tuebingen

#include "Vector3D.h"
#include "Point3D.h"

using namespace gris;

double Vector3D::epsilon = 1e-6;

Point3D Vector3D::getPoint() const
{
	return Point3D(val[0], val[1], val[2]);
}

Point3D Vector3D::operator+(const Point3D &p) const
{
	return Point3D(val[0] + p[0], val[1] + p[1], val[2] + p[2]);
}

Point3D Vector3D::operator-(const Point3D &p) const
{
	return Point3D(val[0] - p[0], val[1] - p[1], val[2] - p[2]);
}
   
Vector3D &Vector3D::operator+=(const Vector3D &v)
{
	for (int i=0; i<3; ++i)
	{
		val[i] += v.val[i];
	}

	return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &v)
{
	for (int i=0; i<3; ++i)
	{
		val[i] -= v.val[i];
	}

	return *this;
}

#ifdef WIN32
std::iostream &operator<<(std::iostream &os, const Vector3D &v)
#else
ostream &operator<<(ostream &os, const Vector3D &v)
#endif
{
	os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";

	return os;
}
