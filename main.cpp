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

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Config.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

SDL_Surface* screen;
std::vector<Bullet*> bullets;
std::vector<Enemy*> enemies;
Player* player;
int WIDTH;
int HEIGHT;
int BPP;
std::string title;
TTF_Font* font;
enum GameState
{
	MainMenu,
	InGame,
	Options
};
GameState state;
typedef struct /* DEFINE HUD ELEMENT */
{
	SDL_Surface* src;
	SDL_Surface* msg;
	SDL_Rect pos;
	SDL_Rect textPos;
	SDL_Color color;
	std::string text;
} HUD_Element;	
typedef struct
{
	std::string text;
	SDL_Surface* msg;
	SDL_Rect pos;
} TEXT;
#define KEY event.key.keysym.sym
void LoadFromConfig()
{
	state = InGame;
	Config* cfg = new Config("Config.ini");
	WIDTH = cfg->SCREEN_WIDTH();
	HEIGHT = cfg->SCREEN_HEIGHT();
	BPP = cfg->SCREEN_BPP();
	int f = cfg->fullscreen();
	title = cfg->TITLE();

	switch(f)
	{
	case 1:
		screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE | SDL_FULLSCREEN);
		break;
	case 0:
		screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
		break;
	default:
		screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
	}
}

void spawnEnemy()
{
	srand(time(NULL));
	int x = rand()%WIDTH+1;
	int y = rand()%HEIGHT+1;
	enemies.push_back(new Enemy(x, y, player));
}

int bulletFireSpeed = 500;
int timeSince = bulletFireSpeed;

	int numberOfEnemies = 0;

	int PISTOL_SPEED = 500;
	int SMG_SPEED = 310;
	int ASSAULT_RIFLE_SPEED = 250;
	int LMG_SPEED = 100;

	int PISTOL = 0;
	int SMG = 800;
	int ASSAULT_RIFLE = 1500;
	int LMG = 2500;

	std::string GUN = "GUN";
	std::string PISTOL_NAME = "PISTOL";
	std::string SMG_NAME = "SMG";
	std::string ASSAULT_NAME = "ASSAULT RIFLE";
	std::string LMG_NAME = "LMG";
	
void checkScore()
{
	if(player->SCORE == PISTOL)
	{
		GUN = PISTOL_NAME;
		bulletFireSpeed = PISTOL_SPEED;
	}
	else if(player->SCORE >= SMG && player->SCORE < ASSAULT_RIFLE)
	{
		GUN = SMG_NAME;
		bulletFireSpeed = SMG_SPEED;
	}
	else if(player->SCORE >= ASSAULT_RIFLE && player->SCORE < LMG)
	{
		GUN = ASSAULT_NAME;
		bulletFireSpeed = ASSAULT_RIFLE_SPEED;
	}
	else if(player->SCORE >= LMG)
	{
		GUN = LMG_NAME;
		bulletFireSpeed = LMG_SPEED;
	}
}

