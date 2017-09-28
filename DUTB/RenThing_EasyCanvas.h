#pragma once
#include "RenThing_Text.h"
#include "RenThing_Image.h"

class RenThing_EasyCanvas : public RenThing
{
public:

	RenThing_EasyCanvas(const char* InCharToLocate_Up, SDL_Color* NewDynamicColor_Up,
		const char* InCharToLocate_Bottom, SDL_Color* NewDynamicColor_Bottom, 
		Coordinates* InCoordinates, int* ResolXRef, int* ResolYRef, int LevelRenderRef = 1) {

		MyCoordinates = *InCoordinates;
		XResol = ResolXRef;
		YResol = ResolYRef;

		LevelRender = LevelRenderRef;

		
		Up_H = 0.55;

		Bottom_H = 0.3;

		UpText = new RenThing_Text(InCharToLocate_Up, NewDynamicColor_Up, MyCoordinates, ResolXRef, ResolYRef);

		UpText->SetFont(48);

		BottomText = new RenThing_Text(InCharToLocate_Bottom, NewDynamicColor_Bottom, MyCoordinates, ResolXRef, ResolYRef);

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
	
		ResetCoord();

		UpText->PrepareThing(RenRef);

		float Coefficient = float(MyRect.h * Up_H) / float(UpText->MyRect.h);
		UpText->MyRect.h = MyRect.h * Up_H;
		UpText->MyRect.w = UpText->MyRect.w * Coefficient;


		BottomText->PrepareThing(RenRef);

		Coefficient = float(MyRect.h * Bottom_H) / float(BottomText->MyRect.h);
		BottomText->MyRect.h = MyRect.h * Bottom_H;
		BottomText->MyRect.w = BottomText->MyRect.w * Coefficient;

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

		ResetCoord();

		UpText->SetPosition(x + (MyRect.w - UpText->MyRect.w) / 2, y + 0.05 * MyRect.h);

		BottomText->SetPosition(x + (MyRect.w - BottomText->MyRect.w) / 2, y + 0.65 * MyRect.h);
	}

private:


	float Up_H;
	RenThing_Text* UpText = nullptr;

	float Bottom_H;
	RenThing_Text* BottomText = nullptr;

};