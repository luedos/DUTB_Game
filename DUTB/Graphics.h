#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "RenThing_Text.h"
#include "RenThing_ImageChangable.h"

using namespace std;

class Graphics

{
public:

	Graphics();
	~Graphics();

	RenThing* AddStaticText(int Level,const char* InCharRef, SDL_Color InStatColor, SDL_Rect* InRect, bool DoesReplaceble = false) {
		switch (Level)
		{
		case 1:
		{
			MainTests.push_back(new RenThing_Text(InCharRef, InStatColor, InRect, DoesReplaceble));
			return MainTests.back();
		}
		case 2:
		{
			SideTests.push_back(new RenThing_Text(InCharRef, InStatColor, InRect, DoesReplaceble));
			return SideTests.back();
		}
		default:
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InStatColor, InRect, DoesReplaceble));
			return RestThings.back();
		}
		}
		
	}

	RenThing* AddDynamicText(int Level, const char* InCharRef, SDL_Color* InDynColor, SDL_Rect* InRect, bool DoesReplaceble = false) {
		switch (Level)
		{
		case 1:
		{
			MainTests.push_back(new RenThing_Text(InCharRef, InDynColor, InRect, DoesReplaceble));
			return MainTests.back();
		}
		case 2:
		{
			SideTests.push_back(new RenThing_Text(InCharRef, InDynColor, InRect, DoesReplaceble));
			return SideTests.back();
		}
		default:
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InDynColor, InRect, DoesReplaceble));
			return RestThings.back();
		}
		}
	}

	RenThing* AddStaticImage(int Level, char *FileName ,SDL_Rect* InRect, bool DoesReplaceble = false) {
		switch (Level)
		{
		case 1:
		{
			MainTests.push_back(new RenThing_Image(MyRenderer, FileName, InRect, DoesReplaceble));
			return MainTests.back();
		}
		case 2:
		{
			SideTests.push_back(new RenThing_Image(MyRenderer, FileName, InRect, DoesReplaceble));
			return SideTests.back();
		}
		default:
		{
			RestThings.push_back(new RenThing_Image(MyRenderer, FileName, InRect, DoesReplaceble));
			return RestThings.back();
		}
		}

	}

	RenThing* AddDynamicImage(int Level, char *FileName, SDL_Rect* InRect, int* InIntRef, bool DoesReplaceble = false, int RenderMode_X_Y_Both_Ref= 0) {
		switch (Level)
		{
		case 1:
		{
			MainTests.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, DoesReplaceble, RenderMode_X_Y_Both_Ref));
			return MainTests.back();
		}
		case 2:
		{
			SideTests.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, DoesReplaceble, RenderMode_X_Y_Both_Ref));
			return SideTests.back();
		}
		default:
		{
			RestThings.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, DoesReplaceble, RenderMode_X_Y_Both_Ref));
			return RestThings.back();
		}
		}
		
	}



	void RenderEverything();

	void ClearEverything();

	void DestroyEveryThing();

	int CreateWindow(int WindowSizeX, int WindowSizeY);

	bool DeleteRenThing(RenThing* ThingToDelete);

	void ReReplace();

private:

	SDL_Renderer* MyRenderer;
	SDL_Window* MyWindow;

	vector<RenThing*> MainTests;

	vector<RenThing*> SideTests;

	vector<RenThing*> RestThings;

	SDL_Rect MainBoard;
	SDL_Rect SideBoard;

	SDL_Texture* BackGroundTexture;
	SDL_Rect BackgroundRect;


};

