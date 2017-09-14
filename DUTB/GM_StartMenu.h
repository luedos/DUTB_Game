#pragma once
#include "GameMode.h"
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


	Graphics* MyGraph;

	class Game* MyGame;

	SDL_Color HeaderTextColor;

	float r, g, b;

	float ColorRate;

};

