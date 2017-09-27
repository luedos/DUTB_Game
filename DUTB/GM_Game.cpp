#include "stdafx.h"
#include "GM_Game.h"
#include <iostream>
#include "Game.h"

using namespace std;

GM_Game::GM_Game(Graphics* GraphRef, Game* GameRef)
{
	MyGame = GameRef;

	MyGraph = GraphRef;

}


GM_Game::~GM_Game()
{
}

void GM_Game::AddTest(ETests WhichTest, int PowerLevel)
{
	SDL_Rect MyRect;
	MyRect.x = 50;
	MyRect.y = 50;
	MyRect.w = 64;
	MyRect.h = 64;

	switch (WhichTest)
	{
	//Do not unpress button :: Pointers
	case ETests::DUBPointers:
	{
		DUB_Test* TestTest = new DUB_Test(&TestsVector, 10.f);

		TestTest->MyThing = MyGraph->AddDynamicImage("../DUTB/Textures/Pointers.png", &MyRect, &TestTest->IntPointer, RenCanvas1, 0, &TestTest->TextColor);

		TestsVector.push_back(TestTest);

		break;
	}
	//Do not unpress button :: Buttons
	case ETests::DUBButtons:
	{
		DUB_Test* TestTest = new DUB_Test(&TestsVector, 10.f, false);

		TestTest->MyThing = MyGraph->AddDynamicText(TestTest->ButtonString.c_str(), &TestTest->TextColor, &MyRect, RenCanvas1);

		TestsVector.push_back(TestTest);

		break;
	}
	// Do press button
	case ETests::DPButton:
	{
		DPB_test* TestTest = new DPB_test(&TestsVector, true, 2000, 1500);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(TestTest->ButtonString.c_str(), &TestTest->ColorToRender, TestTest->SideString.c_str(), &TestTest->ColorToRender, &MyRect, RenCanvas2);

		TestsVector.push_back(TestTest);

		break;
	}
	// Do not press button
	case ETests::DNPButton:
	{
		DPB_test* TestTest = new DPB_test(&TestsVector, false, 2000, 1500);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(TestTest->ButtonString.c_str(), &TestTest->ColorToRender, TestTest->SideString.c_str(), &TestTest->ColorToRender, &MyRect, RenCanvas2);

		TestsVector.push_back(TestTest);

		break;
	}
	// Press N times Button
	case ETests::PNTButton:
	{
		PNTButtons_Test* TestTest = new PNTButtons_Test(&TestsVector, 4, 2500, 1700);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(TestTest->ButtonString.c_str(), &TestTest->MyColor, TestTest->SideString.c_str(), &TestTest->MyColor, &MyRect, RenCanvas2);

		TestsVector.push_back(TestTest);

		break;
	}
	default:
		break;
	}
}


void GM_Game::GM_EventTick(float DeltaTime)
{
	if (bTickTests)
	{
		TickEveryTest(DeltaTime);
		GeneratorTick(DeltaTime);
		DeltaTestTick(DeltaTime);
	}
}

void GM_Game::TickEveryTest(float DeltaTime)
{
	vector<GeneralTest*> TestsToDeleteArray;

	for (int i = 0; i < TestsVector.size(); i++) {
		TestsVector.at(i)->EventTick(DeltaTime);
		GamePoints += TestsVector.at(i)->Points;

		if (TestsVector.at(i)->bIsDelete)
			TestsToDeleteArray.push_back(TestsVector.at(i));
	}

	for (int i = 0; i < TestsToDeleteArray.size(); i++)
		DeleteTest(TestsToDeleteArray.at(i));

	Percent = GamePoints / MaxPoints;

	TextPoints = to_string(int(GamePoints));

	GameTime -= DeltaTime;

	TextGameTime = "Level Time : ";
	TextGameTime += to_string(int(GameTime / 1000.f));
	
	if (GameTime < 0)
		WinGameMenu();

	if (GamePoints <= 0)
		GameOverMenu();
}

