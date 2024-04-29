#include "pch.h"
#include "staticlib_func.h"

int Pow(int a, int b)
{
	int value = 1;

	for (int i = 0; i < b; ++i)
	{
		value *= a;
	}

	return value;
}