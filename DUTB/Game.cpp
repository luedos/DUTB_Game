#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	//GM_Gameplay = GM_Game(&GameGraphics);
}


Game::~Game()
{
}

void Game::AddButton(EButtons Button, SDL_Rect* InRect)
{
	switch (Button)
	{
	case EButtons::Exit:
	{
		GameGraphics.AddButton(this, &Game::ExitGame, "Exit", InRect);
		break;
	}


	default:
		break;
	}

}

void Game::NewGame()
{
	GameGraphics.CreateWindow(800, 600);

	GM_Gameplay.GM_Start();
}

void Game::EventTick(float DeltaTime)
{

	while (SDL_PollEvent(&MyEvent))
	{
		SDL_PumpEvents();
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
	GM_Gameplay.GM_EventTick(DeltaTime);
}

void Game::ExitGame()
{
	Quit = true;

	GameGraphics.DestroyEveryThing();


	GM_Gameplay.GM_End();

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
