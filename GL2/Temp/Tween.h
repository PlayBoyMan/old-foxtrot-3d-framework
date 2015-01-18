#pragma once

#include <vector>

class Tween
{
public:

	float time;

	float application_time;

	bool started;

	int index;	

	std::vector<float> times;
	std::vector<float> points;


	Tween()  {  };

	~Tween() {};

	Tween(const std::vector<float> &time, const std::vector<float> &points);

	float ease_in();
};

