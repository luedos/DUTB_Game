#pragma once
#include "GM_Game.h"
#include "GM_StartMenu.h"


class Game
{
public:
	Game();
	~Game();

	void NewGame();

	void EventTick(float DeltaTime);

	void ExitGame();

	bool Quit = false;

	TestLevel Level1 = TestLevel(&GM_Gameplay);

	Level_1 Level2 = Level_1(&GM_Gameplay);

	void PlaceLevelButtons();

	void GoStartMenu();

	void GoGameplay();

	void TestFunc() { GameGraphics.ChangeWindowMode(!GameGraphics.bIsFullscreen); }

	void TestFunc2() {
		if (GameGraphics.X_Resolution == 800)
			GameGraphics.ChangeWindowSize(1600, 900);
		else
			GameGraphics.ChangeWindowSize(800, 600);
	}

private:

	Graphics GameGraphics;

	SDL_Event MyEvent;

	GM_Game GM_Gameplay = GM_Game(&GameGraphics, this);

	GM_StartMenu GM_StartScreen = GM_StartMenu(&GameGraphics, this);

	RenThing_Button* FindButton(int x, int y);

	GameMode* GM_NowPlaying;

};

