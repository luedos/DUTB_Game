#pragma once

#include "DUB_Test.h"
#include "DPB_test.h"
#include "TestLevel.h"
#include "Level_1.h"
#include "PNTButtons_Test.h"
#include "GameMode.h"


enum ETests {
	DUBPointers,
	DUBButtons,
	DPButton,
	DNPButton,
	PNTButton
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

class GM_Game : public GameMode

{
public:
	
	GM_Game(Graphics* GraphRef, class Game* GameRef);
	~GM_Game();

	void GM_EventTick(float DeltaTime) override;

	void GM_Start() override;

	void GM_End() override;

	void GM_Event(SDL_Event* EventRef) override;

	void AddTest(ETests WhichTest, int PowerLevel);

	void SetLevelVars(float MaxPointsRef, float GameTimeRef) {
		MaxPoints = MaxPointsRef;
		GameTime = GameTimeRef;
		GamePoints = MaxPoints;
	}

	void ClearTests();

	void ClearGenerators();

	bool DeleteTest(GeneralTest* TestToDelete);

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

	void AddDeltaTests(ETests TestRef, int LevelRef, float MS_DeltaTimeRate, int NumbersOfCall = 1)
	{
		DeltaTestsStruct NewDeltaTest;
		NewDeltaTest.TestItself = TestRef;
		NewDeltaTest.Level = LevelRef;
		NewDeltaTest.MS_DeltaTime = MS_DeltaTimeRate;
		NewDeltaTest.MaxCallsNamber = NumbersOfCall;

		DeltaTests.push_back(NewDeltaTest);
	}

	vector<GeneralTest*> TestsVector;

	LevelClass* MyLevel = nullptr;

	void GP_Pause();

	void UnPause();

	void GameOverMenu();

	void WinGameMenu();

	void LevelChooseMenu();

private:
	void TickEveryTest(float DeltaTime);

	void DeltaTestTick(float DeltaTime);

	void GeneratorTick(float DeltaTime);

	bool bTickTests = true;

	float GameTime;

	float MaxPoints;

	float GamePoints;

	float Percent;

	string TextPoints;

	string TextGameTime;

	vector<GeneratorStruct> Generator;
	vector<DeltaTestsStruct> DeltaTests;

	RenThing_Canvas* RenCanvas1 = nullptr;
	RenThing_Canvas* RenCanvas2 = nullptr;

	vector<RenThing*> PauseRenThings;
};

