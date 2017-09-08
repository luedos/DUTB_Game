#pragma once
#include "LevelClass.h"
class TestLevel :
	public LevelClass
{
public:
	TestLevel(class Game* GameRef);
	~TestLevel();

	void StartLevel() override;

	void EventTick(float DeltaTime);

};

