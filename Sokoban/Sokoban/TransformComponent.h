#pragma once
#include "Components.h"
#include "ComponentSystem.h"
#include "Vector2D.h"

//* klasa pozwalajaca ustawic polozenie obiektu
class TransformComponent : public Component
{
public:

	//* przywolanie zmiennych dot. pozycji z klasy Vector2D
	Vector2D position;
	Vector2D velocity;

	//* inicjalizacja zmiennych dot. poruszania
	int height = 100;
	int width = 100;
	int scale = 1;
	std::string tag;
	int speed = 3;

	//* konstruktor z startowa pozycja
	TransformComponent()
	{
		position.Zero();
	}

	//* konstruktor z nazwa obiektu
	//* t - nazwa
	TransformComponent(std::string t) {
		tag = t;
	}

	//* konstruktor z pozycja i skala
	//* sc - skala
	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	//* konstruktor z polozeniem
	//* x - polozenie w osi x
	//* y - polozenie w osi y
	TransformComponent(float x, float y)
	{
		position.Zero();
	}

	//* konstruktor z polozeniem, skala, oraz z wielkoscia
	//* x - polozenie w osi x
	//* y - polozenie w osi y
	//* h - wysokosc
	//* w - szerokosc
	//* sc - skala
	TransformComponent(int x, int y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	//* funkcja inicjalizacyjna polozenie, odwolujaca sie do klasy virtualnej bazowej
	void init() override {
		velocity.Zero();
	}

	//* funkcja odsiwierzajaca poruszanie, odwolujaca sie do klasy virtualnej bazowej
	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};