#include "Quaternion.h"

#include <stdio.h>
#include <math.h>

using namespace framework::quat;
using namespace framework;

namespace q = framework::quat;

Quaternion::Quaternion() { }

/// Construct from 4 floats
Quaternion::Quaternion(float x, float y, float z, float w)
{
	data.x = x;
	data.y = y;
	data.z = z;
	data.w = w;
}

/// Construct from Vec4
Quaternion::Quaternion(const vec::Vec4 &vec)
{
	data.x = vec.x;
	data.y = vec.y;
	data.z = vec.z;
	data.w = vec.w;
}

/// Construct from Vec3 + float
Quaternion::Quaternion(float s, vec::Vec3 &vec)
{
	data.x = vec.x;
	data.y = vec.y;
	data.z = vec.z;
	data.w = s;
}

/// Subscript operator
float Quaternion::operator[](const int i)
{
	return data[i];
}

// Dot product between two quaternions
float q::dot(const Quaternion &left, const Quaternion &right)
{
	return left.data*right.data;
}

// Quaternion product 
Quaternion q::operator*(const Quaternion &left, const Quaternion &right)
{
	Quaternion temp;

	temp.x = left.x*right.w + left.w*right.x + left.y*right.z - left.z*right.y;
	temp.y = left.y*right.w + left.w*right.y + left.z*right.x - left.x*right.z;
	temp.z = left.z*right.w + left.w*right.z + left.x*right.y - left.y*right.x;
	temp.w = left.w*right.w - left.x*right.x - left.y*right.y - left.z*right.z;

	return temp;
}

// Scalar multiplication
Quaternion q::operator*(const float &left, const Quaternion &right)
{
	Quaternion temp = left*right.data;
	return temp;
}

// Sum operator
Quaternion q::operator+(const Quaternion &left, const Quaternion &right)
{
	Quaternion temp;

	temp.data = left.data + right.data;

	return temp;
}

// Subtraction
Quaternion q::operator-(const Quaternion &left, const Quaternion &right)
{
	Quaternion temp;

	temp.data = left.data - right.data;

	return temp;
}

// Conjugate operator, i.e., q = s + v -> !q = s - v
Quaternion q::operator!(const Quaternion &q)
{
	Quaternion temp;

	temp.data = -1.0f*q.data;
	temp.w *= -1.0f;

	return temp;
}

// Absolute value
float q::abs(const Quaternion &q)
{
	return sqrt(((!q)*q).w);
}

// Inverse of a quaternion
Quaternion q::inv(const Quaternion &q)
{
	return (1 / (((!q)*q).w))*!q;
}

// Quaternion division
Quaternion q::operator/(const Quaternion &left, const Quaternion &right)
{
	return left*inv(right);
}

// Print quaternion on the terminal
void q::print_quaternion(const Quaternion &left)
{
	printf("\n %f + %fi + %fj + %fk \n", left.w, left.x, left.y, left.z);
}

