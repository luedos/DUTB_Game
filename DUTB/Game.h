#pragma once
#include "GM_Game.h"

enum EButtons
{
	Exit
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

	bool Quit = false;
private:

	SDL_Event MyEvent;

	Graphics GameGraphics;

	GM_Game GM_Gameplay = GM_Game(&GameGraphics, this);

	RenThing_Button* FindButton(int x, int y);

};

