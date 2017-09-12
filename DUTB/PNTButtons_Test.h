#pragma once
#include "ButtonTest.h"



class PNTButtons_Test :	public ButtonTest
{

public:

	PNTButtons_Test(vector<GeneralTest*>* TestsVectorLocalRef, int PressNumberRef = 3, float End = 1500.f, float Start = 700.f, float PointsRateRef = 50.f);

	~PNTButtons_Test();

	bool EventTick(float DeltaMilliSeconds) override;

	void ReChargeTest(float Input1, float Input2, float Input3, float Input4) override;

	float StartTime;

	float EndTime;

	float Timer;

	int MaxPressNumber;

	int PressNumber = 0;

	string MainString;

	string SideString;

	SDL_Color MyColor;

	bool LastPressed;

	bool NewPressed;
};

