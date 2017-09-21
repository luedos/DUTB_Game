#include "stdafx.h"
#include "LevelClass.h"
#include "GM_Game.h"
#include "Game.h"

LevelClass::LevelClass()
{
}

void LevelClass::FireLevel()
{
	PlaceLevel();
	MyGame->MyGame->SetGameMode(EGameMode::GameGM);
	
}

void LevelClass::PlaceLevel()
{
	MyGame->MyLevel = this;
}