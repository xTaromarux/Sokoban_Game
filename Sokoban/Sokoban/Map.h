#pragma once
#include <string> 

//* klasa generujaca mape wyswietlana
class Map {
public:
	Map();
	~Map();

	//* sciezka wczytywanego pliku z tablica
	std::string map_file;

	//* funkcja wczytujaca plik i rozpoznajaca elementy wyswietlane
	//* path - sciezka pliku
	//* sizeX - definiowanie wilkosci w osi x
	//* sizeY - definiowanie wilkosci w osi y
	void LoadMap(std::string path, int sizeX, int sizeY);

	//* funkcja tworzaca kafelek wyswietlany
	//* id - przypisany numer
	//* x - pozycja osi x
	//* y - pozycja osi y
	void AddTile(int id, int x, int y);

private:
};