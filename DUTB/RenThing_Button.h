#pragma once
#include "RenThing_Text.h"





class Button_IContainer
{
public:
	virtual void Call() = 0;

};

template<class T, class M>
class Button_Container : public Button_IContainer
{};


template<class T>
class Button_Container<T, void(T::*)()> : public Button_IContainer
{

	typedef void (T::*M)();

public:

	Button_Container(T* c, M m) : MyClass(c), MyMethod(m) {}

	void Call() { (MyClass->*MyMethod)();	}

private:
	T* MyClass;
	M MyMethod;

};



class RenThing_Button : public RenThing
{

public:
	

	RenThing_Button(const char* ButtonTextRef, SDL_Rect* InRect, SDL_Color* BGColorRef, SDL_Color* BGColor_PressedRef){
		MyRect = *InRect;

		ButtonText = ButtonTextRef;

		BGColor = *BGColorRef;

		BGColor_Pressed = *BGColor_PressedRef;

		SetFont(48);
	
	}


	template<class T, class U>
	void ConnectNew(T* NewClass, U NewMethod)
	{
		if (MyContainer != nullptr)
			delete MyContainer;

		MyContainer = new Button_Container<T, U>(NewClass, NewMethod);
	}


	void CleanupThing() override {}

	void RenderThing(SDL_Renderer* RenRef) override {

		SDL_RenderCopy(RenRef, BackgroundTexture, NULL, &MyRect);

		SDL_RenderCopy(RenRef, MyTexture, NULL, &TextRect);

	}

	void PrepareThing(SDL_Renderer* RenRef) override {

		SDL_Color ColorToUse = { 225,225,225,225 };

		Surface = TTF_RenderText_Blended(Font, ButtonText, ColorToUse);
		MyTexture = SDL_CreateTextureFromSurface(RenRef, Surface);
		SDL_FreeSurface(Surface);

		SDL_QueryTexture(MyTexture, NULL, NULL, &TextRect.w, &TextRect.h);

		TextRect.x = MyRect.x + float(MyRect.w - TextRect.w) / 2;

		TextRect.y = MyRect.y + float(MyRect.h - TextRect.h) / 2;

		if (BackgroundTexture == nullptr)
		{
			BackgroundTexture = IMG_LoadTexture(RenRef, "../DUTB/Textures/SimpleWhite.png");
			if (BackgroundTexture == nullptr)
			{
				cout << "Bad Background" << endl;
				SDL_Quit();
			}
		}

		SDL_Color LocalColor;

		if (IsPressed)
			LocalColor = BGColor_Pressed;
		else
			LocalColor = BGColor;

		SDL_SetTextureColorMod(BackgroundTexture, LocalColor.r, LocalColor.g, LocalColor.b);

	}

	void SetPosition(int x, int y) override {
		MyRect.x = x;
		MyRect.y = y;
	}

	virtual void ButtonPressed() {
		IsPressed = true;
	}

	virtual void ButtonUnpressed(int x, int y) {

		if (MyRect.x < x && MyRect.y < y && MyRect.x + MyRect.w > x && MyRect.y + MyRect.h > y)
			if (MyContainer != nullptr)
				MyContainer->Call();

		IsPressed = false;
	}

	TTF_Font* Font;

	const char* ButtonText;

	SDL_Surface* Surface;

	SDL_Color BGColor;

	SDL_Color BGColor_Pressed;

	SDL_Rect TextRect;

	bool IsPressed = false;

	//const char* BackgroundFile;

	SDL_Texture* BackgroundTexture = nullptr;

	void SetFont(int ptsizeRef) {
		TTF_CloseFont(Font);
		Font = TTF_OpenFont("../DUTB/Fonts/RiseOfKingdom.ttf", ptsizeRef);
	}

	Button_IContainer* MyContainer = nullptr;
};