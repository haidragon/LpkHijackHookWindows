//Created by AheadLib x86/x64 v1.1


#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>
#include <Shlwapi.h>
#include "Dispatch_USER32.h"
#pragma comment( lib, "Shlwapi.lib")
#define  DebugPrint OutputDebugStringEx


#pragma comment(linker, "/EXPORT:LpkTabbedTextOut=_AheadLib_LpkTabbedTextOut,@1")
#pragma comment(linker, "/EXPORT:LpkDllInitialize=_AheadLib_LpkDllInitialize,@2")
#pragma comment(linker, "/EXPORT:LpkDrawTextEx=_AheadLib_LpkDrawTextEx,@3")
#pragma comment(linker, "/EXPORT:LpkEditControl=_AheadLib_LpkEditControl,@4")
#pragma comment(linker, "/EXPORT:LpkExtTextOut=_AheadLib_LpkExtTextOut,@5")
#pragma comment(linker, "/EXPORT:LpkGetCharacterPlacement=_AheadLib_LpkGetCharacterPlacement,@6")
#pragma comment(linker, "/EXPORT:LpkGetTextExtentExPoint=_AheadLib_LpkGetTextExtentExPoint,@7")
#pragma comment(linker, "/EXPORT:LpkInitialize=_AheadLib_LpkInitialize,@8")
#pragma comment(linker, "/EXPORT:LpkPSMTextOut=_AheadLib_LpkPSMTextOut,@9")
#pragma comment(linker, "/EXPORT:LpkUseGDIWidthCache=_AheadLib_LpkUseGDIWidthCache,@10")
#pragma comment(linker, "/EXPORT:ftsWordBreak=_AheadLib_ftsWordBreak,@11")
PVOID pfnAheadLib_LpkTabbedTextOut;
PVOID pfnAheadLib_LpkDllInitialize;
PVOID pfnAheadLib_LpkDrawTextEx;
PVOID pfnAheadLib_LpkEditControl;
PVOID pfnAheadLib_LpkExtTextOut;
PVOID pfnAheadLib_LpkGetCharacterPlacement;
PVOID pfnAheadLib_LpkGetTextExtentExPoint;
PVOID pfnAheadLib_LpkInitialize;
PVOID pfnAheadLib_LpkPSMTextOut;
PVOID pfnAheadLib_LpkUseGDIWidthCache;
PVOID pfnAheadLib_ftsWordBreak;

void OutputDebugStringEx(const char *strOutputString, ...)  
{  
	va_list vlArgs = NULL;  
	va_start(vlArgs, strOutputString);  
	size_t nLen = _vscprintf(strOutputString, vlArgs) + 1;  
	char *strBuffer = new char[nLen];  
	_vsnprintf_s(strBuffer, nLen, nLen, strOutputString, vlArgs);  
	va_end(vlArgs);  
	OutputDebugStringA(strBuffer);  
	delete [] strBuffer;  
}  


EXTERN_C PVOID AheadLib_LpkEditControl[14] = { 0 };


static HMODULE	g_OldModule = NULL;

// 加载原始模块
__inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];
	GetSystemDirectory(tzPath, MAX_PATH); // 这里是否从系统目录加载或者当前目录，自行修改

	lstrcat(tzPath, TEXT("\\lpk.dll"));
	g_OldModule = LoadLibrary(tzPath);
	if (g_OldModule == NULL)
	{
		wsprintf(tzTemp, TEXT("无法找到模块 %s,程序无法正常运行"), tzPath);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
	}

	return (g_OldModule != NULL);	
}

// 释放原始模块
__inline VOID WINAPI Free()
{
	if (g_OldModule)
	{
		FreeLibrary(g_OldModule);
	}
}
// 获取原始函数地址
FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	FARPROC fpAddress;
	CHAR szProcName[128];
	TCHAR tzTemp[MAX_PATH];

	fpAddress = GetProcAddress(g_OldModule, pszProcName);
	if (fpAddress == NULL)
	{
		if (HIWORD(pszProcName) == 0)
		{
			wsprintfA(szProcName, "%d", pszProcName);
			pszProcName = szProcName;
		}

		wsprintf(tzTemp, TEXT("无法找到函数 %S,程序无法正常运行"), pszProcName);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
		ExitProcess(-2);
	}
	return fpAddress;
}

