#ifndef H_CUDACOMPUTATION
#define H_CUDACOMPUTATION


#include <helper_gl.h>
#include <GL/freeglut.h>

// includes, cuda
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

// Utilities and timing functions
#include <helper_functions.h>    // includes cuda.h and cuda_runtime_api.h

#include <helper_cuda.h>

//#include "GlutManager.h"

extern "C"
void launch_kernel(float4 * pos, unsigned int mesh_width, unsigned int mesh_height, float time);

class CudaComputation
{
public:
	CudaComputation() {};

public:
	void runCuda(cudaGraphicsResource** cuda_vbo_resource, float g_fAnim);

	const unsigned int mesh_width = 128;
	const unsigned int mesh_height = 1024;

};

#endif