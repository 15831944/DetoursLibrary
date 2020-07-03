#pragma once
#include <Windows.h>
#include "memory.h"
#include <malloc.h>

class Detour
{
private:
	bool	iFLAG;
	BYTE*	original;
	BYTE*	hooked;
	long*	address;
public:
	Detour();
	~Detour();
	bool	Install(long* source, long* destination);
	bool	ReInstall();
	bool	UnInstall();
	long*	FindFunction(LPCWSTR szLibName, LPCSTR szFunctionName);
	bool	IsInstalled();
};