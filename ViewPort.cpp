#include"ViewPort.h"

ViewPort::ViewPort() {
	m_screenWidth = 0;
	m_screenHeight = 0;
	m_aspect = 0.0f;
	m_fov = 0.0f;
	m_near = 0.0f;
	m_far = 0.0f;
	m_cameraX = 0.0f;
	m_cameraY = 0.0f;
	m_cameraZ = 0.0f;

	m_pMat = glm::mat4(0.0f);
	m_vMat = glm::mat4(0.0f);
}

void ViewPort::SetViewPort(int screenWidth, int screenHight, float fov, float near, float far) {
	m_screenHeight = screenWidth;
	m_screenWidth = screenWidth;
	m_fov = fov;
	m_aspect = (float)(screenWidth / screenWidth);
	m_near = near;
	m_far = far;
	m_pMat = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void ViewPort::Init(int screenWidth, int screenHight, float fov, float near, float far) {
	SetViewPort(screenWidth, screenHight, fov, near, far);
}

void ViewPort::SetCameraPos(float X, float Y, float Z) {
	m_cameraX = X;
	m_cameraY = Y;
	m_cameraZ = Z;
	m_vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-m_cameraX, -m_cameraY, -m_cameraZ));
}

void ViewPort::SetViewPort(GLFWwindow* winPtr, float fov, float near, float far) {
	assert(winPtr == nullptr && "ViewPort Get Null GLFWindow Ptr");
	glfwGetFramebufferSize(winPtr, &m_screenWidth, &m_screenHeight);
	SetViewPort(m_screenWidth, m_screenHeight, fov, near, far);
}
void ViewPort::Init(GLFWwindow* winPtr, float fov, float near, float far) {
	SetViewPort(winPtr, fov, near, far);
}