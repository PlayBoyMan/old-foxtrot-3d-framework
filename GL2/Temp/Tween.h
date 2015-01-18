#pragma once

#include <vector>

class Tween
{
public:

	float time;

	float application_time;

	bool started;

	int index;	

	float *variable;

	std::vector<float> times;
	std::vector<float> points;


	Tween()  {  };

	~Tween() {};

	Tween(const std::vector<float> &time, const std::vector<float> &points);

	float ease_in();

	float step();

	void attach_variable(float &var);
	void release_variable();
	void rewind();
	void ease_in_variable();
};

