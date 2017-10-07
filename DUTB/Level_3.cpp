#include "stdafx.h"
#include "Level_3.h"
#include "GM_Game.h"
#include "Game.h"


Level_3::Level_3(GM_Game* GameRef)
{
	MyGame = GameRef;

}


Level_3::~Level_3()
{
}

void Level_3::StartLevel()
{
	MyGame->AddDeltaTests(ETests::DUBButtons, 1, 0);
	MyGame->AddDeltaTests(ETests::DUBPointers, 2, 45000);
	MyGame->AddDeltaTests(ETests::DUBPointers, 2, 60000);

	MyGame->AddGeneratorTest(ETests::DPButton, 2, 600, 30, 500);
	MyGame->AddGeneratorTest(ETests::PNTButton, 3, 1000, 20);
	MyGame->AddGeneratorTest(ETests::DNPButton, 2, 1000, 20);

	MyGame->SetLevelVars(500, 120000, 6);
}

void Level_3::FireLevel()
{
	PlaceLevel();
	MyGame->MyGame->GoGameplay();

}

void Level_3::PlaceLevel()
{
	MyGame->MyLevel = this;
}

void Level_3::PassLevel(int Points)
{
	LevelPassed = true;
	if (Points > LevelPoints)
	SetPoints(Points);
	MyGame->MyGame->CreateSaves();
}
