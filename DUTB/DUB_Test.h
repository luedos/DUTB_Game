#pragma once
#include "ButtonTest.h"




class DUB_Test :
	public ButtonTest

{

public:
	DUB_Test(vector<GeneralTest*>* TestsVectorLocalRef, float ChanserSpeed, bool IsPointers = true, float MaxChanser = 1000.f, float MaxTimerCount = 500.f, float MaxDelay = 1500.f);
	~DUB_Test();

	bool EventTick(float DeltaMilliSeconds) override;

	void DUButtonChoser();

	SDL_Color TextColor;

	int IntPointer;

private:
	float DUB_ChanserSpeed;
	float DUB_MaxTimerCount;
	float DUB_MaxChanser;
	float DUB_MaxDelay;

	double Chanser = 0;

	float CountTimer = 0;

	float DelayTimer = 0;

	bool Pointers_Buttons;



};

