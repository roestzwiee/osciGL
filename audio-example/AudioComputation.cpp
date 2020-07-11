#include "AudioComputation.h"
#include "math.h"

AudioComputation::AudioComputation()
{
    bufferSize = sampleRate * sizeof(short);

    waveIn = new short[sampleRate];
	checkCudaErrors(cudaMalloc(&d_waveIn, bufferSize));

	// TODO: should a test mode be implemented?
	// for(int i = 0; i < sampleRate; i++)
	// {
	//        waveIn[i] = i*i;
	// }
	
    initialize();
}

AudioComputation::~AudioComputation()
{
    checkCudaErrors(cudaFree(d_waveIn));
    delete(waveIn);
}

float* AudioComputation::fetchInput()
{
    // Return data, that is stored in a buffer for beeing processed inside a CUDA Kernel 
	// TODO: review architecture and interface
    return nullptr;
}

void AudioComputation::runCuda(cudaGraphicsResource** vbo_resource, float g_fAnim)
{

    // Call a kernel to create a displayable float4* array from the previously fetched input...

    checkCudaErrors(cudaMemcpy(d_waveIn, waveIn, bufferSize, cudaMemcpyHostToDevice));
	
    // map OpenGL buffer object for writing from CUDA
    float4* devPtr;
    size_t num_bytes;

    checkCudaErrors(cudaGraphicsMapResources(1, vbo_resource, nullptr));
    checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void**)&devPtr, &num_bytes, *vbo_resource));

    launch_kernel_convert(d_waveIn, devPtr, mesh_width, mesh_height, g_fAnim);

    checkCudaErrors(cudaGraphicsUnmapResources(1, vbo_resource, nullptr));
	
}

void AudioComputation::initialize()
{
    // Specify recording parameters
    pFormat.wFormatTag = WAVE_FORMAT_PCM;       // simple, uncompressed format
    pFormat.nChannels = 1;                      // 1=mono, 2=stereo
    pFormat.nSamplesPerSec = sampleRate;        // 44100
    pFormat.nAvgBytesPerSec = sampleRate * 2;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
    pFormat.nBlockAlign = 2;                    // = n.Channels * wBitsPerSample/8
    pFormat.wBitsPerSample = 16;                // 16 for high quality, 8 for telephone-grade
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
        return;
    }

    // Wait until finished recording
    do {

        printf("Recording...\n");
        result = waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    } while (result == WAVERR_STILLPLAYING);

	if(result != MMSYSERR_NOERROR)
	{
        printf("Failed to record");
        return;
	}

	waveInClose(hWaveIn);

    printf("Recording finished\n");

}

