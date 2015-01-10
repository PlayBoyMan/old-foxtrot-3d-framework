// GL2.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <glm/glm.hpp>

#include "stdafx.h"
#include "GLApp.h"

int _tmain(int argc, _TCHAR* argv[])
{			

	GLApp *app = new GLApp("My Window", 800, 600);
	app->run();	

}