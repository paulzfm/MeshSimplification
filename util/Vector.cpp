#include "Vector.h"

#include <math.h>

Vector::Vector(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector::length() const
{
	return sqrt(x * x + y * y + z * z);
}

double Vector::square() const
{
	return x * x + y * y + z * z;
}

Vector Vector::normalize() const
{
	double inv = 1 / length();
	return Vector(inv * x, inv * y, inv * z);
}

double Vector::dot(const Vector& that) const
{
	return x * that.x + y * that.y + z * that.z;
}

Vector Vector::cross(const Vector& that) const
{
	return Vector(y * that.z - z * that.y,
				  z * that.x - x * that.z,
				  x * that.y - y * that.x);
}

Vector Vector::operator - () const
{
	return Vector(-x, -y, -z);
}

Vector Vector::operator + (const Vector& that) const
{
	return Vector(x + that.x, y + that.y, z + that.z);
}

Vector Vector::operator - (const Vector& that) const
{
	return Vector(x - that.x, y - that.y, z - that.z);
}

Vector Vector::operator * (const Vector& that) const
{
	return Vector(x * that.x, y * that.y, z * that.z);
}

Vector Vector::operator * (double t) const
{
	return Vector(x * t, y * t, z * t);
}

Vector Vector::operator / (double t) const
{
	return Vector(x / t, y / t, z / t);
}

void Vector::operator += (const Vector& that)
{
	x += that.x;
	y += that.y;
	z += that.z;
}

void Vector::operator -= (const Vector& that)
{
	x -= that.x;
	y -= that.y;
	z -= that.z;
}

void Vector::operator *= (const Vector& that)
{
	x *= that.x;
	y *= that.y;
	z *= that.z;
}

void Vector::operator *= (double t)
{
	x *= t;
	y *= t;
	z *= t;
}

void Vector::operator /= (double t)
{
	x /= t;
	y /= t;
	z /= t;
}

Vector operator * (double t, const Vector& v)
{
	return Vector(t * v.x, t * v.y, t * v.z);
}

std::istream& operator >> (std::istream& is, Vector& v)
{
	double tmp;
	is >> tmp;
	v.x = tmp;
	is >> tmp;
	v.y = tmp;
	is >> tmp;
	v.z = tmp;
	return is;
}

std::ostream& operator << (std::ostream& os, const Vector &v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

double Vector::operator [] (int index) const
{
	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}

	return 0;
}

