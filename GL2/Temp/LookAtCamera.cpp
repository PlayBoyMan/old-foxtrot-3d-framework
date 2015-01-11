#include "LookAtCamera.h"

#include "../framework/Foxtrot.h"

using namespace framework;

void LookAtCamera::set_camera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up)
{
	camera_matrix = transform::look_at_matrix(camera_pos, point, up);
	distance = vec::norm(camera_pos - point);
}

LookAtCamera::LookAtCamera() 
{

}


LookAtCamera::~LookAtCamera()
{
}

LookAtCamera::LookAtCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up)
{
	set_camera(camera_pos, point, up);
}

LookAtCamera::LookAtCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up, Frustum &f)
	: LookAtCamera(camera_pos, point, up)
{
	set_frustum(f);
}


void LookAtCamera::rotate_up(float theta)
{
	
	mat::Mat3 rot_matrix = transform::rotation_matrix_x_axis(theta);

	vec::Vec3 point(0.0f, 0.0f, -distance);
	vec::Vec3 new_camera_pos = rot_matrix * Vec3(0.0f, 0.0f, distance) + point;
	vec::Vec3 new_up = rot_matrix * Vec3(0.0f, 1.0f, 0.0f);

	//camera_matrix = transform::look_at_matrix(new_camera_pos, point, new_up) * camera_matrix;
	update(transform::look_at_matrix(new_camera_pos, point, new_up));

}

void LookAtCamera::rotate_side(float theta)
{

	mat::Mat3 rot_matrix = transform::rotation_matrix_y_axis(theta);

	vec::Vec3 point(0.0f, 0.0f, -distance);
	vec::Vec3 new_camera_pos = rot_matrix * Vec3(0.0f, 0.0f, distance) + point;
	vec::Vec3 new_up =  Vec3(0.0f, 1.0f, 0.0f);

	//camera_matrix = transform::look_at_matrix(new_camera_pos, point, new_up) * camera_matrix;
	update(transform::look_at_matrix(new_camera_pos, point, new_up));

}

void LookAtCamera::walk(float step)
{
	vec::Vec3 point(0.0f, 0.0f, step - distance);
	vec::Vec3 new_camera_pos(0.0f, 0.0f, -step);
	vec::Vec3 new_up(0.0f, 1.0f, 0.0f);

	distance = distance - step;

	//camera_matrix = transform::look_at_matrix(new_camera_pos, point, new_up) * camera_matrix;
	update(transform::look_at_matrix(new_camera_pos, point, new_up));
}

void LookAtCamera::update(const mat::Mat4 &transform)
{
	camera_matrix = transform * camera_matrix;

	view_matrix = frustum->frustum_matrix * camera_matrix;
}

void LookAtCamera::update()
{
	view_matrix = frustum->frustum_matrix * camera_matrix;
}

void LookAtCamera::set_frustum(Frustum &f)
{
	frustum = &f;
	update();
}