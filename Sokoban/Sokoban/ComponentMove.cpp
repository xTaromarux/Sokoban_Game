#include "ComponentMove.h"
#include "Components.h"

extern Manager manager;

ComponentMove::ComponentMove(Game* game, Timer* mTimer) {
	textUI = new Text(&manager);

	this->game = game;
	this->mTimer = mTimer;
}
ComponentMove::~ComponentMove() {
	delete textUI;
}


//* funkcja odswierzajaca kolizje pomiedzy obiektami
//* zawierajaca odwolania do obiektow oraz grup z obiektami
void ComponentMove::update(int counter, class Entity& Player, class std::vector<Entity *> &boxcolliders, class std::vector<Entity*> &points, class std::vector<Entity*> &colliders, class Entity& ui, class Entity& End_game_0, class Entity& End_game_1, class Entity& End_game_2) {

	SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = Player.getComponent<TransformComponent>().position;

	manager.refresh();

	manager.update();

	//*kolizja gracz - obiekt
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, playerCol))
		{
			Player.getComponent<TransformComponent>().position = playerPos;
		}

		for (auto& s : boxcolliders)
		{
			SDL_Rect sCol = s->getComponent<ColliderComponent>().collider;
			Vector2D sPos = s->getComponent<TransformComponent>().position;

			//* kolizja gracz - sciana
			if (Collision::AABB(sCol, playerCol))
			{

				//* od gory
				if (
					playerCol.y >= sCol.y + sCol.h * 9 / 10 &&
					sCol.x + sCol.w > playerCol.x &&
					playerCol.x + playerCol.w >= sCol.x)
				{
					s->getComponent<TransformComponent>().position.y = sPos.y - 3;
					s->getComponent<ColliderComponent>().collider.y = sCol.y - 3;
				}
				//* od dolu
				else if (
					playerCol.y + playerCol.h * 9 / 10 <= sCol.y &&
					sCol.x + sCol.w > playerCol.x &&
					playerCol.x + playerCol.w >= sCol.x)
				{
					s->getComponent<TransformComponent>().position.y = sPos.y + 3;
					s->getComponent<ColliderComponent>().collider.y = sCol.y + 3;
				}
				//* od lewej  
				else if (
					playerCol.x >= sCol.x &&
					sCol.y + sCol.h >= playerCol.y &&
					playerCol.y + playerCol.h * 9 / 10 >= sCol.y)
				{
					s->getComponent<TransformComponent>().position.x = sPos.x - 3;
					s->getComponent<ColliderComponent>().collider.x = sCol.x - 3;
				}
				//* od prawej
				else if (
					playerCol.x <= sCol.x &&
					sCol.y + sCol.h >= playerCol.y &&
					playerCol.y + playerCol.h * 9 / 10 >= sCol.y)
				{

					s->getComponent<TransformComponent>().position.x = sPos.x + 3;
					s->getComponent<ColliderComponent>().collider.x = sCol.x + 3;
				}
			}
			//* kolizja gracz - skrzynia
			else if (Collision::AABB(sCol, cCol))
			{
				//* od gory
				if (
					cCol.y >= sCol.y + sCol.h * 9 / 10 &&
					sCol.x + sCol.w > cCol.x &&
					cCol.x + cCol.w >= sCol.x)
				{
					Player.getComponent<TransformComponent>().position = playerPos;

					s->getComponent<TransformComponent>().position.y = sPos.y - 3;
					s->getComponent<ColliderComponent>().collider.y = sCol.y - 3;
				}
				//* od dolu
				else if (
					cCol.y + cCol.h * 9 / 10 <= sCol.y &&
					sCol.x + sCol.w > cCol.x &&
					cCol.x + cCol.w >= sCol.x)
				{
					Player.getComponent<TransformComponent>().position = playerPos;

					s->getComponent<TransformComponent>().position.y = sPos.y + 3;
					s->getComponent<ColliderComponent>().collider.y = sCol.y + 3;
				}
				//* od lewej
				else if (
					cCol.x >= sCol.x + 5 &&
					sCol.y + sCol.h >= cCol.y &&
					cCol.y + cCol.h * 9 / 10 >= sCol.y)
				{
					Player.getComponent<TransformComponent>().position = playerPos;

					s->getComponent<TransformComponent>().position.x = sPos.x - 3;
					s->getComponent<ColliderComponent>().collider.x = sCol.x - 3;
				}
				//* od prawej
				else if (
					cCol.x + 5 <= sCol.x &&
					sCol.y + sCol.h >= cCol.y &&
					cCol.y + cCol.h * 9 / 10 >= sCol.y)
				{
					Player.getComponent<TransformComponent>().position = playerPos;

					s->getComponent<TransformComponent>().position.x = sPos.x + 3;
					s->getComponent<ColliderComponent>().collider.x = sCol.x + 3;
				}
			}
		}
		//*kolizja gracz - punkt
		for (auto& p : points)
		{
			SDL_Rect sCol = p->getComponent<ColliderComponent>().collider;
			Vector2D sPos = p->getComponent<TransformComponent>().position;
			counter = points.size();
			if (Collision::AABB(sCol, playerCol))
			{

				//* od gory
				if (
					playerCol.y >= sCol.y + sCol.h * 9 / 10 &&
					sCol.x + sCol.w > playerCol.x &&
					playerCol.x + playerCol.w >= sCol.x)
				{
					counter = counter - 1;
					p->destroy();
				}
				//* od dolu
				else if (
					playerCol.y + playerCol.h * 9 / 10 <= sCol.y &&
					sCol.x + sCol.w > playerCol.x &&
					playerCol.x + playerCol.w >= sCol.x)
				{
					counter = counter - 1;
					p->destroy();
				}
				//* od lewej 
				else if (
					playerCol.x >= sCol.x &&
					sCol.y + sCol.h >= playerCol.y &&
					playerCol.y + playerCol.h * 9 / 10 >= sCol.y)
				{
					counter = counter - 1;
					p->destroy();
				}
				//* od prawej
				else if (
					playerCol.x <= sCol.x &&
					sCol.y + sCol.h >= playerCol.y &&
					playerCol.y + playerCol.h * 9 / 10 >= sCol.y)
				{
					counter = counter - 1;
					p->destroy();


				}
			}
			if (counter == 0) {
				game->bool_counter_state(true);
			}
		}
	}
}