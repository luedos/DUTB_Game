#pragma once
#include "RenThing_Image.h"

class RenThing_ImageChangable : public RenThing
{
public:
	RenThing_ImageChangable(SDL_Renderer* Ren, const char *File, SDL_Rect* InRect, int* InInt, bool InReplaceble = false, int RenderMode_X_Y_Both = 0) {

		RenderMode = RenderMode_X_Y_Both;

		IntRef = InInt;

		MyTexture = IMG_LoadTexture(Ren, File);
		MyRect = *InRect;
		bReplaceble = InReplaceble;

		StandartRect.w = MyRect.w;
		StandartRect.h = MyRect.h;
	}

	void RenderThing(SDL_Renderer* RenRef) override { 

		switch (RenderMode)
		{
		case 0:
		{
			StandartRect.y = 0;
			StandartRect.x = *IntRef * StandartRect.w;
			break;
		}
		case 1:
		{
			StandartRect.x = 0;
			StandartRect.y = *IntRef * StandartRect.h;
			break;
		}
		case 2:
		{
			StandartRect.y = *IntRef * StandartRect.h;
			StandartRect.x = *IntRef * StandartRect.w;
			break;
		}

		default:
			break;
		}

		SDL_RenderCopy(RenRef, MyTexture, &StandartRect, &MyRect); }

	void CleanupThing() override { SDL_DestroyTexture(MyTexture); }

	int RenderMode;

	SDL_Rect StandartRect;

	int* IntRef;

};
