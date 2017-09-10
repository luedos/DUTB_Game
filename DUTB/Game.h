#pragma once
#include "GM_Game.h"

class Game
{
public:
	Game();
	~Game();

	void NewGame();

	void EventTick(float DeltaTime);

	void ExitGame();

	bool Quit = false;
private:

	Graphics GameGraphics;

	GM_Game GM_Gameplay = GM_Game(&GameGraphics);

};

