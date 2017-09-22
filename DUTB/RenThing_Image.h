#pragma once
#include "RenThing.h"


class RenThing_Image : public RenThing

{

public:


	RenThing_Image(SDL_Renderer* Ren, const char *File, SDL_Rect* InRect, SDL_Color* ColorRef = nullptr) { 
	MyTexture = IMG_LoadTexture(Ren, File);
	MyRect = *InRect;

	if (ColorRef != nullptr)
	{
		SDL_SetTextureColorMod(MyTexture, ColorRef->r, ColorRef->g, ColorRef->b);
		SDL_SetTextureAlphaMod(MyTexture, ColorRef->a);
	}
	}

	void RenderThing(SDL_Renderer* RenRef) override { SDL_RenderCopy(RenRef, MyTexture, NULL, &MyRect); }

	void CleanupThing() override { SDL_DestroyTexture(MyTexture); }

	void SetPosition(int x, int y) override { 
		MyRect.x = x;
		MyRect.y = y;
	}

};

