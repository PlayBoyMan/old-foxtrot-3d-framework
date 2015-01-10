#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "vector.h"


namespace framework {
	namespace quat {

		/// Quaternion class. Quaternion data is stored in a Vec4 (x, y, z, w), so that q = ix + jy + kz + w.
		class Quaternion {
		public:

			/// Quaternion data
			union {
				struct{
					vec::Vec4 data;
				};
				struct {
					float x, y, z, w;
				};
				
			};
			
			/// Default constructor
			Quaternion();

			/// Construct from 4 floats
			Quaternion(float x, float y, float z, float w);

			/// Construct from Vec4
			Quaternion(const vec::Vec4 &vec);

			/// Construct from Vec3 + float
			Quaternion(float s, vec::Vec3 &vec);

			/// Subscript operator
			float operator[](const int i);
		};

		/// Dot product between two quaternions
		float dot(const Quaternion &left, const Quaternion &right);

		/// Quaternion product 
		Quaternion operator*(const Quaternion &left, const Quaternion &right);

		/// Scalar multiplication
		Quaternion operator*(const float &left, const Quaternion &right);

		/// Sum operator
		Quaternion operator+(const Quaternion &left, const Quaternion &right);

		/// Subtraction
		Quaternion operator-(const Quaternion &left, const Quaternion &right);

		/// Conjugate operator, i.e., q = s + v -> !q = s - v
		Quaternion operator!(const Quaternion &q);

		/// Absolute value
		float abs(const Quaternion &q);

		/// Inverse of a quaternion
		Quaternion inv(const Quaternion &q);

		/// Quaternion division
		Quaternion operator/(const Quaternion &left, const Quaternion &right);

		/// Print quaternion on the terminal
		void print_quaternion(const Quaternion &left);

	}
}

#endif