#include "audio.h"
/*
	Loads an audio file an intiliazes the device.
*/
void Audio::load(const char* filename) {
	SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}
/*
	If audio is already running it will be cleared from the audio queue.
	The audio is then queued and played.
*/
void Audio::play() {
	
	SDL_ClearQueuedAudio(deviceId);
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);

}
/*
	Stops the playback.
*/
void Audio::stopAudio(){
	SDL_CloseAudioDevice(deviceId);
}

