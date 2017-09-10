#pragma once
#include "LevelClass.h"
class TestLevel :
	public LevelClass
{
public:
	TestLevel(class GM_Game* GameRef);
	~TestLevel();

	void StartLevel() override;

	void EventTick(float DeltaTime);


	class GM_Game* MyGame;

};

