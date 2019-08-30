#define DLL_API extern "C" _declspec(dllexport)
#include "Dll2.h"



int Add(int a,int b)
{
	return a+b;
}

int SubTract(int a,int b)
{
	return a-b;
}
