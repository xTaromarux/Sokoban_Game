#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ComponentMove.h"
#include "Timer.h"
#include "UI.h"
#include "TileComponent.h"
#include "Menu.h"
#include "ScoreBoard.h"

//* wskazniki do klas
Map* map;
Menu* MenuOptions;
ScoreBoard* scoreBoard;
SpriteComponent* sprite;
Timer* mTimer;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
ComponentMove* componentMove;
SDL_Event Game::event;
Text* Game::textUI = new Text(&manager);

//* tworzenie obiektow 
//* gracz
auto& Player(manager.addEntity());

//* zegar liczacy oraz koncowy
auto& ui(manager.addEntity());
auto& ui_after(manager.addEntity());

//* menu
auto& Start(manager.addEntity());
auto& ScoreB(manager.addEntity());
auto& Quit(manager.addEntity());

//* tablica wynikow
auto& H_S(manager.addEntity());
auto& Name(manager.addEntity());
auto& Time_H_S(manager.addEntity());
auto& Back(manager.addEntity());

//* czas i gracze tablicy wynikow
auto& Player_H_S_1(manager.addEntity());
auto& Player_H_S_2(manager.addEntity());
auto& Player_H_S_3(manager.addEntity());
auto& Player_H_S_4(manager.addEntity());
auto& Player_H_S_5(manager.addEntity());

auto& Player_time_H_S_1(manager.addEntity());
auto& Player_time_H_S_2(manager.addEntity());
auto& Player_time_H_S_3(manager.addEntity());
auto& Player_time_H_S_4(manager.addEntity());
auto& Player_time_H_S_5(manager.addEntity());

//* napis konca gry
auto& End_game_0(manager.addEntity());
auto& End_game_1(manager.addEntity());
auto& End_game_2(manager.addEntity());
auto& End_game_3(manager.addEntity());
auto& End_game_4(manager.addEntity());

//*Inicjalizacja konstruktora i dekonstruktora
Game::Game() {
	map = new Map();
	MenuOptions = new Menu(this);
	scoreBoard = new ScoreBoard(this);
	mTimer = Timer::Instance();
	componentMove = new ComponentMove(this, mTimer);
}

