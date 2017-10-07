#pragma once
#include <vector>

using namespace std;

template<int IntType>
class CountSystem
{
public: 
	CountSystem() {};

	CountSystem(int TenCSIn) {
	MyValue.insert(MyValue.begin(), TenCSIn);
	Normalize();
	}


	void Normalize() {
		for (int i = 0; i < MyValue.size(); i++)
		{
			if (!MyValue.at(i) < IntType)
				if (i < MyValue.size() - 1)
				{
					int SomeInt = MyValue.at(i) / IntType;
					MyValue.at(i) -= IntType * SomeInt;
					MyValue.at(i + 1) += SomeInt;
				}
				else
				{
					int SomeInt = MyValue.at(i) / IntType;
					if (SomeInt != 0)
					{
						MyValue.at(i) -= IntType * SomeInt;
						MyValue.push_back(SomeInt);
					}
				}
			
		}

		for (int i = MyValue.size() - 1; i > 0; i--)
		{
			if (MyValue.at(i) == 0)
				MyValue.pop_back();
			else
				break;
		}

		if (MyValue.size() > 1)
		{
			if (MyValue.back() < 0)
				for (int i = MyValue.size() - 2; i >= 0; i--)
					if (MyValue.at(i) > 0)
					{
						MyValue.at(i) -= IntType;
						MyValue.at(i + 1) += 1;
					}

			if(MyValue.back() > 0)
				for(int i = MyValue.size() - 2; i >=0; i--)
					if (MyValue.at(i) < 0)
					{
						MyValue.at(i) += IntType;
						MyValue.at(i + 1) -= 1;
					}
		}

		for (int i = MyValue.size() - 1; i > 0; i--)
		{
			if (MyValue.at(i) == 0)
				MyValue.pop_back();
			else
				break;
		}
	}

	void NormalizeVector(vector<int>* InVector, int InOrder = IntType) const  {

		vector<int> TestVector = *InVector;

		for (int i = 0; i < TestVector.size(); i++)
		{
			if (!TestVector.at(i) < InOrder)
				if (i < TestVector.size() - 1)
				{
					int SomeInt = TestVector.at(i) / InOrder;
					TestVector.at(i) -= InOrder * SomeInt;
					TestVector.at(i + 1) += SomeInt;
				}
				else
				{
					int SomeInt = TestVector.at(i) / InOrder;
					if (SomeInt != 0)
					{
						TestVector.at(i) -= InOrder * SomeInt;
						TestVector.push_back(SomeInt);
					}
				}

		}

		for (int i = TestVector.size() - 1; i > 0; i--)
		{
			if (TestVector.at(i) == 0)
				TestVector.pop_back();
			else
				break;
		}

		if (TestVector.size() > 1)
		{
			if (TestVector.back() < 0)
				for (int i = TestVector.size() - 2; i >= 0; i--)
					if (TestVector.at(i) > 0)
					{
						TestVector.at(i) -= InOrder;
						TestVector.at(i + 1) += 1;
					}

			if (TestVector.back() > 0)
				for (int i = TestVector.size() - 2; i >= 0; i--)
					if (TestVector.at(i) < 0)
					{
						TestVector.at(i) += InOrder;
						TestVector.at(i + 1) -= 1;
					}
		}

		for (int i = TestVector.size() - 1; i > 0; i--)
		{
			if (TestVector.at(i) == 0)
				TestVector.pop_back();
			else
				break;
		}

		InVector->swap(TestVector);
	}

