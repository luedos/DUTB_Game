#pragma once
#include "LevelClass.h"
class TestLevel :
	public LevelClass
{
public:
	TestLevel(class GM_Game* GameRef);
	~TestLevel();

	void StartLevel() override;

	void EventTick(float DeltaTime) override;

	void FireLevel() override;

	void PlaceLevel() override;



};

