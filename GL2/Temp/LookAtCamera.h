#pragma once

#include "../framework/Foxtrot.h"

#include "Frustum.h"

using namespace::framework;

/**
 * A class that abstracts a camera, implemented with 'lookat' transformations.
 * The camera is fixed looking at 'point', being able to rotate and go
 * back/foward about that point.
 */
class LookAtCamera
{
public:
	
	float distance;

	mat::Mat4 camera_matrix;	

	mat::Mat4 view_matrix;

	Frustum *frustum;

	LookAtCamera();

	~LookAtCamera();

	LookAtCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up);

	LookAtCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up, Frustum &f);

	void set_frustum(Frustum &f);

	void set_camera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up);

	void rotate_up(float theta);

	void rotate_side(float theta);

	void walk(float step);

	void update(const mat::Mat4 &transform);

	void update();	

};

