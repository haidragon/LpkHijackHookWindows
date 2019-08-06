#include <windows.h>
#include <ntsecapi.h>

#include "Dispatch_USER32_SetWindowLong.h"




//
//Global
//
__pfnSetWindowLongW pfnSetWindowLongW = NULL;



//
//Dispatch_USER32_SetWindowLong Functions
//
LONG
WINAPI
OnSetWindowLongW(
    IN HWND hWnd,
    IN int nIndex,
    IN LONG dwNewLong)
{
	LONG lRet;


	lRet = pfnSetWindowLongW(
		hWnd,
		nIndex,
		dwNewLong
		);

	return lRet;
}