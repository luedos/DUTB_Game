#pragma once
#include "ButtonTest.h"


class DPB_test :
	public ButtonTest

{

public:

	DPB_test(vector<GeneralTest*>* TestsVectorLocalRef, bool DP_DNP_ref = true, float End = 1500.f, float Start = 700.f, float PointsRateRef = 50.f);
	~DPB_test();


	bool EventTick(float DeltaMilliSeconds) override;

	SDL_Color ColorToRender;

private:

	// Для исчесления времени жизни теста
	float Timer;

	// Когда начнуться прибовляться очки
	float MaxStartTimer;

	// Когда тест закончится
	float MaxEndTimer;

	bool DP_DNP;
};

