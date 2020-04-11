#ifndef H_CUDACOMPUTATION
#define H_CUDACOMPUTATION

#include "GlutManager.h"

extern "C"
void launch_kernel(float4 * pos, unsigned int mesh_width, unsigned int mesh_height, float time);

class CudaComputation
{

public:
	void runCuda(cudaGraphicsResource** cuda_vbo_resource, float g_fAnim);

	
};

#endif