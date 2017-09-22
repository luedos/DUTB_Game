#pragma once
#include <iostream>
#include "SDL2/include/SDL.h"
#include "RenThing.h"

using namespace std;



class GeneralTest

{

public:
	GeneralTest() {}
	~GeneralTest() {}

	virtual bool EventTick(float DeltaMilliSeconds) { return false; }

	float Points = 0.f;

	float PointsRate = 10.f;

	bool bIsDelete = false;

	RenThing* MyThing = nullptr;

};

