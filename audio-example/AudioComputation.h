#pragma once
#include "headers\IComputation.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern "C"
void launch_kernel_convert(short * input, float4 * pos, unsigned int mesh_width, unsigned int mesh_height, float time);

class AudioComputation : public IComputation
{
private:
	const unsigned int mesh_width = 88200;
	const unsigned int mesh_height = 1;

public:
	AudioComputation();
	~AudioComputation();

private:
	// recording parameters
	const int sampleRate = 88200;
	short * waveIn;
	
	HWAVEIN     hWaveIn;
	WAVEHDR     WaveInHdr;
	MMRESULT    result;
	WAVEFORMATEX pFormat;

	// cuda variables
	short * d_waveIn;
	size_t bufferSize;
	

	void initialize();
	
public:
	float* fetchInput() override;	
	void runCuda(cudaGraphicsResource** cuda_vbo_resource, float g_fAnim) override;

	unsigned int getMeshWidth() override
	{
		return mesh_width;
	}

	unsigned int getMeshHeigh() override
	{
		return mesh_height;
	}
};

