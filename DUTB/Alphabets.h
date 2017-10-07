#pragma once
#include <string>
#include <vector>
using namespace std;

class Alphabets
{
public:
	Alphabets() {}

	vector<string> RusAlph = { "à", "á", "â", "ã", "ä", "å", "¸", "æ", "ç", "è",
		"é", "ê", "ë", "ì", "í", "î", "ï", "ð", "ñ", "ò",
		"ó", "ô", "õ", "ö", "÷", "ø", "ù", "ú", "û", "ü",
		"ý", "þ", "ÿ", };
	vector<string> EngAlph = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
		"k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
		"u", "v", "w", "x", "y", "z" };

	string GetCharFromNum(unsigned int Num, bool IsEng) {
		if (IsEng) {
			if (Num < 26)
				return EngAlph.at(Num);
		}
		else
			if (Num < 33)
				return RusAlph.at(Num);

		return "NONE";
	}

	int GetNumFromChar(string InChar, bool IsEng) {
		if(IsEng)
			for (int i = 0; i < EngAlph.size(); i++)
			{
				if (EngAlph.at(i) == InChar)
					return i;
			}
		else
			for (int i = 0; i < RusAlph.size(); i++)
			{
				if (RusAlph.at(i) == InChar)
					return i;
			}
		return -1;
		
	}
};