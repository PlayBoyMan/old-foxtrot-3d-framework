#pragma once

#include "../framework/Foxtrot.h"

using namespace::framework;

class LookAtCamera
{
public:
	
	mat::Mat4 view_matrix;
	float distance;


	LookAtCamera();

	LookAtCamera(vec::Vec3 camera_pos, vec::Vec3 point, vec::Vec3 up);

	void set_camera(vec::Vec3 camera_pos, vec::Vec3 point, vec::Vec3 up);

	void rotate_up(float theta);

	void rotate_side(float theta);

	void walk(float step);

	~LookAtCamera();
};

