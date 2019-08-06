#include <windows.h>
#include <ntsecapi.h>

#include "Dispatch_USER32_UnhookWindowsHookEx.h"

//
//Global
//
__pfnUnhookWindowsHookEx pfnUnhookWindowsHookEx = NULL;



//
//Dispatch_USER32_UnhookWindowsHookEx Functions
//
BOOL
WINAPI
OnUnhookWindowsHookEx(
	IN HHOOK hhk)
{
	BOOL bRet;



	bRet = pfnUnhookWindowsHookEx(
		hhk
		);

	return bRet;
}