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
	m_cameraPitch = 0.0f;
	m_cameraRoll = 0.0f;
	m_cameraYaw = 0.0f;
	m_moveSpeed = 1.0f;
	m_pMat = glm::mat4(0.0f);
	m_vMat = glm::mat4(0.0f);
}

void ViewPort::SetViewPort(int screenWidth, int screenHight, float fov, float _near, float _far) {
	m_screenHeight = screenWidth;
	m_screenWidth = screenWidth;
	m_fov = fov;
	m_aspect = (float)(screenWidth / screenWidth);
	m_near = _near;
	m_far = _far;
	m_pMat = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void ViewPort::Init(int screenWidth, int screenHight, float fov, float _near, float _far) {
	SetViewPort(screenWidth, screenHight, fov, _near, _far);
}
//顺序旋转感觉有问题，后面在验证
void ViewPort::SetCameraPos(float X, float Y, float Z) {
	m_cameraX = X;
	m_cameraY = Y;
	m_cameraZ = Z;
	m_vMat = glm::mat4(1.0f);
	//按zyx顺序旋转一遍，然后在移动
	m_vMat = glm::rotate(m_vMat, glm::radians(m_cameraYaw), glm::vec3(0.0f, 0.0f, 1.0f));
	m_vMat = glm::rotate(m_vMat, glm::radians(m_cameraRoll), glm::vec3(0.0f, 1.0f, 0.0f));
	m_vMat = glm::rotate(m_vMat, glm::radians(m_cameraPitch), glm::vec3(1.0f, 0.0f, 1.0f));
	m_vMat = glm::translate(m_vMat, glm::vec3(-m_cameraX, -m_cameraY, -m_cameraZ));
}
//顺序旋转感觉有问题，后面在验证
void ViewPort::SetCameraRotate(CameraRotateAxis rotateAxis, float angle) {
	if (rotateAxis == CameraRotateAxis::X) {
		m_cameraPitch += angle;
	}
	else if (rotateAxis == CameraRotateAxis::Y) {
		m_cameraRoll += angle;
	}
	else if (rotateAxis == CameraRotateAxis::Z) {
		m_cameraYaw += angle;
	}
	m_vMat = glm::mat4(1.0f);
	//按zyx顺序旋转一遍，然后在移动
	m_vMat = glm::rotate(m_vMat, glm::radians(m_cameraYaw), glm::vec3(0.0f, 0.0f, 1.0f));
	m_vMat = glm::rotate(m_vMat, glm::radians(m_cameraRoll), glm::vec3(0.0f, 1.0f, 0.0f));
	m_vMat = glm::rotate(m_vMat, glm::radians(m_cameraPitch), glm::vec3(1.0f, 0.0f, 0.0f));
	m_vMat = glm::translate(m_vMat, glm::vec3(-m_cameraX, -m_cameraY, -m_cameraZ));
	return;
}

void ViewPort::SetViewPort(GLFWwindow* winPtr, float fov, float _near, float _far) {
	assert(winPtr == nullptr && "ViewPort Get Null GLFWindow Ptr");
	glfwGetFramebufferSize(winPtr, &m_screenWidth, &m_screenHeight);
	SetViewPort(m_screenWidth, m_screenHeight, fov, _near, _far);
}
void ViewPort::Init(GLFWwindow* winPtr, float fov, float _near, float _far) {
	SetViewPort(winPtr, fov, _near, _far);
}

std::tuple<float, float, float> ViewPort::GetCameraPos() {
	return std::make_tuple(m_cameraX,m_cameraY,m_cameraZ);
}
std::tuple<float, float, float> ViewPort::GetCameraAngle() {
	return std::make_tuple(m_cameraPitch, m_cameraRoll, m_cameraYaw);
}

void InputMng::RegistInputDevicesCallBakeFun(GLFWwindow* winPtr) {
	glfwSetKeyCallback(winPtr, processNormalKeys);
	KEYBOARDFUN_REGIST(GLFW_KEY_S);
	KEYBOARDFUN_REGIST(GLFW_KEY_W);
	KEYBOARDFUN_REGIST(GLFW_KEY_A);
	KEYBOARDFUN_REGIST(GLFW_KEY_D);
	
}
void InputMng::processNormalKeys(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto& mng = Singleton<InputMng>::GetInstanceRef();
	auto Ret = mng.m_keyBoardFunMap.find(key);
	if (Ret != mng.m_keyBoardFunMap.end()) {
		auto fun = mng.m_keyBoardFunMap[key];
		(mng.*fun)(window, key, scancode, action, mods);
	}
}

KEYBOARDFUN_DEFINE(GLFW_KEY_S) {
	auto& viewport = Singleton<ViewPort>::GetInstanceRef();
	auto pos = viewport.GetCameraPos();
	auto x = std::get<0>(pos);
	auto y = std::get<1>(pos);
	auto z = std::get<2>(pos);
	viewport.SetCameraPos(x, y, z + viewport.GetCameraMoveSpeed());
}
KEYBOARDFUN_DEFINE(GLFW_KEY_W) {
	auto& viewport = Singleton<ViewPort>::GetInstanceRef();
	auto pos = viewport.GetCameraPos();
	auto x = std::get<0>(pos);
	auto y = std::get<1>(pos);
	auto z = std::get<2>(pos);
	viewport.SetCameraPos(x , y, z - viewport.GetCameraMoveSpeed());
}

KEYBOARDFUN_DEFINE(GLFW_KEY_A) {
	auto& viewport = Singleton<ViewPort>::GetInstanceRef();
	auto pos = viewport.GetCameraPos();
	auto x = std::get<0>(pos);
	auto y = std::get<1>(pos);
	auto z = std::get<2>(pos);
	viewport.SetCameraPos(x - viewport.GetCameraMoveSpeed(), y, z);
}
KEYBOARDFUN_DEFINE(GLFW_KEY_D) {
	auto& viewport = Singleton<ViewPort>::GetInstanceRef();
	auto pos = viewport.GetCameraPos();
	auto x = std::get<0>(pos);
	auto y = std::get<1>(pos);
	auto z = std::get<2>(pos);
	viewport.SetCameraPos(x + viewport.GetCameraMoveSpeed(), y, z);
}