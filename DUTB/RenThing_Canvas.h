#pragma once
#include <vector>
#include "RenThing_Image.h"

using namespace std;


class RenThing_Canvas : public RenThing
{
public:

	RenThing_Canvas(Coordinates* InCoordinates, int* ResolXRef, int* ResolYRef,
		SDL_Renderer* RenRef = nullptr, const char* BackGroundFile = nullptr, SDL_Color* ColorRef = nullptr, int LevelRenderRef = 1) {
	
		MyCoordinates = *InCoordinates;
		XResol = ResolXRef;
		YResol = ResolYRef;

		LevelRender = LevelRenderRef;

		

		if (ColorRef != nullptr && RenRef != nullptr && BackGroundFile != nullptr)
			MyBackground = new RenThing_Image(RenRef, BackGroundFile, &MyCoordinates, ResolXRef, ResolYRef, ColorRef);
	}

	void CleanupThing() override {
		for (int i = 0; i < MyThingVector.size(); i++)
		{
			MyThingVector.at(i)->CleanupThing();
			delete MyThingVector.at(i);
		}
		MyThingVector.clear();

		delete MyBackground;
		MyBackground = nullptr;
	}

	void RenderThing(SDL_Renderer* RenRef) override {
	
		if (MyBackground != nullptr)
			MyBackground->RenderThing(RenRef);

		for (int i = 0; i < MyThingVector.size(); i++)
			MyThingVector.at(i)->RenderThing(RenRef);
	
	}

	void PrepareThing(SDL_Renderer* RenRef) override {
	
		if (MyBackground != nullptr)
			MyBackground->PrepareThing(RenRef);

		for (int i = 0; i < MyThingVector.size(); i++)
			MyThingVector.at(i)->PrepareThing(RenRef);

		ResetCoord();

		SDL_Rect LocalRect;
		LocalRect.x = MyRect.x;
		LocalRect.y = MyRect.y;

		// Оба цикла служат для переназначения позиций штук
		for (int i = 0; i < MyThingVector.size(); i++)
		{
			LocalRect.w = MyThingVector.at(i)->MyRect.w;
			LocalRect.h = MyThingVector.at(i)->MyRect.h;

			if (LocalRect.x + LocalRect.w > MyRect.x + MyRect.w)
			{
				LocalRect.x = MyRect.x;
				LocalRect.y += 50;
			}

			if (MyThingVector.at(i)->FirstCreated)
			{
				MyThingVector.at(i)->SetPosition(LocalRect.x, LocalRect.y);
				MyThingVector.at(i)->FirstCreated = false;
			}
			else
				MyThingVector.at(i)->InterpPosition(LocalRect.x, LocalRect.y, DeltaTime, 1.25f);

			LocalRect.x += LocalRect.w + 15;
		}

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

	virtual void ResetCoord() {

		if (MyCoordinates.bRelativeX)
			MyRect.x = *XResol * MyCoordinates.X;
		else
			MyRect.x = MyCoordinates.X;

		if (MyCoordinates.bRelativeY)
			MyRect.y = *YResol * MyCoordinates.Y;
		else
			MyRect.y = MyCoordinates.Y;

		if (MyCoordinates.bRelativeW)
			MyRect.w = *XResol * MyCoordinates.W;
		else
			MyRect.w = MyCoordinates.W;

		if (MyCoordinates.bRelativeH)
			MyRect.h = *YResol * MyCoordinates.H;
		else
			MyRect.h = MyCoordinates.H;

		if (MyBackground != nullptr)
			MyBackground->MyCoordinates = MyCoordinates;
	}

	float DeltaTime = 0.00001f;

	vector<RenThing*> MyThingVector;

private:

	RenThing_Image* MyBackground = nullptr;
};
