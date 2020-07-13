////////////////////////////////////////////////////////////////////////////
//
// Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
//
// Please refer to the NVIDIA end user license agreement (EULA) associated
// with this source code for terms and conditions that govern your use of
// this software. Any use, reproduction, disclosure, or distribution of
// this software and related documentation outside the terms of the EULA
// is strictly prohibited.
//
////////////////////////////////////////////////////////////////////////////

/* sounID project which demonstrates the basics on how to setup a project
* example application.
* Host code.
*/
#include "device_launch_parameters.h"
#include "device_functions.h"


// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// includes CUDA
#include <cuda_runtime.h>

// includes, project
#include <helper_cuda.h>
#include <helper_functions.h> // helper functions for SDK examples


///////////////////////////////////////////////////////////////////////////////
//! Simple kernel to modify vertex positions in sine wave pattern
//! @param data  data in global memory
///////////////////////////////////////////////////////////////////////////////
__global__ void simple_vbo_kernel_convert(short* input, float4* pos, unsigned int width, unsigned int height, float time)
{	
    unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    // calculate uv coordinates
    float u = x / (float)width;
    float v;
    u = u * 2.0f - 1.0f;
    v = input[y * width + x];// / (float)2; // this call lets the kernel crash!
    
    // write output vertex
    pos[y * width + x] = make_float4(u, v / SHRT_MAX, 0.0f, 1.0f);
}

extern "C"
void launch_kernel_convert(short* input, float4 * pos, unsigned int mesh_width,
    unsigned int mesh_height, float time)
{
	// TODO: find a better way to limit the framerate...
    //Sleep(5);
	
    dim3 block(8, 1, 1);

    const int gridSizeX = mesh_width / block.x;
    const int gridSizeY = mesh_height / block.y;

	// TODO: Add further validation!
	if(gridSizeX == 0 || gridSizeY == 0)
	{
        printf("Error on grid size!\n");
        return;
	}
	
    dim3 grid(gridSizeX, gridSizeY, 1);


    checkCudaErrors(cudaGetLastError());
	
    simple_vbo_kernel_convert <<< grid, block >>> (input, pos, mesh_width, mesh_height, time);

    checkCudaErrors(cudaPeekAtLastError());
	
}