#include "GLManager.h"
#include "UserInterfaces/CallbackMapper.h"
#include "AdditionalRenderer/CoordinateSystemRenderSettings.h"
#include "AdditionalRenderer/CoordinateSystemRender.h"
#include "UserInterfaces/ConsoleView.h"
#include <thread>

void GLManager::setComputationCore(ICudaInput* cudaInput)
{
	this->cudaInput = cudaInput;
}

void GLManager::setControls(IUserControls* controls)
{
	this->userControls = controls;
}

void GLManager::initialize(int argc, char* argv[])
{
	sdkCreateTimer(&timer);

	int devID = findCudaDevice(argc, (const char**)argv);

	if (false == initGL(&argc, argv))
	{
		printf("Cannot initialize GL");
		return;
	}

	createVBO(&vbo, &cuda_vbo_resource, cudaGraphicsMapFlagsWriteDiscard);

	consoleView = new ConsoleView(userControls);
	consoleView->runMultiThread();
		
	
	while (!glfwWindowShouldClose(window) && userControls && cudaInput)
	{
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	consoleView->stopMultiThread();
	cleanup(window);
}

bool GLManager::initGL(int* argc, char** argv)
{
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: Cannot initialize GLFW.");
		fflush(stderr);
		return false;
	}

	window = glfwCreateWindow(windowWidth, windowHeight, "Scope", nullptr, nullptr);
	if (!window)
	{
		fprintf(stderr, "ERROR: Cannot create OpenGL window.");
		fflush(stderr);
		return false;
	}
	glfwMakeContextCurrent(window);

	AddCallbackMapping(window, this);

	glfwSetErrorCallback(ErrorCallback);
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

	glfwSetKeyCallback(window, KeyboardCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);
	glfwSetCursorPosCallback(window, MotionCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	if (!isGLVersionSupported(4, 0))
	{
		fprintf(stderr, "ERROR: Support for necessary OpenGL extensions missing.");
		fflush(stderr);
		return false;
	}


	// default initialization
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glDisable(GL_DEPTH_TEST);

	// viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// fixme
	gluPerspective(90.0, static_cast<GLfloat>(windowWidth) / static_cast<GLfloat>(windowHeight), 0.001, 10.0);

	SDK_CHECK_ERROR_GL();

	return true;
}

void GLManager::createVBO(GLuint* vbo, struct cudaGraphicsResource** vbo_res,
                          unsigned int vbo_res_flags) const
{
	assert(vbo);

	// create buffer object
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);

	// initialize buffer object
	const unsigned int size = cudaInput->getMeshWidth() * cudaInput->getMeshHeight() * 4 * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// register this buffer object with CUDA
	checkCudaErrors(cudaGraphicsGLRegisterBuffer(vbo_res, *vbo, vbo_res_flags));

	SDK_CHECK_ERROR_GL();
}

void GLManager::render()
{
	sdkStartTimer(&timer);

	// run CUDA kernel to generate vertex positions
	runComputeInputInternal(&cuda_vbo_resource);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(userControls->getTranslationInX(), userControls->getTranslationInY(), userControls->getTranslationInZ());
	glRotated(userControls->getRotationInX(), 1.0, 0.0, 0.0);
	glRotated(userControls->getRotationInY(), 0.0, 1.0, 0.0);

	// render from the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexPointer(4, GL_FLOAT, 0, nullptr);

	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(0.0, 0.0, 1.0);
	glDrawArrays(GL_POINTS, 0, cudaInput->getCurrentMeshWidth() * cudaInput->getMeshHeight());
	glDisableClientState(GL_VERTEX_ARRAY);

	windowActiveTime += 0.01f;

	/*
	 * TODO: Create interfaces e.g. IPlotAddition to manage loading different options during runtime.
	 */
	CoordinateSystemRenderSettings renderSettings(window, userControls);

	if(renderSettings.getDrawCoordinateSystem())
	{
		CoordinateSystemRender coordinateSystemRender(&renderSettings);
		coordinateSystemRender.render();
	}
	
	sdkStopTimer(&timer);
	computeFPS();
}

void GLManager::runComputeInputInternal(cudaGraphicsResource** vbo_resource) const
{
	cudaInput->computeInput(vbo_resource, windowActiveTime);
}

void GLManager::computeFPS()
{
	frameCount++;
	fpsCount++;

	if (fpsCount == fpsLimit)
	{
		avgFPS = 1.f / (sdkGetAverageTimerValue(&timer) / 1000.f);
		fpsCount = 0;
		fpsLimit = static_cast<int>(MAX(avgFPS, 1.f));

		sdkResetTimer(&timer);
	}

	char fps[256];
	sprintf_s(fps, "osciGL Beta: %3.1f fps (Max 100Hz)", avgFPS);
	glfwSetWindowTitle(window, fps);
}

void GLManager::cleanup(GLFWwindow*)
{
	sdkDeleteTimer(&timer);

	if (vbo)
	{
		deleteVBO(&vbo, cuda_vbo_resource);
	}

	glfwTerminate();

	RemoveCallbackMapping(window);

	delete consoleView;
	delete userControls;
	delete cudaInput;
}

void GLManager::deleteVBO(GLuint* vbo, cudaGraphicsResource* vbo_res)
{
	// unregister this buffer object with CUDA
	checkCudaErrors(cudaGraphicsUnregisterResource(vbo_res));

	glBindBuffer(1, *vbo);
	glDeleteBuffers(1, vbo);

	*vbo = 0;
}
