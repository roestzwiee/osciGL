#pragma once

#include "GLManager.h"
#include <map>


std::map<GLFWwindow*, GLManager*> windowMap;

inline void AddCallbackMapping(GLFWwindow* window, GLManager* glManager)
{
    windowMap[window] = glManager;
}

inline void RemoveCallbackMapping(GLFWwindow* window)
{
    windowMap.erase(window);
}

/*
 * Generic callbacks
 */
inline void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

inline void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}

/*
 * User Callbacks
 */
inline void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    windowMap[window]->getControls()->keyboard(key, scancode, action, mods);
}

inline void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    windowMap[window]->getControls()->mouse(button, action, mods);
}

inline void MotionCallback(GLFWwindow* window, double x, double y)
{
    windowMap[window]->getControls()->motion(x, y);
}

inline void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    windowMap[window]->getControls()->scroll(xoffset, yoffset);
}
