#include "Tween.h"
#include <functional>

Tween::Tween() : 
	time(0.0f), 
	started(false), 
	finished(false), 
	variable(nullptr), 
	index(0), 
	easing_parameters(), 
	callback_function(),
	locked(true),
	use_callback(false),
	use_variable(false)
{

}

Tween::Tween(const std::vector<EasingParameters> &p, float &variable) : 
	time(0.0f),
	started(false),
	finished(false),
	variable(&variable),
	index(0),
	easing_parameters(p),
	callback_function(),
	locked(true),
	use_callback(false),
	use_variable(true)
{
	
}

Tween::Tween(const std::vector<EasingParameters> &p, CallbackFunction f) :
	time(0.0f),
	started(false),
	finished(false),
	variable(nullptr),
	index(0),
	easing_parameters(p),
	callback_function(f),
	locked(true),
	use_callback(true),
	use_variable(false)
{

}

Tween::Tween(const Tween &t) :
	time(t.time),
	started(t.started),
	finished(t.finished),
	variable(t.variable),
	index(t.index),
	easing_parameters(t.easing_parameters),
	callback_function(t.callback_function),
	locked(t.locked),
	use_callback(t.use_callback),
	use_variable(t.use_variable)
{
	
}

Tween & Tween::operator=(const Tween &t)
{
	Tween temp(t);
	temp.swap(*this);
	return *this;
}

void Tween::swap(Tween &t)
{
	std::swap(time, t.time);
	std::swap(started, t.started);
	std::swap(finished, t.finished);
	std::swap(variable, t.variable);
	std::swap(easing_parameters, t.easing_parameters);
	std::swap(index, t.index);
	std::swap(callback_function, t.callback_function);
	std::swap(locked, t.locked);
	std::swap(use_variable, t.use_variable);
	std::swap(use_callback, t.use_callback);
		
}

Tween::~Tween()
{
	
}

void Tween::set_parameters(const std::vector<EasingParameters> &parameters)
{
	easing_parameters = parameters;
	rewind();
	unlock();
}

void Tween::set_variable(float &var)
{
	variable = &var;
	use_variable = true;
}

void Tween::set_callback(CallbackFunction f)
{
	callback_function = f;
	use_callback = true;
}

void Tween::rewind()
{
	time = 0.0f;
	index = 0;
	started = false;
	finished = false;
	locked = true;
}

void Tween::step(float delta)
{
	
	// update time
	time = time + delta;
	
	// if is finished or locked, do nothing
	if (finished || locked)
	{
		return;
	}

	// If it's the first run
	if (started == false)
	{
		started = true;
		finished = false;
		index = 0;
	}

	// Check if current piece is over; if so, increment index and reset time for the next piece
	if (time >= easing_parameters[index].period)
	{
		index++;
		time = 0.0f;
	}

	// Step value
	float value = 0.0f;

	// Check if Tween is finished. If so, return. Else, calculate step.
	if (index >= easing_parameters.size())
	{
		started = false;
		finished = true;
		return;
	}
	else
	{
		// Calculate step value
		value = easing_parameters[index].easing_function(time, easing_parameters[index].period, easing_parameters[index].begin, easing_parameters[index].end);
	}

	// If use variable, set variable
	if (use_variable)
		*variable = value;

	// If use callback, set callback
	if (use_callback)
		callback_function(value);

}

void Tween::lock()
{
	locked = true;
}

void Tween::unlock()
{
	locked = false;
}

TweenManager::TweenManager()
{

}


TweenManager::TweenManager(std::vector<Tween> &t)
{
	tweens = t;
}

TweenManager::~TweenManager()
{

}

Tween* TweenManager::get(const int &i)
{
	return &tweens[i];
}

Tween* TweenManager::add_tween(const Tween &tween)
{
	tweens.push_back(tween);
	return &tweens.back();
}

void TweenManager::step(float delta)
{
	for (int i = 0; i < tweens.size(); i++)
	{
		if (!tweens[i].finished || !tweens[i].locked)
		{
			tweens[i].step(delta);
		}
	}
}
