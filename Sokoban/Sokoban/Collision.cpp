#include "Collision.h"
#include "Components.h"

//* funkcja definujaca kolizje
//* zawiera odwolania do zmiennych biblioteki graficznej dot. okna 
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

//* funkcja definujaca kolizje pomiedzy obiektami
//* zawiera odwolania do klasy definujacej obiekty kolizyjne
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		return true;
	}
	else
	{
		return false;
	}
}