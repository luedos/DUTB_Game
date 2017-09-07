#pragma once
#include "NewIncludes/DelegateClass.h"
#include "SDL2/include/SDL.h"
#include "DUB_Test.h"
#include "Graphics.h"
#include "DPB_test.h"


enum ETests {
	DUBPointers,
	DUBButtons,
	DPButton,
	DNPButton
};

struct GeneratorStruct
{
	// Test options
	ETests TestItself;
	int Level;
	// Generator options
	float MaxDelta;
	float ChanserSpeed;
	float CheckRate;
	int MaxCallsNumber;
	// Local variables
	int CallsNumber = 0;
	float Chanser = 0.f;
	float CheckTimer = 0.f;
};

struct DeltaTestsStruct
{
	ETests TestItself;
	int Level;

	float MS_DeltaTime;
	int MaxCallsNamber;

	float MS_Time = 0;
	int CallsNumber = 0;

};

struct LevelStruct
{
	vector<DeltaTestsStruct> StartDeltaTests;
	vector<GeneratorStruct> StartGeneratorTests;
};

class Game

{
public:
	
	Game();
	~Game();

	

	void AddTest(ETests WhichTest, int PowerLevel);

	void EventTick(float DeltaTime);

	bool Quit;

	SDL_Event MyEvent;

	void TickEveryTest(float DeltaTime);

	void NewGame();

	void NewRound();

	LevelStruct GameLevel;

	void ExitGame();

	float GamePoints = 0;

	string TextPoints;

	void ClearTests();

	void ClearGenerators();

	bool DeleteTest(GeneralTest* TestToDelete);

	void GeneratorTick(float DeltaTime);

	void AddGeneratorTest(ETests TestRef, int LevelRef, float MaxDeltaRef, float ChanserSpeedRef, float CheckRateRef = 1000.f, int NumberOfCallsRef = 0)
	{
		GeneratorStruct NewGenerator;
		NewGenerator.TestItself = TestRef;
		NewGenerator.Level = LevelRef;
		NewGenerator.MaxDelta = MaxDeltaRef;
		NewGenerator.ChanserSpeed = ChanserSpeedRef;
		NewGenerator.CheckRate = CheckRateRef;
		NewGenerator.MaxCallsNumber = NumberOfCallsRef;
		Generator.push_back(NewGenerator);
	}

	void DeltaTestTick(float DeltaTime);

	void AddDeltaTests(ETests TestRef, int LevelRef, float MS_DeltaTimeRate, int NumbersOfCall = 1)
	{
		DeltaTestsStruct NewDeltaTest;
		NewDeltaTest.TestItself = TestRef;
		NewDeltaTest.Level = LevelRef;
		NewDeltaTest.MS_DeltaTime = MS_DeltaTimeRate;
		NewDeltaTest.MaxCallsNamber = NumbersOfCall;

		DeltaTests.push_back(NewDeltaTest);
	}

	Graphics MyGraph;

	vector<GeneralTest*> TestsVector;



private:
	Delegate MyDelegate;

	vector<GeneratorStruct> Generator;
	vector<DeltaTestsStruct> DeltaTests;
};

