#pragma once
#include "SDL2/include/SDL.h"
#include "Graphics.h"


class GameMode
{

public:
	GameMode() {}

	virtual void GM_EventTick(float DeltaTime) {}

	virtual void GM_Start() {}

	virtual void GM_End() {}
	
	virtual void GM_Event(SDL_Event* EventRef) {}

	Graphics* MyGraph;

	class Game* MyGame;
};
