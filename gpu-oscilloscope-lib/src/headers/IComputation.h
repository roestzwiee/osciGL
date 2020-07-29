#ifndef H_IComputation
#define H_IComputation

#include <helper_gl.h>
#include <GLFW/glfw3.h>

// includes, cuda
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

// Utilities and timing functions
#include <helper_functions.h>    // includes cuda.h and cuda_runtime_api.h

#include <helper_cuda.h>


class IComputation
{

public:
	virtual float* fetchInput() = 0;
	virtual void runCuda(cudaGraphicsResource** cuda_vbo_resource, float g_fAnim) = 0;

	/**
	 * Used to actually draw.
	 */
	virtual unsigned int getCurrentMeshWidth() = 0;


	/**
	 * Used for allocations.
	 */
	virtual unsigned int getMeshWidth() = 0;
	virtual unsigned int getMeshHeigh() = 0;
	
};

#endif