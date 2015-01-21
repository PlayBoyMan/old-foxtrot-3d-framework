#include "LookAtCamera.h"
#include "Tween.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#pragma once
class CameraManager
{
public:

	/// Enum to the Tween indexes in tween_manager
	enum { ROTATE_SIDE, ROTATE_UP, WALK_FORWARD };

	/// Enum to the key_flags array indices
	enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S};

	/// Array containing key-press flags
	bool key_flags[6];

	/// Pointer to the look at camera
	LookAtCamera *look_at_camera;

	/// TweenManager to hold the tweens
	TweenManager tween_manager;

	/// Velocity parameters
	float rotate_side_velocity;
	float rotate_up_velocity;
	float walk_forward_velocity;

	/// Max velocities
	float rotate_side_max_velocity;
	float rotate_up_max_velocity;
	float walk_forward_max_velocity;

	/// Pointer to the windows
	GLFWwindow *window;

	/// Default constructor, empty
	CameraManager();

	/// Construct from window and camera pointers
	CameraManager(GLFWwindow *w, LookAtCamera &camera);

	/// Default destructor, empty
	~CameraManager();

	/// Update the camera
	void update(float delta);

	/// Process input
	void input();

	/// Setup tweens
	void set_tweens();
};