void GM_Game::GM_Start()
{
	ClearTests();
	ClearGenerators();

	MyGraph->ClearEverything();

	bTickTests = true;

	SDL_Rect TestRect;
	TestRect.x = 50;
	TestRect.y = 50;
	TestRect.w = 500;
	TestRect.h = 200;

	RenCanvas1 = MyGraph->AddCanvas(&TestRect, true, "..\DUTB\Textures\SimpleWhite.png");

	TestRect.y = 200;

	RenCanvas2 = MyGraph->AddCanvas(&TestRect, true, "..\DUTB\Textures\SimpleWhite.png");

	MyLevel->StartLevel();

	GamePoints = MaxPoints;

	SDL_Color NewColor = { 225, 225, 225, 225 };

	
	TestRect.y = 400;

	MyGraph->AddDynamicText(TextPoints.c_str(), &NewColor, &TestRect);

	TestRect.x = 300;

	MyGraph->AddStaticText(TextGameTime.c_str(), NewColor, &TestRect);

	TestRect.x = 50;
	TestRect.y = 500;
	TestRect.h = 50;
	TestRect.w = 700;

	MyGraph->AddPercentBar(&TestRect, &Percent);
}

void GM_Game::GM_End()
{	
	bTickTests = false;

	ClearTests();
	ClearGenerators();

	PauseRenThings.clear();

	MyGraph->ClearEverything();
}

void GM_Game::GM_Event(SDL_Event* EventRef)
{
	if (EventRef->type == SDL_KEYUP && EventRef->button.button == SDL_SCANCODE_ESCAPE)
	{
		if (bTickTests)
			GP_Pause();
		else
			UnPause();
	}
}

void GM_Game::ClearTests()
{
	for (int i = 0; i < TestsVector.size(); i++)
	{
		MyGraph->DeleteRenThing(TestsVector.at(i)->MyThing);
		delete TestsVector.at(i);
	}
	TestsVector.clear();
}

void GM_Game::ClearGenerators()
{
	Generator.clear();
	DeltaTests.clear();
}

bool GM_Game::DeleteTest(GeneralTest * TestToDelete)
{
	bool bFind = false;

	for (int i = 0; i < TestsVector.size(); i++)
		if (TestsVector.at(i) == TestToDelete)
		{
			MyGraph->DeleteRenThing(TestToDelete->MyThing);
			delete TestsVector.at(i);
			TestsVector.erase(TestsVector.begin() + i);
			bFind = true;
			break;
		}
	
	if (!bFind)
	{
		MyGraph->DeleteRenThing(TestToDelete->MyThing);
		delete TestToDelete;
	}

	return bFind;
}

void GM_Game::GeneratorTick(float DeltaTime)
{
	for (int i = 0; i < Generator.size(); i++)
	{
		Generator.at(i).Chanser += Generator.at(i).ChanserSpeed * DeltaTime * 0.001;
		Generator.at(i).CheckTimer += DeltaTime;

		if (Generator.at(i).CheckTimer >= Generator.at(i).CheckRate)
		{
			Generator.at(i).CheckTimer = 0.f;

			float Chance;

			std::random_device rd;
			std::mt19937_64 gen(rd());
			std::uniform_int_distribution<int> dis(0, Generator.at(i).MaxDelta);

			Chance = dis(gen);

			if (Chance < Generator.at(i).Chanser)
			{
				cout << "Generator Add" << endl;

				AddTest(Generator.at(i).TestItself, Generator.at(i).Level);

				Generator.at(i).Chanser = 0;

				if (Generator.at(i).MaxCallsNumber != 0)
				{
					Generator.at(i).CallsNumber++;
					if (Generator.at(i).CallsNumber >= Generator.at(i).MaxCallsNumber)
					{
						Generator.erase(Generator.begin() + i);
						i--;
					}
				}
			}
		}
	}

}