	template<int NewInt>
	CountSystem<NewInt> MakeNewCS() {
		
		CountSystem<IntType> InOne(NewInt);
				
		CountSystem<IntType> OldOne;
		OldOne = *this;

		CountSystem<NewInt> NewOne;
		NewOne.MyValue.clear();

		int MaxPowInt = 1;

		while (InOne.Pow(MaxPowInt) <= OldOne)
			MaxPowInt++;

		MaxPowInt--;

		for (int i = MaxPowInt; i >= 0; i--)
		{
			CountSystem<IntType> SomeForTest = InOne.Pow(i);

			CountSystem<IntType> TestOne = OldOne / InOne.Pow(i);

			int TestOneInt = 0;
			for (int a = 0; a < TestOne.MyValue.size(); a++)
				TestOneInt += TestOne.MyValue.at(a) * pow(IntType, a);

			NewOne.MyValue.insert(NewOne.MyValue.begin(),TestOneInt);

			OldOne -= TestOne * InOne.Pow(i);

		}
				
		
		int ExtraInt = 0;
		for (int i = 0; i < OldOne.MyValue.size(); i++)
			ExtraInt += OldOne.MyValue.at(i) * pow(IntType, i);

		NewOne.MyValue.at(0) += ExtraInt;

		NewOne.Normalize();

		return  NewOne;
	}

	CountSystem<IntType> Pow(int InPow) {

		CountSystem<IntType> NewOne;

		NewOne.MyValue = MyValue;

		for (int i = 1; i < InPow; i++)
			NewOne *= *this;

		return NewOne;
		

	}

	void PowSelf(int InPow) {

		CountSystem<IntType> NewOne;

		NewOne.MyValue = MyValue;

		for (int i = 1; i < InPow; i++)
			this *= NewOne;

		
	}

	CountSystem<IntType> operator + (const CountSystem<IntType>& InCS) {
		CountSystem<IntType> NewOne;
		
		vector<int> NewVector;

		if (MyValue.size() >= InCS.MyValue.size())
		{
			NewVector = MyValue;
			
			for (int i = 0; i < InCS.MyValue.size(); i++)
				NewVector.at(i) += InCS.MyValue.at(i);
		}
		else
		{
			NewVector = InCS.MyValue;

			for (int i = 0; i < MyValue.size(); i++)
				NewVector.at(i) += MyValue.at(i);
		}

		NewOne.MyValue.swap(NewVector);
		NewOne.Normalize();

		return NewOne;

	}

	void operator += (const CountSystem<IntType>& InCS) {

		vector<int> NewVector;

		if (MyValue.size() >= InCS.MyValue.size())
		{
			NewVector = vector(MyValue);

			for (int i = 0; i < InCS.MyValue.size(); i++)
				NewVector.at(i) += InCS.MyValue.at(i);
		}
		else
		{
			NewVector = InCS.MyValue;

			for (int i = 0; i < MyValue().size(); i++)
				NewVector.at(i) += MyValue.at(i);
		}

		MyValue.swap(NewVector);
		Normalize();

	}

	CountSystem<IntType> operator - (const CountSystem<IntType>& InCS) {
		CountSystem<IntType> OutCS;
		vector<int> TestVector;

		if (MyValue.size() < InCS.MyValue.size())
		{
			TestVector = InCS.MyValue;
			for (int i = 0; i < MyValue.size(); i++)
				TestVector.at(i) -= MyValue.at(i);

			for (int i = 0; i < TestVector.size(); i++)
				TestVector.at(i) *= (-1);
		}
		else
		{
			TestVector = MyValue;

			for (int i = 0; i < InCS.MyValue.size(); i++)
				TestVector.at(i) -= InCS.MyValue.at(i);

		}

		NormalizeVector(&TestVector);

		OutCS.MyValue.swap(TestVector);

		return OutCS;
	}

	void operator -= (const CountSystem<IntType>& InCS) {

		int TestInt = InCS.MyValue.size() - MyValue.size();

		for (int i = 0; i < TestInt; i++)
			MyValue.push_back(0);

		for (int i = 0; i < MyValue.size() && i < InCS.MyValue.size(); i++)
			MyValue.at(i) -= InCS.MyValue.at(i);

		Normalize();

	}

	void operator = (const CountSystem<IntType>& InCS) {
		MyValue = InCS.MyValue;
	}

