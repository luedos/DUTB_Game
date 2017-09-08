#include "stdafx.h"
#include "DUB_Test.h"



DUB_Test::DUB_Test(vector<GeneralTest*>* TestsVectorLocalRef, float ChanserSpeed, float MaxTimerCount, float MaxChanser, float MaxDelay)
{
	KeyboardState = SDL_GetKeyboardState(NULL);

	TestsVectorRef = TestsVectorLocalRef;

	DUB_ChanserSpeed = ChanserSpeed;
	DUB_MaxTimerCount = MaxTimerCount;
	DUB_MaxChanser = MaxChanser;
	DUB_MaxDelay = MaxDelay;

	PointsRate = 10.f;

}


DUB_Test::~DUB_Test()
{
}

bool DUB_Test::EventTick(float DeltaMilliSeconds)
{
	Points = 0;

	DelayTimer += DeltaMilliSeconds;
	
	Chanser += DeltaMilliSeconds * DUB_ChanserSpeed * 0.001;
	CountTimer += DeltaMilliSeconds;

	while (SDL_PollEvent(&MyEvent))
	{
		SDL_PumpEvents();

		
	}

	

	if (CountTimer >= DUB_MaxTimerCount)
	{
		CountTimer = 0;
		if (Chanser > DUB_MaxChanser * (double)rand() / (double)RAND_MAX)
		{
			Chanser = 0;
			DUButtonChoser();
		}
	}

	if (!Pointers_Buttons)
		ButtonString = GetStringFromButton(UintButton);

	if (DelayTimer >= DUB_MaxDelay && !KeyboardState[UintButton])
	{
		DelayTimer = DUB_MaxDelay;
		TextColor = { 225,0,0,225 };
		Points = PointsRate * DeltaMilliSeconds * 0.001;

		SideString = " DUTB";

	}
	
		
	

		if (KeyboardState[UintButton])
		{
			TextColor = { 0,225,0,225 };
			if (!Pointers_Buttons)
				SideString = " Good";

		}
		else
			if (DUB_MaxDelay != DelayTimer)
			{
				float lol = DUB_MaxDelay - DelayTimer;
				TextColor = { Uint8(200 * (1 - lol / DUB_MaxDelay)), Uint8(225 * lol / DUB_MaxDelay), 0 , 225 };
				//if (!Pointers_Buttons)
				//	StringToRender += " " + to_string(lol);
				SideString = " DUTB";
			}
	
	return true;
}

void DUB_Test::ReChargeTest(float Input1, float Input2, float Input3, float Input4)
{
	DUButtonChoser();
	Chanser = 0;
	CountTimer = 0;
	DelayTimer = 0;
	DUB_ChanserSpeed = Input1;
	DUB_MaxTimerCount = Input2;
	DUB_MaxChanser = Input3;
	DUB_MaxDelay = Input4;

}

void DUB_Test::DUButtonChoser()
{
	if (Pointers_Buttons)
		IntPointer = ButtonChoser(PointersPresets, 3);
	else
		ButtonChoser(ButtonsPresets, 14);

	DelayTimer = 0;
}