int main(int argc, char* argv[])
{
	LoadFromConfig();
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	font = TTF_OpenFont("Game_Data\\HUD-Font.ttf", 32);

	SDL_Surface* grass = IMG_Load("Game_Data\\Images\\Grass.png");

	player = new Player(100, 200);
	enemies.push_back(new Enemy(300, 200, player));

	HUD_Element health;
	HUD_Element armour;
	TEXT score;

	// Set Up HEALTH HUD ELEMENT
	health.src = IMG_Load("Game_Data\\Images\\Health-HUD.png");	
	health.color.r = 255; health.color.g = 20; health.color.b = 0;
	health.text = /*"Health: " + */std::to_string(player->health);
	health.msg = TTF_RenderText_Solid(font, health.text.c_str(), health.color);
	health.pos.x = 10;	health.pos.y = HEIGHT - (health.src->h + 10);
	health.textPos.x = health.pos.x + 55; health.textPos.y = health.pos.y + 9;

	// Set Up ARMOUR HUD ELEMENT
	armour.src = IMG_Load("Game_Data\\Images\\Armour-HUD.png");	
	armour.color.r = 255; armour.color.g = 20; armour.color.b = 0;
	armour.text = /*"Armour: " + */std::to_string(player->armour);
	armour.msg = TTF_RenderText_Solid(font, armour.text.c_str(), armour.color);
	armour.pos.x = 150;	armour.pos.y = HEIGHT - (armour.src->h + 10);
	armour.textPos.x = armour.pos.x + 55; armour.textPos.y = armour.pos.y + 9;	

	SDL_Color col = {255, 20, 0};
	// Show AMMO
	TEXT t;
	t.text = "SHOOT-SPEED: " + std::to_string(bulletFireSpeed);
	t.msg = TTF_RenderText_Solid(font, t.text.c_str(), col);
	t.pos.x = 300;
	t.pos.y = armour.pos.y + 9;	
	SDL_WM_SetCaption(title.c_str(), NULL);	

	score.text = "SCORE: " + std::to_string(player->SCORE);
	score.msg = TTF_RenderText_Solid(font, score.text.c_str(), col);
	score.pos.x = WIDTH - (score.msg->w + 100);
	score.pos.y = armour.pos.y + 9;	

	TEXT enemyNum;
	enemyNum.text = "Enemies: " + std::to_string(numberOfEnemies);
	enemyNum.msg = TTF_RenderText_Solid(font, enemyNum.text.c_str(), col);
	enemyNum.pos.x = 300;
	enemyNum.pos.y = armour.pos.y - 29;	

	TEXT gun;
	gun.text = "GUN: " + GUN;
	gun.msg = TTF_RenderText_Solid(font, gun.text.c_str(), col);
	gun.pos.x = 540;
	gun.pos.y = armour.pos.y -29;

	SDL_WM_SetCaption(title.c_str(), NULL);	

	bool running = true;
	Uint32 start = SDL_GetTicks();
	bool fire[4] = {false, false, false, false};

	// Main Loop
	while(running)
	{
		if(state == InGame)
		{
			numberOfEnemies = 0;
			health.text = /*"Health: " + */std::to_string(player->health);
			health.msg = TTF_RenderText_Solid(font, health.text.c_str(), health.color);

			armour.text = /*"Armour: " + */std::to_string(player->armour);
			armour.msg = TTF_RenderText_Solid(font, armour.text.c_str(), armour.color);

			t.text = "SHOOT-SPEED: " + std::to_string(bulletFireSpeed);
			t.msg = TTF_RenderText_Solid(font, t.text.c_str(), col);

			score.text = "SCORE: " + std::to_string(player->SCORE);
			score.msg = TTF_RenderText_Solid(font, score.text.c_str(), col);	

			for(int i = 0; i < enemies.size(); i++)
			{
				if(enemies[i]->alive)
				{
					numberOfEnemies++;
				}
			}

			enemyNum.text = "Enemies: " + std::to_string(numberOfEnemies);
			enemyNum.msg = TTF_RenderText_Solid(font, enemyNum.text.c_str(), col);

			checkScore();
			gun.text = "GUN: " + GUN;
			gun.msg = TTF_RenderText_Solid(font, gun.text.c_str(), col);
		}

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if(state == InGame)
				{
					if(KEY == SDLK_ESCAPE)
						running = false;
					if(KEY == SDLK_w)
						player->move[0] = true;
					if(KEY == SDLK_a)
						player->move[1] = true;
					if(KEY == SDLK_s)
						player->move[2] = true;
					if(KEY == SDLK_d)
						player->move[3] = true;

					if(KEY == SDLK_UP)
						fire[0] = true;
					if(KEY == SDLK_DOWN)
						fire[1] = true;
					if(KEY == SDLK_LEFT)
						fire[2] = true;
					if(KEY == SDLK_RIGHT)
						fire[3] = true;

					if(KEY == SDLK_SPACE)
					{
						spawnEnemy();
					}

					if(KEY == SDLK_e)
						if(bulletFireSpeed < 500) bulletFireSpeed += 10;
					if(KEY == SDLK_q)
						if(bulletFireSpeed > 0) bulletFireSpeed -= 10;
				}
				break;
			case SDL_KEYUP:
				if(state == InGame)
				{
					if(KEY == SDLK_w)
						player->move[0] = false;
					if(KEY == SDLK_a)
						player->move[1] = false;
					if(KEY == SDLK_s)
						player->move[2] = false;
					if(KEY == SDLK_d)
						player->move[3] = false;
				
					if(KEY == SDLK_UP)
						fire[0] = false;
					if(KEY == SDLK_DOWN)
						fire[1] = false;
					if(KEY == SDLK_LEFT)
						fire[2] = false;
					if(KEY == SDLK_RIGHT)
						fire[3] = false;
				}
				break;
			}
		}
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 60, 60, 60));

		if(state == InGame) // START INGAME LOOP
		{			
			for(int i = 0; i < (WIDTH / 50) + 50; i++)
			{
				for(int j = 0; j < (HEIGHT / 50) + 50; j++)
				{
					SDL_Rect r = {i*50, j*50, 50, 50};
					SDL_BlitSurface(grass, 0, screen, &r);
				}
			}					

			for(int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->Update(bullets);
			}
			for(int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->Update();
			}	

			player->Draw(WIDTH, HEIGHT);
			player->Update(enemies);

			// HUD ELEMENTS
			SDL_BlitSurface(health.src, 0, screen, &health.pos);
			SDL_BlitSurface(health.msg, 0, screen, &health.textPos);
			SDL_BlitSurface(armour.src, 0, screen, &armour.pos);
			SDL_BlitSurface(armour.msg, 0, screen, &armour.textPos);
			SDL_BlitSurface(score.msg, 0, screen, &score.pos);
			SDL_BlitSurface(t.msg, 0, screen, &t.pos);
			SDL_BlitSurface(enemyNum.msg, 0, screen, &enemyNum.pos);
			SDL_BlitSurface(gun.msg, 0, screen, &gun.pos);
		}
		timeSince = SDL_GetTicks()-start;
		if(fire[0])
		{
			if(!fire[1] && !fire[2] && !fire[3])
			{
				if(timeSince > bulletFireSpeed)
				{
					start = SDL_GetTicks();
					bullets.push_back(new Bullet(0, player));
				}
			}
		}
		if(fire[1])
		{
			if(!fire[0] && !fire[2] && !fire[3])
			{
				if(timeSince > bulletFireSpeed)
				{
					start = SDL_GetTicks();
					bullets.push_back(new Bullet(1, player));
				}
			}
		}
		if(fire[2])
		{
			if(!fire[1] && !fire[0] && !fire[3])
			{
				if(timeSince > bulletFireSpeed)
				{
					start = SDL_GetTicks();
					bullets.push_back(new Bullet(2, player));
				}
			}
		}
		if(fire[3])
		{
			if(!fire[1] && !fire[2] && !fire[0])
			{
				if(timeSince > bulletFireSpeed)
				{
					start = SDL_GetTicks();
					bullets.push_back(new Bullet(3, player));
				}
			}
		} 
		// END OF INGAME LOOP

		SDL_Flip(screen);

		if(1000/60 > SDL_GetTicks() - start)
			SDL_Delay(1000/60 - (SDL_GetTicks() - start));
	}
	// End of Main Loop
	
	TTF_CloseFont(font);
	SDL_FreeSurface(health.src);
	SDL_FreeSurface(armour.src);
	SDL_FreeSurface(player->src);
	SDL_Quit();
	return EXIT_SUCCESS;
}