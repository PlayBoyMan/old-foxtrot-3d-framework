#include "CameraManager.h"
#include "Easing.h"
#include "Tween.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>



CameraManager::CameraManager(GLFWwindow *w, LookAtCamera &camera) :  
	window(w),
	rotate_up_max_velocity(4.0f),
	rotate_side_max_velocity(4.0f),
	walk_forward_max_velocity(2.0f),
	rotate_side_velocity(0.0f),
	rotate_up_velocity(0.0f),
	walk_forward_velocity(0.0f),
	tween_manager(),
	look_at_camera(&camera)
{
	for (int i = 0; i < 6; i++)
		key_flags[i] = false;
}

CameraManager::CameraManager()
{
	
}

void CameraManager::set_tweens()
{
	tween_manager.add_tween(Tween({ { 10.8f, 0.0f, rotate_side_max_velocity, linear_easing } }, [this](float val){ this->rotate_side_velocity = val;  }));
	tween_manager.add_tween(Tween({ { 10.8f, 0.0f, rotate_up_max_velocity, linear_easing } }, [this](float val){  this->rotate_up_velocity = val;  }));
	tween_manager.add_tween(Tween({ { 10.8f, 0.0f, walk_forward_max_velocity, linear_easing } }, [this](float val){  this->walk_forward_velocity = val;  }));
}

CameraManager::~CameraManager()
{
}

void CameraManager::update(float delta)
{
	// Step trough all the tweens
	tween_manager.step(delta);
	
	// Update camera orientation with parameters
	look_at_camera->rotate_up(rotate_up_velocity*delta);
	look_at_camera->rotate_side(rotate_side_velocity*delta);
	look_at_camera->walk(walk_forward_velocity*delta);
}

void CameraManager::input()
{
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// Check if it's the first loop after key-press, and start tween
		if (!key_flags[KEY_UP])
		{
			key_flags[KEY_UP] = true;
			tween_manager.get(ROTATE_UP)->set_parameters({{ 0.5f, rotate_up_velocity, rotate_up_max_velocity, linear_easing }});
		}
	}
	else
	{
		// Check if it's the first loop after key-release, and start reverse tween
		if (key_flags[KEY_UP])
		{
			tween_manager.get(ROTATE_UP)->set_parameters({ { 0.5f, rotate_up_velocity, 0.0f, linear_easing } });
			key_flags[KEY_UP] = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (!key_flags[KEY_DOWN])
		{
			key_flags[KEY_DOWN] = true;
			tween_manager.get(ROTATE_UP)->set_parameters({ { 0.5f, rotate_up_velocity, -rotate_up_max_velocity, linear_easing } });
		}
	}
	else
	{
		if (key_flags[KEY_DOWN])
		{			
			tween_manager.get(ROTATE_UP)->set_parameters({ { 0.5f, rotate_up_velocity, 0.0f, linear_easing } });
			key_flags[KEY_DOWN] = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!key_flags[KEY_RIGHT])
		{
			key_flags[KEY_RIGHT] = true;
			tween_manager.get(ROTATE_SIDE)->set_parameters({ { 0.5f, rotate_side_velocity, rotate_side_max_velocity, linear_easing } });
		}
	}
	else
	{
		if (key_flags[KEY_RIGHT])
		{
			tween_manager.get(ROTATE_SIDE)->set_parameters({ { 0.5f, rotate_side_velocity, 0.0f, linear_easing } });
			key_flags[KEY_RIGHT] = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (!key_flags[KEY_LEFT])
		{
			key_flags[KEY_LEFT] = true;
			tween_manager.get(ROTATE_SIDE)->set_parameters({ { 0.5f, rotate_side_velocity, -rotate_side_max_velocity, linear_easing } });
		}
	}
	else
	{
		if (key_flags[KEY_LEFT])
		{
			tween_manager.get(ROTATE_SIDE)->set_parameters({ { 0.5f, rotate_side_velocity, 0.0f, linear_easing } });
			key_flags[KEY_LEFT] = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (!key_flags[KEY_W])
		{
			key_flags[KEY_W] = true;
			tween_manager.get(WALK_FORWARD)->set_parameters({ { 0.5f, walk_forward_velocity, walk_forward_max_velocity, linear_easing } });
		}
	}
	else
	{
		if (key_flags[KEY_W])
		{
			tween_manager.get(WALK_FORWARD)->set_parameters({ { 0.5f, walk_forward_velocity, 0.0f, linear_easing } });
			key_flags[KEY_W] = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (!key_flags[KEY_S])
		{
			key_flags[KEY_S] = true;
			tween_manager.get(WALK_FORWARD)->set_parameters({ { 0.5f, walk_forward_velocity, -walk_forward_max_velocity, linear_easing } });
		}
	}
	else
	{
		if (key_flags[KEY_S])
		{			
			tween_manager.get(WALK_FORWARD)->set_parameters({ { 0.5f, walk_forward_velocity, 0.0f, linear_easing } });
			key_flags[KEY_S] = false;
		}
	}
}
