#include "framework/GLAppBase.h"
#include "framework/Graphics/shaders.h"
#include "framework\Math\Matrix.h"
#include "framework/Math/transform.h"
#include "framework/Math/vector.h"
#include "framework\Graphics\Mesh.h"
#include "framework\Graphics\Model.h"

#include "Temp\LookAtCamera.h"
#include "Temp\FreeCamera.h"
#include "Temp\Tween.h"
#include "Temp\CameraManager.h"

#include <string>
#include <math.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <gli\gli.hpp>

using namespace framework;

#pragma once
#include "Temp\Easing.h"
class GLApp : public GLAppBase
{
private:
	
	ShaderProgram shaderProgram;

	mat::Mat4 transform_matrix;

	graphics::Model model;

	LookAtCamera camera;
	FreeCamera free_camera;	
	Frustum myFrustum;

	CameraManager camara_manager;


	static void resize(GLFWwindow *window, int w, int h)
	{
		if (h > 0.562*w)
		{
			int height = floor(0.562 * w);
			
			glViewport(0, (h - height)/2, w, 0.562*w);
		}
		else
		{
			int width = floor (h / (0.562));
			glViewport((w - width) / 2, 0, width, h);

		}
	}

	void init()
	{
		setResizeCallback(resize);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		shaderProgram.compileShader("shaders/shader.vert", GL_VERTEX_SHADER);
		shaderProgram.compileShader("shaders/shader.frag", GL_FRAGMENT_SHADER);
		shaderProgram.linkProgram();

		model.load_model("Resources\\Models\\nanosuit\\nanosuit.obj");

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);

		myFrustum = Frustum(1.0f, 1000.0f, 0.5f, -0.5f, 0.28f, -0.28f);
		camera = LookAtCamera(Vec3(0.0, 10.0, 10.0f), Vec3(0.0f, 10.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), myFrustum);
		free_camera = FreeCamera(Vec3(0.0, 10.0, 20.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), myFrustum);

		camara_manager = CameraManager(window, camera);
		camara_manager.set_tweens();
	}
		
	
	void render(float delta)
	{
		camara_manager.input();
		camara_manager.update(delta);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		transform_matrix = camera.view_matrix;

		int transformPos = glGetUniformLocation(shaderProgram.getProgram(), "transform_matrix");
		glUniformMatrix4fv(transformPos, 1, GL_TRUE, &transform_matrix.data[0][0]);

		glUseProgram(shaderProgram.getProgram());

		model.render();

	}

public:

	GLApp()  { }
	~GLApp() { }
	GLApp(const string &str, int w, int h) : GLAppBase(str, w, h) { }
};

