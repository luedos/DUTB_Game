#include "stdafx.h"
#include "TestLevel.h"
#include "GM_Game.h"
#include "Game.h"

TestLevel::TestLevel(GM_Game* GameRef)
{
	MyGame = GameRef;
}


TestLevel::~TestLevel()
{
}

void TestLevel::StartLevel()
{
	MyGame->AddDeltaTests(ETests::DUBPointers, 1, 0);
	MyGame->AddDeltaTests(ETests::DUBPointers, 1, 30000);
	
	MyGame->AddGeneratorTest(ETests::DPButton, 2, 600, 30, 500);
	MyGame->AddGeneratorTest(ETests::PNTButton, 2, 1000, 10);
	MyGame->AddGeneratorTest(ETests::DNPButton, 2, 1000, 10);

	MyGame->GameTime = 3000;

	MyGame->MaxPoints = 100;
}

void TestLevel::EventTick(float DeltaTime)
{
}

void TestLevel::FireLevel()
{
	PlaceLevel();
	MyGame->MyGame->SetGameMode(EGameMode::GameGM);

}

void TestLevel::PlaceLevel()
{
	MyGame->MyLevel = this;
}