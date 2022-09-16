#include "Game.h"

Game* game;
int main(int argc, char* argv[]) {

	//* Okreslanie limitow klatek na sekunde
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	//*Wywolanie okna 
	game->init("Sokoban", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, false);
	//*Tworzenie petli renderujacej gre
	while (game->running()) {
		frameStart = SDL_GetTicks();
		//*Wywolanie funkcji renderowania, odswierzania, wykrycia wydarzenia
		game->handleEvents();
		game->update();
		game->render();
		//*Ograniczenie ilosci klatek na sekunde by zapewnic plynnosc programu i jego animacji
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	delete game;
	return 0;
}

