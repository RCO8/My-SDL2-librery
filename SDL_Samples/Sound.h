#pragma once
#include <fstream>
using namespace std;

class Sound
{
private:
	char* fileName;	//파일 이름
	float nowVolume;
public:
	bool mute = true;

	Sound();
	~Sound();
	void Play();
	void Pause();
	void Stop();
	void SetVolume();

	float GetVolume() const { return nowVolume; };
};

Sound::Sound()
{
	//사운드 불러오기 및 생성
}

Sound::~Sound()
{
	//사운드 제거
}

void Sound::Play() {};
void Sound::Pause() {};
void Sound::Stop() {};
void Sound::SetVolume() {};