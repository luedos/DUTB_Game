#pragma once
#include "GM_Game.h"
#include "GM_StartMenu.h"

enum EButtons
{
	Play,
	ExitToMenu,
	Exit
};

enum EGameMode
{
	GameGM,
	StartMenuGM
};


class Game
{
public:
	Game();
	~Game();

	void AddButton(EButtons Button, SDL_Rect* InRect);

	void NewGame();

	void EventTick(float DeltaTime);

	void ExitGame();

	void NewRound();

	void SetGameMode(EGameMode GameModeRef);

	bool Quit = false;

	TestLevel Level1 = TestLevel(&GM_Gameplay);

	Level_1 Level2 = Level_1(&GM_Gameplay);

	void PlaceLevelButtons();

private:

	SDL_Event MyEvent;

	Graphics GameGraphics;

	GM_Game GM_Gameplay = GM_Game(&GameGraphics, this);

	GM_StartMenu GM_StartScreen = GM_StartMenu(&GameGraphics, this);

	RenThing_Button* FindButton(int x, int y);

	GameMode* GM_NowPlaying;

};

