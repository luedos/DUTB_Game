#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	GM_NowPlaying = &GM_StartScreen;
}


Game::~Game()
{
}


void Game::NewGame()
{
	GameGraphics.CreateWindow(800, 600);

	GoStartMenu();
}

void Game::PlaceLevelButtons()
{
	GameGraphics.ClearEverything();

	SDL_Rect NewRect;
	NewRect.x = 50;
	NewRect.y = 50;
	NewRect.w = 250;
	NewRect.h = 64;

	GameGraphics.AddStaticText("Choose Level", { 225,225,225,225 }, &NewRect);

	NewRect.y = 150;

	GameGraphics.AddButton(&Level2, &Level_1::FireLevel, "First Level", &NewRect);
	
	NewRect.y = 250;
	
	GameGraphics.AddButton(&Level1, &TestLevel::FireLevel, "Test Level", &NewRect);

}

void Game::GoStartMenu()
{
	GM_NowPlaying->GM_End();
	GM_NowPlaying = &GM_StartScreen;
	GM_NowPlaying->GM_Start();
}

void Game::GoGameplay()
{
	GM_NowPlaying->GM_End();
	GM_NowPlaying = &GM_Gameplay;
	GM_NowPlaying->GM_Start();
}

void Game::EventTick(float DeltaTime)
{
	while (SDL_PollEvent(&MyEvent))
	{
		SDL_PumpEvents();

		GM_NowPlaying->GM_Event(&MyEvent);

		if (MyEvent.type == SDL_QUIT)
		{
			ExitGame();
		}
		if (MyEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			RenThing_Button* TestButton = FindButton(x, y);
			if(TestButton != nullptr)
				TestButton->ButtonPressed();
		}
		if (MyEvent.type == SDL_MOUSEBUTTONUP)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			for (int i = 0; i < GameGraphics.ButtonsArray.size(); i++)
				GameGraphics.ButtonsArray.at(i)->ButtonUnpressed(x, y);
		}
	}
	GM_NowPlaying->GM_EventTick(DeltaTime);

	GameGraphics.RenderEverything(DeltaTime);
}

void Game::ExitGame()
{
	Quit = true;

	GM_Gameplay.GM_End();

	GameGraphics.DestroyEveryThing();
}



RenThing_Button* Game::FindButton(int x, int y)
{
	SDL_Rect* TestRect;

	for (int i = 0; i < GameGraphics.ButtonsArray.size(); i++)
	{
		TestRect = &GameGraphics.ButtonsArray.at(i)->MyRect;

		if (TestRect->x < x && TestRect->y < y && TestRect->x + TestRect->w > x && TestRect->y + TestRect->h > y)
			return GameGraphics.ButtonsArray.at(i);
	}

	return nullptr;
}
