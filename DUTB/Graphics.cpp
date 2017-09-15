#include "stdafx.h"
#include "Graphics.h"


Graphics::Graphics()
{

	MainBoard.x = 50;
	MainBoard.y = 50;
	MainBoard.w = 700;
	MainBoard.h = 150;

	SideBoard.x = 50;
	SideBoard.y = MainBoard.y + MainBoard.h + 50;
	SideBoard.w = 700;
	SideBoard.h = 300;
	
}


Graphics::~Graphics()
{
}

void Graphics::RenderEverything(float DeltaTime)
{
	// Очистка рендера
	SDL_RenderClear(MyRenderer);

	// Если текстура фона отсутствует, загрузить текстуру
	if(BackGroundTexture == nullptr)
		BackGroundTexture = IMG_LoadTexture(MyRenderer, "../DUTB/Textures/Back.png");

	// Рендер фона
	SDL_RenderCopy(MyRenderer, BackGroundTexture, NULL, &BackgroundRect);

	// Подготавка каждой штуки в трех массивах
	for (int i = 0; i < CanvasVector.size(); i++)
	{
		CanvasVector.at(i)->DeltaTime = DeltaTime;
		CanvasVector.at(i)->PrepareThing(MyRenderer);
	}

	for (int i = 0; i < RestThings.size(); i++)
		RestThings.at(i)->PrepareThing(MyRenderer);

	for (int i = 0; i < ButtonsArray.size(); i++)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		ButtonsArray.at(i)->ButtonHovered(x, y);

		ButtonsArray.at(i)->PrepareThing(MyRenderer);
	}
	



	for (int i = 0; i < RenderOrder.size(); i++)
		RenderOrder.at(i)->RenderThing(MyRenderer);



	// Ренедер рендера
	SDL_RenderPresent(MyRenderer);
}

void Graphics::ClearEverything()
{
	for (int i = 0; i < CanvasVector.size(); i++)
	{
		CanvasVector.at(i)->CleanupThing();
		delete CanvasVector.at(i);
	}

	CanvasVector.clear();

	for (int i = 0; i < RestThings.size(); i++)
	{
		RestThings.at(i)->CleanupThing();
		delete RestThings.at(i);
	}

	RestThings.clear();

	for (int i = 0; i < ButtonsArray.size(); i++)
	{
		ButtonsArray.at(i)->CleanupThing();
		delete ButtonsArray.at(i);
	}

	RenderOrder.clear();

	ButtonsArray.clear();

}

void Graphics::DestroyEveryThing()
{
	ClearEverything();
	SDL_DestroyTexture(BackGroundTexture);
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
}

int Graphics::CreateWindow(int WindowSizeX, int WindowSizeY)
{
	MyWindow = SDL_CreateWindow("Don't unpress that Button", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowSizeX, WindowSizeY, SDL_WINDOW_SHOWN);
	if (MyWindow == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
		return 4;
	}

	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (MyRenderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error:" << SDL_GetError() << std::endl;
		return 5;
	}

	BackgroundRect.x = 0;
	BackgroundRect.y = 0;
	BackgroundRect.w = WindowSizeX;
	BackgroundRect.h = WindowSizeY;

	RenderEverything(1);

	return 0;
}

bool Graphics::DeleteRenThing(RenThing * ThingToDelete)
{
	bool bFind = false;

	for(int i = 0; i < RenderOrder.size(); i++)
		if (RenderOrder.at(i) == ThingToDelete)
		{
			RenderOrder.erase(RenderOrder.begin() + i);
			break;
		}

	for (int i = 0; i < CanvasVector.size(); i++)
		if (CanvasVector.at(i) == ThingToDelete)
		{
			CanvasVector.at(i)->CleanupThing();
			delete CanvasVector.at(i);
			CanvasVector.erase(CanvasVector.begin() + i);
			bFind = true;
			break;
	}
	if (!bFind)
	for (int i = 0; i < CanvasVector.size(); i++)
		for(int ii = 0; ii < CanvasVector.at(i)->MyThingVector.size(); ii++)
			if (CanvasVector.at(i)->MyThingVector.at(ii) == ThingToDelete)
			{
				CanvasVector.at(i)->MyThingVector.at(ii)->CleanupThing();
				delete CanvasVector.at(i)->MyThingVector.at(ii);
				CanvasVector.at(i)->MyThingVector.erase(CanvasVector.at(i)->MyThingVector.begin() + ii);
				bFind = true;
				break;
			}


	if (!bFind)
		for (int i = 0; i < RestThings.size(); i++)
			if (RestThings.at(i) == ThingToDelete)
			{
				RestThings.at(i)->CleanupThing();
				delete RestThings.at(i);
				RestThings.erase(RestThings.begin() + i);
				bFind = true;
				break;
			}
	if(!bFind)
		for(int i = 0; i < ButtonsArray.size(); i++)
			if (ButtonsArray.at(i) == ThingToDelete)
			{
				ButtonsArray.at(i)->CleanupThing();
				delete ButtonsArray.at(i);
				ButtonsArray.erase(ButtonsArray.begin() + i);
				bFind = true; 
				break;
			}

	if (!bFind)
	{
		ThingToDelete->CleanupThing();
		delete ThingToDelete;
	}

	

	return bFind;
}

void Graphics::ReReplace()
{

}
