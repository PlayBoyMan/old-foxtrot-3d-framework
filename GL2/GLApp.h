#include "framework/GLAppBase.h"
#include "framework/Graphics/shaders.h"
#include "framework\Math\Matrix.h"
#include "framework/Math/transform.h"
#include "framework/Math/vector.h"
#include "framework\Graphics\Mesh.h"
#include "framework\Graphics\Model.h"
#include "Temp\LookAtCamera.h"
#include "Temp\FreeCamera.h"

#include <string>
#include <math.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <gli\gli.hpp>

using namespace framework;

#pragma once
class GLApp : public GLAppBase
{
private:
	
	ShaderProgram shaderProgram;

	mat::Mat4 transform_matrix;
	
	graphics::Mesh test, t2, t3;

	vec::Vec3 camera_pos, point_pos;

	float angle = 0.0f;

	graphics::Model model;

	LookAtCamera camera;

	FreeCamera free_camera;
	
	Frustum myFrustum;


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

		float triangle[] = { -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		
		
		test.add_vertex(3, triangle);
		test.load();
		
		triangle[2] += 2.0f; triangle[10] += 2.0f; triangle[18] += 2.0f;

		t2.add_vertex(3, triangle);
		t2.load();

		camera_pos = vec::Vec3(0.0f, 0.0f, 10.0f);

		model.load_model("Resources\\Models\\nanosuit\\nanosuit.obj");
		
		
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);

		camera.set_camera(Vec3(0.0, 10.0, 10.0f), Vec3(0.0f, 10.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));	
		myFrustum = Frustum(1.0f, 1000.0f, 0.5f, -0.5f, 0.28f, -0.28f);
		camera.set_frustum(myFrustum);

		free_camera = FreeCamera(Vec3(0.0, 10.0, 10.0f), Vec3(0.0f, 10.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), myFrustum);



	}
	
	void render()
	{

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{			
			camera.rotate_up(0.005f);
			free_camera.walk_foward(0.05f);
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera.rotate_up(-0.005f);
			free_camera.walk_foward(-0.05f);
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera.rotate_side(0.005f);
			free_camera.walk_side(0.05f);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			camera.rotate_side(-0.005f);
			free_camera.walk_side(-0.05f);
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.walk(0.005f);
			free_camera.tilt(0.005f);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.walk(-0.005f);
			free_camera.tilt(-0.005f);
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			camera.frustum->zoom(0.001f);
			camera.update();
			
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			camera.frustum->zoom(-0.001f);
			camera.update();

		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			free_camera.pan(0.005f);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			free_camera.pan(-0.005f);
		}

		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		point_pos = camera_pos + vec::Vec3(0.0f, 0.0f, -1.0f);
		
		

		//transform_matrix = transform::frustum_matrix(1.0f, 100.0f, 1.0f, -1.0f, 0.7f, -0.7f)*transform::look_at_matrix(camera_pos, point_pos, vec::Vec3(0.0f, 1.0f, 0.0f));
		
		//transform_matrix = transform::frustum_matrix(1.0f, 1000.0f, 0.5f, -0.5f, 0.28, -0.28f) * camera.camera_matrix;

		transform_matrix = free_camera.view_matrix;

		int transformPos = glGetUniformLocation(shaderProgram.getProgram(), "transform_matrix");
		glUniformMatrix4fv(transformPos, 1, GL_TRUE, &transform_matrix.data[0][0]);

		glUseProgram(shaderProgram.getProgram());

		//test.render(); 
		
		//t2.render();		

		model.render();
		
	}

public:

	GLApp()  { }
	~GLApp() { }
	GLApp(const string &str, int w, int h) : GLAppBase(str, w, h) { }
};

