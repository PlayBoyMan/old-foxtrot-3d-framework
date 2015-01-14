#ifndef __GLAPPBASE_H__
#define __GLAPPBASE_H__

#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>


#pragma once

using namespace std;

// Abstracts a simple OpenGL/GLFW application framework.
/**
* The GLAppBase abstracts a OpenGL/GLFW single window application.
* It sets up the window, input handling, and a main application loop.
* This is a virtual class, that must be inherited, so the user can 
* define application specific initialization, renderind and termination
* functions.
*/
class GLAppBase
{
public:

	/// GLFW window object
	GLFWwindow *window;

	/// Window width
	int imageWidth;

	/// Window height
	int imageHeight;

	/// Window name
	string windowTitle = "GLFW Window";

	/// Output info to terminal?
	bool verbose = true;
	
	/// Print message on terminal
	inline void log(const string &str)
	{
		if (verbose)
			printf("%s \n", str.c_str());
	}

	/// Report error and exit application
	inline void error(const string &str)
	{
		printf("Error: %s \n", str.c_str());
		exit(-1);
	}

	/// Inner initialization routine. Sets up the GLFW window
	void _init()
	{	
		log("GLAppBase _init()");

		if (!glfwInit())
		{
			error("glwInit() failed.");
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(imageWidth, imageHeight, windowTitle.c_str(), NULL, NULL);
		

		if (!window)
		{
			error("Failed to create window");
		}

		glfwMakeContextCurrent(window);		
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);

		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			error("glewInit() error");
		}	

		log("_init() end");
	}

	/// Default render, to be overriden by the user.
	virtual void render()
	{
		log("GLAppBase render()");
		glClearColor(0.0f, 0.3f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	/// Inner main loop. Calls the render() function, defined by the user.
	virtual void mainLoop()
	{	
		log("GLAppBase mainLoop()");		

		while (!glfwWindowShouldClose(window))
		{
			render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}	
	}

	/// Terminate function, to be defined by the user, and called when the app. exits
	virtual void terminate() { };

	/// User initialization function.
	virtual void init() = 0;

	/// Inner terminate routine. Shuts glfw down.
	void _terminate()
	{
		log("GLAppBase _terminate()");
		glfwTerminate();
	}

	/// Starts up the application, and enters main loop.
	void run()
	{
		log("GLAppBase run()");
		_init();
		init();
		mainLoop();
		_terminate();
		terminate();
	}

	/// Default constructor, empty.
	GLAppBase() : windowTitle("My Window"), imageWidth(1280), imageHeight(720)
	{	
	}

	/// Construct window with given dimensions.
	GLAppBase(int w, int h) : windowTitle("My Window"), imageWidth(w), imageHeight(h)
	{
		imageWidth = w;
		imageHeight = h;		
	}

	/// Construct window with dimensions and name.
	GLAppBase(const string &str, int w, int h) :
		windowTitle(str), imageWidth(w), imageHeight(h)
	{
	}

	
	~GLAppBase() {}				

	/// Sets resize callback.
	void setResizeCallback(GLFWwindowsizefun fun)
	{
		glfwSetWindowSizeCallback(window, fun);
	}

};

#endif