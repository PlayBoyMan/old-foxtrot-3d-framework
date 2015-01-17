#pragma once

#include "../framework/Foxtrot.h"

#include "Frustum.h"

using namespace::framework;

/**
 * A class that abstracts a camera, implemented with 'look at' transformations.
 * The camera is fixed looking at 'point', being able to rotate and go
 * back/forward about that point.
 */
class LookAtCamera
{
public:

	/// Camera transform matrix
	mat::Mat4 camera_matrix;	

	/// Full view matrix
	mat::Mat4 view_matrix;

	/// First camera matrix, set from initial camera position
	mat::Mat4 initial_camera_matrix;


	/// Pointer to frustum
	Frustum *frustum;

	/// Orientation parameters
	float beta;
	float alpha;
	float gamma;

	/// Current distance from camera to point
	float distance;

	/// initial camera distance from point
	float initial_distance;

	/// Default constructor, empty
	LookAtCamera();


	/// Default destructor, empty
	~LookAtCamera();

	/// Construct camera from given parameters
	LookAtCamera(const vec::Vec3 &camera_pos, const vec::Vec3 &point, const vec::Vec3 &up, Frustum &f);

	/// Rotate the camera around the point vertically
	void rotate_up(float theta);

	/// Rotate the camera around the point horizontally
	void rotate_side(float theta);

	/// Walk closer or farther away from the point
	void walk(float step);

	/// update the view matrix
	void update();	

	/// Update the camera and view matrix to the current orientation/position
	void update_orientation();

};

