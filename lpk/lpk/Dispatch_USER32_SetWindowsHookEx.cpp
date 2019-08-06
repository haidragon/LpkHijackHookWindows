#include <windows.h>
#include <ntsecapi.h>

#include "Dispatch_USER32_SetWindowsHookEx.h"



//
//Global
//
__pfnSetWindowsHookExW pfnSetWindowsHookExW = NULL;



//
//Dispatch_USER32_SetWindowsHookEx Functions
//
HHOOK
WINAPI
OnSetWindowsHookExW(
	IN int idHook,
	IN HOOKPROC lpfn,
	IN HINSTANCE hmod,
	IN DWORD dwThreadId)
{
	HHOOK hRet;



	//
	//Parameters
	//
	//dwThreadId
	//If this parameter is zero, the hook procedure is associated with all existing threads running in the same desktop as the calling thread.

	//
	//Check if is global hook
	//
	if( dwThreadId == 0 )
	{
		hRet = NULL;
		return hRet;
	}

	hRet = pfnSetWindowsHookExW(
		idHook,
		lpfn,
		hmod,
		dwThreadId
		);

	return hRet;
}