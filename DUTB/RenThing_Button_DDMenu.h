#pragma once
#include "RenThing_Button.h"
#include <iostream>
#include <vector>
using namespace std;

class RenThing_Button_DDMenu : public RenThing_Button
{
public:

	RenThing_Button_DDMenu(const char* ButtonTextRef, SDL_Rect* InRect, SDL_Color* BGColorRef, SDL_Color* BGColor_PressedRef, SDL_Color* BGColor_HoveredRef, int LevelRenderRef = 1) {
		
		LevelRender = LevelRenderRef;

		RealButtonRect = *InRect;

		ButtonText = ButtonTextRef;

		BGColor_Idle = *BGColorRef;

		BGColor_Hovered = *BGColor_HoveredRef;

		BGColor_Pressed = *BGColor_PressedRef;

		OpenDDFunc(false);

		SetFont(48);
	}

	void CleanupThing() override {}

	void RenderThing(SDL_Renderer* RenRef) override {

		SDL_RenderCopy(RenRef, BackgroundTexture, NULL, &MyRect);

		SDL_RenderCopy(RenRef, MyTexture, NULL, &TextRect);

		if (OpenDD)
			for (int i = 0; i < DDButtonVector.size(); i++)
				DDButtonVector.at(i)->RenderThing(RenRef);

	}

	void PrepareThing(SDL_Renderer* RenRef) override {

		SDL_Color ColorToUse = { 225,225,225,225 };

		Surface = TTF_RenderText_Blended(Font, ButtonText, ColorToUse);
		MyTexture = SDL_CreateTextureFromSurface(RenRef, Surface);
		SDL_FreeSurface(Surface);

		SDL_QueryTexture(MyTexture, NULL, NULL, &TextRect.w, &TextRect.h);

		TextRect.x = RealButtonRect.x + float(RealButtonRect.w - TextRect.w) / 2;

		TextRect.y = RealButtonRect.y + float(RealButtonRect.h - TextRect.h) / 2;

		if (BackgroundTexture == nullptr)
		{
			BackgroundTexture = IMG_LoadTexture(RenRef, "../DUTB/Textures/SimpleWhite.png");
			if (BackgroundTexture == nullptr)
			{
				cout << "Bad Background" << endl;
				SDL_Quit();
			}
		}

		SDL_SetTextureColorMod(BackgroundTexture, BGColor->r, BGColor->g, BGColor->b);

		SDL_SetTextureAlphaMod(BackgroundTexture, BGColor->a);
		
		if(OpenDD)
			for (int i = 0; i < DDButtonVector.size(); i++)
			{
				DDButtonVector.at(i)->PrepareThing(RenRef);
				DDButtonVector.at(i)->SetPosition(RealButtonRect.x, RealButtonRect.y + RealButtonRect.h + i * RealButtonRect.h * 0.8f);
			}
	}

	void ButtonPressed() override {
		IsPressed = true;
	}

	void ButtonHovered(int x, int y) override {
		if (!IsPressed && MyRect.x < x && MyRect.y < y && MyRect.x + MyRect.w > x && MyRect.y + MyRect.h > y)
			BGColor = &BGColor_Hovered;
		else
			if (IsPressed)
				BGColor = &BGColor_Pressed;
			else
				BGColor = &BGColor_Idle;

		if (OpenDD)
			for (int i = 0; i < DDButtonVector.size(); i++)
				DDButtonVector.at(i)->ButtonHovered(x, y);
	}

	void ButtonUnpressed(int x, int y, bool IsOnThis) override{

		IsPressed = false;

		if (IsOnThis)
			if (MyRect.x < x && MyRect.y < y && MyRect.x + MyRect.w > x && MyRect.y + MyRect.h > y && OpenDD)
				for (int i = 0; i < DDButtonVector.size(); i++)
					if (DDButtonVector.at(i)->MyRect.x < x
						&& DDButtonVector.at(i)->MyRect.y < y
						&& DDButtonVector.at(i)->MyRect.x + DDButtonVector.at(i)->MyRect.w > x
						&& DDButtonVector.at(i)->MyRect.y + DDButtonVector.at(i)->MyRect.h > y)
					{
						DDButtonVector.at(i)->ButtonUnpressed(x, y, true);
						break;
					}



			if (RealButtonRect.x < x && RealButtonRect.y < y && RealButtonRect.x + RealButtonRect.w > x && RealButtonRect.y + RealButtonRect.h > y && !OpenDD && IsOnThis)
				OpenDDFunc(true);
			else
				if (OpenDD)
					OpenDDFunc(false);
		
	}

	void OpenDDFunc(bool InPoint) {
		OpenDD = InPoint;
		if (OpenDD)
		{
			MyRect = RealButtonRect;
			MyRect.h = (DDButtonVector.size() * 0.8f + 1.f) * RealButtonRect.h;
			LevelRender++;
		}
		else
		{
			MyRect = RealButtonRect;
			LevelRender--;
		}
	}

	template<typename T, typename M>
	void AddDDButton(T* ClassRef, M MethodRef, const char* DDName) {
		SDL_Rect NewRect;
		
		NewRect.h = RealButtonRect.h * 0.8f;
		NewRect.w = RealButtonRect.w;

		DDButtonVector.push_back(new RenThing_Button(DDName, &NewRect, &BGColor_Idle, &BGColor_Pressed, &BGColor_Hovered));
		DDButtonVector.back()->ConnectNew(ClassRef, MethodRef);
	}

	bool OpenDD;

	SDL_Rect RealButtonRect;

	RenThing_Button* ButtonInCharge;

	vector<RenThing_Button*> DDButtonVector;
	
};