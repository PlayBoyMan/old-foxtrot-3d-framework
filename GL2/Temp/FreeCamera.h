#pragma once
#ifndef __FREECAMERA_H__
#define __FREECAMERA_H__

#include "..\framework\Foxtrot.h"
#include "Frustum.h"

using namespace framework;

class FreeCamera
{
public:
	

	mat::Mat4 camera_matrix;
	mat::Mat4 view_matrix;

	Frustum *frustum;

	float yaw, pitch, roll;

	vec::Vec3 position;
	vec::Vec3 direction;
	vec::Vec3 up;

	vec::Vec3 current_direction;
	vec::Vec3 current_up;

	FreeCamera();

	~FreeCamera();

	FreeCamera(vec::Vec3 camera_position, vec::Vec3 camera_direction, vec::Vec3 camera_up, Frustum &f);
	void update();
	void yaw_pitch_roll();
	void pan(float delta);
	void tilt(float delta);
	void do_roll(float delta);
	void walk_foward(float step);
	void walk_side(float step);
};


#endif
