//#pragma once
#ifndef H_GLUTMANAGER
#define H_GLUTMANAGER

#include "headers/ICudaInput.h"
#include "headers/IUserControls.h"

constexpr auto REFRESH_DELAY = 10; //ms;

class GLManager
{
public:

	GLManager() = default;

private:
	/*
	 * The C++ implementation of User Input Callbacks
	 */
	IUserControls* controls;

	/*
	 * The C++ implementation for Computation
	 */
	ICudaInput* cudaInput;

	/**
	 * GL Inits
	 */
	const unsigned int windowWidth = 640;
	const unsigned int windowHeight = 480;

	/**
	 * CUDA Variables
	 */
	GLuint vbo;
	struct cudaGraphicsResource* cuda_vbo_resource;
	StopWatchInterface* timer = nullptr;

	/**
	 * TheTime
	 */
	float windowActiveTime = 0.0;

	/**
	 * Auto verification code
	 */
	int fpsCount = 0; // FPS count for averaging
	int fpsLimit = 1; // FPS limit for sampling
	float avgFPS = 0.0f;
	unsigned int frameCount = 0;

	/**
	 * GLFW Window
	 */
	GLFWwindow* window;

public:

	/*
	 * Set required control structures
	 */
	void setControls(IUserControls* controls);
	void setComputationCore(ICudaInput* cudaInput);

	/*
	 * Initialize and start
	 */
	void initialize(int argc, char* argv[]);

	IUserControls* getControls() { return controls; }

private:

	/*
	 * Common initialization
	 */
	bool initGL(int* argc, char** argv);
	void createVBO(GLuint* vbo, cudaGraphicsResource** vbo_res, unsigned int vbo_res_flags) const;

	/*
	 * Render
	 */
	void render();

	/*
	 * Computation
	 */
	void runComputeInputInternal(struct cudaGraphicsResource** vbo_resource) const;
	void computeFPS();

	/*
	 * Cleanups
	 */
	static void deleteVBO(GLuint* vbo, cudaGraphicsResource* vbo_res);
	void cleanup(GLFWwindow*);
};

#endif
