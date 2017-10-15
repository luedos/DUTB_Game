#pragma once
#include "RenThing_Image.h"

class RenThing_ImageChangable : public RenThing
{
public:
	RenThing_ImageChangable(SDL_Renderer* Ren, const char *File, int* InInt,
		Coordinates* InCoordinates, int* ResolXRef, int* ResolYRef,
		int RenderMode_X_Y_Both = 0, SDL_Color* ColorRef = nullptr, int LevelRenderRef = 1) {

		MyCoordinates = *InCoordinates;
		XResol = ResolXRef;
		YResol = ResolYRef;

		LevelRender = LevelRenderRef;

		SDL_Color TestColor = { 225, 225, 225, 225 };

		if (ColorRef == nullptr)
			MyColor = &TestColor;
		else
			MyColor = ColorRef;

		RenderMode = RenderMode_X_Y_Both;

		IntRef = InInt;

		MyTexture = IMG_LoadTexture(Ren, File);

		StandartRect.w = MyRect.w;
		StandartRect.h = MyRect.h;
	}

	void PrepareThing(SDL_Renderer* RenRef) override { ResetCoord(); }

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

		int LocalX = x;
		int LocalY = y;


		if (MyCoordinates.bRelativeX)
			MyCoordinates.X = float(LocalX) / *XResol;
		else
			MyCoordinates.X = LocalX;

		if (MyCoordinates.bRelativeY)
			MyCoordinates.Y = float(LocalY) / *YResol;
		else
			MyCoordinates.Y = LocalY;
	}

private:
	int RenderMode;

	SDL_Rect StandartRect;

	int* IntRef;

	SDL_Color* MyColor;
};
