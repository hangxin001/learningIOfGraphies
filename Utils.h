#pragma once
#ifndef __TESTOPENGL__
#define __TESTOPENGL__
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<string>
#include<iostream>
#include<fstream>
#include<assert.h>
#include<type_traits>
#include<glm/glm.hpp>
enum class RotateAxis {
	X = 0,
	Y = 1,
	Z = 2,
};

std::string ReadGLSL(std::string filePath);

void ProgramErrorCheck(GLint program);

GLuint LoadShaderSource(GLuint flag, std::string shaderSourcePath, GLsizei count);	//¼ÓÔØshaderÎÄ¼þ

glm::mat4 buildTranslateMat(float x, float y, float z);

glm::mat4 buildRotateMat(float rad, RotateAxis axis);

glm::mat4 buildScaleMat(float x, float y, float z);


#endif // !__AUXFUN__
