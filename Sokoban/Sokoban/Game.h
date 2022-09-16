#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Text.h"

//* klasa podstawa silnika gry
class Game {
public:
	static SDL_Renderer* renderer;
	static Text* textUI;
	Game();

	//*Inicjalizacja funkcji czyszczacej pamieci po zakonczeniu programu
	~Game();
	
	//* funkcja inicjalizujaca okno programu
	//* title - nazwa okna
	//* xpos - pozycja w osi x
	//* ypos - pozycja w osi y
	//* width - szerokosc
	//* height - wysokosc
	//* fullscreen - defioniowanie okna pelnoekranowego
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//* funkcja wykrycia wydarzenia zwiazanym z oknem
	void handleEvents();

	//* funkcja odswierzanie okna
	void update();

	//* funkcja renderujaca obiekty
	void render();

	//* funkcja czyszczaca pamiec po zakonczeniu programu
	void clean();

	//* funkcja wskazujaceja na dzialanie programu
	bool running() { return isRunning; }

	//* przywolanie zmiennych z biblioteki graficznej dot. tekstur oraz wydarzen
	
	static SDL_Event event;
	static SDL_Color white;

	//* obecny stan generowania mapy
	bool mapstate;
	bool Scoreboard_state;
	bool bool_counter = false;

	//* zmienne do zapisu rekordu (nazwy oraz czasu gracza) tablicy wynikow 
	std::string  str_Player_H_S_1;
	std::string  str_Player_H_S_2;
	std::string  str_Player_H_S_3;
	std::string  str_Player_H_S_4;
	std::string  str_Player_H_S_5;
	std::string  str_Player_time_H_S_1;
	std::string  str_Player_time_H_S_2;
	std::string  str_Player_time_H_S_3;
	std::string  str_Player_time_H_S_4;
	std::string  str_Player_time_H_S_5;

	//*zapis zegara
	std::string Timer;
	std::string Timer_after;

	//* zmienne do zapisu tekstu dla konca gry
	std::string Text_End_game_0 = "Brawo twoj czas wynosi: ";
	std::string Text_End_game_1 = "By zapisac sie w tabeli wynikow ";
	std::string Text_End_game_2 = "wpisz swoj nick w konsoli";
	std::string Text_End_game_3 = "i kliknij Enter";
	std::string Text_End_game_4 = "ESC -> powrot";

	//* zmienna do zapisu nazwy gracza 
	std::string nick;

	//* funkcja zmiany stanu generowania mapy, licznika oraz tablicy wynikow
	void Mapstate(bool mapstate_inside);
	void Scoreboardstate(bool Scoreboard_inside);
	void bool_counter_state(bool bool_counter_inside);

	//* funkcja wywolujaca koniec gry
	void End_game();

	//* inicjalizacja grup dla pozniej tworzonych obiektow
	enum  groupLabels : std::size_t
	{
		groupMap,
		groupPlayer,
		groupMenu,
		groupBoxColliders,
		groupPoints,
		groupScoreboard,
		groupColliders
	};

private:
	SDL_Event ev;

	//* zmienna dot. dzialania okna
	bool isRunning = true;

	//*licznik
	int counter = 2;

	//* zmienna okna
	SDL_Window* window;
};