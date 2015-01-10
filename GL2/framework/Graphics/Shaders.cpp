#include "shaders.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>

using namespace std;


ShaderProgram::ShaderProgram()
{
	programId = 0;

}

ShaderProgram::~ShaderProgram()
{
	if (programId != 0)
		glDeleteProgram(programId);
}

GLuint ShaderProgram::getProgram()
{
	return programId;
}

void ShaderProgram::compileShader(const string& filename, GLuint shaderType)
{
	/* Load text file */
	ifstream shaderFile(filename.c_str());
	stringstream shaderData;
	shaderData << shaderFile.rdbuf();

	string temp = shaderData.str();
	const GLchar * shaderSource = (const GLchar *)temp.c_str();

	/* Pass source code to OpenGL */
	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderSource, NULL);

	/* Compile and check for errors */
	printf("Compiling shader %s...", filename.c_str());
	printf("\nCODE: \n %s \n END OF CODE \n", (char *)shaderSource);
	glCompileShader(shaderId);

	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &status);
		vector<GLchar> errorLog(status);
		glGetShaderInfoLog(shaderId, status, &status, &errorLog[0]);
		printf("Error compiling shader: %s", (char *) &errorLog[0]);
		printf("%s", shaderData.str().c_str());
	}
	

	shaderIds.push_back(shaderId);
}

void ShaderProgram::linkProgram()
{
	programId = glCreateProgram();

	for (auto id : shaderIds)
	{
		glAttachShader(programId, id);
	}

	glLinkProgram(programId);

	GLint status;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &status);
		vector<GLchar> errorLog(status);
		glGetProgramInfoLog(programId, status, &status, &errorLog[0]);
		printf("Error linking program: %s", &errorLog[0]);
	}

	for (auto id : shaderIds)
	{
		glDeleteShader(id);
	}

}


