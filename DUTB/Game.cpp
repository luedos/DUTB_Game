#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	GM_NowPlaying = &GM_StartScreen;
	setlocale(LC_ALL, "rus");
}


Game::~Game()
{
}


void Game::NewGame()
{
	GameGraphics.CreateWindow(800, 600);

	if (!ReadSaves())
		RecreateSaves();

	cout << "Reading after recreating : " << ReadSaves() << endl;

	GoStartMenu();
}

void Game::PlaceLevelButtons()
{
	GameGraphics.ClearEverything();

	SDL_Color MyTextColor = { 225,225,225,225 };

	Coordinates TestCoord;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeY = true;

	TestCoord.X = 0.05;
	TestCoord.W = 0.4;
	TestCoord.Y = 0.05;
	TestCoord.H = 50;


	GameGraphics.AddStaticText("Choose Level", { 225,225,225,225 }, &TestCoord);

	TestCoord.W = 0.35;
	TestCoord.Y = 0.2;


	GameGraphics.AddButton(&Level1, &Level_1::FireLevel, "FirstLevel", &TestCoord);

	TestCoord.X = 0.5;
	GameGraphics.AddStaticText(Level1.StringPoints.c_str(), MyTextColor, &TestCoord);
	TestCoord.X = 0.05;

	TestCoord.Y = 0.3;

	if (Level1.LevelPassed) {
		GameGraphics.AddButton(&Level2, &Level_2::FireLevel, "SecondLevel", &TestCoord);

		TestCoord.X = 0.5;
		GameGraphics.AddStaticText(Level2.StringPoints.c_str(), MyTextColor, &TestCoord);
		TestCoord.X = 0.05;
	}

	

	TestCoord.Y = 0.4;

	if (Level2.LevelPassed) {
		GameGraphics.AddButton(&Level3, &Level_3::FireLevel, "ThirdLevel", &TestCoord);
		TestCoord.X = 0.5;
		GameGraphics.AddStaticText(Level3.StringPoints.c_str(), MyTextColor, &TestCoord);
		TestCoord.X = 0.05;
	}

	TestCoord.Y = 0.5;
	
	GameGraphics.AddButton(&Level_Test, &TestLevel::FireLevel, "Test Level", &TestCoord);

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

			RenThing_Button* TestButton = FindButton(x, y);
			if (TestButton != nullptr)
				TestButton->ButtonUnpressed(x, y, true);

			for (int i = 0; i < GameGraphics.ButtonsArray.size(); i++)
				if(GameGraphics.ButtonsArray.at(i) != TestButton)
					GameGraphics.ButtonsArray.at(i)->ButtonUnpressed(x, y, false);
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

	RenThing_Button* TestButton = nullptr;
	int TestRenLevel = 0;

	for (int i = GameGraphics.ButtonsArray.size() - 1; i > -1; i--)
	{
		TestRect = &GameGraphics.ButtonsArray.at(i)->MyRect;

		if (TestRect->x < x && TestRect->y < y && TestRect->x + TestRect->w > x && TestRect->y + TestRect->h > y && GameGraphics.ButtonsArray.at(i)->LevelRender >= TestRenLevel)
		{
			TestButton = GameGraphics.ButtonsArray.at(i);
			TestRenLevel = GameGraphics.ButtonsArray.at(i)->LevelRender;
		}
	}

	return TestButton;
}