// 初始化获取原函数地址
BOOL WINAPI Init()
{
	if(NULL == (pfnAheadLib_LpkTabbedTextOut = GetAddress("LpkTabbedTextOut")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkDllInitialize = GetAddress("LpkDllInitialize")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkDrawTextEx = GetAddress("LpkDrawTextEx")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkEditControl = GetAddress("LpkEditControl")))
		return FALSE;
	memcpy(AheadLib_LpkEditControl,pfnAheadLib_LpkEditControl,sizeof(PVOID) * 14);
	if(NULL == (pfnAheadLib_LpkExtTextOut = GetAddress("LpkExtTextOut")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkGetCharacterPlacement = GetAddress("LpkGetCharacterPlacement")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkGetTextExtentExPoint = GetAddress("LpkGetTextExtentExPoint")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkInitialize = GetAddress("LpkInitialize")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkPSMTextOut = GetAddress("LpkPSMTextOut")))
		return FALSE;
	if(NULL == (pfnAheadLib_LpkUseGDIWidthCache = GetAddress("LpkUseGDIWidthCache")))
		return FALSE;
	if(NULL == (pfnAheadLib_ftsWordBreak = GetAddress("ftsWordBreak")))
		return FALSE;
	return TRUE;
}

DWORD WINAPI ThreadProc(LPVOID lpThreadParameter)
{
	PVOID			addr1 = reinterpret_cast<PVOID>(0x00401000);
	unsigned char	data1[] = { 0x90, 0x90, 0x90, 0x90 };

	HANDLE			hProcess;

	HMODULE uresr32handle = LoadLibraryA("User32.dll");

	GetProcAddress(uresr32handle,"RegisterClass");





	//
	//绕过VMP3.x 以上版本的 内存属性保护
	//
	hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if (hProcess != NULL)
	{
		WriteProcessMemory(hProcess, addr1, data1, sizeof(data1), NULL);
		CloseHandle(hProcess);
	}
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		if(Load() && Init())
		{
			TCHAR szAppName[MAX_PATH]  = TEXT("wps.exe");	//请改为相应的Dll宿主文件名
            int status = Dispatch_USER32_Start();
			if(status)
			{
		      DebugPrint("HOOK成功");
			}else{
              DebugPrint("HOOK失败");
			}
	
			TCHAR szFullPath[MAX_PATH] = {0};
			int nLength = 0;
			nLength = GetModuleFileName(NULL, szFullPath, MAX_PATH);
			PathStripPath(szFullPath);
			if (StrCmpI(szAppName, szFullPath) == 0 || TRUE) //这里是否判断宿主进程名?
			{
				::CreateThread(NULL, NULL, ThreadProc, NULL, NULL, NULL); //打补丁线程
			}
		}
		else
		{
			return FALSE;
		}
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		Free();
	}

	return TRUE;
}

 // 导出函数
EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkTabbedTextOut(void)
{
	__asm jmp pfnAheadLib_LpkTabbedTextOut;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkDllInitialize(void)
{
	__asm jmp pfnAheadLib_LpkDllInitialize;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkDrawTextEx(void)
{
	__asm jmp pfnAheadLib_LpkDrawTextEx;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkExtTextOut(void)
{
	__asm jmp pfnAheadLib_LpkExtTextOut;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkGetCharacterPlacement(void)
{
	__asm jmp pfnAheadLib_LpkGetCharacterPlacement;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkGetTextExtentExPoint(void)
{
	__asm jmp pfnAheadLib_LpkGetTextExtentExPoint;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkInitialize(void)
{
	__asm jmp pfnAheadLib_LpkInitialize;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkPSMTextOut(void)
{
	__asm jmp pfnAheadLib_LpkPSMTextOut;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_LpkUseGDIWidthCache(void)
{
	__asm jmp pfnAheadLib_LpkUseGDIWidthCache;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_ftsWordBreak(void)
{
	__asm jmp pfnAheadLib_ftsWordBreak;
}

