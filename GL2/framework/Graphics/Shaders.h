#ifndef __SHADERS_H__
#define __SHADERS_H__

#include <string>
#include <list>

#include <GL\glew.h>

using namespace std;

class ShaderProgram
{
private:

	GLuint programId;	
	list<GLuint> shaderIds;

public:
	ShaderProgram();
	~ShaderProgram();

	void compileShader(const std::string& filename, GLuint shaderType);
	void linkProgram();
	GLuint getProgram();

};

#endif
