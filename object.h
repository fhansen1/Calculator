#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>

class Object {
private:
	SDL_Rect dest;
	SDL_Texture* tex;
public:
	Object() {}
	SDL_Rect getDest() const { return dest; }
	void setDest(float x, float y, float w, float h);
	void setImage(string filename, SDL_Renderer* ren);
	SDL_Texture* getTex() const { return tex; }
};
#endif //OBJECT_H