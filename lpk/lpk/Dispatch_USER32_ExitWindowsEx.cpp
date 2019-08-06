#include <windows.h>
#include <ntsecapi.h>

#include "Dispatch_USER32_ExitWindowsEx.h"



//
//Global
//
__pfnExitWindowsEx pfnExitWindowsEx = NULL;



//
//Dispatch_USER32_ExitWindowsEx Functions
//
BOOL
WINAPI
OnExitWindowsEx(
    IN UINT uFlags,
    IN DWORD dwReserved)
{


	//
	//Refuse directly
	//
	return FALSE;
}