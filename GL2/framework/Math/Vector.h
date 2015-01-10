#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <GL\glew.h>

#pragma once

namespace framework {
	namespace vec {

		/**
		 * Vector class, using templates for a generic 'n' dimension.
		 * The vector is implemented as an array of floar values.
		 */
		template <int n>
		class Vector {

		public:
			
			/// Float array with the vector's data.
			float data[n];

			
			/// Default constructor, empty.			
			Vector() {}

			
			/// Construct a vector from a float array.			
			Vector(const float values[])
			{
				for (int i = 0; i < n; i++)
					data[i] = values[i];
			}

			/// Constructs a vector from a single float value.
			Vector(float value)
			{
				fill(value);
			}

			/// Fills the vector with a float value.
			void fill(float value)
			{
				for (int i = 0; i < n; i++)
					data[i] = value;
			}

			/// Subscript operator to access data.
			float operator[](const int i)
			{
				return data[i];
			}

		};
		

		/// Class specialization for 2D vectors
		template <> class Vector < 2 >
		{
		public:

			/// Anonynous union: data can be accessed either trough the 'data' array, or trough .x and .y
			union
			{
				/// Float data array
				float data[2];

				/// Float data for x, y coordinates
				struct {
					float x, y;
				};
			};

			/// Default constructor, empty
			Vector() { }

			/// Construct from two floats
			Vector(float a, float b)
			{
				x = a;
				y = b;
			}

			/// Construct from single float
			Vector(float a)
			{
				x = a;
				y = a;
			}

			/// Construct from float array
			Vector(const float v[2])
			{
				x = v[0];
				y = v[1];
			}

			/// Subscript operator
			float operator[](const int i)
			{
				return data[i];
			}

		};

		/// Class specialization for 3D vectors
		template <> class Vector < 3 >
		{
		public:

			/// Anonynous union: data can be accessed either trough the 'data' array,  or trough .x .y .z
			union
			{
				float data[3];
				struct {
					float x, y, z;
				};
			};

			/// Default constructor, empy
			Vector() { }

			Vector(float a, float b, float c)
			{
				x = a;
				y = b;
				z = c;
			}

			/// Constructs from single float value
			Vector(float a)
			{
				x = a;
				y = a;
				z = a;
			}

			/// Constructs from float array
			Vector(const float v[3])
			{
				x = v[0];
				y = v[1];
				z = v[2];
			}

			/// Subscript operator
			float operator[](const int i)
			{
				return data[i];
			}
		};

		/// Class specialization for 4D vectors
		template <> class Vector < 4 >
		{
		public:

			/// Anonynous union: data can be accessed either trough the 'data' array,  or trough .x .y .z . w
			union
			{
				float data[4];
				struct {
					float x, y, z, w;
				};
			};

			/// Default constructor, empty.
			Vector() { }

			/// Construct from 4 float values.
			Vector(float a, float b, float c, float d)
			{
				x = a;
				y = b;
				z = c;
				w = d;
			}

			/// Construct from single float.
			Vector(float a)
			{
				x = a;
				y = a;
				z = a;
				w = a;
			}

			/// Construct from float array
			Vector(const float v[4])
			{
				x = v[0];
				y = v[1];
				z = v[2];
				w = v[3];
			}

			/// Subscript operator
			float operator[](const int i)
			{
				return data[i];
			}

			/// Returns 3d vector xyz
			Vector<3> xyz()
			{
				return Vector<3>(x, y, z);
			}

			/// Returns 2d vector xy
			Vector<2> xy()
			{
				return Vector<2>(x, y);
			}

		};

		/// Returns the norm of the vector.		 
		template <int n>
		float norm(const Vector<n> &vec)
		{
			float temp = 0.0f;

			for (int i = 0; i < n; i++)
				temp += vec.data[i] * vec.data[i];

			return sqrt(temp);
		}

		/// Vector addition operator
		template <int n>
		Vector<n> operator+(const Vector<n> &left, const Vector<n> &right)
		{
			float temp[n];

			for (int i = 0; i < n; i++)
				temp[i] = left.data[i] + right.data[i];

			return Vector<n>(temp);
		}

		/// Scalar multiplication (left)
		template <int n>
		Vector<n> operator*(float value, const Vector<n> &right)
		{
			float temp[n];

			for (int i = 0; i < n; i++)
				temp[i] = value * right.data[i];

			return Vector<n>(temp);
		}

		/// Scalar multiplication (right)
		template <int n>
		Vector<n> operator*(const Vector<n> &right, float value)
		{
			float temp[n];

			for (int i = 0; i < n; i++)
				temp[i] = value * right.data[i];

			return Vector<n>(temp);
		}

		/// Vector subtraction operator
		template <int n>
		Vector<n> operator-(const Vector<n> &left, const Vector<n> &right)
		{
			Vector<n> temp;

			for (int i = 0; i < n; i++)
				temp.data[i] = left.data[i] - right.data[i];

			return temp;
		}

		/// Vector dot product operator
		template <int n>
		float operator*(const Vector<n> &left, const Vector<n> &right)
		{
			float dot = 0;

			for (int i = 0; i < n; i++)
				dot += left.data[i] * right.data[i];

			return dot;
		}

		/// Cross product operator
		Vector<3> operator^(const Vector<3> &left, const Vector<3> &right);

		/// Print vector on the terminal
		template<int n>
		void print_vector(const Vector<n> &vec)
		{
			printf("\n(");

			for (int i = 0; i < (n - 1); i++)
				printf(" %f,", vec.data[i]);
			printf(" %f)\n", vec.data[n - 1]);

		}

		/// Normalizes the input vector
		template<int n>
		Vector<n> normalize(const Vector<n> &vec)
		{
			Vector <n> temp;

			temp = (1.0f / norm(vec))*vec;

			return temp;
		}

		/// 2D Vector
		typedef Vector<2> Vec2;

		/// 3D Vector
		typedef Vector<3> Vec3;

		/// 4D Vector
		typedef Vector<4> Vec4;


	}
}



#endif