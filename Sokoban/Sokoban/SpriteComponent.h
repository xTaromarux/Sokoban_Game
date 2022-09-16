#pragma once
#include "TransformComponent.h"
#include "TextureManager.h"
#include "Animation.h"
#include "SDL.h"
#include <map>

//* klasa pozwalajaca wyswietlac postac wraz z animacja ruchu
class SpriteComponent : public Component {
private:
	//* wskaznik do klasy
	TransformComponent* transform;
	
	//* odwolania do zmiennych dot. tekstur z biblioteki graficznej
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	//* zmienna wskazujaca na stan animacji
	bool animated = false;

	//* zmienne wskazujace na ilosc klatek oraz ich predkosc wyswietlania
	int frames = 1;
	int speed = 100;

public:
	//* zmienna indeksu
	int animIndex = 0;
	
	//* mapa zbierajaca stany animacji
	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent();
	
	//* konstruktor ustawiajacy teksture
	//* path - sciezka pliku
	SpriteComponent(const char* path) {
		setTexture(path);
	}

	//* konstruktor tworzacy stany animacji wraz z dodaniem do mapy
	//* path - sciezka pliku
	//* isAnimated - wskazanie stanu animacji
	SpriteComponent(const char* path, bool isAnimated) {
		animated = isAnimated;
		Animation idle = Animation(0, 1, 100);
		Animation walk = Animation(1, 8, 100);
		Animation change = Animation(0, 2, 250);
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Change", change);

		play("Idle");

		setTexture(path);
	}

	//* dekonstruktor niszczacy teksture
	~SpriteComponent() {}

	//* funkcja ustawiajaca teksture
	//* path - sciezka pliku
	void setTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	//* funkcja inicjalizacyjna, odwolujaca sie do klasy virtualnej bazowej
	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	//* funkcja odsiwierzajaca animacje, odwolujaca sie do klasy virtualnej bazowej
	void update() override {

		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	//* funkcja wyswietlajaca teksture, odwolujaca sie do klasy virtualnej bazowej
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	//* funkcja wprawiajaca w ruch animacje
	//* animName - nazwa obiektu
	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};