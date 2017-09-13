#pragma once
#include <vector>
#include "RenThing_Image.h"

using namespace std;


class RenThing_Canvas : public RenThing
{
public:

	RenThing_Canvas(SDL_Rect* InRect, bool DoBackGround = false, SDL_Renderer* RenRef = nullptr, const char* BackGroundFile = nullptr) {
	
		MyRect = *InRect;

		if (DoBackGround && RenRef != nullptr && BackGroundFile != nullptr)
			MyBackground = new RenThing_Image(RenRef, BackGroundFile, InRect);


	
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
	
		for (int i = 0; i < MyThingVector.size(); i++)
			MyThingVector.at(i)->PrepareThing(RenRef);

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
		MyRect.x = x;
		MyRect.y = y;
	}

	RenThing_Image* MyBackground = nullptr;

	vector<RenThing*> MyThingVector;

	float DeltaTime = 0.00001f;

};
