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

	//if(IMG_Init(SDL_INIT_EVERYTHING) != 0)
	//{
	//	std::cout << "IMG_Init Error:" << IMG_GetError() << std::endl;
	//	return 2;
	//}

	if (TTF_Init() != 0)
	{
		std::cout << "IMG_Init Error:" << IMG_GetError() << std::endl;
		return 3;
	}


	//SDL_Window* MyWindow = SDL_CreateWindow("Don't unpress that Button", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 64, SDL_WINDOW_SHOWN);
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
	//}
	


	bool bDoStaff = true;

	string SomeString = "blah blah";

	cout << "Start game? \n  Yes/No" << endl;

	while (SomeString != "Yes" && SomeString != "No")
	{
		cin >> SomeString;
		if (!(SomeString == "Yes" || SomeString == "No"))
			cout << "Print again" << endl;
	}
	if (SomeString == "Yes")
		bDoStaff = true;
	else
		bDoStaff = false;


	//SDL_Event MyEvent;

	if (bDoStaff)
	{
		float InTime = 1.f;
		Game MyGame;

		MyGame.NewGame();

		while (!MyGame.Quit)
		{
			auto BeginTime = chrono::high_resolution_clock::now();

			//while (SDL_PollEvent(&MyEvent))
			//{
			//	SDL_PumpEvents();
			//	if (MyEvent.button.button == SDL_QUIT)
			//		MyGame.ExitGame();
			//
			//
			//
			//}
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

