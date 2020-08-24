#ifndef H_CUDACOMPUTATION
#define H_CUDACOMPUTATION

#include "../Headers/ICudaInput.h"

extern "C"
void launch_kernel(float4 * pos, unsigned int mesh_width, unsigned int mesh_height, float time);

class ExampleInput : public ICudaInput
{
private:
    const unsigned int mesh_width = 128;
	const unsigned int mesh_height = 1024;
public:
	ExampleInput() = default;

	void computeInput(cudaGraphicsResource** cuda_vbo_resource, float g_fAnim) override
	{
		// map OpenGL buffer object for writing from CUDA
		float4* devPtr;
		size_t num_bytes;

		checkCudaErrors(cudaGraphicsMapResources(1, cuda_vbo_resource, nullptr));
		checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void**)&devPtr, &num_bytes, *cuda_vbo_resource));

		launch_kernel(devPtr, mesh_width, mesh_height, g_fAnim); // windowActiveTime

		checkCudaErrors(cudaGraphicsUnmapResources(1, cuda_vbo_resource, nullptr));
	};

	unsigned int getCurrentMeshWidth() override
	{
		return mesh_width;
	}
	
	unsigned int getMeshWidth() override
	{
		return mesh_width;
	}

	unsigned int getMeshHeight() override
	{
		return mesh_height;
	}

};

#endif