Game::~Game() {
	delete textUI;
	delete map;
	delete MenuOptions;
	delete scoreBoard;
	delete componentMove;
	mTimer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

//*Inicjalizacja funkcji inicjalizujacej okno programu
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	//*funkcja pelnego ekranu okna
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	bool_counter = false;
	//*tworzenie i komunikowanie o powstaniu okna 
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialised" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		if (window) {
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
			std::cout << "Renderer created" << std::endl;
		}
		
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error with SDL_ttf" << std::endl;
	}

	//* tworzenie czcionek
	textUI->AddFonts("cocogoose_25", "Fonts/cocogoose.ttf", 25);
	textUI->AddFonts("cocogoose", "Fonts/cocogoose.ttf", 35);
	textUI->AddFonts("cocogoose_40", "Fonts/cocogoose.ttf", 40);
	textUI->AddFonts("cocogoose_50", "Fonts/cocogoose.ttf", 50);

	//* tworzenie kolorow
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0, 0, 0, 0 };

	//* dodanie czcionki i pozycji do zegara
	ui.addComponent<UI>(10, 10, "", "cocogoose", white);

	//* dodanie pozycji, wielkosci, wygladu oraz grupy gracza
	Player.addComponent<TransformComponent>(220, 720, 50, 80, 1);
	Player.addComponent<SpriteComponent>("Assets/animations.png", true);
	Player.addComponent<ColliderComponent>("player");
	Player.addGroup(Game::groupPlayer);

	//* wywolywanie mapy
	map->LoadMap("Maps/Map.map", 9, 9);

	//* wywolywanie menu
	if (mapstate == false) {
		MenuOptions->Options(Start, ScoreB, Quit);
		scoreBoard->Options(H_S, Name, Time_H_S, Back);
	}

	//* dodanie do obiketow w tabeli wynikow pozycji i czcionki
	Player_H_S_1.addComponent<UI>(350, 300, "", "cocogoose", white);
	Player_H_S_2.addComponent<UI>(350, 350, "", "cocogoose", white);
	Player_H_S_3.addComponent<UI>(350, 400, "", "cocogoose", white);
	Player_H_S_4.addComponent<UI>(350, 450, "", "cocogoose", white);
	Player_H_S_5.addComponent<UI>(350, 500, "", "cocogoose", white);

	Player_time_H_S_1.addComponent<UI>(580, 300, "", "cocogoose", white);
	Player_time_H_S_2.addComponent<UI>(580, 350, "", "cocogoose", white);
	Player_time_H_S_3.addComponent<UI>(580, 400, "", "cocogoose", white);
	Player_time_H_S_4.addComponent<UI>(580, 450, "", "cocogoose", white);
	Player_time_H_S_5.addComponent<UI>(580, 500, "", "cocogoose", white);

	//* wczytywanie danych z pliku do tablicy wynikow
	scoreBoard->loadScoreBoard( "Maps/Players.map", "Maps/Time.map");

	//* dodanie do obiketow w tabeli wynikow napisow
	Player_H_S_1.getComponent<UI>().SetText(str_Player_H_S_1, "cocogoose");
	Player_H_S_2.getComponent<UI>().SetText(str_Player_H_S_2, "cocogoose");
	Player_H_S_3.getComponent<UI>().SetText(str_Player_H_S_3, "cocogoose");
	Player_H_S_4.getComponent<UI>().SetText(str_Player_H_S_4, "cocogoose");
	Player_H_S_5.getComponent<UI>().SetText(str_Player_H_S_5, "cocogoose");

	Player_time_H_S_1.getComponent<UI>().SetText(str_Player_time_H_S_1, "cocogoose");
	Player_time_H_S_2.getComponent<UI>().SetText(str_Player_time_H_S_2, "cocogoose");
	Player_time_H_S_3.getComponent<UI>().SetText(str_Player_time_H_S_3, "cocogoose");
	Player_time_H_S_4.getComponent<UI>().SetText(str_Player_time_H_S_4, "cocogoose");
	Player_time_H_S_5.getComponent<UI>().SetText(str_Player_time_H_S_5, "cocogoose");

	//* dodanie do zegara czcionki i pozycji
	ui_after.addComponent<UI>(300, 220, "", "cocogoose_50", white);

	//* dodanie do napisow koncowych pozycji i czcionki
	End_game_0.addComponent<UI>(100, 140, "", "cocogoose_50", black);
	End_game_1.addComponent<UI>(100, 400, "", "cocogoose", white);
	End_game_2.addComponent<UI>(100, 450, "", "cocogoose", white);
	End_game_3.addComponent<UI>(100, 500, "", "cocogoose", white);
	End_game_4.addComponent<UI>(100, 600, "", "cocogoose", white);
}

//* tworzenie grup
auto& menu(manager.getGroup(Game::groupMenu));
auto& tiles(manager.getGroup(Game::groupMap));
auto& boxcolliders(manager.getGroup(Game::groupBoxColliders));
auto& player(manager.getGroup(Game::groupPlayer));
auto& points(manager.getGroup(Game::groupPoints));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& Scoreboard_g(manager.getGroup(Game::groupScoreboard));

//* funkcja zmienajaca stan mapy
void Game::Mapstate(bool mapstate_inside) {
	mapstate = mapstate_inside;
}

//* funkcja zmienajaca stan tablicy wynikow
void Game::Scoreboardstate(bool Scoreboard_inside) {
	Scoreboard_state = Scoreboard_inside;
}

//* funkcja zmienajaca stan licznika
void Game::bool_counter_state(bool bool_counter_inside) {
	bool_counter = bool_counter_inside;
}

