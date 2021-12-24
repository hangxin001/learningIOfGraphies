#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"Utils.h"
#include<glm/gtx/string_cast.hpp>
using namespace std;
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {
	GLuint vShader = LoadShaderSource(GL_VERTEX_SHADER, "./shader/vshader.shader", 1);
	GLuint fShader = LoadShaderSource(GL_FRAGMENT_SHADER, "./shader/fshader.shader", 1);
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	ProgramErrorCheck(vfProgram);
	return vfProgram;
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}
float x = 0.0f;
float inc = 0.01f;
float scaleRatio = 1.0f;
float scaleRate = 0.01f;
void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);
	//ÒÆ¶¯
	x += inc;
	inc = x > 1.0f || x < -1.0f ? -inc : inc;
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);
	//Ëõ·Å
	scaleRatio += scaleRate;
	scaleRate = scaleRatio > 1.5 || scaleRatio < 0.5 ? -scaleRate : scaleRate;
	GLuint scaleLoc = glGetUniformLocation(renderingProgram, "scaleOffset");
	glProgramUniform1f(renderingProgram, scaleLoc, scaleRatio);
	
	
	//glPointSize(2.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
int main() {
	
	if (!glfwInit())	exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* windows = glfwCreateWindow(400, 400, "Chapter2", NULL, NULL);
	glfwMakeContextCurrent(windows);
	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);
	glfwSwapInterval(1);
	init(windows);

	while (!glfwWindowShouldClose(windows)) {
		display(windows, glfwGetTime());
		glfwSwapBuffers(windows);
		glfwPollEvents();
	}
	glfwDestroyWindow(windows);
	glfwTerminate();
}