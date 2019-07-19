#ifndef AUDIO_H

#define AUDIO_H
#include <iostream>

using namespace std;
#include <SDL.h>
#include <SDL_audio.h>

class Audio {
public:
	~Audio() {};
	void load(const char* filename);
	void play();
	void stopAudio();
	
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceId;
};
#endif // AUDIO_H
