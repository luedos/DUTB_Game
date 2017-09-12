#pragma once
#include "RenThing.h"


class RenThing_Image : public RenThing

{

public:


	RenThing_Image(SDL_Renderer* Ren, const char *File, SDL_Rect* InRect, bool InReplaceble = false) { 
	MyTexture = IMG_LoadTexture(Ren, File);
	MyRect = *InRect;
	bReplaceble = InReplaceble;
	}

	void RenderThing(SDL_Renderer* RenRef) override { SDL_RenderCopy(RenRef, MyTexture, NULL, &MyRect); }

	void CleanupThing() override { SDL_DestroyTexture(MyTexture); }

	void SetPosition(int x, int y) override { 
		MyRect.x = x;
		MyRect.y = y;
	}

};

