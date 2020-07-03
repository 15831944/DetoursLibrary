#include "example.h"

Detour test;
typedef int (*fun)(int arg);

int originalFun(int arg)
{
	printf("Original: %d\n", arg);
	return arg + 1;
}

int hookedFun(int arg)
{
	test.UnInstall();
	printf("From hooked: %d\n", arg);
	int rsl = originalFun(arg);
	test.ReInstall();
	return rsl;
}

int main(int argc, char* argv[])
{
	printf("Hello, this is testing application.\n");

	test.Install(reinterpret_cast<long*>((fun)originalFun), reinterpret_cast<long*>((fun)hookedFun));
	printf("Hooked result: %d", originalFun(5));
	test.UnInstall();

	MessageBox(0, L"Debug pause.", L"", MB_OK);
	return 0;
}