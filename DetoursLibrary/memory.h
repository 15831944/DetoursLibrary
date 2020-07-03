#pragma once
#include <Windows.h>

namespace Memory
{
	template<typename T>
	bool Write(LPVOID lpAddress, T value)
	{
		if (!lpAddress) return false;
		*((T*)lpAddress) = value;
		return true;
	}

	template<typename T>
	T Read(LPVOID lpAddress)
	{
		return *((T*)lpAddress);
	}

	bool FastUnprotect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect);
}