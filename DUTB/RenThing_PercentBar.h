#pragma once
#include "RenThing.h"

class RenThing_PercentBar : public RenThing
{
public:


	RenThing_PercentBar(SDL_Renderer* Ren, float* PercetRef,
		Coordinates* InCoordinates, int* ResolXRef, int* ResolYRef,
		SDL_Color* BackColorRef = nullptr, SDL_Color* FrontColorRef = nullptr, int LevelRenderRef = 1) {

		MyCoordinates = *InCoordinates;
		XResol = ResolXRef;
		YResol = ResolYRef;

		LevelRender = LevelRenderRef;

		Percent = PercetRef;

		MyTexture = IMG_LoadTexture(Ren, "../DUTB/Textures/SimpleWhite.png");

		FrontTexture = IMG_LoadTexture(Ren, "../DUTB/Textures/SimpleWhite.png");

		if (FrontColorRef != nullptr)
		{
			SDL_SetTextureColorMod(FrontTexture, FrontColorRef->r, FrontColorRef->g, FrontColorRef->b);
			SDL_SetTextureAlphaMod(FrontTexture, FrontColorRef->a);
		}
		else
		{
			SDL_SetTextureColorMod(FrontTexture, 170,200,0);
		}
		if (BackColorRef != nullptr)
		{
			SDL_SetTextureColorMod(FrontTexture, BackColorRef->r, BackColorRef->g, BackColorRef->b);
			SDL_SetTextureAlphaMod(FrontTexture, BackColorRef->a);
		}
	}

	void PrepareThing(SDL_Renderer* RenRef) override {

		ResetCoord();
		FrontRect = MyRect;
		FrontRect.w = *Percent * MyRect.w;
	}

	void RenderThing(SDL_Renderer* RenRef) override { 
		SDL_RenderCopy(RenRef, MyTexture, NULL, &MyRect); 
		SDL_RenderCopy(RenRef, FrontTexture, NULL, &FrontRect);
	}

	void CleanupThing() override { 
		SDL_DestroyTexture(MyTexture); 
		SDL_DestroyTexture(FrontTexture);
	}

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

	SDL_Rect FrontRect;

	float* Percent;

	SDL_Color BackColor;
	SDL_Color FrontColor;

	SDL_Texture* FrontTexture;

};
