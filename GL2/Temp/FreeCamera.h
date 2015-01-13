#pragma once
#ifndef __FREECAMERA_H__
#define __FREECAMERA_H__

#include "..\framework\Foxtrot.h"
#include "Frustum.h"

using namespace framework;

class FreeCamera
{
public:

	mat::Mat4 view_matrix;
	mat::Mat4 camera_matrix;

	struct Oritentation {

		vec::Vec3 z;
		vec::Vec3 x;
		vec::Vec3 y;

		vec::Vec3 position;
	};

	Frustum *frustum;
	
	Frustum self_frustum;

	FreeCamera();

	~FreeCamera();

	FreeCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &direction, const vec::Vec3 &up, Frustum &f);

	FreeCamera(Frustum &f);

	void set(const vec::Vec3 &camera_pos, const vec::Vec3 &direction, const vec::Vec3 &up);

	void set_frustum(Frustum &f);

	void update();

	void walk(vec::Vec3 direction, float distance);

	void walk_side(float distance);

	void walk_foward(float distance);

	void pan(float angle);

	void tilt(float angle);
};


#endif
