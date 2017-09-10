#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	//GM_Gameplay = GM_Game(&GameGraphics);
}


Game::~Game()
{
}

void Game::NewGame()
{
	GameGraphics.CreateWindow(800, 600);

	GM_Gameplay.GM_Start();
}

void Game::EventTick(float DeltaTime)
{
	GM_Gameplay.GM_EventTick(DeltaTime);
}

void Game::ExitGame()
{
	Quit = true;

	GameGraphics.DestroyEveryThing();


	GM_Gameplay.GM_End();

}
