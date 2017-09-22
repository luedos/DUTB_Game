#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "RenThing_Text.h"
#include "RenThing_ImageChangable.h"
#include "RenThing_EasyCanvas.h"
#include "RenThing_Button.h"
#include "RenThing_Canvas.h"
#include "RenThing_PercentBar.h"

using namespace std;

class Graphics

{
public:

	Graphics();
	~Graphics();

	RenThing* AddStaticText(const char* InCharRef, SDL_Color InStatColor, SDL_Rect* InRect, RenThing_Canvas* CanvasRef = nullptr) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InStatColor, InRect));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Text(InCharRef, InStatColor, InRect));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}		
	}

	RenThing* AddDynamicText(const char* InCharRef, SDL_Color* InDynColor, SDL_Rect* InRect, RenThing_Canvas* CanvasRef = nullptr) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InDynColor, InRect));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Text(InCharRef, InDynColor, InRect));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}
	}

	RenThing* AddStaticImage(char *FileName ,SDL_Rect* InRect, RenThing_Canvas* CanvasRef = nullptr, SDL_Color* ColorRef = nullptr) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Image(MyRenderer, FileName, InRect, ColorRef));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Image(MyRenderer, FileName, InRect, ColorRef));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}
	}

	RenThing* AddDynamicImage(char *FileName, SDL_Rect* InRect, int* InIntRef, RenThing_Canvas* CanvasRef = nullptr, int RenderMode_X_Y_Both_Ref= 0, SDL_Color* ColoRef = nullptr) {
		
		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, RenderMode_X_Y_Both_Ref, ColoRef));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, RenderMode_X_Y_Both_Ref, ColoRef));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}		
	}

	RenThing* AddCanvas_TextText(const char* InCharToLocate_UpRef, SDL_Color* NewDynamicColor_UpRef,
		const char* InCharToLocate_BottomRef, SDL_Color* NewDynamicColor_BottomRef,
		SDL_Rect* InRectRef, RenThing_Canvas* CanvasRef = nullptr) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_EasyCanvas(InCharToLocate_UpRef, NewDynamicColor_UpRef, InCharToLocate_BottomRef, NewDynamicColor_BottomRef, InRectRef));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_EasyCanvas(InCharToLocate_UpRef, NewDynamicColor_UpRef, InCharToLocate_BottomRef, NewDynamicColor_BottomRef, InRectRef));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}

	}

	RenThing_Canvas* AddCanvas(SDL_Rect* InRect, bool DoBackGround = false, const char* BackGroundFile = nullptr)
	{
		CanvasVector.push_back(new RenThing_Canvas(InRect, DoBackGround, MyRenderer, BackGroundFile));
		RenderOrder.push_back(CanvasVector.back());
		return CanvasVector.back();
	}

	RenThing* AddPercentBar(SDL_Rect* InRect, float* PercetRef, SDL_Color* BackColorRef = nullptr, SDL_Color* FrontColorRef = nullptr, RenThing_Canvas* CanvasRef = nullptr)
	{
		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_PercentBar(MyRenderer, InRect, PercetRef, BackColorRef, FrontColorRef));
			RenderOrder.push_back(RestThings.back());
			return RestThings.back();
		}
		else
		{
			CanvasRef->MyThingVector.push_back(new RenThing_PercentBar(MyRenderer, InRect, PercetRef, BackColorRef, FrontColorRef));
			RenderOrder.push_back(CanvasRef->MyThingVector.back());
			return CanvasRef->MyThingVector.back();
		}
	}

	template<class T, class M>
	RenThing_Button* AddButton(T* MyClass, M MyMethod, const char* ButtonTextRef, SDL_Rect* InRect, SDL_Color BGColorRef = { 150,150,150,120 }, SDL_Color BGColor_PressedRef = { 100,100,100,180 }, SDL_Color BGColor_HoveredRef = {120,120,120,150}) {
		
		RenThing_Button* TestTest = new RenThing_Button(ButtonTextRef, InRect, &BGColorRef, &BGColor_PressedRef, &BGColor_HoveredRef);

		TestTest->ConnectNew(MyClass, MyMethod);

		ButtonsArray.push_back(TestTest);
		RenderOrder.push_back(ButtonsArray.back());
		return ButtonsArray.back();

	}

	void RenderEverything(float DeltaTime);

	void ClearEverything();

	void DestroyEveryThing();

	int CreateWindow(int WindowSizeX, int WindowSizeY);

	bool DeleteRenThing(RenThing* ThingToDelete);

	vector<RenThing_Button*> ButtonsArray;

private:

	vector<RenThing_Canvas*> CanvasVector;

	SDL_Renderer* MyRenderer;
	SDL_Window* MyWindow;

	vector<RenThing*> RestThings;

	SDL_Texture* BackGroundTexture;
	SDL_Rect BackgroundRect;

	vector<RenThing*> RenderOrder;
};

