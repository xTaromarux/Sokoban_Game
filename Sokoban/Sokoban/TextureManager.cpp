#include "TextureManager.h"

//* funkcje ladujace tekstury z zewnetrznej bibioteki graficznej 
SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}
SDL_Texture* toTexture(SDL_Surface* surface, int destroySurface)
{
	SDL_Texture* texture;

	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

	if (destroySurface)
	{
		SDL_FreeSurface(surface);
	}

	return texture;
}

// funkcja rysujaca tekture
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}