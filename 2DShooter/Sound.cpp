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
	//��ʼ��DSound����Ҫ������
	if (!InitializeDirectSound(hwnd)) return false;

	if (!LoadWaveFile("D:/IMG/Arrow.wav", &m_secondaryBuffer1)) return false;

	//if (!PlayWaveFile())return false;

	return true;
}

void Sound::ShuntDown()
{
	//�ͷŻ�����
	ShutdownWaveFile(&m_secondaryBuffer1);

	//�ر�DSound
	ShutdownDirectSound();

	return;
}

bool Sound::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	//ΪĬ����Ƶ�豸��ʼ��DSound����ָ��
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//������Ҫ������Э���ȼ�,��������Ա��޸�
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	//������Ҫ������
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//��ȡ�������Բ����豸�Ŀ���Ȩ
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//������Ҫ����������Ƶ��ʽ
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

//��ȡ��Ƶ�ļ�
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

	//����Ƶ�ļ�
	error = fopen_s(&filePtr, file, "rb");
	if (error != 0)
	{
		return false;
	}

	//��ȡ��Ƶͷ�ļ�
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	//����ID�Ƿ���RIFF
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	//ȷ����WAV��ʽ�ļ�
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	//�鿴����ID
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	//ȷ����Ƶ��ʽΪWAVE_FORMAT_PCM.
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	//ȷ����Ƶ������Ϊ2
	if (waveFileHeader.numChannels != 2)
	{
		return false;
	}

	// ����Ƶ�ļ��ǲ���44.1HZ��
	/*if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}*/

	//ȷ����Ƶ�ļ���16λ��ʽ
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	//�鿴����ͷ
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	//���õڶ������������ڶ�Ӧ����Ƶ�ļ�
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 11025;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	//���õڶ����������������
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//����һ���������ù�����ʱ������
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//���Բ������ڶ�������
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*buffer);
	if (FAILED(result))
	{
		return false;
	}

	//�ͷ���ʱ������
	tempBuffer->Release();
	tempBuffer = 0;

	//�ƶ�����Ƶ������ʼλ��
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	//����һ����ʱ��������Ȩ��Ƶ����
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		return false;
	}

	//��ȡ��Ƶ�ļ���һ���´�������ʱ������
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	//�ļ���ȡ��ɺ󣬹ر��ļ�
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	//�����ڶ���������Ȼ��������д������
	result = (*buffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	//������Ƶ�������ڶ�������
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	//������д��ڶ��������󣬽����ڶ�������
	result = (*buffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	//д����ɺ��ͷ���Ƶ����
	delete[] waveData;
	waveData = 0;

	return true;

}

void Sound::ShutdownWaveFile(IDirectSoundBuffer8 ** buffer)
{
	//�Ƿŵڶ���������
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