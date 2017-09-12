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
	for (int i = 0; i < MainTests.size(); i++)
		MainTests.at(i)->PrepareThing(MyRenderer);

	for (int i = 0; i < SideTests.size(); i++)
		SideTests.at(i)->PrepareThing(MyRenderer);

	for (int i = 0; i < RestThings.size(); i++)
		RestThings.at(i)->PrepareThing(MyRenderer);

	for (int i = 0; i < ButtonsArray.size(); i++)
		ButtonsArray.at(i)->PrepareThing(MyRenderer);

	// Создание ректа для упрощения назначения мест у главных и второстепенных штук
	SDL_Rect LocalRect;
	LocalRect.x = MainBoard.x;
	LocalRect.y = MainBoard.y;

	// Оба цикла служат для переназначения позиций штук
	for (int i = 0; i < MainTests.size(); i++)
	{
		LocalRect.w = MainTests.at(i)->MyRect.w;
		LocalRect.h = MainTests.at(i)->MyRect.h;

		if (LocalRect.x + LocalRect.w > MainBoard.x + MainBoard.w)
		{
			LocalRect.x = MainBoard.x;
			LocalRect.y += 50;
		}

		if (MainTests.at(i)->FirstCreated)
		{
			MainTests.at(i)->SetPosition(LocalRect.x, LocalRect.y);
			MainTests.at(i)->FirstCreated = false;
		}
		else
			MainTests.at(i)->InterpPosition(LocalRect.x, LocalRect.y, DeltaTime, 1.25f);

		LocalRect.x += LocalRect.w + 15;
	}

	LocalRect.x = SideBoard.x;
	LocalRect.y = SideBoard.y;

	for (int i = 0; i < SideTests.size(); i++)
	{
		LocalRect.w = SideTests.at(i)->MyRect.w;
		LocalRect.h = SideTests.at(i)->MyRect.h;

		if (LocalRect.x + LocalRect.w > SideBoard.x + SideBoard.w)
		{
			LocalRect.x = SideBoard.x;
			LocalRect.y += 50;
		}

		if (SideTests.at(i)->FirstCreated)
		{
			SideTests.at(i)->SetPosition(LocalRect.x, LocalRect.y);
			SideTests.at(i)->FirstCreated = false;
		}
		else
			SideTests.at(i)->InterpPosition(LocalRect.x, LocalRect.y, DeltaTime, 1.25f);

		LocalRect.x += LocalRect.w + 15;
	}

	// Непосредственный рендер всех штук
	for (int i = 0; i < MainTests.size(); i++)
		MainTests.at(i)->RenderThing(MyRenderer);

	for (int i = 0; i < SideTests.size(); i++)
		SideTests.at(i)->RenderThing(MyRenderer);

	for (int i = 0; i < RestThings.size(); i++)
		RestThings.at(i)->RenderThing(MyRenderer);

	for (int i = 0; i < ButtonsArray.size(); i++)
		ButtonsArray.at(i)->RenderThing(MyRenderer);

	// Ренедер рендера
	SDL_RenderPresent(MyRenderer);
}

void Graphics::ClearEverything()
{
	for (int i = 0; i < MainTests.size(); i++)
	{
		MainTests.at(i)->CleanupThing();
		delete MainTests.at(i);
	}

	MainTests.clear();

	for (int i = 0; i < SideTests.size(); i++)
	{
		SideTests.at(i)->CleanupThing();
		delete SideTests.at(i);
	}

	SideTests.clear();

	for (int i = 0; i < RestThings.size(); i++)
	{
		RestThings.at(i)->CleanupThing();
		delete RestThings.at(i);
	}

	RestThings.clear();
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

	for (int i = 0; i < MainTests.size(); i++)
		if (MainTests.at(i) == ThingToDelete)
		{
			MainTests.at(i)->CleanupThing();
			delete MainTests.at(i);
			MainTests.erase(MainTests.begin() + i);
			bFind = true;
			break;
		}

	if (!bFind)
		for (int i = 0; i < SideTests.size(); i++)
			if (SideTests.at(i) == ThingToDelete)
			{
				SideTests.at(i)->CleanupThing();
				delete SideTests.at(i);
				SideTests.erase(SideTests.begin() + i);
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
