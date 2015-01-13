#include "FreeCamera.h"

#include "../framework/Foxtrot.h"

using namespace framework;

FreeCamera::FreeCamera()
{
}


FreeCamera::~FreeCamera()
{
}


FreeCamera::FreeCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &direction, const vec::Vec3 &up, Frustum &f) 	
{
	set_frustum(f);
	set(camera_pos, direction, up);
}

void FreeCamera::set(const vec::Vec3 &camera_pos, const vec::Vec3 &direction, const vec::Vec3 &up)
{
	camera_matrix = transform::look_at_matrix(camera_pos, direction, up);
	update();
}

FreeCamera::FreeCamera(Frustum &f)
	: FreeCamera(vec::Vec3(0.0f), vec::Vec3(0.0f, 0.0f, -1.0f), vec::Vec3(0.0f, 1.0f, 0.0f), f)
{

}

void FreeCamera::update()
{
	view_matrix = frustum->frustum_matrix * camera_matrix;
}

void FreeCamera::set_frustum(Frustum &f)
{
	frustum = &f;
}

void FreeCamera::walk(vec::Vec3 direction, float distance)
{
	mat::Mat4 translation = transform::translation_matrix_4d(-1.0f*distance*direction);

	camera_matrix = translation * camera_matrix;

	update();
}

void FreeCamera::walk_side(float distance)
{
	walk(vec::Vec3(1.0f, 0.0f, 0.0f), distance);
}

void FreeCamera::walk_foward(float distance)
{
	walk(vec::Vec3(0.0f, 0.0f, -1.0f), distance);
}

void FreeCamera::tilt(float angle)
{

	mat::Mat3 rot = transform::rotation_matrix_x_axis(angle);
	vec::Vec3 point = rot*vec::Vec3(0.0f, 0.0f, -1.0f);
	vec::Vec3 new_up = rot*vec::Vec3(0.0f, 1.0f, 0.0f);
	mat::Mat4 transform = transform::look_at_matrix(vec::Vec3(0.0f, 0.0f, 0.0f), point, new_up);

	camera_matrix = transform * camera_matrix;
	
	update();
}


void FreeCamera::pan(float angle)
{
	vec::Vec3 point = transform::rotation_matrix_y_axis(-1.0f*angle)*vec::Vec3(0.0f, 0.0f, -1.0f);
	
	mat::Mat4 transform = transform::look_at_matrix(vec::Vec3(0.0f, 0.0f, 0.0f), point, vec::Vec3(0.0f, 1.0f, 0.0f));

	camera_matrix = transform * camera_matrix;

	update();
}

