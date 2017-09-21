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

//struct LevelStruct
//{
//	vector<DeltaTestsStruct> StartDeltaTests;
//	vector<GeneratorStruct> StartGeneratorTests;
//};

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



	void TickEveryTest(float DeltaTime);

	void NewRound();

	//LevelStruct GameLevel;

	float MaxPoints;

	float GamePoints;

	float Percent;

	string TextPoints;

	string TextGameTime;

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

	Graphics* MyGraph;

	class Game* MyGame;

	vector<GeneralTest*> TestsVector;

	LevelClass* MyLevel = nullptr;

	void GP_Pause();

	void UnPause();

	void GameOver();

	void WinGameMenu();

	bool bTickTests = true;

	const Uint8 *KeyboardState;

	float GameTime;

	void LevelChooseMenu();

private:

	vector<GeneratorStruct> Generator;
	vector<DeltaTestsStruct> DeltaTests;

	RenThing_Canvas* RenCanvas1 = nullptr;
	RenThing_Canvas* RenCanvas2 = nullptr;

	vector<RenThing*> PauseRenThings;
};

