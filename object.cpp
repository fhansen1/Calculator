#include "object.h"
/*
	Sets rectangle size and placement
*/
void Object::setDest(float x, float y, float w, float h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}
/*
	Creates a texture from an image which can be rendered later
*/
void Object::setImage(string filename, SDL_Renderer* ren) {
	SDL_Surface* surf = IMG_Load(filename.c_str());
	tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
}