#pragma once
#include "DirectX.h"

class  Sound
{
private:

	//��Ƶ�ļ�����ϸ��Ϣ
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
	//��Ӧ�ĸ���ָ��
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
	
	//��ʼ��Dsound
	bool InitializeDirectSound(HWND hwnd);
	//�ر�Dsound
	void ShutdownDirectSound();

	//��ȡ��Ƶ�ļ�
	bool LoadWaveFile(char* file, IDirectSoundBuffer8** buffer);
	//�ر���Ƶ�ļ�
	void ShutdownWaveFile(IDirectSoundBuffer8** buffer);

	//������Ƶ�ļ�
	bool PlayWaveFile();
};