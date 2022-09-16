#pragma once
#include <string>
#include "ComponentSystem.h"
#include "Components.h"
#include "SpriteComponent.h"

//* rozszerzenie dzialania szablonu Manager
extern Manager manager;

//* klasa zawierajaca dzialanie menu
//* z klasa bazowa Component 
class Menu : public Component {
public:
	
	//* wskazniki do klas
	SpriteComponent* sprite;
	Map* map;
	Game* game;
	Timer* mTimer;

	//* zmienan wskazujaca stan animacji obiektu 
	bool Menuanimation = false;

	Menu();
	Menu( Game* game);

	//* kolstruktor przypisujacy stan do zmiennej
	//* isAnimated - wskazanie stanu
	Menu(bool isAnimated) {
		Menuanimation = isAnimated;
	}
	~Menu();

	//* funkcja z zdefiniowanymi opcjami menu
	//* odwolania do obiektow
	void Options(Entity& Start, Entity& ScoreB, Entity& Quit);


	//* funkcja odswierzajaca stan opcji wybranej
	//* odwolania do obiektow oraz ich grupy
	void update(bool mapstate, class std::vector<Entity*> menu, Entity& Start, Entity& ScoreB, Entity& Quit, Entity& Player);
};