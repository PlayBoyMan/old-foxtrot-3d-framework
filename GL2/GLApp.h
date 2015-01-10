#include "framework/GLAppBase.h"
#include "framework/Graphics/shaders.h"
#include "framework\Math\Matrix.h"
#include "framework/Math/transform.h"
#include "framework/Math/vector.h"
#include "framework\Graphics\Mesh.h"
#include "framework\Graphics\Model.h"

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

	static void resize(GLFWwindow *window, int w, int h)
	{
		glViewport(0, 0, w, h);		
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
		
	}
	
	void render()
	{

		if (glfwGetKey(window, GLFW_KEY_UP) == GL_TRUE)
		{
			camera_pos.z -= 0.005f;
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GL_TRUE)
		{
			camera_pos.z += 0.005f;			
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GL_TRUE)
		{
			camera_pos.x += 0.005f;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GL_TRUE)
		{
			camera_pos.x -= 0.005f;
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		point_pos = camera_pos + vec::Vec3(0.0f, 0.0f, -1.0f);
		

		mat::Mat4 object_matrix = mat::Mat4(transform::rotation_matrix_x_axis(angle), vec::Vec3(0.0f));

		transform_matrix = transform::frustum_matrix(1.0f, 100.0f, 1.0f, -1.0f, 0.7f, -0.7f)*transform::look_at_matrix(camera_pos, point_pos, vec::Vec3(0.0f, 1.0f, 0.0f));
		

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
	GLApp(const string &str, int w, int h) { }
};

