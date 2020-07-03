#include "memory.h"

bool Memory::FastUnprotect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect)
{
	DWORD dwOldProtect;
	bool result;
	result = VirtualProtect(lpAddress, dwSize, flNewProtect, &dwOldProtect);
	return result;
}
