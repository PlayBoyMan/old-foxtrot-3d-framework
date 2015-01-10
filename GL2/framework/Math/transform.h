#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Matrix.h"
#include "Quaternion.h"

namespace framework {
	namespace transform {

		/// Returns a 3x3 matrix, representing a rotation of angle theta around the z axis
		mat::Mat3 rotation_matrix_z_axis(float theta);

		/// Returns a 3x3 matrix, representing a rotation of angle theta around the y axis
		mat::Mat3 rotation_matrix_y_axis(float theta);

		/// Returns a 3x3 matrix, representing a rotation of angle theta around the x axis
		mat::Mat3 rotation_matrix_x_axis(float theta);

		/// Returns a 4x4 projection matrix from frustum/camera-space to clip space.
		/** 
		  * Constructs the perspective frustum->clip space projection matrix, where
		  * @param n is the near plane distance (>0)
		  * @param f is the far plane distance (>0)
		  * @param r is the right viewport edge
		  * @param l is the left viewport edge
		  * @param t is the top viewport edge
		  * @param b is the bottom viewport edge
		  */
		mat::Mat4 frustum_matrix(float n, float f, float r, float l, float t, float b);

		/// Returns a 4x4 orthogonal projection matrix.
		/**
		* Constructs the orthogonal projection matrix, where
		* @param n is the near plane distance (>0)
		* @param f is the far plane distance (>0)
		* @param r is the right viewport edge
		* @param l is the left viewport edge
		* @param t is the top viewport edge
		* @param b is the bottom viewport edge
		*/
		mat::Mat4 orthogonal_projection_matrix(float n, float f, float r, float l, float t, float b);

		/// Returns the 'lookat' transform matrix.
		/**
		 * Constructs the 'look at' transform matrix, that aligns the world to camera eye coordinates, 
		 * pointing to a given point of interest.
		 * @param camera_pos camera position
		 * @param point interest point
		 * @param up up (new y axis) direction
		 */
		mat::Mat4 look_at_matrix(vec::Vec3 camera_pos, vec::Vec3 point, vec::Vec3 up);
				
		/// Quaternion representing a rotation of angla theta around axis.
		quat::Quaternion quaternion_rotation(vec::Vec3 axis, float theta);

		/// Returns the 3x3 rotation matrix from a given rotation quaternion.
		mat::Mat3 quaternion_rotation_matrix(quat::Quaternion q);

		/// 3x3 rotation matrix from quaternion with parameters.
		mat::Mat3 quaternion_rotation_matrix(vec::Vec3 axis, float theta);

		/// Returns a 4d rotation matrix from 3d rotation matrix
		mat::Mat4 rotation_matrix_4d(const mat::Mat3 &mat);

		/// Returns a 4d translation matrix from translation vector
		mat::Mat4 translation_matrix_4d(const vec::Vec3 &vec);

		/// Returns a 4d matrix representing a rotation after a translation
		mat::Mat4 rotation_translation_matrix(const mat::Mat3 &mat, const vec::Vec3 &vec);

		/// Returns a general 4d transformation matrix
		mat::Mat4 transform_matrix(const mat::Mat3 &mat, const vec::Vec3 &vec);

	}
}

#endif