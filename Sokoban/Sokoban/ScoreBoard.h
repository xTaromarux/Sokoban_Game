#pragma once
#include <string>
#include <fstream>
#include "Menu.h"
#include "Components.h"
#include "SpriteComponent.h"

//* rozszerzenie dzialania szablonu Manager
extern Manager manager;

//* klasa zawierajaca dzialanie menu
//* z klasa bazowa Component 
class ScoreBoard : public Component {
public:

	//* wskazniki do klas
	SpriteComponent* sprite;
	Map* map;
	Game* game;
	Timer* mTimer;

	//* zmienna okreslajaca stan animacji obiektu
	bool Menuanimation = false;

	//* zmnienne do zapisu sciezki plikow
	std::string SB_file_players;
	std::string SB_file_time;

	ScoreBoard();
	ScoreBoard(Game* game);

	//* kolstruktor przypisujacy stan do zmiennej
	//* isAnimated - wskazanie stanu
	ScoreBoard(bool isAnimated) {
		Menuanimation = isAnimated;
	}
	~ScoreBoard();

	//* funkcja z zdefiniowanymi opcjami menu
	//* odwolania do obiektow
	void Options(Entity& H_S, Entity& Name, Entity& Time_H_S, Entity& Back);


	//* funkcja odswierzajaca stan opcji wybranej
	//* odwolania do obiektow oraz ich grupy
	void update(class std::vector<Entity*> Scoreboard_g, Entity& Back);

	//* funkcja ladujaca z plikow dane dot. tabeli wynikow
	//* SB_file_players -> sciezka pliku z nazwami graczy
	//* SB_file_time -> sciezka pliku z czasami graczy
	void loadScoreBoard(std::string SB_file_players, std::string SB_file_time);
};