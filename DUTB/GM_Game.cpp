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
	Coordinates MyCoord;
	MyCoord.H = 64;
	MyCoord.W = 64;

	switch (WhichTest)
	{
	//Do not unpress button :: Pointers
	case ETests::DUBPointers:
	{
		DUB_Test* TestTest = new DUB_Test(&TestsVector, 10.f);

		TestTest->MyThing = MyGraph->AddDynamicImage("../DUTB/Textures/Pointers.png", &MyCoord, &TestTest->IntPointer, RenCanvas1, 0, &TestTest->TextColor);

		TestsVector.push_back(TestTest);

		break;
	}
	//Do not unpress button :: Buttons
	case ETests::DUBButtons:
	{
		DUB_Test* TestTest = new DUB_Test(&TestsVector, 10.f, false);

		TestTest->MyThing = MyGraph->AddDynamicText(TestTest->ButtonString.c_str(), &TestTest->TextColor, &MyCoord, RenCanvas1);

		TestsVector.push_back(TestTest);

		break;
	}
	// Do press button
	case ETests::DPButton:
	{
		DPB_test* TestTest = new DPB_test(&TestsVector, true, 2000, 1500);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(TestTest->ButtonString.c_str(), &TestTest->ColorToRender, TestTest->SideString.c_str(), &TestTest->ColorToRender, &MyCoord, RenCanvas2);

		TestsVector.push_back(TestTest);

		break;
	}
	// Do not press button
	case ETests::DNPButton:
	{
		DPB_test* TestTest = new DPB_test(&TestsVector, false, 2000, 1500);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(TestTest->ButtonString.c_str(), &TestTest->ColorToRender, TestTest->SideString.c_str(), &TestTest->ColorToRender, &MyCoord, RenCanvas2);

		TestsVector.push_back(TestTest);

		break;
	}
	// Press N times Button
	case ETests::PNTButton:
	{
		PNTButtons_Test* TestTest = new PNTButtons_Test(&TestsVector, 4, 2500, 1700);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(TestTest->ButtonString.c_str(), &TestTest->MyColor, TestTest->SideString.c_str(), &TestTest->MyColor, &MyCoord, RenCanvas2);

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


	TextGameTime = to_string(int(GameTime / 1000.f));

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

	Coordinates TestCoord;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeY = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeH = true;

	TestCoord.X = 0.1;
	TestCoord.W = 0.8;
	TestCoord.Y = 0.1;
	TestCoord.H = 0.3;

	SDL_Color NewColor = { 13, 13, 120, 100 };

	RenCanvas1 = MyGraph->AddCanvas(&TestCoord, "../DUTB/Textures/SimpleWhite.png", &NewColor);

	TestCoord.Y = 0.45;

	RenCanvas2 = MyGraph->AddCanvas(&TestCoord, "../DUTB/Textures/SimpleWhite.png", &NewColor);

	MyLevel->StartLevel();

	GamePoints = MaxPoints;

	NewColor = { 225, 225, 225, 225 };

	TestCoord.bRelativeH = false;

	TestCoord.W = 0.6;
	TestCoord.Y = 0.8;
	TestCoord.H = 50;
	
	MyGraph->AddDynamicText(TextPoints.c_str(), &NewColor, &TestCoord);

	TestCoord.bRelativeX = true;
	TestCoord.X = 0.4;

	RenThing_Canvas* TestCanvas = MyGraph->AddCanvas(&TestCoord);
	
	MyGraph->AddStaticText("Level time : ", NewColor, &TestCoord, TestCanvas);

	TestCoord.X = 0.7;

	MyGraph->AddStaticText(TextGameTime.c_str(), NewColor, &TestCoord, TestCanvas);

	TestCoord.bRelativeX = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeH = true;

	TestCoord.X = 0.1;
	TestCoord.W = 0.8;
	TestCoord.Y = 0.9;
	TestCoord.H = 0.08;

	MyGraph->AddPercentBar(&TestCoord, &Percent);
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

	Coordinates TestCoord;

	TestCoord.bRelativeW = true;
	TestCoord.bRelativeH = true;

	TestCoord.X = 0;
	TestCoord.W = 1;
	TestCoord.Y = 0;
	TestCoord.H = 1;

	SDL_Color TestColor = { 180,180,180,60 };

	PauseRenThings.push_back(MyGraph->AddStaticImage("../DUTB/Textures/SimpleWhite.png", &TestCoord, nullptr, &TestColor));

	TestCoord.bRelativeH = false;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeY = true;
	TestCoord.X = 0.1;
	TestCoord.W = 0.35;
	TestCoord.Y = 0.1;
	TestCoord.H = 50;
	
	TestColor = { 200,200,200,225 };

	PauseRenThings.push_back(MyGraph->AddStaticText("Pause Menu", TestColor, &TestCoord));

	TestCoord.Y = 0.2;

	PauseRenThings.push_back(MyGraph->AddButton(this, &GM_Game::UnPause, "Return", &TestCoord));

	TestCoord.Y = 0.3;

	PauseRenThings.push_back(MyGraph->AddButton(MyGame, &Game::GoStartMenu, "Main Menu", &TestCoord));

	TestCoord.Y = 0.4;

	PauseRenThings.push_back(MyGraph->AddButton(MyGame, &Game::ExitGame, "Exit Game", &TestCoord));
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

	Coordinates TestCoord;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeY = true;

	TestCoord.X = 0.3;
	TestCoord.W = 0.4;
	TestCoord.Y = 0.05;
	TestCoord.H = 50;

	MyGraph->AddStaticText("Game Over", { 225, 0, 0 }, &TestCoord);

	TestCoord.X = 0.2;
	TestCoord.W = 0.3;
	TestCoord.Y = 0.1;

	MyGraph->AddButton(this, &GM_Game::GM_Start, "Try Again", &TestCoord);

	TestCoord.Y = 0.3;

	PauseRenThings.push_back(MyGraph->AddButton(MyGame, &Game::GoStartMenu, "Main Menu", &TestCoord));

	TestCoord.Y = 0.4;

	MyGraph->AddButton(MyGame, &Game::ExitGame, "Exit Game", &TestCoord);
}

void GM_Game::WinGameMenu()
{
	GM_End();

	Coordinates TestCoord;
	TestCoord.bRelativeX = true;
	TestCoord.bRelativeW = true;
	TestCoord.bRelativeY = true;

	TestCoord.X = 0.3;
	TestCoord.W = 0.4;
	TestCoord.Y = 0.05;
	TestCoord.H = 50;

	MyGraph->AddStaticText("Level passed", { 15,225,15,225 }, &TestCoord);

	TestCoord.X = 0.2;
	TestCoord.W = 0.3;
	TestCoord.Y = 0.2;

	MyGraph->AddButton(this, &GM_Game::LevelChooseMenu, "Choose level", &TestCoord);

	TestCoord.Y = 0.3;

	MyGraph->AddButton(MyGame, &Game::ExitGame, "ExitGame", &TestCoord);
}

void GM_Game::LevelChooseMenu()
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

	MyGraph->AddButton(this, &GM_Game::WinGameMenu, "Back", &TestCoord);
}