//* funkcja konca gry
void Game::End_game(){

	std::cout << "Nick: (max 8 liter)" << std::endl;
	std::getline(std::cin, nick);
	if (nick.empty())
	{
		std::cout << "Wpisano do tabeli jako Player" << std::endl;

		std::fstream save;
		save.open("Maps/Players.map");
		save << "Player" << std::endl;
		save.close(); //*obowiazkowo nalezy zamknac plik

		save.open("Maps/Time.map", std::ios::app);
		save << Timer_after << std::endl;
		save.close(); //*obowiazkowo nalezy zamknac plik
	}
	else{
		if (nick.length() <= 8)
		{
			std::cout << "Wpisano do tabeli" << std::endl;

			std::fstream save;
			save.open("Maps/Players.map", std::ios::app);
			save << nick << std::endl;
			save.close(); //*obowiazkowo nalezy zamknac plik

			save.open("Maps/Time.map", std::ios::app);
			save << Timer_after << std::endl;
			save.close(); //*obowiazkowo nalezy zamknac plik

		}
		else 
		{
			std::cout << "Za dluga nazwa, podaj nick raz jeszcze" << std::endl;
			std::cin >> nick;
		}
	}
	
}

//*Inicjalizacja funkcji wykrycia wydarzenia zwiazanym z oknem
void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

//*Inicjalizacja funkcji odswierzanie okna
void Game::update() {

	mTimer->Update();

	if (mTimer->deltaTime() >= 60.0) {
		mTimer->AddMinute();
		mTimer->Reset();
	}
	if (mTimer->Minute() >= 60) {
		mTimer->AddHour();
		mTimer->ResetMin();
	}
	componentMove->update(counter, Player, boxcolliders, points, colliders, ui_after, End_game_0, End_game_1, End_game_2);
	


	Timer = std::to_string(mTimer->Hour()) + " : " + std::to_string(mTimer->Minute()) + " : " + std::to_string(mTimer->deltaTime());
	//*Timer_after = std::to_string(mTimer->Hour()) + " : " + std::to_string(mTimer->Minute()) + " : " + std::to_string(mTimer->deltaTime());
	
	//* wywolanie zegara
	if (mapstate == true) {
		ui.getComponent<UI>().SetText("Time: "+Timer, "cocogoose_25");
	}

	//* wywolanie konca gry
	if (bool_counter == true) {

		SDL_Color white = { 255, 255, 255, 255 };
		Timer_after = Timer;
		ui_after.getComponent<UI>().SetText(Timer, "cocogoose_50");

		End_game_0.getComponent<UI>().SetText(Text_End_game_0, "cocogoose_50");
		End_game_1.getComponent<UI>().SetText(Text_End_game_1, "cocogoose");
		End_game_2.getComponent<UI>().SetText(Text_End_game_2, "cocogoose");
		End_game_3.getComponent<UI>().SetText(Text_End_game_3, "cocogoose");
		End_game_4.getComponent<UI>().SetText(Text_End_game_4, "cocogoose");

		bool_counter = false;
		counter -= 1;
	}

	//* wywolanie menu
	MenuOptions->update(mapstate, menu, Start, ScoreB, Quit, Player);
	
	//* wywolanie tablicy wynikow
	if(Scoreboard_state == true){
		scoreBoard->update(Scoreboard_g, Back);
	}

	
}

//*Inicjalizacja funkcji renderujacej obiekty
void Game::render() {
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}
	if (mapstate == false) {
		if(Scoreboard_state == true){
			for (auto& s : Scoreboard_g)
			{
				s->draw();

				Player_H_S_1.draw();
				Player_H_S_2.draw();
				Player_H_S_3.draw();
				Player_H_S_4.draw();
				Player_H_S_5.draw();

				Player_time_H_S_1.draw();
				Player_time_H_S_2.draw();
				Player_time_H_S_3.draw();
				Player_time_H_S_4.draw();
				Player_time_H_S_5.draw();
			}
		}
		else {
			for (auto& m : menu)
			{
				m->draw();
			}
		}
	}
	else
	{
		for (auto& c : colliders)
		{
			c->draw();
		}
		for (auto& p : boxcolliders)
		{
			p->draw();
		}
		for (auto& p : points)
		{
			p->draw();
		}

		ui_after.draw();

		End_game_0.draw();
		End_game_1.draw();
		End_game_2.draw();
		End_game_3.draw();
		End_game_4.draw();
		

		if(counter == 2)
		{
			for (auto& p : player)
			{
				p->draw();
			}
			ui.draw();
		}

	}
	SDL_RenderPresent(renderer);

	if (counter == 1) {
		Game::End_game();
		counter -= 1;
	}
}

//* funkcja czyszczaca
void Game::clean()
{
	mTimer->Release();
	isRunning = false;
}