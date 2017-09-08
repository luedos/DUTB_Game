#include "stdafx.h"
#include "TestLevel.h"
#include "Game.h"

TestLevel::TestLevel(Game* GameRef)
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
	
	MyGame->AddGeneratorTest(ETests::DPButton, 2, 700, 15, 600);
	MyGame->AddGeneratorTest(ETests::DNPButton, 2, 1000, 10);
}

void TestLevel::EventTick(float DeltaTime)
{
}
