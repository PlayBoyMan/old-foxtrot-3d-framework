#include "GLFW/glfw3.h"

#include "Tween.h"
#include "Easing.h"


Tween::Tween(const std::vector<float> &time, const std::vector<float> &point)
{
	times = time;
	points = point;
	started = false;
	
	this->time = 0.0f;
	variable = nullptr;
}

void Tween::attach_variable(float &var)
{
	variable = &var;
}

void Tween::release_variable()
{
	variable = nullptr;
	rewind();
}

void Tween::rewind()
{
	started = false;
	this->time = 0.0f;
}

void Tween::ease_in_variable()
{
	(*variable) = ease_in();
}
	
float Tween::ease_in()
{

	if (!started)
	{
		time = 0.0f;
		application_time = (float) glfwGetTime();
		this->started = true;

		index = 0;
	}
	else
	{
		float t = glfwGetTime();
		time = t - application_time;
	}

	if (time < times[index+1])
	{
		if (index == 0)
			return linear_easing(time, times[1] - times[0], points[0], points[1]);
		else
			return linear_easing(time  - times[index], times[index+1] - times[index], points[index], points[index+1]);
	}
	else
	{
		index++;
		if ((index + 1) >= times.size())
		{
			started = false;
			return linear_easing(time - times[index-1], times[index] - times[index-1], points[index-1], points[index]);
		}
		else
		{
			return linear_easing(time - times[index], times[index + 1] - times[index], points[index], points[index + 1]);
		}
	}

	return 0;
}
