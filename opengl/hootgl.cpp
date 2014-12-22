#include "hootgl.h"
#include <iostream>

void printInfoLog(GLuint shader)
{
	GLint len;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if( len > 1 ) {
		GLchar *buffer = new GLchar[len];
		glGetShaderInfoLog(shader, len, NULL, buffer);

		GLint sourceLen;
		glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &sourceLen);
		GLchar *sourceBuff = new GLchar[sourceLen];
		glGetShaderSource(shader, sourceLen, nullptr, sourceBuff);

		std::cerr << "Shader InfoLog(" << shader << "):\n" << buffer << "\nSource:\n" << sourceBuff << std::endl;

		delete[] buffer;
		delete[] sourceBuff;
	}
	
}

GLuint hglCreateProgram(const GLchar *vss, const GLchar *fss)
{
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertex, 1, &vss, 0);
	glShaderSource(fragment, 1, &fss, 0);
	
	glCompileShader(vertex);
	glCompileShader(fragment);
	
	GLint status;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);

	if( status != GL_TRUE ) {
		std::cerr << "Vertex Shader Compilation Failed" << std::endl;
	}
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);

	if( status != GL_TRUE ) {
		std::cerr << "Fragment Shader Compilation Failed" << std::endl;
	}
	
	printInfoLog(vertex);
	printInfoLog(fragment);
	
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	
	// Allow GL to delete shaders once program is deleted.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return program;
}
