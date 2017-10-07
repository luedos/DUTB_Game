#pragma once
#include "LevelClass.h"

class Level_2 :
	public LevelClass

{
public:

	Level_2(class GM_Game* GameRef);
	~Level_2();

	void StartLevel() override;

	void FireLevel() override;

	void PlaceLevel() override;

	void PassLevel(int Points) override;

};

