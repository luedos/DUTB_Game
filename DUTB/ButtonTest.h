#pragma once
#include "GeneralTest.h"
#include <vector>
#include <random>
#include <string>


class ButtonTest : public GeneralTest
{
public:
	ButtonTest() {}

	Uint8 UintButton;

	vector<GeneralTest*>* TestsVectorRef;

	SDL_Event MyEvent;

	const Uint8 *KeyboardState;

	// Массив всех кнопок, используется в частности для функции определения названия кнопки из uint8 кода
	Uint8 EveryButton[30] = { SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_R, SDL_SCANCODE_T,
		SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_F, SDL_SCANCODE_G,
		SDL_SCANCODE_Z, SDL_SCANCODE_X, SDL_SCANCODE_C, SDL_SCANCODE_V, SDL_SCANCODE_B,
		SDL_SCANCODE_Y, SDL_SCANCODE_U, SDL_SCANCODE_I, SDL_SCANCODE_O, SDL_SCANCODE_P, 
		SDL_SCANCODE_H, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L, SDL_SCANCODE_N, 
		SDL_SCANCODE_M, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT };

	// Только для функции определения названия кнопки из uint8 кода
	string EveryString[30] = { "Q", "W" ,"E" ,"R" ,"T",
		"A" ,"S" ,"D" ,"F" ,"G",
		"Z" ,"X" ,"C" ,"V" ,"B", 
		"Y" ,"U" ,"I" ,"O" ,"P", 
		"H" ,"J" ,"K" ,"L" ,"N", 
		"M" ,"UP" ,"DOWN" ,"LEFT" ,"RIGHT" };

	// Функция определения названия кнопки из uint8 кода
	string GetStringFromButton(Uint8 ButtonRef)
	{
		for (int i = 0; i < 30; i++)
			if (ButtonRef == EveryButton[i])
				return EveryString[i];

		return "NONE";
	}

	// Функция для инициализации рандомной кнопки из массива

	int ButtonChoser(Uint8* ButtonsArrayRef, int MaxInt , int MinInt = 0)
	{

		int Chance;

		// true что бы цикл while стартовал
		bool TestBool = true;

		// Инициализация бога рандома
		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_int_distribution<int> dis(MinInt, MaxInt);

		// Цикл на проверку отсутствия создания двух одинаковых кнопок
		while (TestBool)
		{
			// Если цикл на проверку ничего не найдет переменная останется false
			TestBool = false;

			// Создание числа из рандома
			Chance = dis(gen);

			// Непосредственная проверка на отсутсвие 2 одинаковых кнопок
			for (int i = 0; i < TestsVectorRef->size(); i++)
			{
				ButtonTest* TestTest = dynamic_cast<ButtonTest*>(TestsVectorRef->at(i));

				if (TestTest)
					if (TestTest != this)
						if (TestTest->UintButton == ButtonsArrayRef[Chance])
							TestBool = true;
			}

		}

		UintButton = ButtonsArrayRef[Chance];
		return Chance;
	}


};