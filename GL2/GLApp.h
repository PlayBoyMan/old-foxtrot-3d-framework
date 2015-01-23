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
#include <IL/il.h>

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
	Frustum myFrustum;

	Mesh quad;
	GLuint texture_id;

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

	void load_models()
	{
		const float p1[8] = { -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
		const float p2[8] = { -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f };
		const float p3[8] = {  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		const float p4[8] = {  1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f };

		quad.add_vertex(p1);
		quad.add_vertex(p2);
		quad.add_vertex(p3);
		quad.add_vertex(p4);

		quad.indices = vector<GLuint> {0, 3, 1, 3, 2, 1};

		quad.load();

		// texture code

		GLuint image_id;

		ilInit();
		ilClearColour(255, 255, 255, 000);


		ilGenImages(1, &image_id);

		ilBindImage(image_id);

		ilEnable(IL_ORIGIN_SET);

		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		
		if (!ilLoadImage((ILstring) "Resources\\Images\\stone_wall.jpg"))
		{
			error("Error loading image");
			exit(-1);
		}

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0);


		printf("(%d, %d)\n", ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		ilBindImage(0);


	}

	void init()
	{
		setResizeCallback(resize);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		shaderProgram.compileShader("shaders/shader.vert", GL_VERTEX_SHADER);
		shaderProgram.compileShader("shaders/shader.frag", GL_FRAGMENT_SHADER);
		shaderProgram.linkProgram();

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);

		
		
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);

		myFrustum = Frustum(1.0f, 1000.0f, 0.5f, -0.5f, 0.28f, -0.28f);
		camera = LookAtCamera(Vec3(0.0, 0.0, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), myFrustum);

		camara_manager = CameraManager(window, camera);
		camara_manager.set_tweens();

		load_models();


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

		glBindTexture(GL_TEXTURE_2D, texture_id);
		quad.render();
	}

public:

	GLApp()  { }
	~GLApp() { }
	GLApp(const string &str, int w, int h) : GLAppBase(str, w, h) { }
};

