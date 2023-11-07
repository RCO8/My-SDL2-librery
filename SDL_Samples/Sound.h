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
	void Stop();
	void SetInputMode(int reStart);	//소리 재생 모드
	void SetPlayLoop(int count);	//반복 회수

	/*여기에 필요한 확장 요소*/
	//배속 증감, 음높이 증감, 다른 확장자, 역재생
};

class Music
{
private:
	Mix_Music* music;
public:
	Music(const char* filename);
	~Music();

	void Play(int loop);
private:
	void Pause();
	void Stop();
	void SetMode();
	void SetVolume();
	void SetFrame();
	void SetSpeed();
	void MovePosition();
	void Reward();
};