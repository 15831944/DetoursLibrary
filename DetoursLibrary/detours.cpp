#include "detours.h"

Detour::Detour()
{
	this->address = 0;
	this->hooked = nullptr;
	this->original = nullptr;
	this->iFLAG = false;
	this->hFLAG = false;
}

Detour::~Detour()
{
	this->UnInstall();

	if (this->iFLAG)
	{
		free(this->original);
		free(this->hooked);
	}
}

bool Detour::Install(LPVOID lpSource, LPVOID lpDestination)
{
	if (this->iFLAG)
		return false;

	if (lpSource == nullptr || lpDestination == nullptr)
		return false;

#define X86OP_JMP 0xE9
#define X86OP_RET 0xC3
	this->original = (BYTE*)malloc(0x06);
	if (this->original == nullptr)
		return false;

	this->hooked = (BYTE*)malloc(0x06);
	if (this->hooked == nullptr)
	{
		free(this->original);
		return false;
	}

	Memory::FastUnprotect(lpSource, 6, PAGE_EXECUTE_READWRITE);
	if (!ReadProcessMemory((HANDLE)-1, lpSource, this->original, 0x06, 0))
	{
		free(this->original);
		free(this->hooked);
		return false;
	}

	DWORD dwCalc = (DWORD)lpDestination - (DWORD)lpSource - 5;
	Memory::Write<BYTE>(this->hooked, X86OP_JMP);
	Memory::Write<DWORD>(this->hooked + 0x01, dwCalc);
	Memory::Write<BYTE>(this->hooked + 5, X86OP_RET);

	if (WriteProcessMemory((HANDLE)-1, lpSource, this->hooked, 0x06, 0))
	{
		this->iFLAG = true;
		this->address = (DWORD*)lpSource;
		this->hFLAG = true;
		return true;
	}
#undef X86OP_JMP
#undef X86OP_RET
	return false;
}

bool Detour::ReInstall()
{
	if (!this->iFLAG)
		return false;

	if (WriteProcessMemory((HANDLE)-1, this->address, this->hooked, 0x06, 0))
		return true;

	this->hFLAG = true;
	return false;
}

bool Detour::UnInstall()
{
	if (!this->iFLAG)
		return false;

	if (!this->hFLAG)
		return false;

	if (WriteProcessMemory((HANDLE)-1, this->address, this->original, 0x06, 0))
	{
		this->hFLAG = false;
		return true;
	}

	return false;
}

long* Detour::FindFunction(LPCWSTR szLibName, LPCSTR szFunctionName)
{
	return reinterpret_cast<long*>(GetProcAddress(GetModuleHandle(szLibName), szFunctionName));
}

bool Detour::IsInstalled()
{
	return hFLAG;
}
