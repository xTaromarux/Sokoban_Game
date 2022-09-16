#pragma once
#include "Collision.h"
#include "ComponentSystem.h"
#include  "Timer.h"
#include  "UI.h"
#include  "Game.h"

extern Manager manager;

//* klasa dot. poruszania sie obiektow 
class ComponentMove{
public:
	Timer* mTimer;
	Game* game;
	Text* textUI;
	
	ComponentMove(Game* game, Timer* mTimer);

	~ComponentMove();

	//* funkcja odswierzajaca
	//* zawierajaca odwolania do obiektow oraz grup z obiektami
	void update(int counter, class Entity& Player, class std::vector<Entity *> &boxcolliders, class std::vector<Entity*> &points, class std::vector<Entity*> &colliders, class Entity& ui, class Entity& End_game_0, class Entity& End_game_1, class Entity& End_game_2);


private:
};
