#pragma once
#include "ButtonTest.h"




class DUB_Test :
	public ButtonTest

{

public:
	DUB_Test(vector<GeneralTest*>* TestsVectorLocalRef, float ChanserSpeed, float MaxChanser = 1000.f, float MaxTimerCount = 500.f, float MaxDelay = 1500.f);
	~DUB_Test();

	bool EventTick(float DeltaMilliSeconds) override;

	void ReChargeTest(float Input1, float Input2, float Input3, float Input4) override;

	float DUB_ChanserSpeed;
	float DUB_MaxTimerCount;
	float DUB_MaxChanser;
	float DUB_MaxDelay;

	void DUButtonChoser();

	string SideString;

	string ButtonString;

	SDL_Color TextColor;

	int IntPointer;

	bool Pointers_Buttons = true;

private:

	
	string Time;

	double Chanser = 0;

	float CountTimer = 0;

	float DelayTimer = 0;

	Uint8 ButtonsPresets[15] = { SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_R, SDL_SCANCODE_T,
		SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_F, SDL_SCANCODE_G,
		SDL_SCANCODE_Z, SDL_SCANCODE_X, SDL_SCANCODE_C, SDL_SCANCODE_V, SDL_SCANCODE_B };

	Uint8 PointersPresets[4] = { SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT };

	SDL_Event MyEvent;





};

