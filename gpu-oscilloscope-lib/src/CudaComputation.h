#ifndef H_CUDACOMPUTATION
#define H_CUDACOMPUTATION

#include "headers/IComputation.h"

extern "C"
void launch_kernel(float4 * pos, unsigned int mesh_width, unsigned int mesh_height, float time);

class CudaComputation : public IComputation
{
private:
    const unsigned int mesh_width = 128;
	const unsigned int mesh_height = 1024;
public:
	CudaComputation() {};

public:
	float* fetchInput() override { return nullptr; };
	void runCuda(cudaGraphicsResource** cuda_vbo_resource, float g_fAnim) override;

	unsigned int getCurrentMeshWidth() override
	{
		return mesh_width;
	}
	
	unsigned int getMeshWidth() override
	{
		return mesh_width;
	}

	unsigned int getMeshHeigh() override
	{
		return mesh_height;
	}

};

#endif