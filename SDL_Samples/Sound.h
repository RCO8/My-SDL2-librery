#pragma once
#include <fstream>
using namespace std;

class Sound
{
private:
	char* fileName;	//���� �̸�
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
	//���� �ҷ����� �� ����
}

Sound::~Sound()
{
	//���� ����
}

void Sound::Play() {};
void Sound::Pause() {};
void Sound::Stop() {};
void Sound::SetVolume() {};