void GM_Game::DeltaTestTick(float DeltaTime)
{
	for (int i = 0; i < DeltaTests.size(); i++)
	{
		DeltaTests.at(i).MS_Time += DeltaTime;

		if (DeltaTests.at(i).MS_Time >= DeltaTests.at(i).MS_DeltaTime)
		{
			DeltaTests.at(i).MS_Time = 0;

			AddTest(DeltaTests.at(i).TestItself, DeltaTests.at(i).Level);

			if (DeltaTests.at(i).MaxCallsNamber != 0)
			{
				DeltaTests.at(i).CallsNumber++;
				if (DeltaTests.at(i).CallsNumber >= DeltaTests.at(i).MaxCallsNamber)
				{
					DeltaTests.erase(DeltaTests.begin() + i);
					i--;
				}
			}
		}
	}
}

void GM_Game::GP_Pause()
{
	bTickTests = false;

	SDL_Rect TestRect;
	TestRect.x = 0;
	TestRect.y = 0;
	TestRect.w = 800;
	TestRect.h = 600;

	SDL_Color TestColor = { 180,180,180,60 };

	PauseRenThings.push_back(MyGraph->AddStaticImage("../DUTB/Textures/SimpleWhite.png", &TestRect, nullptr, &TestColor));

	TestRect.x = 50;
	TestRect.y = 30;
	
	TestColor = { 200,200,200,225 };

	PauseRenThings.push_back(MyGraph->AddStaticText("Pause Menu", TestColor, &TestRect));

	TestRect.y = 100;
	TestRect.w = 240;
	TestRect.h = 50;
	PauseRenThings.push_back(MyGraph->AddButton(this, &GM_Game::UnPause, "Return", &TestRect));

	TestRect.y = 170;

	PauseRenThings.push_back(MyGraph->AddButton(MyGame, &Game::GoStartMenu, "Main Menu", &TestRect));

	TestRect.y = 250;

	PauseRenThings.push_back(MyGraph->AddButton(MyGame, &Game::ExitGame, "Exit Game", &TestRect));
}

void GM_Game::UnPause()
{
	for (int i = 0; i < PauseRenThings.size(); i++)
		MyGraph->DeleteRenThing(PauseRenThings.at(i));
	
	PauseRenThings.clear();

	bTickTests = true;
}

void GM_Game::GameOverMenu()
{
	GM_End();

	SDL_Rect NewRect;
	NewRect.x = 50;
	NewRect.y = 50;
	NewRect.w = 200;
	NewRect.h = 64;

	MyGraph->AddStaticText("Game Over", { 225, 0, 0 }, &NewRect);

	NewRect.y = 120;

	MyGraph->AddButton(this, &GM_Game::GM_Start, "Try Again", &NewRect);

	NewRect.y = 200;

	PauseRenThings.push_back(MyGraph->AddButton(MyGame, &Game::GoStartMenu, "Main Menu", &NewRect));

	NewRect.y = 280;

	MyGraph->AddButton(MyGame, &Game::ExitGame, "Exit Game", &NewRect);
}

void GM_Game::WinGameMenu()
{
	GM_End();

	SDL_Rect NewRect;
	NewRect.x = 50;
	NewRect.y = 50;
	NewRect.w = 200;
	NewRect.h = 50;

	MyGraph->AddStaticText("Level passed", { 15,225,15,225 }, &NewRect);

	NewRect.y = 150;

	MyGraph->AddButton(this, &GM_Game::LevelChooseMenu, "Choose level", &NewRect);

	NewRect.y = 220;

	MyGraph->AddButton(MyGame, &Game::ExitGame, "ExitGame", &NewRect);
}

void GM_Game::LevelChooseMenu()
{
	SDL_Rect NewRect;
	NewRect.x = 50;
	NewRect.y = 350;
	NewRect.w = 250;
	NewRect.h = 64;

	MyGame->PlaceLevelButtons();

	MyGraph->AddButton(this, &GM_Game::WinGameMenu, "Back", &NewRect);
}


