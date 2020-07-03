#pragma once
#include <Windows.h>
#include "memory.h"
#include <malloc.h>

class Detour
{
private:
	bool	iFLAG;
	bool	hFLAG;
	BYTE*	original;
	BYTE*	hooked;
	DWORD*	address;
public:
	Detour();
	~Detour();
	bool	Install(LPVOID source, LPVOID destination);
	bool	ReInstall();
	bool	UnInstall();
	long*	FindFunction(LPCWSTR szLibName, LPCSTR szFunctionName);
	bool	IsInstalled();
};