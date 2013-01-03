/*
////////////////////////////////////////////////////////////////
//															  //
//	OneGameAMonth (OGAM) - Month 1 ( January 1st, 2013 )	  //
//	Titter: @PotatoSoftware									  //
//	Tumblr: PotatoSoftware http://potatosoftware.tumblr.com/  //
//	Reddit: FoamyPop http://reddit.com/user/foamypop		  //
//															  //
////////////////////////////////////////////////////////////////
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "IMAGE.h"
#include "RECTANGLE.h"
#include "BUTTON.h"
#include "STRING.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using std::cout;	
using std::cin;		
using std::endl;
using std::vector;

vector<Bullet*> bullets;
vector<Enemy*> enemies;
Player* player;

enum GameState
{
	Menu,
	Options,
	Ingame,
	Paused
};
GameState state;
GameState prevState;

void genEnemy()
{
	srand(time(NULL));
	const int x = rand()%1280+1;
	const int y = rand()%720+1;
	enemies.push_back(new Enemy(x, y, *player));
}

int main(int argc, char* argv[])
{
	RenderWindow WINDOW(VideoMode(1280, 720, 32), "SFML-TITLE-SHIT", Style::Close);
	WINDOW.SetFramerateLimit(60);

	int enemyCount = 0;
	STRING* ENEMIES = new STRING("ENEMIES: " + std::to_string(enemyCount), 400, 10);

	player = new Player( 200, 200 );
	enemies.push_back(new Enemy(300, 200, *player));

	sf::Clock clock;
	float time = clock.GetElapsedTime();
	float fireSpeed = 0.4f;

	state = Menu;
	prevState = Menu;

	/* Main Menu Buttons */
	BUTTON play(440, 200, "PLAY");
	BUTTON options(440, 320, "OPTIONS");
	BUTTON quit(440, 440, "QUIT");

	/* Pause Buttons */
	BUTTON resume(440, 200, "RESUME");
	BUTTON pauseOptions(440, 320, "OPTIONS");
	BUTTON quitToMenu(440, 440, "QUIT TO MENU");

	STRING SCORE("Score: " + std::to_string(player->SCORE), 100, 10);	
	
	while(WINDOW.IsOpened())
	{
		Event event;
		SCORE.SetText("SCORE: " + std::to_string(player->SCORE));
		ENEMIES->SetText("ENEMIES: " + std::to_string(enemyCount));

		sf::Vector2i mouse(WINDOW.GetInput().GetMouseX(), WINDOW.GetInput().GetMouseY());
		time = clock.GetElapsedTime();

		enemyCount = 0;
		for(int i = 0; i < enemies.size(); i++)
		{
			if(enemies[i]->alive)
				enemyCount++;
		}

		if(enemyCount <= 0)
		{
			genEnemy();
		}

		if(WINDOW.GetInput().IsKeyDown(Key::W))
			player->move[0] = true;
		else if(!WINDOW.GetInput().IsKeyDown(Key::W))
			player->move[0] = false;		

		if(WINDOW.GetInput().IsKeyDown(Key::S))
			player->move[1] = true;
		else if(!WINDOW.GetInput().IsKeyDown(Key::S))
			player->move[1] = false;		

		if(WINDOW.GetInput().IsKeyDown(Key::A))
			player->move[2] = true;
		else if(!WINDOW.GetInput().IsKeyDown(Key::A))
			player->move[2] = false;		

		if(WINDOW.GetInput().IsKeyDown(Key::D))
			player->move[3] = true;
		else if(!WINDOW.GetInput().IsKeyDown(Key::D))
			player->move[3] = false;

		if(WINDOW.GetInput().IsKeyDown(Key::Up))
		{
			if(time > fireSpeed) 
			{
				bullets.push_back(new Bullet(0, *player)); 
				clock.Reset();
			}
		}
		else if(WINDOW.GetInput().IsKeyDown(Key::Down))
		{
			if(time > fireSpeed) 
			{
				bullets.push_back(new Bullet(1, *player)); 
				clock.Reset();
			}
		}
		else if(WINDOW.GetInput().IsKeyDown(Key::Left))
		{
			if(time > fireSpeed) 
			{
				bullets.push_back(new Bullet(2, *player)); 
				clock.Reset();
			}
		}
		else if(WINDOW.GetInput().IsKeyDown(Key::Right))
		{
			if(time > fireSpeed) 
			{
				bullets.push_back(new Bullet(3, *player)); 
				clock.Reset();
			}
		}

		if(WINDOW.GetInput().IsKeyDown(Key::Num1))
		{
			fireSpeed = 0.1f;
		}
		if(WINDOW.GetInput().IsKeyDown(Key::Num2))
		{
			fireSpeed = 0.2f;
		}
		if(WINDOW.GetInput().IsKeyDown(Key::Num3))
		{
			fireSpeed = 0.3f;
		}
		if(WINDOW.GetInput().IsKeyDown(Key::Num4))
		{
			fireSpeed = 0.4f;
		}

		while(WINDOW.GetEvent(event))
		{
			switch(event.Type)
			{
			case Event::Closed:
				WINDOW.Close();
				break;
			case Event::KeyPressed:
				if(event.Key.Code == Key::Escape)
				{
					if(state == Menu)
					{					
						WINDOW.Close();		
					}
					else if(state == Ingame)
					{
						state = Paused;
						prevState = Ingame;
					}
					else if(state == Options)
					{
						state = prevState;
						prevState = Options;
					}
					else if(state == Paused)
					{
						state = prevState;
						prevState = Paused;
					}
				}	
				if(event.Key.Code == Key::Space)
				{
					genEnemy();
				}
				break;
			case sf::Event::MouseButtonReleased:
				if(event.MouseButton.Button == sf::Mouse::Button::Left)
				{
					if(state == Menu)
					{
						if(play.contains(mouse))
						{
							state = Ingame;
						}
						else if(options.contains(mouse))
						{
							state = Options;
							prevState = Menu;
						}
						else if(quit.contains(mouse))
						{
							WINDOW.Close();
						}
					}
					else if(state == Paused)
					{
						if(resume.contains(mouse))
						{
							state = Ingame;
						}
						else if(pauseOptions.contains(mouse))
						{
							state = Options;
							prevState = Paused;
						}
						else if(quitToMenu.contains(mouse))
						{
							state = Menu;
							prevState = Paused;
						}
					}
				}
				break;
			}	
		}
		WINDOW.Clear(Color(80, 80, 80, 255));
		/* DRAWING CODE */
		if(state == Ingame)
		{
			for(int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->Update(WINDOW);
			}
			player->Draw(WINDOW);
			for(int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->Update(WINDOW, bullets, *player);
			}	
			SCORE.Draw(WINDOW);
			ENEMIES->Draw(WINDOW);
		}
		else if(state == Menu)
		{
			play.Draw(WINDOW);
			options.Draw(WINDOW);
			quit.Draw(WINDOW);
			play.Update(mouse);
			options.Update(mouse);
			quit.Update(mouse);
		}
		else if(state == Options)
		{

		}
		else if(state == Paused)
		{
			resume.Draw(WINDOW);
			pauseOptions.Draw(WINDOW);
			quitToMenu.Draw(WINDOW);
			resume.Update(mouse);
			pauseOptions.Update(mouse);
			quitToMenu.Update(mouse);
		}
		/* END OF DRAWING */
		WINDOW.Display();
	}
	return EXIT_SUCCESS;
}