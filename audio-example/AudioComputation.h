#pragma once
#include "headers\IComputation.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class AudioComputation : public IComputation
{
private:
	const unsigned int mesh_width = 44100;
	const unsigned int mesh_height = 1;

public:
	AudioComputation();
	~AudioComputation();

private:
	const int sampleRate = 44100;
	short int *waveIn;
	
	HWAVEIN     hWaveIn;
	WAVEHDR     WaveInHdr;
	MMRESULT    result;
	WAVEFORMATEX pFormat;
	void initialize();

	
	void fetchData();
	
public:
	void fetchInput(GLuint* vbo) override;	
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

