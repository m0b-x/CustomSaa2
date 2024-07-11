#include <Windows.h>
#include <iostream>
#include "SAA2.h"

HINSTANCE g_hInst = NULL;
HMODULE g_hModule = NULL;
LPVOID g_pExports[12] = {0};

bool FileExists(const std::string& fileName) {
	DWORD fileAttr = GetFileAttributes(fileName.c_str());
	if (fileAttr == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return true;
}

void WINAPI Load()
{
	if (g_hModule != NULL)
		return;

	char szLibFile[264];
	GetSystemDirectory(szLibFile, sizeof(szLibFile));
	strcat_s(szLibFile, sizeof(szLibFile), "\\DSOUND.dll");
	g_hModule = LoadLibrary(szLibFile);
	if (g_hModule == NULL)
	{
		MessageBox(0, "Fatal error: cannot LoadLibrary", szLibFile, MB_OK | MB_ICONERROR);
		return;
	}

	g_pExports[0] = GetProcAddress(g_hModule, "DirectSoundCreate");
	g_pExports[1] = GetProcAddress(g_hModule, "DirectSoundEnumerateA");
	g_pExports[2] = GetProcAddress(g_hModule, "DirectSoundEnumerateW");
	g_pExports[3] = GetProcAddress(g_hModule, "DllCanUnloadNow");
	g_pExports[4] = GetProcAddress(g_hModule, "DllGetClassObject");
	g_pExports[5] = GetProcAddress(g_hModule, "DirectSoundCaptureCreate");
	g_pExports[6] = GetProcAddress(g_hModule, "DirectSoundCaptureEnumerateA");
	g_pExports[7] = GetProcAddress(g_hModule, "DirectSoundCaptureEnumerateW");
	g_pExports[8] = GetProcAddress(g_hModule, "GetDeviceID");
	g_pExports[9] = GetProcAddress(g_hModule, "DirectSoundFullDuplexCreate");
	g_pExports[10] = GetProcAddress(g_hModule, "DirectSoundCreate8");
	g_pExports[11] = GetProcAddress(g_hModule, "DirectSoundCaptureCreate8");
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

	if (!GetModuleHandleA("SAMP.dll"))
		return TRUE;

	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		g_hInst = hinstDLL;
		SAA2Load();
		break;

	case DLL_PROCESS_DETACH:
		if (g_hModule != NULL)
		{
			FreeLibrary(g_hModule);
			g_hModule = NULL;
		}
		break;
	}

	return TRUE;
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundCreate()
{
	__asm call Load
	__asm jmp g_pExports[0*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundEnumerateA()
{
	__asm call Load
	__asm jmp g_pExports[1*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundEnumerateW()
{
	__asm call Load
	__asm jmp g_pExports[2*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DllCanUnloadNow()
{
	__asm call Load
	__asm jmp g_pExports[3*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DllGetClassObject()
{
	__asm call Load
	__asm jmp g_pExports[4*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundCaptureCreate()
{
	__asm call Load
	__asm jmp g_pExports[5*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundCaptureEnumerateA()
{
	__asm call Load
	__asm jmp g_pExports[6*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundCaptureEnumerateW()
{
	__asm call Load
	__asm jmp g_pExports[7*4]
}

extern "C" __declspec(naked) void _stdcall proxy_GetDeviceID()
{
	__asm call Load
	__asm jmp g_pExports[8*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundFullDuplexCreate()
{
	__asm call Load
	__asm jmp g_pExports[9*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundCreate8()
{
	__asm call Load
	__asm jmp g_pExports[10*4]
}

extern "C" __declspec(naked) void _stdcall proxy_DirectSoundCaptureCreate8()
{
	__asm call Load
	__asm jmp g_pExports[11*4]
}