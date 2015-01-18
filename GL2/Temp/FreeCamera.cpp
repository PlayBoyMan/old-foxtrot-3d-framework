#include "FreeCamera.h"

#include "../framework/Foxtrot.h"

using namespace framework;

FreeCamera::FreeCamera(vec::Vec3 camera_position, vec::Vec3 camera_direction, vec::Vec3 camera_up, Frustum &f)
{
	// Set the frustum
	frustum = &f;

	// Set initial orientation
	position = camera_position;
	original_direction = camera_direction;
	original_up = camera_up;

	// Set current orientation
	direction = original_direction;
	up = original_up;

	// Orientation parameters to 0 
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;

	// Create camera matrix
	camera_matrix = transform::look_at_matrix(position, original_direction + position, original_up);

	// Update view matrix
	update();
}

FreeCamera::FreeCamera()
{

}

FreeCamera::~FreeCamera()
{

}


void FreeCamera::tilt(float delta)
{
	pitch = pitch + delta;
	yaw_pitch_roll();
}

void FreeCamera::pan(float delta)
{
	yaw = yaw - delta;	
	yaw_pitch_roll();
}

void FreeCamera::do_roll(float delta)
{
	roll = roll + delta;
	yaw_pitch_roll();
}

void FreeCamera::walk_forward(float step)
{
	position = position + step*direction;	
	yaw_pitch_roll();
}

void FreeCamera::walk_side(float step)
{
	// Get side vector from camera matrix (lookat)
	vec::Vec3 side(camera_matrix(0,0), camera_matrix(0, 1), camera_matrix(0, 2));

	// Update position
	position = position + step*side;
	yaw_pitch_roll();
}

void FreeCamera::yaw_pitch_roll()
{	
	// Rotation matrix, consisting of rotations of the three axis (from the original orientation)
	mat::Mat3 rotation_matrix = transform::rotation_matrix_z_axis(roll) * transform::rotation_matrix_y_axis(yaw) * transform::rotation_matrix_x_axis(pitch);
	
	// Calculate rotated directions and up
	direction = rotation_matrix * original_direction;		
	up = rotation_matrix * original_up;	

	// Calculate new camera matrix
	camera_matrix = transform::look_at_matrix(position, direction + position, up);


	// Update view
	update();

}

void FreeCamera::update()
{
	view_matrix = frustum->frustum_matrix * camera_matrix;
}