	CountSystem<IntType> operator * (const CountSystem<IntType>& InCS) {

		vector<int> NewVector = vector<int>(1,0);

		for (int i = 0; i < InCS.MyValue.size(); i++)
		{
			vector<int> TestVector = MyValue;

			for (int ii = 0; ii < TestVector.size(); ii++)
				TestVector.at(ii) *= InCS.MyValue.at(i);

			NormalizeVector(&TestVector);

			VectorTenPow(&TestVector, i);

			for (int ii = 0; ii < NewVector.size() && ii < TestVector.size(); ii++)
				NewVector.at(ii) += TestVector.at(ii);

			if (TestVector.size() > NewVector.size())
			{
				int TestInt = NewVector.size();
				for (int ii = TestInt; ii < TestVector.size(); ii++)
					NewVector.push_back(TestVector.at(ii));
			}

			NormalizeVector(&NewVector);

		}

		CountSystem<IntType> NewCS;
		NewCS.MyValue.swap(NewVector);

		return NewCS;

	}

	void operator *= (const CountSystem<IntType>& InCS) {
		vector<int> NewVector = vector<int>(1, 0);

		for (int i = 0; i < InCS.MyValue.size(); i++)
		{
			vector<int> TestVector = MyValue;

			for (int ii = 0; ii < TestVector.size(); ii++)
				TestVector.at(ii) *= InCS.MyValue.at(i);

			NormalizeVector(&TestVector);

			VectorTenPow(&TestVector, i);

			for (int ii = 0; ii < NewVector.size() && ii < TestVector.size(); ii++)
				NewVector.at(ii) += TestVector.at(ii);

			if (TestVector.size() > NewVector.size())
			{
				int TestInt = NewVector.size();
				for (int ii = TestInt; ii < TestVector.size(); ii++)
					NewVector.push_back(TestVector.at(ii));
			}

			NormalizeVector(&NewVector);

		}

		MyValue.swap(NewVector);
	}

	void SelfMultOnInt (int InInt) {

		for (int i = 0; i < MyValue.size(); i++)
			MyValue *= InInt;

		Normalize();

	}

	CountSystem<IntType> MultOnInt (int InInt) const  {
		vector<int> NewVector;
	
		for (int i = 0; i < MyValue.size(); i++)
			NewVector.push_back(MyValue.at(i) * InInt);
	
		NormalizeVector(&NewVector);
	
		CountSystem<IntType> NewCS;
		NewCS.MyValue.swap(NewVector);
	
		return NewCS;
	}

	void operator /= (const CountSystem<IntType>& InCS) {
	
		vector<int> TestVector;

		CountSystem<IntType> TestCS;

		for (int i = MyValue.size() - 1; i >= 0; i--)
		{
			TestCS.MyValue.insert(TestCS.MyValue.begin(), MyValue.at(i));

			if (TestCS < InCS)
			{
				if (TestCS.MyValue.size() > 2)
					TestVector.insert(TestVector.begin(), 0);

				TestCS.Normalize();
				continue;
			}
			else
			{
				int DiveideInt = 1;
				while (InCS.MultOnInt(DiveideInt) <= TestCS)
				{
					DiveideInt++;
				}

				DiveideInt--;

				TestVector.insert(TestVector.begin(), DiveideInt);

				TestCS -= InCS.MultOnInt(DiveideInt);
			}
		}

		NormalizeVector(&TestVector);

		MyValue.swap(TestVector);
	}

