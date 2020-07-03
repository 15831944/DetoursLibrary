#include "example.h"

Detour test;

typedef int (*fun)(int arg);
fun orig;
fun hooked;

int originalFun(int arg)
{
	printf("From original: %d\n", arg);
	return arg + 1;
}

int hookedFun(int arg)
{
	test.UnInstall();
	printf("From hooked: %d\n", arg);
	int rsl = orig(arg);
	test.ReInstall();
	return rsl;
}

int main(int argc, char* argv[])
{
	printf("Hello, this is detours testing application.\n");

	orig = &originalFun;
	hooked = &hookedFun;

	test.Install(orig, hooked);
	printf("Hooked result: %d", originalFun(5));
	test.UnInstall();

	MessageBox(0, L"Debug pause.", L"", MB_OK);
	return 0;
}