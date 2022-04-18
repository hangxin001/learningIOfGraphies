#pragma once
#ifndef TESTOPENGL__VIEWPORT
#define TESTOPENGL__VIEWPORT
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/ext.hpp>
#include<glm/gtx/string_cast.hpp>
class ViewPort {
public:
	ViewPort();
	void Init(int screenWidth, int screenHight, float fov, float near, float far);
	void Init(GLFWwindow* winPtr, float fov, float near, float far);
	void SetViewPort(int screenWidth, int screenHight, float fov, float near, float far);
	void SetViewPort(GLFWwindow* winPtr, float fov, float near, float far);
	void SetCameraPos(float X, float Y, float Z);
	inline glm::mat4 GetPMat() { return m_pMat; }
	inline glm::mat4 GetVMat() { return m_vMat; }
	inline int GetScreenWidth() { return m_screenWidth; };
	inline int GetScreenHeight() { return m_screenHeight; }

private:
	int m_screenWidth;
	int m_screenHeight;
	float m_aspect;
	float m_fov;
	float m_near;
	float m_far;

	float m_cameraX;
	float m_cameraY;
	float m_cameraZ;
	
	glm::mat4 m_pMat;
	glm::mat4 m_vMat;
};
#endif