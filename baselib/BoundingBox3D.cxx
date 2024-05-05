#include "BoundingBox3D.h"

#include <assert.h>

#define MIN(x,y) ((x<y) ? x : y)
#define MAX(x,y) ((x<y) ? y : x)

using namespace gris;

BoundingBox3D::BoundingBox3D(const Point3D &ll, const Point3D &ur)
 : myLowerLeft(MIN(ll.x(), ur.x()), MIN(ll.y(), ur.y()), MIN(ll.z(), ur.z())), 
   myUpperRight(MAX(ll.x(), ur.x()), MAX(ll.y(), ur.y()), MAX(ll.z(), ur.z()))
{
}

BoundingBox3D::BoundingBox3D(const BoundingBox3D &bbox)
{
	myLowerLeft  = bbox.myLowerLeft;
	myUpperRight = bbox.myUpperRight;
}

const BoundingBox3D &BoundingBox3D::operator=(const BoundingBox3D &bbox)
{
	myLowerLeft  = bbox.myLowerLeft;
	myUpperRight = bbox.myUpperRight;

	return *this;
}

BoundingBox3D BoundingBox3D::operator+(const BoundingBox3D &bbox) const
{
	return BoundingBox3D(Point3D(MIN(myLowerLeft.x(), bbox.myLowerLeft.x()), 
								 MIN(myLowerLeft.y(), bbox.myLowerLeft.y()),
								 MIN(myLowerLeft.z(), bbox.myLowerLeft.z())),
						 Point3D(MAX(myUpperRight.x(), bbox.myUpperRight.x()), 
								 MAX(myUpperRight.y(), bbox.myUpperRight.y()),
								 MAX(myUpperRight.z(), bbox.myUpperRight.z())));
}

const BoundingBox3D &BoundingBox3D::operator+=(const BoundingBox3D& bbox)
{
	myLowerLeft = Point3D(MIN(myLowerLeft.x(), bbox.myLowerLeft.x()), 
				  		  MIN(myLowerLeft.y(), bbox.myLowerLeft.y()),
						  MIN(myLowerLeft.z(), bbox.myLowerLeft.z()));
	myUpperRight = Point3D(MAX(myUpperRight.x(), bbox.myUpperRight.x()), 
						   MAX(myUpperRight.y(), bbox.myUpperRight.y()),
						   MAX(myUpperRight.z(), bbox.myUpperRight.z()));

	return *this;
}

BoundingBox3D BoundingBox3D::operator+(const Point3D &p) const
{
	return BoundingBox3D(Point3D(MIN(myLowerLeft.x(), p.x()), 
	 							 MIN(myLowerLeft.y(), p.y()),
								 MIN(myLowerLeft.z(), p.z())),
				         Point3D(MAX(myUpperRight.x(), p.x()), 
								 MAX(myUpperRight.y(), p.y()),
								 MAX(myUpperRight.z(), p.z())));
}

const BoundingBox3D &BoundingBox3D::operator+=(const Point3D &p)
{
	myLowerLeft = Point3D(MIN(myLowerLeft.x(), p.x()), 
				  		  MIN(myLowerLeft.y(), p.y()),
						  MIN(myLowerLeft.z(), p.z()));
	myUpperRight = Point3D(MAX(myUpperRight.x(), p.x()), 
						   MAX(myUpperRight.y(), p.y()),
						   MAX(myUpperRight.z(), p.z()));

	return *this;
}

Point3D BoundingBox3D::operator[](int v) const
{
	switch (v)
	{
		case 0: return Point3D(myLowerLeft[0],  myLowerLeft[1],  myLowerLeft[2]);
		case 1: return Point3D(myUpperRight[0], myLowerLeft[1],  myLowerLeft[2]);
		case 2: return Point3D(myLowerLeft[0],  myUpperRight[1], myLowerLeft[2]);
		case 3: return Point3D(myUpperRight[0], myUpperRight[1], myLowerLeft[2]);
		case 4: return Point3D(myLowerLeft[0],  myLowerLeft[1],  myUpperRight[2]);
		case 5: return Point3D(myUpperRight[0], myLowerLeft[1],  myUpperRight[2]);
		case 6: return Point3D(myLowerLeft[0],  myUpperRight[1], myUpperRight[2]);
		case 7: return Point3D(myUpperRight[0], myUpperRight[1], myUpperRight[2]);	
		default: assert(0); return 0;
	}
}
