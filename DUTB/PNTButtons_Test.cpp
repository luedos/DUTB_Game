#include "stdafx.h"
#include "PNTButtons_Test.h"


PNTButtons_Test::PNTButtons_Test(vector<GeneralTest*>* TestsVectorLocalRef, int PressNumberRef, float End, float Start, float PointsRateRef)
{
	KeyboardState = SDL_GetKeyboardState(NULL);

	TestsVectorRef = TestsVectorLocalRef;
	EndTime = End;
	StartTime = Start;
	PointsRate = PointsRateRef;
	PressNumber = PressNumberRef;

	ButtonChoser(EveryButton, 25, 15);

	LastPressed = false;

	NewPressed = false;

	ButtonString = GetStringFromButton(UintButton);
}


PNTButtons_Test::~PNTButtons_Test()
{
}

bool PNTButtons_Test::EventTick(float DeltaMilliSeconds)
{
	Points = 0;

	Timer += DeltaMilliSeconds;

	NewPressed = KeyboardState[UintButton];


	if (NewPressed != LastPressed)
	{
		if (NewPressed)
		{
			PressNumber--;
			if (PressNumber < 0)
				Points -= PointsRate / 4;
		}
		LastPressed = NewPressed;
	}

	if (PressNumber = 0)
		MyColor = { 0,225,0,225 };
	else
		if (PressNumber < 0)
			MyColor = { 225,0,0,225 };
		else
			if (Timer < StartTime)
				MyColor = { Uint8(225 * (1.f - Timer / StartTime)) , Uint8(225 * (Timer / StartTime)) , 0 ,225 };
			else
			{
				MyColor = { 225, 0, 0, 225 };
				Points -= DeltaMilliSeconds * PointsRate * 0.001;
			}


	if (Timer > EndTime)
		bIsDelete = true;

	SideString = to_string(PressNumber) + " Times";

	return true;
}
