#include "LookAtCamera.h"

#include "../framework/Foxtrot.h"

using namespace framework;


LookAtCamera::LookAtCamera()
{

}

LookAtCamera::~LookAtCamera()
{

}


LookAtCamera::LookAtCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up, Frustum &f)
{
	
	// Calculate camera matrix
	camera_matrix = transform::look_at_matrix(camera_pos, point, up);

	// Store first camera matrix for later use
	initial_camera_matrix = camera_matrix;

	// Calculate the distance from the camera to the point
	distance = vec::norm(camera_pos - point);

	// Store the initial distance
	initial_distance = distance;

	// Rotation parameters
	alpha = 0.0f;
	beta = 0.0f;
	gamma = 0.0f;

	// Store the pointer to the frustum object
	frustum = &f;

	// Update the view matrix
	update();
}

void LookAtCamera::rotate_side(float delta)
{
	beta = beta + delta;
	update_orientation();
}

void LookAtCamera::rotate_up(float delta)
{
	alpha = alpha + delta;
	update_orientation();
}

void LookAtCamera::walk(float step)
{
	distance = distance + step;
	update_orientation();
}


void LookAtCamera::update()
{
	view_matrix = frustum->frustum_matrix * camera_matrix;
}

void LookAtCamera::update_orientation()
{
	// Calculate rotation matrix from parameters (relative to the original orientation, 
	// stored in camera_base_matrix
	mat::Mat3 rotation_matrix = transform::rotation_matrix_x_axis(alpha) * transform::rotation_matrix_y_axis(beta) * transform::rotation_matrix_z_axis(gamma);
	
	const vec::Vec3 rotated_z_axis = rotation_matrix * vec::Vec3(0.0f, 0.0f, 1.0f);

	// Camera position due to rotation = Rot * (0,0,initial dist.) - (0,0,initial dist)
	vec::Vec3 camera_rotation =  initial_distance * rotated_z_axis  + vec::Vec3(0.0f, 0.0f, -initial_distance);

	// Camera position due to translation
	vec::Vec3 camera_translation = (distance - initial_distance) * rotated_z_axis;

	// New up position
	vec::Vec3 new_up = rotation_matrix * vec::Vec3(0.0f, 1.0f, 0.0f);

	// Calculate the new camera matrix from the original camera_base_matrix
	camera_matrix = transform::look_at_matrix(camera_rotation + camera_translation,  vec::Vec3(0.0f, 0.0f, -initial_distance), new_up) * initial_camera_matrix;

	// Update the view matrix
	update();
}
