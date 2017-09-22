#pragma once


class LevelClass
{
public:
	LevelClass() {}

	virtual void StartLevel() {}

	virtual void FireLevel() {}

	virtual void PlaceLevel() {}

protected:
	class GM_Game* MyGame;
};