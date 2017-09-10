#pragma once


class GameMode
{

public:
	GameMode() {}

	virtual void GM_EventTick(float DeltaTime) {}

	virtual void GM_Start() {}

	virtual void GM_End() {}
	

};
