#pragma once
#include "RenThing.h"
#include <string>
#include <iostream>
#include "SDL2/include/SDL_ttf.h"

using namespace std;

class RenThing_Text : public RenThing
{
public:

	RenThing_Text(const char* InCharToLocate, SDL_Color NewStaticColor, SDL_Rect* InRect, bool InReplaceble = false) {
		bReplaceble = InReplaceble;
		UseStaticColor = true;
		StaticColor = NewStaticColor;
		MyRect = *InRect;
		SomeToRender = InCharToLocate;
	}

	RenThing_Text(const char* InCharToLocate, SDL_Color* NewDynamicColor, SDL_Rect* InRect, bool InReplaceble = false) {
		bReplaceble = InReplaceble;
		UseStaticColor = false;
		DynamicColor = NewDynamicColor;
		MyRect = *InRect;
		SomeToRender = InCharToLocate;

	}


	void RenderThing(SDL_Renderer* RenRef) override {

		SDL_RenderCopy(RenRef, MyTexture, NULL, &MyRect);
	}

	void CleanupThing() override { TTF_CloseFont(Font);
	SDL_DestroyTexture(MyTexture);
	}

	void PrepareThing(SDL_Renderer* RenRef) override {
		SDL_Color ColorToUse;
		if (UseStaticColor)
			ColorToUse = StaticColor;
		else
			ColorToUse = *DynamicColor;

		Surface = TTF_RenderText_Solid(Font, SomeToRender, ColorToUse);
		MyTexture = SDL_CreateTextureFromSurface(RenRef, Surface);
		SDL_FreeSurface(Surface);
		SDL_QueryTexture(MyTexture, NULL, NULL, &MyRect.w, &MyRect.h);
	}

	TTF_Font* Font = TTF_OpenFont("../DUTB/Fonts/RiseOfKingdom.ttf", 48);

	const char* SomeToRender;

	SDL_Surface* Surface;

	SDL_Color StaticColor;
	SDL_Color* DynamicColor;

	bool UseStaticColor = true;


};