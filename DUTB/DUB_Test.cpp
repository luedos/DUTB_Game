#include "stdafx.h"
#include "DUB_Test.h"



DUB_Test::DUB_Test(vector<GeneralTest*>* TestsVectorLocalRef, float ChanserSpeed, bool IsPointers, float MaxTimerCount, float MaxChanser, float MaxDelay)
{
	KeyboardState = SDL_GetKeyboardState(NULL);

	TestsVectorRef = TestsVectorLocalRef;

	Pointers_Buttons = IsPointers;

	DUB_ChanserSpeed = ChanserSpeed;
	DUB_MaxTimerCount = MaxTimerCount;
	DUB_MaxChanser = MaxChanser;
	DUB_MaxDelay = MaxDelay;

	DUButtonChoser();

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

	if (CountTimer >= DUB_MaxTimerCount)
	{
		CountTimer = 0;
		if (Chanser > DUB_MaxChanser * (double)rand() / (double)RAND_MAX)
		{
			Chanser = 0;
			DUButtonChoser();
			
		}
	}	
		if (KeyboardState[UintButton])
			TextColor = { 0,225,0,225 };
		else
			if (DUB_MaxDelay > DelayTimer)
			{
				float lol = DUB_MaxDelay - DelayTimer;
				TextColor = { Uint8(200 * (1 - lol / DUB_MaxDelay)), Uint8(225 * lol / DUB_MaxDelay), 0 , 225 };
			}
			else
			{
				TextColor = { 225,0,0,225 };
				Points = -PointsRate * DeltaMilliSeconds * 0.001;
			}
	
	return true;
}

void DUB_Test::DUButtonChoser()
{
	if (Pointers_Buttons)
		IntPointer = ButtonChoser(EveryButton, 29,26) - 26;
	else
		ButtonChoser(EveryButton, 14);

	ButtonString = GetStringFromButton(UintButton);

	DelayTimer = 0;
}


