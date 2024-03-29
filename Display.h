#ifndef DISPLAY_H
#define DISPLAY_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

/*

	Display Jobs:

	- Initialize GLFW
	- Create a window
	- Initialize GLAD

*/

class Display {
public:
	Display(std::string);
	Display(int, int, std::string);
	~Display();

	GLFWwindow* GetWindow() { return mWindow; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	std::string GetTitle() { return mTitle; }
private:
	void LogContextInfo();
	
	GLFWwindow* mWindow;
	int mWidth, mHeight;
	std::string mTitle;
};
#endif