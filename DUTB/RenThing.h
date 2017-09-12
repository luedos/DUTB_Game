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

	virtual void SetPosition(int x, int y) {}

	void InterpPosition(int InterpTo_x, int InterpTo_y, float DeltaTime_MS, float PercentInSec)
	{
		SetPosition(MyRect.x + float(InterpTo_x - MyRect.x) * DeltaTime_MS * 0.001 * PercentInSec,
			MyRect.y + float(InterpTo_y - MyRect.y) * DeltaTime_MS * 0.001 * PercentInSec);
	}

	SDL_Rect MyRect;

	SDL_Texture* MyTexture;

	bool FirstCreated = true;

	bool bReplaceble = false;
};

