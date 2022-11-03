#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

const float CAMERA_SPEED = 5.0f;
const float CAMERA_SENSITIVITY = 0.1f;

/*

	Camera Class:

	- Responsible for updating the view matrix
	- By default is looking down the positive x-axis

*/

class Camera {
public:
	Camera(GLFWwindow*);
	Camera(GLFWwindow*, glm::vec3);
	Camera(GLFWwindow*, glm::vec3, glm::vec2);
	
	void Update(float);
	
	glm::mat4 GetViewMatrix() { return glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp); }
	glm::vec3 GetCameraPos() { return mCameraPos; }
	glm::vec3 GetCameraDir() { return mCameraFront; }
private:
	float mCameraSpeed;

	glm::mat4 mViewMatrix;

	glm::vec3 mCameraPos;	// Camera Position
	glm::vec3 mCameraFront;	// Camera Direction
	glm::vec3 mCameraUp;	// Absolute Up

	glm::vec2 mEulerAngles; // Yaw, Pitch

	glm::dvec2 mLastMousePos;
	bool mFirstMouse;

	GLFWwindow* mWindow;
};
#endif