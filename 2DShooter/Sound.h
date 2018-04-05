#pragma once
#include "DirectX.h"

class  Sound
{
private:

	//音频文件的详细信息
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};



public:
	 Sound();
	 Sound(const Sound&);
	~ Sound();

	bool Initialize(HWND hwnd);
	void ShuntDown();

private:
	//对应的各个指针
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
	
	//初始化Dsound
	bool InitializeDirectSound(HWND hwnd);
	//关闭Dsound
	void ShutdownDirectSound();

	//读取音频文件
	bool LoadWaveFile(char* file, IDirectSoundBuffer8** buffer);
	//关闭音频文件
	void ShutdownWaveFile(IDirectSoundBuffer8** buffer);

	//播放音频文件
	bool PlayWaveFile();
};