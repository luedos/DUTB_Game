#pragma once
#include "LevelClass.h"


class Level_1 :
	public LevelClass
{
public:
	Level_1(class GM_Game* GameRef);
	~Level_1();

	void StartLevel() override;

	void FireLevel() override;

	void PlaceLevel() override;

	void PassLevel(int Points) override;
};

