#include "Sound.h"

Sound::Sound()
{
	m_DirectSound = NULL;
	m_primaryBuffer = NULL;
	m_secondaryBuffer1 = NULL;
}

Sound::~Sound()
{
}

bool Sound::Initialize(HWND hwnd)
{
	//初始化DSound和主要缓冲区
	if (!InitializeDirectSound(hwnd)) return false;

	if (!LoadWaveFile("D:/IMG/Arrow.wav", &m_secondaryBuffer1)) return false;

	//if (!PlayWaveFile())return false;

	return true;
}

void Sound::ShuntDown()
{
	//释放缓冲区
	ShutdownWaveFile(&m_secondaryBuffer1);

	//关闭DSound
	ShutdownDirectSound();

	return;
}

bool Sound::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	//为默认音频设备初始化DSound交互指针
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//设置主要缓冲区协作等级,以让其可以被修改
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	//设置主要缓冲区
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//获取缓冲区对播放设备的控制权
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//配置主要缓冲区的音频格式
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Sound::ShutdownDirectSound()
{
	if (m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = NULL;
	}

	if (m_secondaryBuffer1)
	{
		m_secondaryBuffer1->Release();
		m_secondaryBuffer1 = NULL;
	}

	if (m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = NULL;
	}
}

//读取音频文件
bool Sound::LoadWaveFile(char* file, IDirectSoundBuffer8 ** buffer)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;

	//打开音频文件
	error = fopen_s(&filePtr, file, "rb");
	if (error != 0)
	{
		return false;
	}

	//读取音频头文件
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	//看块ID是否是RIFF
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	//确定是WAV格式文件
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	//查看副块ID
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	//确保音频格式为WAVE_FORMAT_PCM.
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	//确保音频的音轨为2
	if (waveFileHeader.numChannels != 2)
	{
		return false;
	}

	// 看音频文件是不是44.1HZ的
	/*if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}*/

	//确保音频文件是16位格式
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	//查看数据头
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	//设置第二缓冲区，用于对应该音频文件
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 11025;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	//设置第二缓冲区的相关数据
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//创建一个特殊设置过的临时缓冲区
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//测试并创建第二缓冲区
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*buffer);
	if (FAILED(result))
	{
		return false;
	}

	//释放临时缓冲区
	tempBuffer->Release();
	tempBuffer = 0;

	//移动至音频数据起始位置
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	//创建一个临时缓冲区除权音频数据
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		return false;
	}

	//读取音频文件到一个新创建的临时缓冲区
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	//文件读取完成后，关闭文件
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	//锁定第二缓冲区，然后往里面写入数据
	result = (*buffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	//拷贝音频数据至第二缓冲区
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	//在数据写入第二缓冲区后，解锁第二缓冲区
	result = (*buffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	//写入完成后释放音频数据
	delete[] waveData;
	waveData = 0;

	return true;

}

void Sound::ShutdownWaveFile(IDirectSoundBuffer8 ** buffer)
{
	//是放第二主缓冲区
	if (*buffer)
	{
		(*buffer)->Release();
		*buffer = 0;
	}
}

bool Sound::PlayWaveFile()
{
	HRESULT result;


	// Set position at the beginning of the sound buffer.
	result = m_secondaryBuffer1->SetCurrentPosition(0);
	if (FAILED(result))
	{
		return false;
	}

	// Set volume of the buffer to 100%.
	result = m_secondaryBuffer1->SetVolume(DSBVOLUME_MAX);
	if (FAILED(result))
	{
		return false;
	}

	// Play the contents of the secondary sound buffer.
	result = m_secondaryBuffer1->Play(0, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	return true;

}