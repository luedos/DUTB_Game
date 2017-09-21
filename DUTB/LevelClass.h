#pragma once


class LevelClass
{
public:
	LevelClass();

	virtual void StartLevel() {}

	virtual void EventTick(float DeltaTime) {}

	virtual void FireLevel();

	virtual void PlaceLevel();

	class GM_Game* MyGame;


};