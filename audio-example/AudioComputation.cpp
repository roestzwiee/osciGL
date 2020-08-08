#include "AudioComputation.h"

AudioComputation::AudioComputation()
{
	bufferSize = sampleRate * sizeof(short);

	waveIn = new short[sampleRate];
	checkCudaErrors(cudaMalloc(&d_waveIn, bufferSize));

	initializeAudioStream();
}

AudioComputation::~AudioComputation()
{
	checkCudaErrors(cudaFree(d_waveIn));

	closeAudioStream();

	delete waveIn;
}

void AudioComputation::computeInput(cudaGraphicsResource** vbo_resource, float g_fAnim)
{
	/*
	 * What happens here could be improved by not using Cuda.
	 *
	 * Instead the fetched Audio Input could just be written on the gl buffer and be processed by OpenGL shader.
	 * 
	 * However, this is used as a demonstration for fully computed input.
	 *
	 * The GlManager currently has no support for shader anyway.
	 */
	
	fetchAudioStream();

	float4* devPtr;
	size_t num_bytes;

	checkCudaErrors(cudaMemcpy(d_waveIn, waveIn, bufferSize, cudaMemcpyHostToDevice));

	checkCudaErrors(cudaGraphicsMapResources(1, vbo_resource, nullptr));
	checkCudaErrors(cudaGraphicsResourceGetMappedPointer(reinterpret_cast<void**>(&devPtr), &num_bytes, *vbo_resource));

	launch_kernel_convert(d_waveIn, devPtr, getCurrentMeshWidth(), mesh_height, g_fAnim);

	checkCudaErrors(cudaGraphicsUnmapResources(1, vbo_resource, nullptr));
}

void AudioComputation::initializeAudioStream()
{
	// Specify recording parameters
	pFormat.wFormatTag = WAVE_FORMAT_PCM;		// simple, uncompressed format
	pFormat.nChannels = 1;						// 1=mono, 2=stereo
	pFormat.nSamplesPerSec = 44100;				// 44100
	pFormat.nAvgBytesPerSec = sampleRate * 2;	// = nSamplesPerSec * n.Channels * wBitsPerSample/8
	pFormat.nBlockAlign = 2;					// = n.Channels * wBitsPerSample/8
	pFormat.wBitsPerSample = 16;				// 16 for high quality, 8 for telephone-grade
	pFormat.cbSize = 0;

	result = waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat,
	                    0L, 0L, WAVE_FORMAT_DIRECT);
	if (result)
	{
		char fault[256];
		waveInGetErrorText(result, (LPWSTR)fault, 256);
		printf("Failed to open waveform input device.");
		return;
	}

	// Set up and prepare header for input
	WaveInHdr.lpData = (LPSTR)waveIn;
	WaveInHdr.dwBufferLength = sampleRate * 2;
	WaveInHdr.dwBytesRecorded = 0;
	WaveInHdr.dwUser = 0L;
	WaveInHdr.dwFlags = 0L;
	WaveInHdr.dwLoops = 0L;
	waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

	// Insert a wave input buffer
	result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	if (result)
	{
		printf("Failed to read block from device");
		return;
	}


	// Commence sampling input
	result = waveInStart(hWaveIn);
	if (result)
	{
		printf("Failed to start recording");
	}
}

void AudioComputation::fetchAudioStream()
{
	// Wait until finished recording
	if (result == WAVERR_STILLPLAYING)
	{
		printf("Recording...\n");
		result = waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	}

	if (result != MMSYSERR_NOERROR)
	{
		printf("Failed to record");
	}
}

void AudioComputation::closeAudioStream() const
{
	waveInClose(hWaveIn);

	printf("Recording finished\n");
}
