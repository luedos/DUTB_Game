#pragma once
#include "RenThing_Text.h"
#include "RenThing_Image.h"

class RenThing_EasyCanvas : public RenThing
{
public:

	RenThing_EasyCanvas(const char* InCharToLocate_Up, SDL_Color* NewDynamicColor_Up, 
		const char* InCharToLocate_Bottom, SDL_Color* NewDynamicColor_Bottom, 
		SDL_Rect* InRect, bool InReplaceble = false) {
		
		//CleanupThing();

		bReplaceble = InReplaceble;

		MyRect = *InRect;

		UpRect.h = 0.55 * MyRect.h;

		BottomRect.h = 0.3 * MyRect.h;

		UpText = new RenThing_Text(InCharToLocate_Up, NewDynamicColor_Up, InRect);

		UpText->SetFont(48);

		BottomText = new RenThing_Text(InCharToLocate_Bottom, NewDynamicColor_Bottom, InRect);

		BottomText->SetFont(48);
	}

	void CleanupThing() override {
		if(UpText != nullptr)
			UpText->CleanupThing();
		delete UpText;
		UpText = nullptr;

		if(BottomText != nullptr)
			BottomText->CleanupThing();
		delete BottomText;
		BottomText = nullptr;
	} 

	void RenderThing(SDL_Renderer* RenRef) override {
		UpText->RenderThing(RenRef);
		BottomText->RenderThing(RenRef);
	}

	void PrepareThing(SDL_Renderer* RenRef) override {
	
		

		UpText->PrepareThing(RenRef);

		float Coefficient = float(UpRect.h) / float(UpText->MyRect.h);
		UpText->MyRect.h = UpRect.h;
		UpText->MyRect.w = UpText->MyRect.w * Coefficient;


		BottomText->PrepareThing(RenRef);

		Coefficient = float(BottomRect.h) / float(BottomText->MyRect.h);
		BottomText->MyRect.h = BottomRect.h;
		BottomText->MyRect.w = BottomText->MyRect.w * Coefficient;

	}

	void SetPosition(int x, int y) override {
		MyRect.x = x;
		MyRect.y = y;

		UpText->SetPosition(x + (MyRect.w - UpText->MyRect.w) / 2, y + 0.05 * MyRect.h);

		BottomText->SetPosition(x + (MyRect.w - BottomText->MyRect.w) / 2, y + 0.65 * MyRect.h);
	}


	SDL_Rect UpRect;
	RenThing_Text* UpText = nullptr;

	SDL_Rect BottomRect;
	RenThing_Text* BottomText = nullptr;

};