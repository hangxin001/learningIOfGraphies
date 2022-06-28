#pragma once
#ifndef TESTOPENGL__VIEWPORT
#define TESTOPENGL__VIEWPORT
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/ext.hpp>
#include<glm/gtx/string_cast.hpp>
#include<tuple>
#include"Utils.h"
#include<unordered_map>
#include<functional>
class ViewPort {
public:
	enum class CameraRotateAxis {
		X = 0,
		Y = 1,
		Z = 2,
	};
	ViewPort();
	ViewPort(const ViewPort&) = delete;
	void Init(int screenWidth, int screenHight, float fov, float near, float far);
	void Init(GLFWwindow* winPtr, float fov, float near, float far);
	void SetViewPort(int screenWidth, int screenHight, float fov, float near, float far);
	void SetViewPort(GLFWwindow* winPtr, float fov, float near, float far);
	void SetCameraPos(float X, float Y, float Z);
	void SetCameraRotate(CameraRotateAxis rotateAxis, float angle);
	inline glm::mat4 GetPMat() { return m_pMat; }
	inline glm::mat4 GetVMat() { return m_vMat; }
	inline int GetScreenWidth() { return m_screenWidth; };
	inline int GetScreenHeight() { return m_screenHeight; }
	std::tuple<float, float, float> GetCameraPos();	//返回x，y，z顺序的tuple
	std::tuple<float, float, float> GetCameraAngle();

private:
	int m_screenWidth;
	int m_screenHeight;
	float m_aspect;
	float m_fov;
	float m_near;
	float m_far;

	float m_cameraX;		//相机位置
	float m_cameraY;
	float m_cameraZ;
	
	float m_cameraPitch;	//相机欧拉角
	float m_cameraYaw;
	float m_cameraRoll;

	glm::mat4 m_pMat;
	glm::mat4 m_vMat;
};


#define KEYBOARDFUN_DECLARE(keyName) static void KeyBoardFun_##keyName(GLFWwindow* window, int key, int scancode, int action, int mods);
#define KEYBOARDFUN_DEFINE(keyName) void InputMng::KeyBoardFun_##keyName(GLFWwindow* window, int key, int scancode, int action, int mods)
#define KEYBOARDFUN_REGIST(keyName)	m_keyBoardFunMap[keyName] = InputMng::KeyBoardFun_##keyName;
class InputMng //键鼠操作
{
public:
	void RegistInputDevicesCallBakeFun(GLFWwindow* winPtr);
private:
	std::unordered_map<unsigned char, void(*)(GLFWwindow* window, int key, int scancode, int action, int mods)>	m_keyBoardFunMap;
	std::unordered_map<unsigned char, void(*)()>	m_MouseFunMap;
private:
	static void processNormalKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	KEYBOARDFUN_DECLARE(GLFW_KEY_D);
};



#endif