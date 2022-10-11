#include "Camera.h"

Camera::Camera(GLFWwindow* w) : mWindow(w) {
	mCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mViewMatrix = glm::mat4(1.0f);
	mEulerAngles = glm::vec2(-90.0f, 0.0f);
	glfwGetCursorPos(mWindow, &mLastMousePos.x, &mLastMousePos.y);
	mFirstMouse = true;
	mCameraSpeed = CAMERA_SPEED;
}

Camera::Camera(GLFWwindow* w, glm::vec3 pos) : mWindow(w) {
	mCameraPos = pos;
	mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mViewMatrix = glm::mat4(1.0f);
	mEulerAngles = glm::vec2(-90.0f, 0.0f);
	glfwGetCursorPos(mWindow, &mLastMousePos.x, &mLastMousePos.y);
	mFirstMouse = true;
	mCameraSpeed = CAMERA_SPEED;
}

Camera::Camera(GLFWwindow* w, glm::vec3 pos, glm::vec3 front) : mWindow(w) {
	mCameraPos = pos;
	mCameraFront = front;
	mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mViewMatrix = glm::mat4(1.0f);
	mEulerAngles = glm::vec2(-90.0f, 0.0f);
	glfwGetCursorPos(mWindow, &mLastMousePos.x, &mLastMousePos.y);
	mFirstMouse = true;
	mCameraSpeed = CAMERA_SPEED;
}

void Camera::Update(float deltaTime) {
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);

	double xoffset = (xpos - mLastMousePos.x) * CAMERA_SENSITIVITY;
	double yoffset = -(ypos - mLastMousePos.y) * CAMERA_SENSITIVITY;
	mLastMousePos = glm::vec2(xpos, ypos);

	mEulerAngles += glm::vec2(xoffset, yoffset);

	if (mEulerAngles.y > 89.0f)
		mEulerAngles.y = 89.0f;
	if (mEulerAngles.y < -89.0f)
		mEulerAngles.y = -89.0f;

	glm::vec3 dir = glm::vec3(0.0);
	dir.x = cos(glm::radians(mEulerAngles.x)) * cos(glm::radians(mEulerAngles.y));
	dir.y = sin(glm::radians(mEulerAngles.y));
	dir.z = sin(glm::radians(mEulerAngles.x)) * cos(glm::radians(mEulerAngles.y));
	mCameraFront = glm::normalize(dir);
	
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT)) {
		mCameraSpeed = 2.0f * CAMERA_SPEED;
	} else if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		mCameraSpeed = CAMERA_SPEED;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_W))
		mCameraPos += mCameraFront * mCameraSpeed * deltaTime;
	if (glfwGetKey(mWindow, GLFW_KEY_S))
		mCameraPos -= mCameraFront * mCameraSpeed * deltaTime;
	if (glfwGetKey(mWindow, GLFW_KEY_D))
		mCameraPos += glm::normalize(glm::cross(mCameraFront, mCameraUp)) * mCameraSpeed * deltaTime;
	if (glfwGetKey(mWindow, GLFW_KEY_A))
		mCameraPos -= glm::normalize(glm::cross(mCameraFront, mCameraUp)) * mCameraSpeed * deltaTime;
}