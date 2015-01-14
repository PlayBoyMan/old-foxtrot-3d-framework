#include "FreeCamera.h"

#include "../framework/Foxtrot.h"

using namespace framework;

FreeCamera::FreeCamera(vec::Vec3 camera_position, vec::Vec3 camera_direction, vec::Vec3 camera_up, Frustum &f)
{
	frustum = &f;

	position = camera_position;
	direction = camera_direction;
	up = camera_up;

	current_direction = direction;
	current_up = up;

	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;

	camera_matrix = transform::look_at_matrix(position, direction + position, up);

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

void FreeCamera::walk_foward(float step)
{
	vec::Vec3 new_position = position + step*current_direction;

	position = new_position;
	
	yaw_pitch_roll();
}

void FreeCamera::walk_side(float step)
{
	vec::Vec3 side(camera_matrix(0,0), camera_matrix(0, 1), camera_matrix(0, 2));

	position = position + step*side;

	yaw_pitch_roll();
}

void FreeCamera::yaw_pitch_roll()
{	

	mat::Mat3 rotation_matrix = transform::rotation_matrix_z_axis(roll) * transform::rotation_matrix_y_axis(yaw) * transform::rotation_matrix_x_axis(pitch);
	
	current_direction = rotation_matrix * direction;		
	current_up = rotation_matrix * up;	

	camera_matrix = transform::look_at_matrix(position, current_direction + position, current_up);

	update();

}

void FreeCamera::update()
{
	view_matrix = frustum->frustum_matrix * camera_matrix;
}

