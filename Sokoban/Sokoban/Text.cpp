#include "Text.h"

Text::Text(Manager* man) : manager(man){}

Text::~Text(){}

//* funkcja tworzaca tekst, pobierajaca czcionke
//* id - przypisany numer 
//* path - sciezka pliku
//* fontSize - wielkosc czcionki
void Text::AddFonts(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* Text::GetFont(std::string id) {
	return fonts[id];
}