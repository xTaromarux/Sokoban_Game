#include "Map.h"
#include "Game.h"
#include <fstream>
#include "Components.h"
#include "TileComponent.h"


extern Manager manager;

Map::Map() {} 

Map::~Map() {}

//* funkcja wczytujaca plik i rozpoznajaca elementy wyswietlane
//* path - sciezka pliku
//* sizeX - definiowanie wilkosci w osi x
//* sizeY - definiowanie wilkosci w osi y
void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	Map::map_file = path;
	std::fstream map;
	map.open(map_file);

	for (int row = 0; row < sizeY; row++) {
		for (int column = 0; column < sizeX; column++) {
			map.get(tile);
			//* rozpoznanie obiektu - sciana
			 if (tile == '1') {
				AddTile(atoi(&tile), row * 100, column * 100);
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("wall", column * 100, row * 100, 100);
				tcol.addGroup(Game::groupColliders);
				map.ignore();
			}
			 //* rozpoznanie obiektu - skrzynia
			else if (tile == '2') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<TransformComponent>(column * 100, row * 100, 100, 100, 1);
				tcol.addComponent<SpriteComponent>("Assets/box.png", false);
				tcol.addComponent<ColliderComponent>("box", column * 101, row * 101, 90);
				tcol.addGroup(Game::groupBoxColliders);
				tcol.addGroup(Game::groupColliders);

				map.ignore();
			}
			 //* rozpoznanie obiektu - punkt
			else if (tile == '3') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<TransformComponent>(column * 100, row * 100, 100, 100, 1);
				tcol.addComponent<SpriteComponent>("Assets/point.png", false);
				tcol.addComponent<ColliderComponent>("point", column * 101, row * 101, 90);
				tcol.addGroup(Game::groupPoints);
				tcol.addGroup(Game::groupColliders);
				map.ignore();
			}
			 //* rozpoznanie obiektu - pusta komurka
			else {
				AddTile(atoi(&tile), row * 100, column * 100);
				map.ignore();
			}
		}
	}
	map.ignore();

}

//* funkcja tworzaca kafelek wyswietlany
//* id - przypisany numer
//* x - pozycja osi x
//* y - pozycja osi y
void Map::AddTile(int id, int y, int x) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 100, 100, id);
	tile.addGroup(Game::groupMap);
}
