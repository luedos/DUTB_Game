#include "stdafx.h"
#include "Level_1.h"
#include "GM_Game.h"
#include "Game.h"


Level_1::Level_1(GM_Game* GameRef)
{
	MyGame = GameRef;
}


Level_1::~Level_1()
{
}

void Level_1::StartLevel()
{
	MyGame->AddDeltaTests(ETests::DUBButtons, 1, 0);
	MyGame->AddDeltaTests(ETests::DUBButtons, 1, 30000);

	MyGame->AddGeneratorTest(ETests::DPButton, 2, 600, 30, 500);
	MyGame->AddGeneratorTest(ETests::PNTButton, 2, 1000, 10);
	MyGame->AddGeneratorTest(ETests::DNPButton, 2, 1000, 10);

	MyGame->SetLevelVars(500, 120000);
}

void Level_1::FireLevel()
{
	PlaceLevel();
	MyGame->MyGame->GoGameplay();

}

void Level_1::PlaceLevel()
{
	MyGame->MyLevel = this;
}

