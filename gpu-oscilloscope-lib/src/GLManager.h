//#pragma once
#ifndef H_GLUTMANAGER
#define H_GLUTMANAGER

#include "headers/IComputation.h"
#include "headers/IUserControls.h"


#define MAX(a,b) ((a > b) ? a : b)

#define REFRESH_DELAY     10 //ms

// /*
//  * Forward declarations for GLFW Callbacks
//  */
// void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
// void MouseCallback(GLFWwindow* window, int button, int action, int mods);
// void MotionCallback(GLFWwindow* window, double x, double y);
// void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// void WindowResizeCallback(GLFWwindow* window, int width, int height);
// void ErrorCallback(int error, const char* description);

class GLManager
{
public:
	GLManager() {};

	/*
	 * Initialize and start
	 */
	void initialize(int argc, char* argv[]);

	/*
	 * Set required control structures
	 */
	void setControls(IUserControls * controls);
	void setComputationCore(IComputation * computationCoree);

	IUserControls* getControls() { return controls; }
	
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

	/*
	 * The C++ implementation of User Input Callbacks
	 */
	IUserControls* controls;

	/*
	 * The C++ implementation for Computation
	 */
	IComputation* computationCore;

	/**
	 * GL Inits
	 */
	const unsigned int window_width = 512;
	const unsigned int window_height = 512;

	/**
	 * CUDA Variables
	 */
	GLuint vbo;
	struct cudaGraphicsResource* cuda_vbo_resource;
	StopWatchInterface* timer = NULL;

	/**
	 * TheTime
	 */
	float g_fAnim = 0.0;

	/**
	 * Auto verification code
	 */
	int fpsCount = 0;        // FPS count for averaging
	int fpsLimit = 1;        // FPS limit for sampling
	int g_Index = 0;
	float avgFPS = 0.0f;
	unsigned int frameCount = 0;
	unsigned int g_TotalErrors = 0;
	bool g_bQAReadback = false;

	/**
	 * GLFW Window
	 */
	GLFWwindow* window;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;
};

#endif
