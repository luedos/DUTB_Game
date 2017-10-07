#include "stdafx.h"
#include "Level_2.h"
#include "GM_Game.h"
#include "Game.h"


Level_2::Level_2(GM_Game* GameRef)
{
	MyGame = GameRef;

}


Level_2::~Level_2()
{
}

void Level_2::StartLevel()
{
	MyGame->AddDeltaTests(ETests::DUBButtons, 1, 0);
	MyGame->AddDeltaTests(ETests::DUBPointers, 2, 45000);

	MyGame->AddGeneratorTest(ETests::DPButton, 2, 600, 30, 500);
	MyGame->AddGeneratorTest(ETests::PNTButton, 1, 1000, 20);
	MyGame->AddGeneratorTest(ETests::DNPButton, 1, 1000, 20);

	MyGame->SetLevelVars(500, 90000, 5);
}

void Level_2::FireLevel()
{
	PlaceLevel();
	MyGame->MyGame->GoGameplay();

}

void Level_2::PlaceLevel()
{
	MyGame->MyLevel = this;
}

void Level_2::PassLevel(int Points)
{
	LevelPassed = true;
	if (Points > LevelPoints)
	SetPoints(Points);
	MyGame->MyGame->CreateSaves();
}
