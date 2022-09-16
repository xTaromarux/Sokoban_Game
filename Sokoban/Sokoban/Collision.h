#pragma once
#include "SDL.h"
class ColliderComponent;

//* klasa dot. kolizji i jej obliczania
class Collision
{
public:
	//* funkcja z wzorcem kolizji w oknie
	//* zawiera odwolania do zmiennych biblioteki graficznej dot. okna 
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	
	//* funkcja z wzorcem kolizji pomiedzy obiektami
	//* zawiera odwolania do klasy definujacej obiekty kolizyjne
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
