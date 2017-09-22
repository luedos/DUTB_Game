#include "stdafx.h"
#include "DPB_test.h"


DPB_test::DPB_test(vector<GeneralTest*>* TestsVectorLocalRef, bool DP_DNP_ref, float End, float Start, float PointsRateRef)
{
	KeyboardState = SDL_GetKeyboardState(NULL);

	DP_DNP = DP_DNP_ref;
	TestsVectorRef = TestsVectorLocalRef;

	ButtonChoser(EveryButton, 25, 15);

	if (DP_DNP)
		SideString = "DPress ";
	else
		SideString = "DNPress ";

	ButtonString = GetStringFromButton(UintButton);
	ColorToRender = { 225,225,225,225 };
	Timer = 0;
	MaxStartTimer = Start;
	MaxEndTimer = End;
	PointsRate = PointsRateRef;


}


DPB_test::~DPB_test()
{
}

bool DPB_test::EventTick(float DeltaMilliSeconds)
{
	Timer += DeltaMilliSeconds;

	Points = 0;


	if (KeyboardState[UintButton])
	{
		ColorToRender = { 0,225,0,225 };
		if (!DP_DNP)
			Points = -PointsRate * DeltaMilliSeconds * 0.001;
	}
	else
		if(Timer < MaxStartTimer)
			ColorToRender = { Uint8(200 * (Timer / MaxStartTimer)), Uint8(200 * (1 - Timer / MaxStartTimer)) , 0 , 225 };
		else
		{
			if (DP_DNP)
				Points = -PointsRate * DeltaMilliSeconds * 0.001;
			ColorToRender = { 225,0,0,225 };
		}



	if (Timer >= MaxEndTimer)
		bIsDelete = true;

	return true;
}