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

	Coordinates TestCoord;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeY = true;

	TestCoord.X = 0.05;
	TestCoord.W = 0.8;
	TestCoord.Y = 0.05;
	TestCoord.H = 50;

	MyGraph->AddDynamicText("Don't Unpress That Button", &HeaderTextColor, &TestCoord);

	TestCoord.Y = 0.2;
	TestCoord.W = 0.35;

	MyGraph->AddButton(this, &GM_StartMenu::LevelChooseMenu, "Chose level", &TestCoord);

	TestCoord.Y = 0.3;

	RenThing_Button_DDMenu* TestOne = MyGraph->AddDDMenu("Screen Mode", &TestCoord);
	TestOne->AddDDButton(MyGraph, &Graphics::WindFullscreen, "Fullscreen");
	TestOne->AddDDButton(MyGraph, &Graphics::WindWindowed, "Windowed");

	TestCoord.Y = 0.4;

	TestOne = MyGraph->AddDDMenu("Resolution", &TestCoord);
	TestOne->AddDDButton(MyGraph, &Graphics::Resolution800x600, "800x600");
	TestOne->AddDDButton(MyGraph, &Graphics::Resolution1280x720, "1280x720");
	TestOne->AddDDButton(MyGraph, &Graphics::Resolution1600x900, "1600x900");

	TestCoord.Y = 0.5;

	MyGraph->AddButton(MyGame, &Game::ExitGame, "Exit", &TestCoord);


}

void GM_StartMenu::GM_End()
{
	MyGraph->ClearEverything();
}


void GM_StartMenu::LevelChooseMenu()
{
	Coordinates TestCoord;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeY = true;

	TestCoord.X = 0.6;
	TestCoord.W = 0.3;
	TestCoord.Y = 0.8;
	TestCoord.H = 50;

	MyGame->PlaceLevelButtons();

	MyGraph->AddButton(this, &GM_StartMenu::GM_Start, "Back", &TestCoord);
}


