#include "LookAtCamera.h"

#include "../framework/Foxtrot.h"

using namespace framework;

void LookAtCamera::set_camera(vec::Vec3 camera_pos, vec::Vec3 point, vec::Vec3 up)
{
	view_matrix = transform::look_at_matrix(camera_pos, point, up);
	distance = vec::norm(camera_pos - point);
}

LookAtCamera::LookAtCamera()
{
}


LookAtCamera::~LookAtCamera()
{
}

LookAtCamera::LookAtCamera(vec::Vec3 camera_pos, vec::Vec3 point, vec::Vec3 up)
{
	set_camera(camera_pos, point, up);
}

void LookAtCamera::rotate_up(float theta)
{
	
	mat::Mat3 rot_matrix = transform::rotation_matrix_x_axis(theta);

	vec::Vec3 point(0.0f, 0.0f, -distance);
	vec::Vec3 new_camera_pos = rot_matrix * Vec3(0.0f, 0.0f, distance) + point;
	vec::Vec3 new_up = rot_matrix * Vec3(0.0f, 1.0f, 0.0f);

	view_matrix = transform::look_at_matrix(new_camera_pos, point, new_up) * view_matrix;

}

void LookAtCamera::rotate_side(float theta)
{

	mat::Mat3 rot_matrix = transform::rotation_matrix_y_axis(theta);

	vec::Vec3 point(0.0f, 0.0f, -distance);
	vec::Vec3 new_camera_pos = rot_matrix * Vec3(0.0f, 0.0f, distance) + point;
	vec::Vec3 new_up =  Vec3(0.0f, 1.0f, 0.0f);

	view_matrix = transform::look_at_matrix(new_camera_pos, point, new_up) * view_matrix;

}

void LookAtCamera::walk(float step)
{
	vec::Vec3 point(0.0f, 0.0f, step - distance);
	vec::Vec3 new_camera_pos(0.0f, 0.0f, -step);
	vec::Vec3 new_up(0.0f, 1.0f, 0.0f);

	distance = distance - step;

	view_matrix = transform::look_at_matrix(new_camera_pos, point, new_up) * view_matrix;
}