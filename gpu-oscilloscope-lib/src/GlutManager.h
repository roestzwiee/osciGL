//#pragma once
#ifndef H_GLUTMANAGER
#define H_GLUTMANAGER

#include <helper_gl.h>
#include <GL/freeglut.h>

// includes, cuda
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

// Utilities and timing functions
#include <helper_functions.h>    // includes cuda.h and cuda_runtime_api.h

#include <helper_cuda.h>

#define MAX(a,b) ((a > b) ? a : b)

#define REFRESH_DELAY     10 //ms

 /**
  * GL Inits
  */
const unsigned int window_width = 512;
const unsigned int window_height = 512;
const unsigned int mesh_width = 128;
const unsigned int mesh_height = 1024;

/*
 * Common initialization
 */
void initialize(int argc, char* argv[]);
bool initGL(int* argc, char** argv);
void createVBO(GLuint* vbo, cudaGraphicsResource** vbo_res, unsigned int vbo_res_flags);

/*
 * Computation
 */
void runCudaInternal(struct cudaGraphicsResource** vbo_resource);
void computeFPS();

/*
 * Forward declarations for GLUT Callbacks
 */
void DisplayCallback();
void KeyboardCallback(unsigned char key, int x, int y);
void MouseCallback(int button, int state, int x, int y);
void MotionCallback(int x, int y);
void TimerCallback(int value);

/*
 * Cleanups
 */
void deleteVBO(GLuint* vbo, cudaGraphicsResource* vbo_res);
void cleanup();

#endif
