#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <random>
#include <algorithm>
#include "vector.h"

using namespace framework::vec;

namespace framework {
	namespace mat {

		/// Matrix class template, representing a matrix of dimensions n x m.
		template <int n, int m>
		class Matrix {
		public:

			/// Matrix data, a 2D array of floats, of dim. n x m (n rows, m collumns,) so that A_ij -> A.data[i][j].
			float data[n][m];

			/// Default constructor (empty).
			Matrix() { }

			/// Construct matrix from 2D array.
			Matrix(const float values[n][m])
			{				
				memcpy((void *)&data[0][0], (void *)&values[0][0], sizeof(data));				
			}

			/// Construct matrix from 1D array.
			Matrix(const float values[])
			{			
				memcpy((void *)&data[0][0], (void *)&values[0], sizeof(data));
			}

			/// Construct matrix from single value, repeating it.
			Matrix(const float val)
			{
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++)
						data[i][j] = val;				
			}

			// Fills the matrix with a given value.
			void fill(const float val)
			{
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++)
						data[i][j] = val;
			}

			/// Subsrcript operator.
			float* operator[](const int i)
			{
				return data[i];
			}

		};


		/// Class specialization for 2x2 Matrix;
		template <> class Matrix < 2, 2 >
		{
		public:

			/// Anonymous union, so that we can access data either trough the 2d array or trough .a .b .c and .d
			union {
				float data[2][2];
				struct {
					float a, b, c, d;
				};
			};

			/// Default cosntructor
			Matrix() { }

			/// Construct from a single value
			Matrix(float value)
			{
				a = b = c = d = value;
			}

			/// Construct from 1D array
			Matrix(float values[4])
			{
				memcpy((void *)&data[0][0], (void *)&values[0], sizeof(data));
			}

			/// Subscript operator
			float *operator[](const int i)
			{
				return data[i];
			}

		};


		/// Class specialization for 3x3 Matrix
		template <> class Matrix < 3, 3 >
		{
		public:

			/// Matrix data as 2D array
			float data[3][3];

			/// Default constructor
			Matrix() {}

			/// Fills the matrix with a given value
			void fill(float value)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						data[i][j] = value;
			}

			/// Construct from a single value
			Matrix(float value)
			{
				fill(value);
			}

			/// Construct diagonal matrix from 3 values
			Matrix(float d1, float d2, float d3)
			{
				fill(0.0f);

				data[0][0] = d1;
				data[1][1] = d2;
				data[2][2] = d3;
			}

			/// Construct diagonal matrix from a 3d vector
			Matrix(Vec3 diag)
			{
				fill(0.0f);

				data[0][0] = diag.x;
				data[1][1] = diag.y;
				data[2][2] = diag.z;
			}

			/// Construct a matrix from 3 row-vectors
			Matrix(Vec3 row1, Vec3 row2, Vec3 row3)
			{
				size_t size = sizeof(row1.data);

				memcpy((void*)&data[0][0], (void *)row1.data, size);
				memcpy((void*)&data[1][0], (void *)row2.data, size);
				memcpy((void*)&data[2][0], (void *)row3.data, size);
			}

			/// Subscript operator
			float *operator[](const int i)
			{
				return data[i];
			}
		};


		/// Class specialization for 4x4 matrix
		template <> class Matrix < 4, 4 >
		{
		public:

			/// Matrix data
			float data[4][4];

			/// Default constructor
			Matrix() {}

			void fill(const float value)
			{
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						data[i][j] = value;
			}

			/// Construct from a single value
			Matrix(float value)
			{
				fill(value);
			}

			/// Construct diag. matrix from 4D vector
			Matrix(Vec4 diag)
			{
				fill(0.0f);

				data[0][0] = diag.x;
				data[1][1] = diag.y;
				data[2][2] = diag.z;
				data[3][3] = diag.w;
			}

			/**
			 *Construct matrix in the form (  M  T )
			 *                              (  0  1 )
			 * from a matrix M and vector T
			 */
			Matrix(Matrix<3, 3> transform, Vec3 translation)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						data[i][j] = transform.data[i][j];
				for (int i = 0; i < 3; i++)
					data[i][3] = translation.data[i];
				data[3][3] = 1.0f;
				data[3][0] = 0.0f;
				data[3][1] = 0.0f;
				data[3][2] = 0.0f;
			}

			///  Construct matrix from 4 4D row vectors
			Matrix(Vec4 row1, Vec4 row2, Vec4 row3, Vec4 row4)
			{
				size_t size = sizeof(row1.data);

				memcpy((void*)&data[0][0], (void *)row1.data, size);
				memcpy((void*)&data[1][0], (void *)row2.data, size);
				memcpy((void*)&data[2][0], (void *)row3.data, size);
				memcpy((void*)&data[3][0], (void *)row4.data, size);
			}

			/// Subscript operator
			float* operator[](const int i) { return data[i]; }

			float& operator()(int i, int j)
			{
				return data[i][j];
			}

			float operator()(int i, int j) const
			{
				return data[i][j];
			}


		};

		/// 2x2 Matrix
		typedef Matrix<2, 2> Mat2;

		/// 3x3 Matrix
		typedef Matrix<3, 3> Mat3;

		/// 4x4 Matrix
		typedef Matrix<4, 4> Mat4;


		/// Print matrix on the terminal.
		template <int n, int m>
		void print_matrix(const Matrix<n, m> &M)
		{
			printf("\n");
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
					printf("%2f \t", M.data[i][j]);
				printf("\n");
			}
		}

		/// Matrix addition operator.
		template <int n, int m>
		Matrix<n, m> operator+(const Matrix<n, m> &left, const Matrix<n, m> &right)
		{
			Matrix<m, m> temp;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp.data[i][j] = left.data[i][j] + right.data[i][j];
			return temp;
		}

		/// Matrix scalar multiplication (left).
		template <int n, int m>
		Matrix<n, m> operator*(const float value, const Matrix<n, m> &right)
		{
			Matrix<m, m> temp;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp.data[i][j] = value * right.data[i][j];
			return temp;
		}


		/// Matrix scalar multiplication (right).
		template <int n, int m>
		Matrix<n, m> operator*(const Matrix<n, m> &right, const float value)
		{
			Matrix<m, m> temp;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp[i][j] = value * right[i][j];
			return temp;
		}

		/// Matrix scalar multiplication (left).
		template <int n, int m>
		vec::Vector<m> operator*(const Matrix<n,m> &mat, const Vector<m> &vec)
		{
			vec::Vector<n> temp(0.0f);

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp.data[i] += mat.data[i][j] * vec.data[j];

			return temp;
		}

		/// 2x2 Matrix multiplication
		Matrix<2, 2> operator*(const Matrix<2, 2> &left, const Matrix<2, 2> &right);

		/// 3x3 Matrix multiplication.
		Matrix<3, 3> operator*(const Matrix<3, 3> &left, const Matrix<3, 3> &right);

		/// 4x4 Matrix multiplication
		Matrix<4, 4> operator*(const Matrix<4, 4> &left, const Matrix<4, 4> &right);

		/// General matrix multiplication (n,m) x (m,p)
		template <int n, int m, int p>
		Matrix <n, p> operator*(const Matrix<n, m> &left, const Matrix<m, p> &right)
		{
			Matrix<n, p> temp(0.0f);
			
			for (int i = 0; i < n; i++)
				for (int j = 0; j < p; j++)
					for (int k = 0; k < m; k++)
						temp.data[i][j] += left.data[i][k] * right.data[k][j];						

			return temp;
		}

		/// Fill the matrix with random values
		template <int n, int m>
		Matrix<n, m>& randomize_matrix(Matrix <n, m> &mat, float min, float max)
		{
			std::random_device rd;

			std::mt19937 e2(rd());
			std::uniform_real_distribution<float> dist(min, max);

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					mat.data[i][j] = dist(e2);

			return mat;
		}

		/// Fill matrix with a single value
		template <int n, int m>
		void fill_matrix(Matrix <n, m> &mat, float value)
		{
			std::fill(mat.data, mat.data + n*m, value);
		}

		/// Returns a new matrix that is the transpose of the input matrix.
		template <int n, int m>
		Matrix<n, m> transpose(const Matrix <n, m> &mat)
		{
			Matrix <n, m> temp;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp.data[i][j] = mat.data[j][i];

			return temp;
		}

		/// Transposes the input matrix
		template <int n, int m>
		void  transpose_matrix(Matrix <n, m> &mat)
		{
			Matrix <n, m> temp;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp.data[i][j] = mat.data[j][i];

			mat = Matrix<n, m>(temp.data);
		}

		/// Returns a matrix constructed from column vectors.
		Matrix <3, 3> matrix_from_column_vectors(Vec3 col1, Vec3 col2, Vec3 col3);
		
	}
}

#endif