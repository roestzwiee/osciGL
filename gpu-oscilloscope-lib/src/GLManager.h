//#pragma once
#ifndef H_GLUTMANAGER
#define H_GLUTMANAGER

#include "headers/IComputation.h"
#include "headers/IUserControls.h"


#define MAX(a,b) ((a > b) ? a : b)

#define REFRESH_DELAY     10 //ms

 /**
  * GL Inits
  */
const unsigned int window_width = 512;
const unsigned int window_height = 512;

/*
 * Set externals
 */
void setControls(IUserControls * controls);
void setComputationCore(IComputation * computationCoree);

/*
 * Forward declarations for GLFW Callbacks
 */
void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseCallback(GLFWwindow* window, int button, int action, int mods);
void MotionCallback(GLFWwindow* window, double x, double y);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void WindowResizeCallback(GLFWwindow* window, int width, int height);
void ErrorCallback(int error, const char* description);

class GLManager
{
public:
	GLManager() {};

	void initialize(int argc, char* argv[]);
private:
	
	/*
	 * Common initialization
	 */
	bool initGL(int* argc, char** argv);
	void createVBO(GLuint* vbo, cudaGraphicsResource** vbo_res, unsigned int vbo_res_flags);

	/*
	 * Render
	 */
	void DisplayCallback();
	
	/*
	 * Computation
	 */
	void runCudaInternal(struct cudaGraphicsResource** vbo_resource);
	void computeFPS();
	
	/*
	 * Cleanups
	 */
	void deleteVBO(GLuint* vbo, cudaGraphicsResource* vbo_res);
	void cleanup(GLFWwindow *);
};

#endif
