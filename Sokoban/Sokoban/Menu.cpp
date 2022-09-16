#include "Menu.h"
#include "Game.h"

Menu::Menu(Game* game) {
	this->game = game;
}

Menu::~Menu() {}

//* funkcja z zdefiniowanymi opcjami menu
//* odwolania do obiektow
void Menu::Options(Entity& Start, Entity& ScoreB, Entity& Quit) {

	//* tworzenie obiektu logo
	auto& Logo(manager.addEntity());
	Logo.addComponent<TransformComponent>(300, 150, 77, 300, 1);
	Logo.addComponent<SpriteComponent>("Assets/Logo.png", false);
	Logo.addComponent<TransformComponent>("Logo");
	Logo.addGroup(Game::groupMenu);

	//* tworzenie obiektu opisu osoby tworzacej projekt
	auto& Created(manager.addEntity());
	Created.addComponent<TransformComponent>(430, 205, 26, 283, 1);
	Created.addComponent<SpriteComponent>("Assets/Created.png", false);
	Created.addComponent<TransformComponent>("Created");
	Created.addGroup(Game::groupMenu);

	//* tworzenie obiektu - przycisk start
	Start.addComponent<TransformComponent>(390, 400, 50, 112, 1);
	Start.addComponent<SpriteComponent>("Assets/Start.png", true);
	Start.addComponent<TransformComponent>("Start");
	Start.addComponent<Menu>(true);
	Start.addGroup(Game::groupMenu);
	
	//* tworzenie obiektu - przycisk tablica wynikow
	ScoreB.addComponent<TransformComponent>(320, 450, 50, 267, 1);
	ScoreB.addComponent<SpriteComponent>("Assets/ScoreBoard.png", true);
	ScoreB.addComponent<TransformComponent>("ScoreB");
	ScoreB.addComponent<Menu>(false);
	ScoreB.addGroup(Game::groupMenu);

	//* tworzenie obiektu - przycisk wyjscie
	Quit.addComponent<TransformComponent>(395, 500, 50, 91, 1);
	Quit.addComponent<SpriteComponent>("Assets/Quit.png", true);
	Quit.addComponent<TransformComponent>("Quit");
	Quit.addComponent<Menu>(false);
	Quit.addGroup(Game::groupMenu);

	//* inicjalizacja poczatkowego aktywnego obiektu 
	std::string Button = Start.getComponent<TransformComponent>().tag;
	sprite = &Start.getComponent<SpriteComponent>();
	if (Button == "Start") {
		sprite = &Start.getComponent<SpriteComponent>();
		sprite->play("Change");
	}
}

//* funkcja odswierzajaca stan opcji wybranej
//* odwolania do obiektow oraz ich grupy
void Menu::update(bool mapstate, class std::vector<Entity*> menu, Entity& Start, Entity& ScoreB, Entity& Quit, Entity& Player) {
	
	
	//* zmienne okreslajace stan animacji obiektu
	bool Start_t = Start.getComponent<Menu>().Menuanimation;
	bool ScoreB_t = ScoreB.getComponent<Menu>().Menuanimation;
	bool Quit_t = Quit.getComponent<Menu>().Menuanimation;

	//* petla przechodzaca przez przyciski i okreslajaca wywolanie akcji
	for (auto& m : menu) {
		std::string Button = m->getComponent<TransformComponent>().tag;
		//*sprite = &m->getComponent<SpriteComponent>();
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			//* okreslenie stanu po wcisnieciu przycisku - esc
			case SDLK_ESCAPE:
				game->Mapstate(false);
				break;
			//* okreslenie stanu po wcisnieciu przycisku - enter
			case SDLK_RETURN:
				if (Button == "Start" && Start_t == true && Quit_t == false) {
					Player.addComponent<KeyboardControl>();
					game->Mapstate(true);
				}
				else if (Button == "ScoreB" && ScoreB_t == true && Start_t == false) {
					game->Scoreboardstate(true);
				}
				else if (Button == "Quit" && Quit_t == true && ScoreB_t == false) {
					game->clean();
				}
				break;
			//* okreslenie stanu po wcisnieciu przycisku - w lub stralki w gore
			case SDLK_w:
			case SDLK_UP:
				
				//* przycisk - start
				if (Button == "Start" && Start_t == true && Quit_t == false) {
					Start.addComponent<Menu>(false);
					ScoreB.addComponent<Menu>(false);
					Quit.addComponent<Menu>(true);
					for (auto& n : menu) {
						std::string next_Button = n->getComponent<TransformComponent>().tag;
						sprite = &n->getComponent<SpriteComponent>();
						if (next_Button == "Quit") {
							sprite->play("Change");
						}
						else  {
							sprite->play("Idle");
						}
						
					}

				}

				//* przycisk - tablicy wynikow
				else if (Button == "ScoreB" && ScoreB_t == true && Start_t == false) {
					Start.addComponent<Menu>(true);
					ScoreB.addComponent<Menu>(false);
					Quit.addComponent<Menu>(false);
					for (auto& n : menu) {
						std::string next_Button = n->getComponent<TransformComponent>().tag;
						sprite = &n->getComponent<SpriteComponent>();
						if (next_Button == "Start") {
							sprite->play("Change");
						}
						else  {
							sprite->play("Idle");
						}
				
					}
				}

				//* przycisk - wyjscia
				else if (Button == "Quit" && Quit_t == true && ScoreB_t == false) {
					 Start.addComponent<Menu>(false);
					 ScoreB.addComponent<Menu>(true);
					 Quit.addComponent<Menu>(false);
					 for (auto& n : menu) {
						 std::string next_Button = n->getComponent<TransformComponent>().tag;
						 sprite = &n->getComponent<SpriteComponent>();
						 if (next_Button == "ScoreB") {
							 sprite->play("Change");
						 }
						 else {
							 sprite->play("Idle");
						 }
						 
					 }
				}
				break;
			//* okreslenie stanu po wcisnieciu przycisku - s lub stralki w dol
			case SDLK_s:
			case SDLK_DOWN:

				//* przycisk - start
				if (Button == "Start" && Start_t == true && ScoreB_t == false) {
					Start.addComponent<Menu>(false);
					ScoreB.addComponent<Menu>(true);
					Quit.addComponent<Menu>(false);
					for (auto& n : menu) {
						std::string next_Button = n->getComponent<TransformComponent>().tag;
						sprite = &n->getComponent<SpriteComponent>();
						if (next_Button == "ScoreB") {
							sprite->play("Change");
						}
						else {
							sprite->play("Idle");
						}
					}
				}

				//* przycisk - tablicy wynikow
				else if (Button == "ScoreB" && ScoreB_t == true && Quit_t == false) {
					Start.addComponent<Menu>(false);
					ScoreB.addComponent<Menu>(false);
					Quit.addComponent<Menu>(true);
					for (auto& n : menu) {
						std::string next_Button = n->getComponent<TransformComponent>().tag;
						sprite = &n->getComponent<SpriteComponent>();
						if (next_Button == "Quit") {
							sprite->play("Change");
						}
						else {
							sprite->play("Idle");
						}

					}
				}

				//* przycisk - wyjscia
				else if (Button == "Quit" && Quit_t == true && Start_t == false) {
					Start.addComponent<Menu>(true);
					ScoreB.addComponent<Menu>(false);
					Quit.addComponent<Menu>(false);
					for (auto& n : menu) {
						std::string next_Button = n->getComponent<TransformComponent>().tag;
						sprite = &n->getComponent<SpriteComponent>();
						if (next_Button == "Start") {
							sprite->play("Change");
						}
						else {
							sprite->play("Idle");
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
}