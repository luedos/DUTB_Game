#pragma once
#include <string> 
using namespace std;

class LevelClass
{
public:
	LevelClass() {}

	virtual void StartLevel() {}

	virtual void FireLevel() {}

	virtual void PlaceLevel() {}

	virtual void PassLevel(int Points) {}

	bool LevelPassed = false;

	int LevelPoints = 0;

	string StringPoints = "";

	void SetPoints(int Points) { 
		LevelPoints = Points; 
		StringPoints = to_string(Points);
	}

protected:
	class GM_Game* MyGame;
};