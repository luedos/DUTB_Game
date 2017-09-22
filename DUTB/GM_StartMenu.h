#pragma once
#include "GM_Game.h"
#include "Graphics.h"

class GM_StartMenu :
	public GameMode
{
public:

	GM_StartMenu(Graphics* MyGraphRef, class Game* MyGameRef);

	~GM_StartMenu();

	void GM_EventTick(float DeltaTime) override;

	void GM_Start() override;

	void GM_End() override;

	void LevelChooseMenu();

private:
	float r, g, b;

	float ColorRate;

	SDL_Color HeaderTextColor;
};

