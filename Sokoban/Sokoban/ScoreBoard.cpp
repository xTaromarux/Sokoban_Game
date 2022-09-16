#include "ScoreBoard.h"
#include "Game.h"

ScoreBoard::ScoreBoard(Game* game) {
	this->game = game;
}

ScoreBoard::~ScoreBoard() {}

//* funkcja z zdefiniowanymi opcjami menu
//* odwolania do obiektow
void ScoreBoard::Options(Entity& H_S, Entity& Name, Entity& Time_H_S, Entity& Back) {

	//* tworzenie obiektu logo
	H_S.addComponent<TransformComponent>(300, 150, 78, 390, 1);
	H_S.addComponent<SpriteComponent>("Assets/High_score.png", false);
	H_S.addComponent<TransformComponent>("High scores");
	H_S.addGroup(Game::groupScoreboard);

	//* tworzenie obiektu opisu osoby tworzacej projekt
	Name.addComponent<TransformComponent>(350, 235, 50, 132, 1);
	Name.addComponent<SpriteComponent>("Assets/Name.png", false);
	Name.addComponent<TransformComponent>("Name");
	Name.addGroup(Game::groupScoreboard);

	//* tworzenie obiektu opisu osoby tworzacej projekt
	Time_H_S.addComponent<TransformComponent>(580, 235, 50, 108, 1);
	Time_H_S.addComponent<SpriteComponent>("Assets/Time.png", false);
	Time_H_S.addComponent<TransformComponent>("Time");
	Time_H_S.addGroup(Game::groupScoreboard);

	//* tworzenie obiektu - przycisk back
	Back.addComponent<TransformComponent>(300, 580, 50, 110, 1);
	Back.addComponent<SpriteComponent>("Assets/Back.png", true);
	Back.addComponent<TransformComponent>("Back");
	Back.addComponent<Menu>(false);
	Back.addGroup(Game::groupScoreboard);

	//* inicjalizacja poczatkowego aktywnego obiektu 
	std::string Button = Back.getComponent<TransformComponent>().tag;
	sprite = &Back.getComponent<SpriteComponent>();
	if (Button == "Back") {
		sprite = &Back.getComponent<SpriteComponent>();
		sprite->play("Change");
	}
}

//* funkcja odswierzajaca stan opcji wybranej
//* odwolania do obiektow oraz ich grupy
void ScoreBoard::update(class std::vector<Entity*> Scoreboard_g, Entity& Back) {

	//* zmienne okreslajace stan animacji obiektu
	bool Back_state = Back.getComponent<Menu>().Menuanimation;
	Back.addComponent<Menu>(true);

	//* petla przechodzaca przez przyciski i okreslajaca wywolanie akcji
	for (auto& m : Scoreboard_g) {
		//*sprite = &m->getComponent<SpriteComponent>();
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
				//* okreslenie stanu po wcisnieciu przycisku - esc
			case SDLK_ESCAPE:
				game->Mapstate(false);
				game->Scoreboardstate(false);
				break;

				//* okreslenie stanu po wcisnieciu przycisku - enter
			case SDLK_RETURN:
				if (game->Scoreboard_state == true && Back_state == true) {
					game->Mapstate(false);
					game->Scoreboardstate(false);
					Back.addComponent<Menu>(false);
				}
				break;
			default:
				break;
			}
		}
	}
}

//* Funkcja wczytujaca dane z plikow
void ScoreBoard::loadScoreBoard( std::string path_players,std::string path_time)	{
	
	std::string player;
	std::string time;
	SDL_Color white = { 255, 255, 255, 255 };

	ScoreBoard::SB_file_players = path_players;
	ScoreBoard::SB_file_time = path_time;
	//* otwieranie plikow
	std::fstream file_players;
	std::fstream file_time;
	file_players.open(SB_file_players);
	file_time.open(SB_file_time);

	//* wyczytywanie danych z plikow do zmiennych
		getline(file_players, game->str_Player_H_S_1);
		getline(file_players, game->str_Player_H_S_2);
		getline(file_players, game->str_Player_H_S_3);
		getline(file_players, game->str_Player_H_S_4);
		getline(file_players, game->str_Player_H_S_5);

		getline(file_time, game->str_Player_time_H_S_1);
		getline(file_time, game->str_Player_time_H_S_2);
		getline(file_time, game->str_Player_time_H_S_3);
		getline(file_time, game->str_Player_time_H_S_4);
		getline(file_time, game->str_Player_time_H_S_5);

	//* zamykanie plikow
	file_time.ignore();
	file_players.ignore();

}