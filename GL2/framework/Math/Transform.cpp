#include "Transform.h"

using namespace framework::transform;
using namespace framework;

namespace T = framework::transform;

// Returns a 3x3 matrix, representing a 
// rotation of angle theta around the z axis
mat::Mat3 T::rotation_matrix_z_axis(float theta)
{
	mat::Mat3 temp;

	float c = cos(theta);
	float s = sin(theta);

	temp[0][0] = c;	temp[0][1] = -s; temp[0][2] = 0;
	temp[1][0] = s; temp[1][1] = c;	 temp[1][2] = 0;
	temp[2][0] = 0; temp[2][1] = 0;  temp[2][2] = 1;

	return temp;

}

// Returns a 3x3 matrix, representing a 
// rotation of angle theta around the y axis
mat::Mat3 T::rotation_matrix_y_axis(float theta)
{
	mat::Mat3 temp;

	float c = cos(theta);
	float s = sin(theta);

	temp[0][0] = c;	temp[0][1] = 0; temp[0][2] = s;
	temp[1][0] = 0; temp[1][1] = 1;	 temp[1][2] = 0;
	temp[2][0] = -s; temp[2][1] = 0;  temp[2][2] = c;

	return temp;

}

// Returns a 3x3 matrix, representing a 
// rotation of angle theta around the x axis
mat::Mat3 T::rotation_matrix_x_axis(float theta)
{
	mat::Mat3 temp;

	float c = cos(theta);
	float s = sin(theta);

	temp[0][0] = 1;	temp[0][1] = 0; temp[0][2] = 0;
	temp[1][0] = 0; temp[1][1] = c;	 temp[1][2] = -s;
	temp[2][0] = 0; temp[2][1] = s;  temp[2][2] = c;

	return temp;
}

// Returns a 4x4 projection matrix from frustum/camera-space to 
// clip space.
mat::Mat4 T::frustum_matrix(float n, float f, float r, float l, float t, float b)
{
	mat::Mat4 temp;

	temp[0][0] = (2.0f * n) / (r - l);	temp[0][1] = 0;	temp[0][2] = (r + l) / (r - l);	temp[0][3] = 0;
	temp[1][0] = 0;	temp[1][1] = (2.0f * n) / (t - b);	temp[1][2] = (t + b) / (t - b); temp[1][3] = 0;
	temp[2][0] = 0; temp[2][1] = 0; temp[2][2] = -((f + n) / (f - n)); temp[2][3] = -((2.0f * n*f) / (f - n));
	temp[3][0] = 0; temp[3][1] = 0; temp[3][2] = -1.0f; temp[3][3] = 0;

	return temp;
}

// Returns a 4x4 othogonal projection matrix.
mat::Mat4 T::orthogonal_projection_matrix(float n, float f, float r, float l, float t, float b)
{
	mat::Mat4 temp(0.0f);

	temp[0][0] = 2.0f / (r - l);	temp[0][3] = -((r + l) / (r - l));
	temp[1][1] = 2.0f / (t - b);	temp[1][3] = -((t + b) / (t - b));
	temp[2][2] = -2.0f / (f - n);	temp[2][3] = -((f + n) / (f - n));
	temp[3][3] = 1.0f;

	return temp;
}

// Returns the 'lookat' transform matrix, that aligns the world 
// coordinates to camera-view, given a foward, up and point vectors.
mat::Mat4 T::look_at_matrix(vec::Vec3 camera_pos, vec::Vec3 point, vec::Vec3 up)
{
	vec::Vec3 foward_vector;
	vec::Vec3 side_vector;
	vec::Vec3 up_vector;

	// Unit foward vector, pointing from 'point' towards the camera
	foward_vector = camera_pos - point;
	foward_vector = vec::normalize(foward_vector);

	// Side vector (x = y x z)
	side_vector = up^foward_vector;
	side_vector = vec::normalize(side_vector);

	// New, orthonormal up vector ( y = z x x)
	up_vector = foward_vector^side_vector;	

	// lookat matrix: first, translate camera to origin; then, rotate the camera.
	// To rotate, we perform a change of coordinates to the new basis (s, u, f).
	// Since we know (s, u, f) in terms of (x, y, z) the apropriate matrix is 
	// the matrix where s, u, and f are the rows, not the columns, .i.e., 
	// ( s.x, s.y, s.z )
	// ( u.x, u.y, u.z )
	// ( f.x, f.y, f.z )
	// since x' = [old basis are columns] * x

	return rotation_translation_matrix(mat::Mat3(side_vector, up_vector, foward_vector), -1.0*camera_pos);

}

// Quaternion representing a rotation of angla theta around axis.
quat::Quaternion T::quaternion_rotation(vec::Vec3 axis, float theta)
{
	return quat::Quaternion(cos(theta / 2.0f), sin(theta / 2.0f)*axis);
}

// Returns the 3x3 rotation matrix from a given
// rotation quaternion.
mat::Mat3 T::quaternion_rotation_matrix(quat::Quaternion q)
{
	mat::Mat3 temp;

	temp[0][0] = 1 - 2 * q.y*q.y - 2 * q.z*q.z;
	temp[0][1] = 2 * q.x*q.y - 2 * q.w*q.z;
	temp[0][2] = 2 * q.x*q.z + 2 * q.w*q.y;
	temp[1][0] = 2 * q.x*q.y + 2 * q.w*q.z;
	temp[1][1] = 1 - 2 * q.x*q.x - 2 * q.z*q.z;
	temp[1][2] = 2 * q.y*q.z - 2 * q.w*q.x;
	temp[2][0] = 2 * q.x*q.z - 2 * q.w*q.y;
	temp[2][1] = 2 * q.y*q.z + 2 * q.w*q.x;
	temp[2][2] = 1 - 2 * q.x*q.x - 2 * q.y*q.y;

	return temp;
}

// 3x3 rotation matrix from quaternion with parameters.
mat::Mat3 T::quaternion_rotation_matrix(vec::Vec3 axis, float theta)
{
	return quaternion_rotation_matrix(quat::Quaternion(cos(theta / 2.0f), sin(theta / 2.0f)*axis));
}

mat::Mat4 T::rotation_matrix_4d(const mat::Mat3 &mat)
{
	return mat::Mat4(mat, vec::Vec3(0.0f));
}

mat::Mat4 T::translation_matrix_4d(const vec::Vec3 &vec)
{
	return mat::Mat4(mat::Mat3(1.0f, 1.0f, 1.0f), vec);
}

mat::Mat4 T::rotation_translation_matrix(const mat::Mat3 &mat, const vec::Vec3 &vec)
{
	return rotation_matrix_4d(mat) * translation_matrix_4d(vec);
}

mat::Mat4 T::transform_matrix(const mat::Mat3 &mat, const vec::Vec3 &vec)
{
	return mat::Mat4(mat, vec);
}