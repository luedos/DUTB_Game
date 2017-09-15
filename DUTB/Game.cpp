#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	//GM_Gameplay = GM_Game(&GameGraphics);

	GameplayLevel = new TestLevel(&GM_Gameplay);
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
	case EButtons::Play:
	{
		GameGraphics.AddButton(this, &Game::NewRound, "PlayGame", InRect);
	}
	case EButtons::ExitToMenu:
	{

	}


	default:
		break;
	}

}

void Game::NewGame()
{
	GameGraphics.CreateWindow(800, 600);

	GM_NowPlaying = &GM_StartScreen;

	GM_StartScreen.GM_Start();

}

void Game::NewRound()
{
	GM_StartScreen.GM_End();

	delete GM_Gameplay.MyLevel;
	GM_Gameplay.MyLevel = GameplayLevel;

	GM_NowPlaying = &GM_Gameplay;

	GM_Gameplay.GM_Start();
}

void Game::SetGameMode(EGameMode GameModeRef)
{


	GM_NowPlaying->GM_End();

	switch (GameModeRef)
	{
	case EGameMode::StartMenuGM:
	{

	}
	default:
		break;
	}
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

	//GM_Gameplay.GM_EventTick(DeltaTime);
}

void Game::ExitGame()
{
	Quit = true;

	GM_StartScreen.GM_End();

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
