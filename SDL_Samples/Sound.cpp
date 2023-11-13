#include "Sound.h"

Sound::Sound(const char* filename)
{
	//사운드 불러오기 및 생성
	if (SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL)
	{
		SDL_Log("Failed to load WAV file : %s\n", SDL_GetError());
		this->~Sound();
	}
	dev = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
	if (dev == NULL)
	{
		SDL_Log("Failed to open audio device: %s\n", SDL_GetError());
		this->~Sound();
	}

	recallAudio = SDL_QueueAudio(dev, wav_buffer, wav_length);
	if (recallAudio != 0)
	{
		SDL_Log("Failed to queue audio: %s\n", SDL_GetError());
		this->~Sound();
	}

	audioPlaySize = SDL_GetQueuedAudioSize(dev);
}

Sound::~Sound()
{
	//사운드 제거
	//Mix_FreeMusic();
	//Mix_CloseAudio();
	SDL_CloseAudioDevice(dev);
	SDL_FreeWAV(wav_buffer);
	SDL_AudioQuit();
}

void Sound::Play()
{
	//소리가 재생상태가 아니라면 실행
	if (SDL_GetQueuedAudioSize(dev) <= audioPlaySize)
		SDL_PauseAudioDevice(dev, 0);	//사운드 한번만 재생
	if(SDL_GetQueuedAudioSize(dev) == 0)
		recallAudio = SDL_QueueAudio(dev, wav_buffer, wav_length);
}
void Sound::Pause()
{
	SDL_PauseAudioDevice(dev, 1);
}

Music::Music(const char* filename)
{
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("Failed to initialize SDL_mixer: %s", Mix_GetError());
		this->~Music();
	}
	music = Mix_LoadMUS(filename);

	volume = Mix_Volume(2, 128);
	SDL_Log("Volume : %d", volume);
}
Music::~Music()
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	Mix_Quit();
}
void Music::Play(int loop)
{
	//일시정지면 다시 이어서
	if (Mix_PausedMusic())
		Mix_ResumeMusic();
	else //다끝날때 까지 처음부터 재생거부
		if(!Mix_PlayingMusic())
			Mix_PlayMusic(music, loop);
}
void Music::Pause()
{
	Mix_PauseMusic();
}
void Music::Stop()
{
	Mix_HaltMusic();
}

void Music::ChangeVolume(int val)
{
	if(volume <= 128 && volume >= 0)
		volume += val;
	Mix_VolumeMusic(volume);
	//SDL_Log("Volume : %d", volume);
}
void Music::SetVolume(int val)
{
	if (volume >= 128 && volume < 0)
		return;
	Mix_Volume(2, val);
}

void Music::SetTone(int val)
{

}