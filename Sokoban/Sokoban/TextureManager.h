#pragma once
#include "Game.h"

//* klasa zarzadajaca generowaniem tekstur
class TextureManager {
public:
	
	//* funkcje ladujace tekstury z zewnetrznej bibioteki graficznej 
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* toTexture(SDL_Surface* surface, int destroySurface);
	
	//* funkcja rysujaca tekture
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);

};