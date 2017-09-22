// DUTB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_image.h"
#include "SDL2/include/SDL_ttf.h"
#include "SDL2/include/SDL_mixer.h"
#include "Game.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;


int main(int argc, char* argv[])
{


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		return 1;
	}

	if (TTF_Init() != 0)
	{
		std::cout << "IMG_Init Error:" << IMG_GetError() << std::endl;
		return 3;
	}


	//SDL_Window* MyWindow = SDL_CreateWindow("Don't unpress that Button", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN);
	//if (MyWindow == nullptr)
	//{
	//	std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
	//	return 4;
	//}
	//
	//SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if (MyRenderer == nullptr)
	//{
	//	std::cout << "SDL_CreateRenderer Error:" << SDL_GetError() << std::endl;
	//	return 5;
	//}
	//
	//SDL_Texture* BackTexture = IMG_LoadTexture(MyRenderer, "../DUTB/Textures/Point.png");
	//
	//SDL_Texture* SimpleWhiteTex = IMG_LoadTexture(MyRenderer, "../DUTB/Textures/Lines.png");
	//
	//SDL_Rect TestRect;
	//TestRect.x = 0;
	//TestRect.y = 0;
	//TestRect.w = 512;
	//TestRect.h = 512;
	//
	//
	//
	//const Uint8 *KeyboardState;
	//
	//KeyboardState = SDL_GetKeyboardState(NULL);
	//
	//bool QuitTest = false;
	//
	//SDL_Event MyEvent;
	//
	//while (!QuitTest)
	//{
	//	SDL_RenderClear(MyRenderer);
	//
	//	if (KeyboardState[SDL_SCANCODE_Q])
	//		QuitTest = true;
	//
	//	if (KeyboardState[SDL_KEYDOWN])
	//		cout << "Some button down" << endl;
	//
	//	while (SDL_PollEvent(&MyEvent))
	//	{
	//		SDL_PumpEvents();
	//		if (MyEvent.type == SDL_QUIT)
	//			QuitTest = true;
	//			
	//		if (MyEvent.type == SDL_KEYDOWN)
	//			cout << "Some button from event down" << endl;
	//	
	//	
	//	}
	//
	//	SDL_RenderCopy(MyRenderer, SimpleWhiteTex, NULL, &TestRect);
	//
	//	SDL_SetTextureAlphaMod(BackTexture, 10);
	//
	//	SDL_RenderCopy(MyRenderer, BackTexture, NULL, &TestRect);
	//
	//
	//
	//
	//
	//
	//	SDL_RenderPresent(MyRenderer);
	//}
	//
	//SDL_DestroyTexture(SimpleWhiteTex);
	//SDL_DestroyTexture(BackTexture);
	//SDL_DestroyRenderer(MyRenderer);
	//SDL_DestroyWindow(MyWindow);



	string SomeString = "blah blah";

	cout << "Start game? \n    Y/N" << endl;

	while (SomeString != "Y" && SomeString != "N")
	{
		cin >> SomeString;
		if (SomeString != "Y" && SomeString != "N")
			cout << "Print again" << endl;
	}
	if (SomeString == "Y")
	{
		float InTime = 1.f;
		Game MyGame;

		MyGame.NewGame();

		while (!MyGame.Quit)
		{
			auto BeginTime = chrono::high_resolution_clock::now();

			MyGame.EventTick(InTime / 1000000.f);

			auto EndTime = chrono::high_resolution_clock::now();
			InTime = chrono::duration_cast<chrono::nanoseconds>(EndTime - BeginTime).count();
		}

		MyGame.ExitGame();
		SDL_Quit();
	}

	system("Pause");
	
    return 0;
}

