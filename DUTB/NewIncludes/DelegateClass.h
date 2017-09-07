#pragma once
#include <iostream>
#include <vector>

using namespace std;


struct NIL{};
class IArguments { public: virtual ~IArguments() {} };
template<class A = NIL>
class Arguments : public IArguments
{
public: 
	Arguments(A Arg) : MyArg(Arg) {}
public:
	A MyArg;
};

class IContainer
{
public:
	virtual void Call(IArguments*) = 0;

};

template<class T, class M>
class Container : public IContainer
{};


template<class T, class A1>
class Container<T, void(T::*)(A1)> : public IContainer
{
	template<class t1, class a1>
	friend	class Container;

	typedef void (T::*M)(A1);
	typedef Arguments<A1> A;


public:

	Container(T* c, M m) : MyClass(c), MyMethod(m) {}

	void Call(IArguments* NewArgs)
	{
		A* a = dynamic_cast<A*>(NewArgs);
		//assert(a);
		if (a)
			(MyClass->*MyMethod)(a->MyArg);
	}

	bool IsEqualTo(IContainer* NewContainer)
	{
		Container* testContainer = dynamic_cast<Container*>(NewContainer);

		if (testContainer)
			return testContainer->MyClass == MyClass && testContainer->MyMethod == MyMethod;

		return false;
	}

private:
	T* MyClass;
	M MyMethod;

};

class Delegate
{
public:

	template<class T, class U>
	void ConnectNew(T* NewClass, U NewMethod)
	{
		MyContainer.push_back(new Container<T, U>(NewClass, NewMethod));
	}

	void DeleteEverything()
	{
		MyContainer.clear();
		MyContainer.shrink_to_fit();
	}

	template<class A1>
	void operator ()(A1 NewArg)
	{
		for (int i = 0; i < MyContainer.size(); i++)
			MyContainer.at(i)->Call(&Arguments<A1>(NewArg));
	}

	template<class T, class M>
	void DeleteSpecific(T* SpecificClass, M SpecificMethod)
	{
		Container<T,M> TestOne = Container<T, M>(SpecificClass, SpecificMethod);



		for(int i = 0; i < MyContainer.size(); i++)
			if (TestOne.IsEqualTo(MyContainer.at(i)))
			{
//				delete MyContainer.at(i);
				MyContainer.erase(MyContainer.begin()+i);
				MyContainer.shrink_to_fit();
			}
//		delete &TestOne;
		
	}

	void DeleteSpecific(int Index)
	{
		if (MyContainer.at(Index))
		{
			MyContainer.erase(MyContainer.begin() + Index);
			MyContainer.shrink_to_fit();
		}
	}



private:

	vector<IContainer*> MyContainer;

};