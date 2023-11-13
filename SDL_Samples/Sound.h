#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class Sound
{
private:
	float nowVolume = 0.f;

	SDL_AudioSpec wav_spec;
	SDL_AudioDeviceID dev;
	SDL_AudioStream* wav_stream;
	Uint8* wav_buffer;
	Uint32 wav_length;
	int recallAudio;
	int audioPlaySize;
public:
	Sound(const char * filename);
	~Sound();
	void Play();
	void Pause();
};

class Music
{
private:
	const int Channel = 2;
	int volume;
	Mix_Music* music;
public:
	Music(const char* filename);
	~Music();

	void Play(int loop = 1);
	void Pause();
	void Stop();
	void ChangeVolume(int val);
	void SetVolume(int val);
private:
	void SetTone(int val);	//톤 증감
	void SetMode();
	void SetSpeed();	//속도 증감
	void MovePosition();	//구간 이동
	void Reward();		//되감기
};