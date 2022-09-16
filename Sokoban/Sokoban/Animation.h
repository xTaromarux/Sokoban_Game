#pragma once

//* Struktura zawierajaca dane dot. Animacji
//* index przypisany numer
//* frames ilosc klatek 
//* speed szybkosc wyswietlania
//* konstruktor zawierajacy wszystkie te zmienne
struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {
		Animation::index = 0;
		Animation::frames = 0;
		Animation::speed = 0;
	}
	Animation(int i, int f, int s) {
		index = i;
		frames = f;
		speed = s;
	}
};