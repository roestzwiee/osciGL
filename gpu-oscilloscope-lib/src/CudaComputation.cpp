#include "CudaComputation.h"

/**
 * Computation
 */
void CudaComputation::runCuda(cudaGraphicsResource** vbo_resource, float g_fAnim)
{
    // map OpenGL buffer object for writing from CUDA
    float4* devPtr;
    size_t num_bytes;

    checkCudaErrors(cudaGraphicsMapResources(1, vbo_resource, nullptr));
    checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void**)&devPtr, &num_bytes, *vbo_resource));

    launch_kernel(devPtr, mesh_width, mesh_height, g_fAnim); // g_fAnim

    checkCudaErrors(cudaGraphicsUnmapResources(1, vbo_resource, nullptr));
}