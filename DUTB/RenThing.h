#pragma once
#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_image.h"

class RenThing

{

public:

	RenThing() {}
	
	virtual void CleanupThing() {}

	virtual void RenderThing(SDL_Renderer* RenRef) {}

	virtual void PrepareThing(SDL_Renderer* RenRef) {}

	SDL_Rect MyRect;

	SDL_Texture* MyTexture;

	bool bReplaceble = false;
};

