#pragma once
#include <SDL.h>

class Sound
{
private:
	float nowVolume = 0.f;

	SDL_AudioSpec wav_spec;
	SDL_AudioDeviceID dev;
	Uint8* wav_buffer;
	Uint32 wav_length;
	int recallAudio;
	int audioPlaySize;
public:
	Sound(const char * filename);
	~Sound();
	void Play();
	void Pause();
	void Stop();
	void SetInputMode(int reStart);	//�Ҹ� ��� ���
	void SetPlayLoop(int count);	//�ݺ� ȸ��

	/*���⿡ �ʿ��� Ȯ�� ���*/
	//��� ����, ������ ����, �ٸ� Ȯ����, �����
};