	CountSystem<IntType> operator / (const CountSystem<IntType>& InCS) {

		vector<int> TestVector;

		CountSystem<IntType> TestCS;

		TestCS.MyValue.clear();

		for (int i = MyValue.size() - 1; i >= 0; i--)
		{
			TestCS.MyValue.insert(TestCS.MyValue.begin(), MyValue.at(i));

			if (TestCS < InCS)
			{
				if (TestCS.MyValue.size() > 2)
					TestVector.insert(TestVector.begin(), 0);

				TestCS.Normalize();
				continue;
			}
			else
			{
				int DiveideInt = 1;
				while (InCS.MultOnInt(DiveideInt) <= TestCS)
				{
					DiveideInt++;
				}

				DiveideInt--;

				TestVector.insert(TestVector.begin(), DiveideInt);
				
				TestCS -= InCS.MultOnInt(DiveideInt);
			}
		}

		NormalizeVector(&TestVector);

		TestCS.MyValue.swap(TestVector);

		return TestCS;
	}

	bool operator > (const CountSystem<IntType>& InCS) {
		if (MyValue.size() > InCS.MyValue.size())
			return true;

		if (MyValue.size() < InCS.MyValue.size())
			return false;

		if(MyValue.size() == InCS.MyValue.size())
			for (int i = MyValue.size() - 1; i >= 0; i--)
			{
				if (MyValue.at(i) > InCS.MyValue.at(i))
					return true;

				if (MyValue.at(i) < InCS.MyValue.at(i))
					return false;
			}

		return false;
	}

	bool operator < (const CountSystem<IntType>& InCS) {
		if (MyValue.size() > InCS.MyValue.size())
			return false;

		if (MyValue.size() < InCS.MyValue.size())
			return true;

		if (MyValue.size() == InCS.MyValue.size())
			for (int i = MyValue.size() - 1; i >= 0; i--)
			{
				if (MyValue.at(i) > InCS.MyValue.at(i))
					return false;

				if (MyValue.at(i) < InCS.MyValue.at(i))
					return true;
			}

		return false;
	}

	bool operator <= (const CountSystem<IntType>& InCS) {
		if (MyValue.size() > InCS.MyValue.size())
			return false;

		if (MyValue.size() < InCS.MyValue.size())
			return true;

		if (MyValue.size() == InCS.MyValue.size())
			for (int i = MyValue.size() - 1; i >= 0; i--)
			{
				if (MyValue.at(i) > InCS.MyValue.at(i))
					return false;

				if (MyValue.at(i) < InCS.MyValue.at(i))
					return true;
			}

		return true;
	}

	bool operator >= (const CountSystem<IntType>& InCS) {
		if (MyValue.size() > InCS.MyValue.size())
			return true;

		if (MyValue.size() < InCS.MyValue.size())
			return false;

		if (MyValue.size() == InCS.MyValue.size())
			for (int i = MyValue.size() - 1; i >= 0; i--)
			{
				if (MyValue.at(i) > InCS.MyValue.at(i))
					return true;

				if (MyValue.at(i) < InCS.MyValue.at(i))
					return false;
			}

		return true;
	}

	bool operator == (const CountSystem<IntType>& InCS) {

		if (MyValue.size() != InCS.MyValue.size())
			return false;

		if (MyValue.size() == InCS.MyValue.size())
			for (int i = MyValue.size() - 1; i >= 0; i--)
			{
				if (MyValue.at(i) != InCS.MyValue.at(i))
					return false;
			}

		return true;
	}

	bool operator != (const CountSystem<IntType>& InCS) {

		if (MyValue.size() != InCS.MyValue.size())
			return true;

		if (MyValue.size() == InCS.MyValue.size())
			for (int i = MyValue.size() - 1; i >= 0; i--)
			{
				if (MyValue.at(i) != InCS.MyValue.at(i))
					return true;
			}

		return false;
	}


	int GetOrder() { return MyOrder; }

	vector<int> MyValue = { 0 };

private:
	int MyOrder = IntType;

	void VectorTenPow(vector<int>* InVector, unsigned int TenthOrder) {
		vector<int> NewVector = vector<int>(InVector->size() + TenthOrder);

		for (int i = 0; i < InVector->size(); i++)
			NewVector.at(i + TenthOrder) = InVector->at(i);

		InVector->swap(NewVector);

	}

};
