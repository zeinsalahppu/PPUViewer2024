#ifndef BOUNDINGBOX3D_H
#define BOUNDINGBOX3D_H

#include "Point3D.h"
#include "Vector3D.h"

#include <math.h>
#include <float.h>

namespace gris
{

class BoundingBox3D 
{
public:
	//! Constructor
	BoundingBox3D(const Point3D &ll = Point3D(0, 0, 0),
		          const Point3D &ur = Point3D(1, 1, 1)); 
	//! copy constructor. 
	BoundingBox3D(const BoundingBox3D &bbox);
	//! asignment operator
	const BoundingBox3D &operator=(const BoundingBox3D &bbox);

	//! returns sum of both bounding boxes. 
	BoundingBox3D operator+(const BoundingBox3D &bbox) const;
    //! adds specified bounding box to this. 
	const BoundingBox3D &operator+=(const BoundingBox3D& bbox);
	//! Adds the specified point to the bounding box, extending it
	BoundingBox3D operator+(const Point3D &p) const;
	//! Adds the specified point to the bounding box, extending it
	const BoundingBox3D &operator+=(const Point3D &p);

	//! lower left corner point of the bounding box. 
	Point3D lowerLeft() const;
	//! upper right corner point of the bounding box. 
	Point3D upperRight() const;

	//! Returns the corner vertex.
	Point3D operator[](int v) const;
	/*! Returns the corner vertex.
     * 0=000 (xyz), 1=100, 2=010, 3=110, 4=001, 5=101, 6=011, 7=111. 
	 */
	//! Center of box
	Point3D center() const;

	//! Returns the radius of the maximum sphere being enclosing in the bounding box. 
	double innerRadius() const;
	//! Returns the radius of the minimum sphere enclosing the bounding box. 
	double outerRadius() const;
	//! Returns the minimum of the range in all dimensions.
	double minSize() const;
	//! Returns the maximum of the range in all dimensions. 
	double maxSize() const;
	//! Returns the size of the box according to dimension d 
	double size(int d) const;

	//! Returns whether or not a point/vector is within the bounding box. 
	bool isInside(const Point3D&) const;

private:
	Point3D myLowerLeft,
			myUpperRight;

}; // class CBoundingBox3D

inline
Point3D BoundingBox3D::lowerLeft() const
{
	return myLowerLeft;
}

inline
Point3D BoundingBox3D::upperRight() const
{
	return myUpperRight;
}

inline
Point3D BoundingBox3D::center() const
{
	return myLowerLeft + (myUpperRight - myLowerLeft)/2;
}

inline
double BoundingBox3D::outerRadius() const 
{ 
	return 0.5 * sqrt(3*maxSize()*maxSize()); 
}; 

inline
double BoundingBox3D::innerRadius() const 
{ 
	return 0.5 * sqrt(3*minSize()*minSize()); 
}

inline
double BoundingBox3D::size(int d) const
{
	assert(0<=d && d<3);

	return myUpperRight[d]-myLowerLeft[d];
}

inline
double BoundingBox3D::minSize() const 
{ 
	double result = DBL_MAX;

	for (short i=0; i<3; ++i)
	{
		if (myUpperRight[i] - myLowerLeft[i] < result)
		{
			result = myUpperRight[i] - myLowerLeft[i];
		}
	}

	return result;
}

inline
double BoundingBox3D::maxSize() const 
{ 
	double result = DBL_MIN;

	for (short i=0; i<3; ++i)
	{
		if (myUpperRight[i] - myLowerLeft[i] > result)
		{
			result = myUpperRight[i] - myLowerLeft[i];
		}
	}

	return result;
}

inline
bool BoundingBox3D::isInside(const Point3D &p) const
{
	for (short i=0; i<3; ++i)
	{
		if (myLowerLeft[i] > p[i] || myUpperRight[i] < p[i])
		{
			return false;
		}
	}

	return true;
}

} // namespace gris

#endif
