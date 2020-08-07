#include "GLManager.h"

/**
 * CUDA Variables
 */
GLuint vbo;
struct cudaGraphicsResource* cuda_vbo_resource;
void* d_vbo_buffer = NULL;
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
/*
 * The C++ implementation of Callbacks
 */
IUserControls * controls;

/*
 * The C++ implementation for Computation
 */
IComputation* computationCore;

/*
 * Outsourced functionality
 */

void setComputationCore(IComputation* computationCoree)
{
    computationCore = computationCoree;
}

void setControls(IUserControls* controlss)
{
    controls = controlss;
}

/*
 * Callback implementation
 */
void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    controls->keyboard(key, scancode, action, mods);
}

void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    controls->mouse(button, action, mods);
}

void MotionCallback(GLFWwindow* window, double x, double y)
{
    controls->motion(x, y);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    controls->scroll(xoffset, yoffset);
}


/**
 * Initialization Routines
 */
void GLManager::initialize(int argc, char* argv[])
{	
    // Create the CUTIL timer
    sdkCreateTimer(&timer);

    // use command-line specified CUDA device, otherwise use device with highest Gflops/s
    int devID = findCudaDevice(argc, (const char**)argv);

    // First initialize OpenGL context, so we can properly set the GL for CUDA.
    // This is necessary in order to achieve optimal performance with OpenGL/CUDA interop.
    if (false == initGL(&argc, argv))
    {
        printf("Cannot initialize GL");
        //return -1;
    }

    createVBO(&vbo, &cuda_vbo_resource, cudaGraphicsMapFlagsWriteDiscard);

    // start entering the compute and render main loop
    while (!glfwWindowShouldClose(window) && controls && computationCore)
    {
        DisplayCallback();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(window);
}

bool GLManager::initGL(int* argc, char** argv)
{
    // initialize necessary OpenGL extensions
	if (!glfwInit())
    {
        fprintf(stderr, "ERROR: Cannot initialize GLFW.");
        fflush(stderr);
        return false;
    }
	
    window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: Cannot create OpenGL window.");
        fflush(stderr);
        return false;
    }
    glfwMakeContextCurrent(window);

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
    glViewport(0, 0, window_width, window_height);

    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // fixme
	gluPerspective(60.0, (GLfloat)window_width / (GLfloat)window_height, 0.001, 10.0);

	
    SDK_CHECK_ERROR_GL();

    return true;
}

void GLManager::createVBO(GLuint* vbo, struct cudaGraphicsResource** vbo_res,
    unsigned int vbo_res_flags)
{
    assert(vbo);

    // create buffer object
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    // initialize buffer object
    const unsigned int size = computationCore->getMeshWidth() * computationCore->getMeshHeigh() * 4 * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // register this buffer object with CUDA
    checkCudaErrors(cudaGraphicsGLRegisterBuffer(vbo_res, *vbo, vbo_res_flags));

    SDK_CHECK_ERROR_GL();
}

/**
 * Computation
 */
void GLManager::runCudaInternal(cudaGraphicsResource** vbo_resource)
{
	// TODO: OpenGL calls cannot be invoked from an other class. create kind of a hook therefore!
    float* input = computationCore->fetchInput();
	if(input != nullptr)
    { 
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    // initialize buffer object
	    const unsigned int size = computationCore->getMeshWidth() * computationCore->getCurrentMeshWidth() * 4 * sizeof(float);
	    glBufferData(GL_ARRAY_BUFFER, size, input, GL_DYNAMIC_DRAW);

	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
    computationCore->runCuda(vbo_resource, g_fAnim);
}

void GLManager::computeFPS()
{
    frameCount++;
    fpsCount++;

    if (fpsCount == fpsLimit)
    {
        avgFPS = 1.f / (sdkGetAverageTimerValue(&timer) / 1000.f);
        fpsCount = 0;
        fpsLimit = (int)MAX(avgFPS, 1.f);

        sdkResetTimer(&timer);
    }

    char fps[256];
    sprintf_s(fps, "osciGL Beta: %3.1f fps (Max 100Hz)", avgFPS);
    glfwSetWindowTitle(window, fps);
}

/**
 * Callbacks
 */
void GLManager::DisplayCallback()
{
    sdkStartTimer(&timer);
    
    // run CUDA kernel to generate vertex positions
    runCudaInternal(&cuda_vbo_resource);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(controls->getTranslationInX(), controls->getTranslationInY(), controls->getTranslationInZ());
    glRotated(controls->getRotationInX(), 1.0, 0.0, 0.0);
    glRotated(controls->getRotationInY(), 0.0, 1.0, 0.0);
	
    // render from the vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 0.0, 0.0);	
    glDrawArrays(GL_POINTS, 0, computationCore->getCurrentMeshWidth() * computationCore->getMeshHeigh());
    glDisableClientState(GL_VERTEX_ARRAY);
    
    g_fAnim += 0.01f;
    
    sdkStopTimer(&timer);
    computeFPS();
}

/**
 * Cleanups
 */
void GLManager::cleanup(GLFWwindow*)
{
	
    sdkDeleteTimer(&timer);

    if (vbo)
    {
        deleteVBO(&vbo, cuda_vbo_resource);
    }

    glfwTerminate();
	
    delete controls;
    delete computationCore;

}

void GLManager::deleteVBO(GLuint* vbo, cudaGraphicsResource* vbo_res)
{
    // unregister this buffer object with CUDA
    checkCudaErrors(cudaGraphicsUnregisterResource(vbo_res));

    glBindBuffer(1, *vbo);
    glDeleteBuffers(1, vbo);

    *vbo = 0;
}