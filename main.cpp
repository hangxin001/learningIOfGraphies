#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"Utils.h"
#include<glm/gtx/string_cast.hpp>
#include<vector>
#include<glm/ext.hpp>
using namespace std;
using namespace glm;
constexpr int numVAOs = 1;
constexpr int numVBOs = 2;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
float cameraX,cameraY, cameraZ;
float cubeLocX,cubeLocY, cubeLocZ;

//display()÷– π”√
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
glm::mat4 tMat, rMat;

GLuint createShaderProgram() {
	GLuint vShader = LoadShaderSource(GL_VERTEX_SHADER, "./shader/vshader.glsl", 1);
	GLuint fShader = LoadShaderSource(GL_FRAGMENT_SHADER, "./shader/fshader.glsl", 1);
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	ProgramErrorCheck(vfProgram);
	return vfProgram;
}
void InitModelData() {
	float vertexPosistion[108] = {
	 -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
	  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
	  1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	  -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	  -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
	  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
	  -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
	  -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
	  1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosistion), vertexPosistion, GL_STATIC_DRAW);
}
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	cameraX = 0.0f;	cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocX = 0.0f; cubeLocY = -2.0f;	cubeLocZ = 0.0f;
	InitModelData();
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
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

		glfwGetFramebufferSize(window, &width, &height);
		aspect = (float)width / (float)height;
		pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
		vMat = glm::translate(glm::mat4(f1), glm::vec3(-cameraX, -cameraY, -cameraZ));
		//mMat = glm::translate(glm::mat4(f1), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
		tMat = glm::translate(glm::mat4(1.0f),
			glm::vec3(sin(-.35f * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f));
		rMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
		rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(1.0f, 0, 0));
		rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(0, 0, 1.0f));
		mMat = tMat * rMat;
		mvMat = vMat * mMat;

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 36);

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