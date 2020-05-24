#include "AudioComputation.h"

AudioComputation::AudioComputation()
{
    waveIn = new short[sampleRate];
}

AudioComputation::~AudioComputation()
{
    delete(waveIn);
}

void AudioComputation::fetchInput(GLuint* vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    // initialize buffer object
    const unsigned int size = getMeshWidth() * getMeshHeigh() * 4 * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, size, waveIn, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AudioComputation::runCuda(cudaGraphicsResource** vbo_resource, float g_fAnim)
{


	
}

void AudioComputation::initialize()
{
    // Specify recording parameters
    pFormat.wFormatTag = WAVE_FORMAT_PCM;       // simple, uncompressed format
    pFormat.nChannels = 1;                      //  1=mono, 2=stereo
    pFormat.nSamplesPerSec = sampleRate;        // 44100
    pFormat.nAvgBytesPerSec = sampleRate * 2;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
    pFormat.nBlockAlign = 2;                    // = n.Channels * wBitsPerSample/8
    pFormat.wBitsPerSample = 16;                //  16 for high quality, 8 for telephone-grade
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

    } while (waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING);

    waveInClose(hWaveIn);

    printf("Recording finished");
}


void AudioComputation::fetchData()
{
	
}

