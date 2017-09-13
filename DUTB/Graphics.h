#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "RenThing_Text.h"
#include "RenThing_ImageChangable.h"
#include "RenThing_EasyCanvas.h"
#include "RenThing_Button.h"
#include "RenThing_Canvas.h"

using namespace std;

class Graphics

{
public:

	Graphics();
	~Graphics();

	RenThing* AddStaticText(const char* InCharRef, SDL_Color InStatColor, SDL_Rect* InRect, RenThing_Canvas* CanvasRef = nullptr, bool DoesReplaceble = false) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InStatColor, InRect, DoesReplaceble));
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Text(InCharRef, InStatColor, InRect, DoesReplaceble));
			return CanvasRef->MyThingVector.back();
		}		
	}

	RenThing* AddDynamicText(const char* InCharRef, SDL_Color* InDynColor, SDL_Rect* InRect, RenThing_Canvas* CanvasRef = nullptr, bool DoesReplaceble = false) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Text(InCharRef, InDynColor, InRect, DoesReplaceble));
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Text(InCharRef, InDynColor, InRect, DoesReplaceble));
			return CanvasRef->MyThingVector.back();
		}
	}

	RenThing* AddStaticImage(char *FileName ,SDL_Rect* InRect, RenThing_Canvas* CanvasRef = nullptr, bool DoesReplaceble = false) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_Image(MyRenderer, FileName, InRect, DoesReplaceble));
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_Image(MyRenderer, FileName, InRect, DoesReplaceble));
			return CanvasRef->MyThingVector.back();
		}
	}

	RenThing* AddDynamicImage(char *FileName, SDL_Rect* InRect, int* InIntRef, RenThing_Canvas* CanvasRef = nullptr, bool DoesReplaceble = false, int RenderMode_X_Y_Both_Ref= 0, SDL_Color* ColoRef = nullptr) {
		
		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, DoesReplaceble, RenderMode_X_Y_Both_Ref, ColoRef));
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_ImageChangable(MyRenderer, FileName, InRect, InIntRef, DoesReplaceble, RenderMode_X_Y_Both_Ref, ColoRef));
			return CanvasRef->MyThingVector.back();
		}		
	}

	RenThing* AddCanvas_TextText(const char* InCharToLocate_UpRef, SDL_Color* NewDynamicColor_UpRef,
		const char* InCharToLocate_BottomRef, SDL_Color* NewDynamicColor_BottomRef,
		SDL_Rect* InRectRef, RenThing_Canvas* CanvasRef = nullptr, bool InReplacebleRef = false) {

		if (CanvasRef == nullptr)
		{
			RestThings.push_back(new RenThing_EasyCanvas(InCharToLocate_UpRef, NewDynamicColor_UpRef, InCharToLocate_BottomRef, NewDynamicColor_BottomRef, InRectRef, InReplacebleRef));
			return RestThings.back();
		}
		else
		{

			CanvasRef->MyThingVector.push_back(new RenThing_EasyCanvas(InCharToLocate_UpRef, NewDynamicColor_UpRef, InCharToLocate_BottomRef, NewDynamicColor_BottomRef, InRectRef, InReplacebleRef));
			return CanvasRef->MyThingVector.back();
		}

	}

	RenThing_Canvas* AddCanvas(SDL_Rect* InRect, bool DoBackGround = false, const char* BackGroundFile = nullptr)
	{
		CanvasVector.push_back(new RenThing_Canvas(InRect, DoBackGround, MyRenderer, BackGroundFile));
		return CanvasVector.back();
	}

	template<class T, class M>
	RenThing_Button* AddButton(T* MyClass, M MyMethod, const char* ButtonTextRef, SDL_Rect* InRect, SDL_Color BGColorRef = { 150,150,150,120 }, SDL_Color BGColor_PressedRef = {100,100,100,180}) {
		
		


		RenThing_Button* TestTest = new RenThing_Button(ButtonTextRef, InRect, &BGColorRef, &BGColor_PressedRef);

		TestTest->ConnectNew(MyClass, MyMethod);

		ButtonsArray.push_back(TestTest);
		return ButtonsArray.back();

	}

	void RenderEverything(float DeltaTime);

	void ClearEverything();

	void DestroyEveryThing();

	int CreateWindow(int WindowSizeX, int WindowSizeY);

	bool DeleteRenThing(RenThing* ThingToDelete);

	void ReReplace();

	vector<RenThing_Button*> ButtonsArray;

	

private:

	vector<RenThing_Canvas*> CanvasVector;

	SDL_Renderer* MyRenderer;
	SDL_Window* MyWindow;

	vector<RenThing*> RestThings;



	SDL_Rect MainBoard;
	SDL_Rect SideBoard;

	SDL_Texture* BackGroundTexture;
	SDL_Rect BackgroundRect;


};

