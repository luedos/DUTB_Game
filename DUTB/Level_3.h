#pragma once
#include "LevelClass.h"


class Level_3 :
	public LevelClass
{
public:
	Level_3(GM_Game* GameRef);
	~Level_3();

	void StartLevel() override;

	void FireLevel() override;

	void PlaceLevel() override;

	void PassLevel(int Points) override;

};

