#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"Utils.h"
#include<glm/gtx/string_cast.hpp>
#include<vector>
using namespace std;
using namespace glm;
#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
float x = 0.0f;
float inc = 0.01f;
float scaleRatio = 1.2f;
int scaleCount = 0;
vector<glm::vec4> vecTrianglesVertex;
GLfloat* vecrawTrianglesVertex;

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
void InitVertexData() {
	vecTrianglesVertex.emplace_back(vec4(0.0, 0.25, 0.0, 1.0));
	vecTrianglesVertex.emplace_back(vec4(0.25, 0.0, 0.0, 1.0));
	vecTrianglesVertex.emplace_back(vec4(-0.25, 0.0, 0.0, 1.0));
	vecrawTrianglesVertex = new GLfloat[3 * 4];
	for (int i = 0, vecIndex = 0; i < 12; ++i) {
		*(vecrawTrianglesVertex + i) = vecTrianglesVertex[i / 4][i % 4];
	}
}
void display(GLFWwindow* window, double currentTime) {
	using namespace glm;
	auto rotate = [](vector<glm::vec4>& vecTrianglesVertex, float rad) {
		for (auto v = vecTrianglesVertex.begin(); v != vecTrianglesVertex.end(); ++v) {
			*v = buildRotateMat(rad, RotateAxis::Z) * (*v);
		}
	};
	auto scale = [](vector<glm::vec4>& vecTrianglesVertex, float scaleX, float scaleY, float scaleZ) {
		for (auto v = vecTrianglesVertex.begin(); v != vecTrianglesVertex.end(); ++v) {
			*v = buildScaleMat(scaleX, scaleY, scaleZ) * (*v);
		}
	};
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	//缩放
	//放大系数有问题，应该放大和缩小不是成比例，如1放大1.5为1.5，但是1.5缩写0.5为0.75；
	scale(vecTrianglesVertex, scaleRatio, scaleRatio, scaleRatio);

	//旋转
	rotate(vecTrianglesVertex, 0.1);
	
	for (int i = 0, vecIndex = 0; i < 12; ++i) {
		*(vecrawTrianglesVertex + i) = vecTrianglesVertex[i / 4][i%4];
	}
	GLuint vertexsLoc = glGetUniformLocation(renderingProgram, "vertexs");
	glProgramUniform4fv(renderingProgram,vertexsLoc,3, vecrawTrianglesVertex);

	/*
	//移动
	x += inc;
	inc = x > 1.0f || x < -1.0f ? -inc : inc;
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);
	//缩放
	scaleRatio += scaleRate;
	scaleRate = scaleRatio > 1.5 || scaleRatio < 0.5 ? -scaleRate : scaleRate;
	GLuint scaleLoc = glGetUniformLocation(renderingProgram, "scaleOffset");
	glProgramUniform1f(renderingProgram, scaleLoc, scaleRatio);
	*/
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
	InitVertexData();
	while (!glfwWindowShouldClose(windows)) {
		display(windows, glfwGetTime());
		glfwSwapBuffers(windows);
		glfwPollEvents();
	}
	glfwDestroyWindow(windows);
	glfwTerminate();
}