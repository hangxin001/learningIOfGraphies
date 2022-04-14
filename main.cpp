#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"Utils.h"
#include"Sphere.h"
#include"Torus.h"
#include<glm/gtx/string_cast.hpp>
#include<vector>
#include<glm/ext.hpp>
#include"MaterialData.h"
using namespace std;
using namespace glm;
static MaterialDataManager g_materialDataMng;
constexpr int numVAOs = 1;
constexpr int numVBOs = 3;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
float cameraX,cameraY, cameraZ;
float cubeLocX,cubeLocY, cubeLocZ;

//display()÷– π”√
GLuint mvLoc, projLoc, vLoc, mLoc, tfLoc;
GLuint brickTexture;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
glm::mat4 tMat, rMat;
Torus g_torus(2,1,10);

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

	auto vertex = VertexToArray(g_torus.GetVertices(), g_torus.GetIndices());
	auto indices = g_torus.GetIndices();
	auto texCoord = TexCoordsToArray(g_torus.GetTexCoords(), g_torus.GetIndices());
	auto normals = VertexToArray(g_torus.GetNormals(), g_torus.GetIndices());
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(vertex)::value_type) * vertex.size(), vertex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(texCoord)::value_type) * texCoord.size(), texCoord.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(normals)::value_type) * normals.size(), normals.data(), GL_STATIC_DRAW);
	brickTexture = loadTexture("pic.jpg");
}
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	cameraX = 0.0f;	cameraY = 0.0f; cameraZ = 10;
	cubeLocX = 0.0f; cubeLocY = 0.0f;	cubeLocZ = 0.0f;
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
	
	//mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
	mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
	tfLoc = glGetUniformLocation(renderingProgram, "tf");

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
	vMat = glm::translate(glm::mat4(f1), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(f1), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
		/*
		tMat = glm::translate(glm::mat4(1.0f),
		glm::vec3(sin(-.35f * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f));
		rMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
		rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(1.0f, 0, 0));
		rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(0, 0, 1.0f));
		mMat = tMat * rMat;
		mvMat = vMat * mMat;

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		*/
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
	auto timeFactor = (float)(currentTime);
	glUniform1f(tfLoc, (float)timeFactor);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_torus.GetNumIndices(), 1);

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