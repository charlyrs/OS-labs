#include "Vector.h"
Vector::Vector()
{
	x.setNumber(0);
	y.setNumber(0);
}

Vector::Vector(Number x_coord, Number y_coord)
{
	this->x.setNumber(x_coord.getNumber());
	this->y.setNumber(y_coord.getNumber());
}

Number Vector::calculatePolarRadius()
{
	return Number(sqrt((x*x + y*y).getNumber()));
}

Number Vector::calculatePolarAngle()
{
	return Number(atan((y/x).getNumber()));
}

Vector Vector::operator+(const Vector& vector)
{
	return Vector(x + vector.x, y+vector.y);
}

