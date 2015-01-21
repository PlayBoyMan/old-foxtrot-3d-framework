#include <vector>
#include <functional>

#pragma once


/**
 * Tween class: manages time-based interpolation of a set of values 
 * trough the use of easing functions.
 */
class Tween
{
public:

	/// Typedef: Easing function (i.e., interpolation) type
	typedef std::function<float(float, float, float, float)> EasingFunction;

	/// Typedef: Callback function, called at each step, with the current value as argument.
	typedef std::function<void(float)> CallbackFunction;

	/// Struct with the parameters to be passed to the easing function and the easing function to be called 
	typedef struct { float period, begin, end; EasingFunction easing_function; } EasingParameters;

	/// Current interpolation time (piece-wise)
	float time;

	/// If the tween has started
	bool started;

	/// If the tween has finished
	bool finished;

	/// If the tween is locked there is no step
	bool locked;

	/// Current index 
	int index;

	/// Vector with the easing parameters to be used, i.e., a sequence of interpolations
	std::vector<EasingParameters> easing_parameters;

	/// Pointer to the variable to be updated
	float *variable;

	/// Callback function to be called at each update
	CallbackFunction callback_function;

	/// Default constructor, empty
	Tween();

	/// Default destructor, empty
	~Tween();

	/// Constructor with parameters and reference to variable
	Tween(const std::vector<EasingParameters> &param, float &variable);

	/// Constructor with parameters and callback function
	Tween(const std::vector<EasingParameters> &param, CallbackFunction func);

	/// Copy constructor
	Tween(const Tween &t);

	/// Copy-assignment operator
	Tween & Tween::operator=(const Tween &t);

	/// Do a step of 'delta' in the interpolation
	void step(float delta);

	/// Set easing parameters
	void set_parameters(const std::vector<EasingParameters> &parameters);

	/// Set the variable pointer
	void set_variable(float &var);

	/// Set callback function
	void set_callback(CallbackFunction f);

	/// Rewind the tween
	void rewind();

	/// Lock the Tween
	void lock();

	/// Unlock the Tween
	void unlock();

private:

	/// Use variable pointer
	bool use_variable;

	/// Use callback function
	bool use_callback;
	
	/// Swap function for the assignment operator
	void swap(Tween &t);
};

/**
 * TweenManager class: Manages a set of Tweens to be run simultaneously 
 */
class TweenManager
{
public:

	/// Vector containing the Tweens
	std::vector<Tween> tweens;

	/// Default constructor, empty
	TweenManager();

	/// Default destructor, empty
	~TweenManager();

	/// Construct from a vector of tweens
	TweenManager(std::vector<Tween> &t);

	/// Add a Tween (by copy) and return a pointer to the stored Tween
	Tween* add_tween(const Tween &tween);

	/// Update Tweens
	void step(float delta);

	/// Return pointer to tween of index i
	Tween* get(const int &i);
};

