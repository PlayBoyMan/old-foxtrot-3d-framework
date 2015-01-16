#pragma once
#ifndef __FREECAMERA_H__
#define __FREECAMERA_H__

#include "..\framework\Foxtrot.h"
#include "Frustum.h"

using namespace framework;

/**
 *  Free camera class. Implements a free looking camera.
 *	It starts looking at a given direction from a given position.
 *  Then, the orientation is changed by the parameters yaw, pitch and roll, 
 *  that control the rotations (relative to the initial orientations), 
 *  of the x, y, and z axis.
 *
 */
class FreeCamera
{
public:
	
	/// A 4x4 Matrix representing the camera transform
	mat::Mat4 camera_matrix;

	/// A 4x4 Matrix representing the full view transform (camera + frustum)
	mat::Mat4 view_matrix;

	/// Pointer to the current view frustum
	Frustum *frustum;

	/// Orientation parameters, yaw (y axis), pitch (x axis) and roll (z axis)
	float yaw, pitch, roll;

	/// Current camera position
	vec::Vec3 position;

	/// Original camera direction
	vec::Vec3 original_direction;

	/// Original camera up
	vec::Vec3 original_up;

	/// Current camera direction
	vec::Vec3 direction;

	/// Current camera up
	vec::Vec3 up;

	/// Default constructor, empty
	FreeCamera();

	/// Default destructor, empty
	~FreeCamera();

	/// Construct from camera parameters and frustum
	FreeCamera(vec::Vec3 camera_position, vec::Vec3 camera_direction, vec::Vec3 camera_up, Frustum &f);

	/// Updates view_matrix from comera_matrix and frustum->frustum_matrix
	void update();

	/// Updates camera_matrix using current orientation parameters
	void yaw_pitch_roll();

	/// Pans the camera (y axis rotation) an angle delta
	void pan(float delta);

	/// Tilts the camera (x axis rotation) an angle delta
	void tilt(float delta);

	/// Rolls the camera (y axis rotation) an angle delta
	void do_roll(float delta);

	/// Move the camera a 'step' in the camera's forward (-z) direction
	void walk_forward(float step);

	/// Move the camera a 'step' in the camera's forward (-z) direction
	void walk_side(float step);
};


#endif
