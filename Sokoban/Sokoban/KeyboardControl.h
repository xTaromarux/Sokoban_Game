#pragma once
#include "Game.h"
#include "Components.h"
#include "TextureManager.h"
#include "Map.h"
#include "TileComponent.h"
#include "ComponentMove.h"

//* klasa pozwalajaca na kontrole postacia za pomoca klawiatury
//* z klasa bazowa Component
class KeyboardControl : public Component {
public:
	//* wskazniki do klas
	TransformComponent* transform;
	SpriteComponent* sprite;

	//* funkcja inicjalizacyjna, odwolujaca sie do klasy virtualnej bazowej
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	//* funkcja odsiwierzajaca klikniecie, odwolujaca sie do klasy virtualnej bazowej
	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			default:
				break;
			}
		}
	}
};
