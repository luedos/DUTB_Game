#include "stdafx.h"
#include "GM_StartMenu.h"
#include "Game.h"


GM_StartMenu::GM_StartMenu(Graphics* MyGraphRef, Game* MyGameRef)
{
	MyGame = MyGameRef;
	MyGraph = MyGraphRef;

	ColorRate = 150;

	HeaderTextColor = { 225, 0 , 0, 225 };

	r = 225;
	b = 0;
	g = 0;
}


GM_StartMenu::~GM_StartMenu()
{
}

void GM_StartMenu::GM_EventTick(float DeltaTime)
{
	if (r == 225)
	{
		if (b > 0)
		{
			b -= DeltaTime * ColorRate * 0.001;
			if (b < 0)
				b = 0;
		}
		else
		{
			g += DeltaTime * ColorRate * 0.001;
			if (g >= 225)
				g = 225;
		}
	}
	if (g == 225)
	{
		if (r > 0)
		{
			r -= DeltaTime * ColorRate * 0.001;
			if (r < 0)
				r = 0;
		}
		else
		{
			b += DeltaTime * ColorRate * 0.001;
			if (b > 225)
				b = 225;
		}
	}
	if (b == 225)
	{
		if (g > 0)
		{
			g -= DeltaTime * ColorRate * 0.001;
			if (g < 0)
				g = 0;
		}
		else
		{
			r += DeltaTime * ColorRate * 0.001;
			if (r > 225)
				r = 225;
		}
	}

	HeaderTextColor = { Uint8(r), Uint8(g), Uint8(b), 225 };
}

void GM_StartMenu::GM_Start()
{
	MyGraph->ClearEverything();

	SDL_Rect NewRect;
	NewRect.x = 50;
	NewRect.y = 40;
	NewRect.h = 60;
	NewRect.w = 220;

	MyGraph->AddDynamicText("Don't Unpress That Button", &HeaderTextColor, &NewRect);

	NewRect.y = 100;

	MyGraph->AddButton(this, &GM_StartMenu::LevelChooseMenu, "Chose level", &NewRect);

	NewRect.y = 170;

	MyGraph->AddButton(MyGame, &Game::ExitGame, "Exit", &NewRect);
}

void GM_StartMenu::GM_End()
{
	MyGraph->ClearEverything();
}


void GM_StartMenu::LevelChooseMenu()
{
	SDL_Rect NewRect;
	NewRect.x = 50;
	NewRect.y = 350;
	NewRect.w = 250;
	NewRect.h = 64;

	MyGame->PlaceLevelButtons();

	MyGraph->AddButton(this, &GM_StartMenu::GM_Start, "Back", &NewRect);
}


