#include "stdafx.h"
#include "GM_Game.h"
#include <iostream>

using namespace std;

GM_Game::GM_Game(Graphics* GraphRef)
{


	MyGraph = GraphRef;


	//AddGeneratorTest(ETests::DPButton, 1, 1000.f, 15.f);
	
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

		TestTest->ReChargeTest(30, 500, 800, 1500);

		TestTest->MyThing = MyGraph->AddDynamicImage(1, "../DUTB/Textures/Pointers.png", &MyRect, &TestTest->IntPointer, false, 0, &TestTest->TextColor);

		TestsVector.push_back(TestTest);

		break;
	}
	//Do not unpress button :: Buttons
	case ETests::DUBButtons:
	{
		DUB_Test* TestTest = new DUB_Test(&TestsVector, 10.f);

		TestTest->Pointers_Buttons = false;

		TestTest->ReChargeTest(30, 500, 800, 1500);

		TestTest->MyThing = MyGraph->AddDynamicText(1, TestTest->ButtonString.c_str(), &TestTest->TextColor, &MyRect);

		TestsVector.push_back(TestTest);

		break;
	}
	// Do press button
	case ETests::DPButton:
	{
		DPB_test* TestTest = new DPB_test(&TestsVector);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(2, TestTest->ButtonString.c_str(), &TestTest->ColorToRender, TestTest->SideString.c_str(), &TestTest->ColorToRender, &MyRect);

		TestsVector.push_back(TestTest);

		break;
	}
	// Do not press button
	case ETests::DNPButton:
	{
		DPB_test* TestTest = new DPB_test(&TestsVector, false);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(2, TestTest->ButtonString.c_str(), &TestTest->ColorToRender, TestTest->SideString.c_str(), &TestTest->ColorToRender, &MyRect);

		TestsVector.push_back(TestTest);

		break;
	}
	case ETests::PNTButton:
	{
		PNTButtons_Test* TestTest = new PNTButtons_Test(&TestsVector, 4, 2000, 1300);

		TestTest->MyThing = MyGraph->AddCanvas_TextText(2, TestTest->MainString.c_str(), &TestTest->MyColor, TestTest->SideString.c_str(), &TestTest->MyColor, &MyRect);

		TestsVector.push_back(TestTest);

		break;
	}


	default:
		break;
	}
}


void GM_Game::GM_EventTick(float DeltaTime)
{

	//while (SDL_PollEvent(&MyEvent))
	//{
	//	SDL_PumpEvents();
	//	if (MyEvent.type == SDL_QUIT)
	//	{
	//		ExitGame();
	//	}
	//
	//
	//}
	

	TickEveryTest(DeltaTime);
	GeneratorTick(DeltaTime);
	DeltaTestTick(DeltaTime);

	MyGraph->RenderEverything(DeltaTime);
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

	TextPoints = to_string(int(GamePoints));

	
}

void GM_Game::GM_Start()
{


	if (MyLevel != nullptr)
	{
		delete MyLevel;
		MyLevel = nullptr;
	}

	MyLevel = new TestLevel(this);
	
	NewRound();


}

void GM_Game::NewRound()
{
	ClearTests();
	ClearGenerators();

	GamePoints = 0;

	MyLevel->StartLevel();

	SDL_Color NewColor = { 225, 225, 225, 225 };

	SDL_Rect NewRect;

	NewRect.x = 50;
	NewRect.y = 500;
	NewRect.w = 64;
	NewRect.h = 64;

	MyGraph->AddDynamicText(3, TextPoints.c_str(), &NewColor, &NewRect);
}

void GM_Game::GM_End()
{

	ClearTests();

	ClearGenerators();


}

void GM_Game::ClearTests()
{
	for (int i = 0; i < TestsVector.size(); i++)
		delete TestsVector.at(i);

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


