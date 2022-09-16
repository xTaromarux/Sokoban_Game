#pragma once
#include "SDL_ttf.h"
#include <map>
#include <string>
#include "ComponentSystem.h"

//* klasa inicjalizujaca tekt
class Text {
public:
	Text(Manager* man);
	~Text();

	//* funkcja tworzaca tekst, pobierajaca czcionke
	//* id - przypisany numer 
	//* path - sciezka pliku
	//* fontSize - wielkosc czcionki
	void AddFonts(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

private:
	Manager* manager;
	//* mapa z czcionkami
	std::map<std::string, TTF_Font*> fonts;
};