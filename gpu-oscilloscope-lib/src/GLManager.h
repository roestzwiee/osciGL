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
 * Forward declarations for GLUT Callbacks
 */
void DisplayCallback();
void KeyboardCallback(unsigned char key, int x, int y);
void MouseCallback(int button, int state, int x, int y);
void MotionCallback(int x, int y);
void TimerCallback(int value);

// new: 




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

	/**
	 * Callbacks
	 */
	void ErrorCallback(int error, const char* description);
	
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
