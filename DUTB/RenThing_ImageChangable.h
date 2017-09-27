#pragma once
#include "RenThing_Image.h"

class RenThing_ImageChangable : public RenThing
{
public:
	RenThing_ImageChangable(SDL_Renderer* Ren, const char *File, SDL_Rect* InRect, int* InInt, int RenderMode_X_Y_Both = 0, SDL_Color* ColorRef = nullptr, int LevelRenderRef = 1) {

		LevelRender = LevelRenderRef;

		SDL_Color TestColor = { 225, 225, 225, 225 };

		if (ColorRef == nullptr)
			MyColor = &TestColor;
		else
			MyColor = ColorRef;

		

		RenderMode = RenderMode_X_Y_Both;

		IntRef = InInt;

		MyTexture = IMG_LoadTexture(Ren, File);

		

		MyRect = *InRect;

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

		SDL_SetTextureColorMod(MyTexture, MyColor->r, MyColor->g, MyColor->b);

		SDL_SetTextureAlphaMod(MyTexture, MyColor->a);

		SDL_RenderCopy(RenRef, MyTexture, &StandartRect, &MyRect); }

	void CleanupThing() override { SDL_DestroyTexture(MyTexture); }

	void SetPosition(int x, int y) override {
		MyRect.x = x;
		MyRect.y = y;
	}

private:
	int RenderMode;

	SDL_Rect StandartRect;

	int* IntRef;

	SDL_Color* MyColor;
};
