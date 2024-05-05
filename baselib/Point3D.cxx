#include "Point3D.h"
#include "Vector3D.h"

using namespace gris;

double Point3D::epsilon = 1e-6;

Vector3D Point3D::getVector() const
{
	return Vector3D(val[0], val[1], val[2]);
}

Point3D Point3D::operator+(const Vector3D &v) const
{
	return Point3D(val[0]+v[0], val[1]+v[1], val[2]+v[2]);
}

Point3D Point3D::operator-(const Vector3D &v) const
{
	return Point3D(val[0]-v[0], val[1]-v[1], val[2]-v[2]);
}

Vector3D Point3D::operator-(const Point3D &p) const
{
	return Vector3D(val[0]-p.val[0], val[1]-p.val[1], val[2]-p.val[2]);
}
   
Point3D &Point3D::operator+=(const Vector3D &v)
{
	for (int i=0; i<3; ++i)
	{
		val[i] += v[i];
	}

	return *this;
}

Point3D &Point3D::operator-=(const Vector3D &v)
{
	for (int i=0; i<3; ++i)
	{
		val[i] -= v[i];
	}

	return *this;
}

#ifdef WIN32
std::iostream &operator<<(std::iostream &os, const Point3D &p)
#else
iostream &operator<<(iostream &os, const Point3D &p)
#endif
{
	os << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")";

	return os;
}
