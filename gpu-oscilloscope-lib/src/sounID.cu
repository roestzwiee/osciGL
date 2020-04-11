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

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void poo()
{

    // const int NUMPTS = 44100 * 10;              // 10 seconds
    // int sampleRate = 44100;
    // short int waveIn[NUMPTS];                   // 'short int' is a 16-bit type; I request 16-bit samples below
				// 								// for 8-bit capture, you'd use 'unsigned char' or 'BYTE' 8-bit types
    //
    // HWAVEIN     hWaveIn;
    // WAVEHDR     WaveInHdr;
    // MMRESULT    result;
    //
    // // Specify recording parameters
    // WAVEFORMATEX pFormat;
    // pFormat.wFormatTag = WAVE_FORMAT_PCM;       // simple, uncompressed format
    // pFormat.nChannels = 1;                      //  1=mono, 2=stereo
    // pFormat.nSamplesPerSec = sampleRate;        // 44100
    // pFormat.nAvgBytesPerSec = sampleRate * 2;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
    // pFormat.nBlockAlign = 2;                    // = n.Channels * wBitsPerSample/8
    // pFormat.wBitsPerSample = 16;                //  16 for high quality, 8 for telephone-grade
    // pFormat.cbSize = 0;
    //
    // result = waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat,
    //     0L, 0L, WAVE_FORMAT_DIRECT);
    // if (result)
    // {
    //     char fault[256];
    //     waveInGetErrorText(result, fault, 256);
    //     printf("Failed to open waveform input device.");
    //     return;
    // }
    //
    // // Set up and prepare header for input
    // WaveInHdr.lpData = (LPSTR)waveIn;
    // WaveInHdr.dwBufferLength = NUMPTS * 2;
    // WaveInHdr.dwBytesRecorded = 0;
    // WaveInHdr.dwUser = 0L;
    // WaveInHdr.dwFlags = 0L;
    // WaveInHdr.dwLoops = 0L;
    // waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    //
    // // Insert a wave input buffer
    // result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    // if (result)
    // {
    //     printf("Failed to read block from device");
    //     return;
    // }
    //
    //
    // // Commence sampling input
    // result = waveInStart(hWaveIn);
    // if (result)
    // {
    //     printf("Failed to start recording");
    //     return;
    // }
    //
    //
    // // Wait until finished recording
    // do {
    //
    //     printf("Recording...\n");
    //
    // } while (waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING);
    //
    // waveInClose(hWaveIn);
    //
    // printf("Recording finished");

}


///////////////////////////////////////////////////////////////////////////////
//! Simple kernel to modify vertex positions in sine wave pattern
//! @param data  data in global memory
///////////////////////////////////////////////////////////////////////////////
__global__ void simple_vbo_kernel(float4* pos, unsigned int width, unsigned int height, float time)
{
    unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

    // calculate uv coordinates
    float u = x / (float)width;
    float v = y / (float)height;
    u = u * 2.0f - 1.0f;
    v = v * 2.0f - 1.0f;

    // calculate simple sine wave pattern
    float freq = 4.0f;
    float w = sinf(u * freq + time) * cosf(v * freq + time) * 0.5f;

    // write output vertex
    pos[y * width + x] = make_float4(u, w, v, 1.0f);
}

extern "C"
void launch_kernel(float4 * pos, unsigned int mesh_width,
    unsigned int mesh_height, float time)
{
    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
    simple_vbo_kernel << < grid, block >> > (pos, mesh_width, mesh_height, time);
}