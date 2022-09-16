#pragma once
#include "ComponentSystem.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>






//* klasa ustawiajaca polozenie tekstu w oknie
class UI : public Component
{
public:
	UI() {};
	//* konstruktor z polozeniem tekstu
	//* xpos - polozenie na osi x
	//* ypos - polozenie na osi y
	//* text - tekst wyswietlany
	//* font - czcionka
	//* color - kolor czcionki
	UI(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) 
		: Text(text), Font(font), Color(color) {
		pos.x = xpos;
		pos.y = ypos;

		SetText(Text, Font);
	}
	~UI() {}

	//* funkcja ustawiajaca tekst
	//* text - tekst 
	//* font - czcionka
	void SetText(std::string text, std::string font) {
		Free_All();
		surface = TTF_RenderText_Blended(Game::textUI->GetFont(font), text.c_str(), Color);
		Texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_QueryTexture(Texture, nullptr, nullptr, &pos.w, &pos.h);
	}

	//* funkcja wyswietlajaca teksture, odwolujaca sie do klasy virtualnej bazowej
	void draw() override {
		SDL_RenderCopy(Game::renderer, Texture, nullptr, &pos);
	}

	//* funkcja zwalniajaca pamiec 
	void Free_All()
	{
		if (surface == NULL) {
			//*cout << "Text surface already free'd" << endl;
		}
		else {
			SDL_FreeSurface(surface);
			surface = NULL;
			//*cout << "Free'd surface \n";
		}

		if (Texture == NULL) {
			//*cout << "Could not free memory for text \"" << text << "\". Error from SDL is: " << TTF_GetError() << endl;
		}
		else {
			SDL_DestroyTexture(Texture);
			Texture = NULL;
		}
	}

private:

	//* inicjalizacja zmiennych dla tektu
	std::string Font;
	std::string Text;
	SDL_Color Color;
	SDL_Texture* Texture = NULL;
	SDL_Surface* surface = NULL;
	SDL_Rect pos;

};
