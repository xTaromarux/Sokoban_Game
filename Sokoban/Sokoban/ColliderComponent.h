#pragma once
#include "string"
#include "SDL.h"
#include "ComponentSystem.h"
#include "TransformComponent.h"
#include "TextureManager.h"

//* klasa dzieki ktorej mozliwa jest kolizja obiektow
class ColliderComponent : public Component {
public:
	//* zienna dot. nazwy
	std::string tag;

	//* przywolanie zmiennych z biblioteki graficznej dot. tekstur
	SDL_Rect collider;
	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	//* wskaznik do klasu TransformComponent
	TransformComponent* transform;

	//* konstruktow z zawartoscia
	//* nazwa
	ColliderComponent(std::string t) {
		tag = t;
	}

	//* konstruktow z zawartoscia
	//* nazwa
	//* pozycja w osi x
	//* pozycja w osi y
	//* wielkosc 
	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	//* funkcja inicjalizacyjna, odwolujaca sie do klasy virtualnej bazowej
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

	}

	//* funkcja odsiwierzajaca kolizje, odwolujaca sie do klasy virtualnej bazowej
	void update() override {
		if (tag != "wall" && tag != "box") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

	}

	//* funkcja wyswietlajaca teksture, odwolujaca sie do klasy virtualnej bazowej
	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}

};