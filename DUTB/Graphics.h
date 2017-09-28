#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "RenThing_Text.h"
#include "RenThing_ImageChangable.h"
#include "RenThing_EasyCanvas.h"
#include "RenThing_Button_DDMenu.h"
#include "RenThing_Canvas.h"
#include "RenThing_PercentBar.h"

using namespace std;

class Graphics

{
public:

	Graphics();
	~Graphics();

	RenThing* AddStaticText(const char* InCharRef, SDL_Color InStatColor, Coordinates* InCoord, RenThing_Canvas* CanvasRef = nullptr, int RenLevel = 1) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InStatColor, InCoord, &X_Resolution, &Y_Resolution, RenLevel));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Text(InCharRef, InStatColor, InCoord, &X_Resolution, &Y_Resolution, RenLevel));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}		
	}

	RenThing* AddDynamicText(const char* InCharRef, SDL_Color* InDynColor, Coordinates* InCoord, RenThing_Canvas* CanvasRef = nullptr, int RenLevel = 1) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InDynColor, *InCoord, &X_Resolution, &Y_Resolution, RenLevel));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Text(InCharRef, InDynColor, *InCoord, &X_Resolution, &Y_Resolution, RenLevel));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}
	}

	RenThing* AddStaticImage(char *FileName , Coordinates* InCoord, RenThing_Canvas* CanvasRef = nullptr, SDL_Color* ColorRef = nullptr, int RenLevel = 0) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Image(MyRenderer, FileName, InCoord, &X_Resolution, &Y_Resolution, ColorRef, RenLevel));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Image(MyRenderer, FileName, InCoord, &X_Resolution, &Y_Resolution, ColorRef, RenLevel));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}
	}

	RenThing* AddDynamicImage(char *FileName, Coordinates* InCoord, int* InIntRef, RenThing_Canvas* CanvasRef = nullptr, int RenderMode_X_Y_Both_Ref= 0, SDL_Color* ColoRef = nullptr, int RenLevel = 1) {
		
		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_ImageChangable(MyRenderer, FileName,  InIntRef, InCoord, &X_Resolution, &Y_Resolution, RenderMode_X_Y_Both_Ref, ColoRef, RenLevel));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InIntRef, InCoord, &X_Resolution, &Y_Resolution, RenderMode_X_Y_Both_Ref, ColoRef, RenLevel));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}		
	}

	RenThing* AddCanvas_TextText(const char* InCharToLocate_UpRef, SDL_Color* NewDynamicColor_UpRef,
		const char* InCharToLocate_BottomRef, SDL_Color* NewDynamicColor_BottomRef,
		Coordinates* InCoord, RenThing_Canvas* CanvasRef = nullptr, int RenLevel = 1) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_EasyCanvas(InCharToLocate_UpRef, NewDynamicColor_UpRef, InCharToLocate_BottomRef, NewDynamicColor_BottomRef, InCoord, &X_Resolution, &Y_Resolution, RenLevel));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_EasyCanvas(InCharToLocate_UpRef, NewDynamicColor_UpRef, InCharToLocate_BottomRef, NewDynamicColor_BottomRef, InCoord, &X_Resolution, &Y_Resolution, RenLevel));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}

	}

	RenThing_Canvas* AddCanvas(Coordinates* InCoord, const char* BackGroundFile = nullptr, SDL_Color* ColorRef = nullptr, int RenLevel = 1)
	{
		CanvasVector.push_back(new RenThing_Canvas(InCoord, &X_Resolution, &Y_Resolution, MyRenderer, BackGroundFile, ColorRef, RenLevel));
		RenderOrder.push_back(CanvasVector.back());
		return CanvasVector.back();
	}

	RenThing* AddPercentBar(Coordinates* InCoord, float* PercetRef, SDL_Color* BackColorRef = nullptr, SDL_Color* FrontColorRef = nullptr, RenThing_Canvas* CanvasRef = nullptr, int RenLevel = 1)
	{
		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_PercentBar(MyRenderer, PercetRef, InCoord, &X_Resolution, &Y_Resolution, BackColorRef, FrontColorRef, RenLevel));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{
			CanvasRef->MyThingVector.push_back(new RenThing_PercentBar(MyRenderer, PercetRef, InCoord, &X_Resolution, &Y_Resolution, BackColorRef, FrontColorRef, RenLevel));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}
	}

	template<class T, class M>
	RenThing_Button* AddButton(T* MyClass, M MyMethod, const char* ButtonTextRef, 
		Coordinates* InCoord, SDL_Color BGColorRef = { 150,150,150,120 }, SDL_Color BGColor_PressedRef = { 100,100,100,180 },
		SDL_Color BGColor_HoveredRef = {120,120,120,150}, int RenLevel = 1) {
		
		RenThing_Button* TestTest = new RenThing_Button(ButtonTextRef, &BGColorRef, &BGColor_PressedRef, &BGColor_HoveredRef, InCoord, &X_Resolution, &Y_Resolution, RenLevel);

		TestTest->ConnectNew(MyClass, MyMethod);

		ButtonsArray.push_back(TestTest);
		RenderOrder.push_back(ButtonsArray.back());
		return ButtonsArray.back();

	}

	RenThing_Button_DDMenu* AddDDMenu(const char* ButtonTextRef, Coordinates* InCoord, SDL_Color BGColorRef = { 150,150,150,120 },
		SDL_Color BGColor_PressedRef = { 100,100,100,180 }, SDL_Color BGColor_HoveredRef = { 120,120,120,150 }, int LevelRenderRef = 1) {

		RenThing_Button_DDMenu* TestTest = new RenThing_Button_DDMenu(ButtonTextRef, &BGColorRef, &BGColor_PressedRef, &BGColor_HoveredRef, InCoord, &X_Resolution, &Y_Resolution, LevelRenderRef);

		ButtonsArray.push_back(TestTest);
		RenderOrder.push_back(ButtonsArray.back());
		return TestTest;
	}

	void ChangeWindowSize(int x, int y);

	void ChangeWindowMode(bool IsFullscreen);

	void RenderEverything(float DeltaTime);

	void ClearEverything();

	void DestroyEveryThing();

	int CreateWindow(int WindowSizeX, int WindowSizeY);

	bool DeleteRenThing(RenThing* ThingToDelete);

	vector<RenThing_Button*> ButtonsArray;

	bool bIsFullscreen = false;

	int X_Resolution, Y_Resolution;

	void Resolution800x600() { ChangeWindowSize(800, 600); }

	void Resolution1280x720() { ChangeWindowSize(1280, 720); }

	void Resolution1600x900() { ChangeWindowSize(1600, 900); }

	void WindFullscreen() { ChangeWindowMode(true); }

	void WindWindowed() { ChangeWindowMode(false); }

private:

	vector<RenThing_Canvas*> CanvasVector;

	SDL_Renderer* MyRenderer;
	SDL_Window* MyWindow;

	vector<RenThing*> RestThings;

	SDL_Texture* BackGroundTexture;
	SDL_Rect BackgroundRect;

	vector<RenThing*> RenderOrder;
};

