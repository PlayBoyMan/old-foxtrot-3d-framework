#include "Matrix.h"

using namespace framework::mat;

// 2x2 Matrix multiplication
Matrix<2, 2> framework::mat::operator*(const Matrix<2, 2> &left, const Matrix<2, 2> &right)
{
	Matrix <2, 2> temp;

	temp.data[0][0] = left.data[0][0] * right.data[0][0] + left.data[0][1] * right.data[1][0];
	temp.data[0][1] = left.data[0][0] * right.data[0][1] + left.data[0][1] * right.data[1][1];
	temp.data[1][0] = left.data[1][0] * right.data[0][0] + left.data[1][1] * right.data[1][0];
	temp.data[1][1] = left.data[1][0] * right.data[0][1] + left.data[1][1] * right.data[1][1];

	return temp;

}

// 3x3 Matrix multiplication.
Matrix<3, 3> framework::mat::operator*(const Matrix<3, 3> &left, const Matrix<3, 3> &right)
{
	Matrix<3, 3> temp;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			temp[i][j] = left.data[i][0] * right.data[0][j] + left.data[i][1] * right.data[1][j] + left.data[i][2] * right.data[2][j];

	return temp;

}

// 4x4 Matrix multiplication
Matrix<4, 4> framework::mat::operator*(const Matrix<4, 4> &left, const Matrix<4, 4> &right)
{
	Matrix<4, 4> temp;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp[i][j] = left.data[i][0] * right.data[0][j] +
			left.data[i][1] * right.data[1][j] +
			left.data[i][2] * right.data[2][j] +
			left.data[i][3] * right.data[3][j];

	return temp;

}

Matrix <3, 3> framework::mat::matrix_from_column_vectors(Vec3 col1, Vec3 col2, Vec3 col3)
{
	Mat3 temp;

	for (int i = 0; i < 3; i++)
	{
		temp[i][0] = col1[i];
		temp[i][1] = col2[i];
		temp[i][2] = col3[i];
	}

	return temp;
}