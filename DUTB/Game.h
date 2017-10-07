#pragma once
#include "GM_Game.h"
#include "GM_StartMenu.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"
#include "TestLevel.h"
#include "CountSystem.h"
#include "Alphabets.h"
#include <fstream>
#include <limits>


class Game
{
public:
	Game();
	~Game();

	void NewGame();

	void EventTick(float DeltaTime);

	void ExitGame();

	bool Quit = false;

	TestLevel Level_Test= TestLevel(&GM_Gameplay);

	Level_1 Level1 = Level_1(&GM_Gameplay);
	Level_2 Level2 = Level_2(&GM_Gameplay);
	Level_3 Level3 = Level_3(&GM_Gameplay);
	vector<LevelClass*> LVector = { &Level1, &Level2, &Level3 };

	void PlaceLevelButtons();

	void GoStartMenu();

	void GoGameplay();


	bool ReadSaves() {
		ifstream Fin("Saves.txt");

		if (!Fin.is_open())
			return false;
		
		Alphabets SimpleAlph;

		for (int i = 0; i < LVector.size(); i++)
		{
			string LString;

			Fin >> LString;

			if (LString.length() > 30)
			{
				Fin.close();
				return false;
			}

			CountSystem<26> Fin_CS; Fin_CS.MyValue.clear();

			for (int ii = 0; ii < LString.length(); ii++)
			{
				int TestInt = SimpleAlph.GetNumFromChar(string(1, LString.at(ii)), true);
				if (TestInt == -1)
				{
					Fin.close();
					return false;
				}

				Fin_CS.MyValue.push_back(TestInt);
			}

			CountSystem<33> F_CS = Fin_CS.MakeNewCS<33>();

			if (F_CS.MyValue.size() < 10)
			{
				Fin.close();
				return false;
			}

			LString.clear();

			for (int ii = F_CS.MyValue.size() - 1; ii >= F_CS.MyValue.size() - 10; ii--)
				LString += SimpleAlph.GetCharFromNum(F_CS.MyValue.at(ii), false);

			if (LString == FailString.at(i))
				LVector.at(i)->LevelPassed = false;
			else
				if (LString == DoneString.at(i))
					LVector.at(i)->LevelPassed = true;
				else
				{
					Fin.close();
					return false;
				}


			for (int ii = 0; ii < 10; ii++)
				F_CS.MyValue.pop_back();

			CountSystem<33> P_CS; P_CS.MyValue.clear();

			for (int ii = 0; ii < F_CS.MyValue.size(); ii++)
				P_CS.MyValue.insert(P_CS.MyValue.begin(), F_CS.MyValue.at(ii));

			P_CS.Normalize();

			if (P_CS.MyValue.size() > 4)
			{
				Fin.close();
				return false;
			}

			int TestInt = 0;

			for (int ii = 0; ii < P_CS.MyValue.size(); ii++)
				TestInt += P_CS.MyValue.at(ii) * pow(33, ii);

			LVector.at(i)->SetPoints(TestInt);

			Fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		Fin.close();

		return true;

	}

	void CreateSaves() {
		ofstream Fout("Saves.txt");

		Alphabets SimpleAlph;

		for (int i = 0; i < LVector.size(); i++)
		{
			string LString;
			if (LVector.at(i)->LevelPassed)
				LString = DoneString.at(i);
			else
				LString = FailString.at(i);

			CountSystem<33> LN_CS; LN_CS.MyValue.clear();

			for (int ii = 0; ii < LString.length(); ii++)
				LN_CS.MyValue.push_back(SimpleAlph.GetNumFromChar(string(1, LString.at(ii)), false));

			CountSystem<33> P_CS(LVector.at(i)->LevelPoints);

			for (int ii = 0; ii < P_CS.MyValue.size(); ii++)
				LN_CS.MyValue.push_back(P_CS.MyValue.at(ii));

			CountSystem<33> H_CS; H_CS.MyValue.clear();

			for (int ii = 0; ii < LN_CS.MyValue.size(); ii++)
				H_CS.MyValue.insert(H_CS.MyValue.begin(), LN_CS.MyValue.at(ii));

			CountSystem<26> F_CS = H_CS.MakeNewCS<26>();

			LString.clear();

			for (int ii = 0; ii < F_CS.MyValue.size(); ii++)
				LString += SimpleAlph.GetCharFromNum(F_CS.MyValue.at(ii), true);

			Fout << LString << endl;
		}

		Fout.close();

	}

	void RecreateSaves() {

		ofstream Fout("Saves.txt");

		Alphabets SimpleAlph;

		for (int i = 0; i < LVector.size(); i++)
		{
			string LString;

			LString = FailString.at(i);

			CountSystem<33> LN_CS; LN_CS.MyValue.clear();

			for (int ii = 0; ii < LString.length(); ii++)
				LN_CS.MyValue.push_back(SimpleAlph.GetNumFromChar(string(1, LString.at(ii)), false));

			CountSystem<33> P_CS(0);

			for (int ii = 0; ii < P_CS.MyValue.size(); ii++)
				LN_CS.MyValue.push_back(P_CS.MyValue.at(ii));

			CountSystem<33> H_CS; H_CS.MyValue.clear();

			for (int ii = 0; ii < LN_CS.MyValue.size(); ii++)
				H_CS.MyValue.insert(H_CS.MyValue.begin(), LN_CS.MyValue.at(ii));

			CountSystem<26> F_CS = H_CS.MakeNewCS<26>();

			LString.clear();

			for (int ii = 0; ii < F_CS.MyValue.size(); ii++)
				LString += SimpleAlph.GetCharFromNum(F_CS.MyValue.at(ii), true);

			Fout << LString << endl;
		}

		Fout.close();
	}

private:

	vector<string> DoneString = { "первыйхорш", "второйхорш", "третийхорш" };
	vector<string> FailString = { "первыйплох", "второйплох", "третийплох" };

	std::fstream& GotoLine(std::fstream& file, unsigned int num) {
		file.seekg(std::ios::beg);
		for (int i = 0; i < num - 1; ++i) {
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return file;
	}

	Graphics GameGraphics;

	SDL_Event MyEvent;

	GM_Game GM_Gameplay = GM_Game(&GameGraphics, this);

	GM_StartMenu GM_StartScreen = GM_StartMenu(&GameGraphics, this);

	RenThing_Button* FindButton(int x, int y);

	GameMode* GM_NowPlaying;

};

