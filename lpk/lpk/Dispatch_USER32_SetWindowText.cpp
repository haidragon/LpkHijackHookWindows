#include <windows.h>
#include <ntsecapi.h>

#include "./Dispatch_USER32_SetWindowText.h"



//
//Global
//
__pfnSetWindowTextA pfnSetWindowTextA = NULL;
__pfnSetWindowTextW pfnSetWindowTextW = NULL;



//
//Dispatch_USER32_SetWindowText Functions
//
BOOL
WINAPI
OnSetWindowTextA(
    IN HWND hWnd,
    IN LPCSTR lpString)
{
	BOOL bRet;



	//
	//Check if includes [WS_CAPTION] Window Styles
	//
	LONG lStylesValue = GetWindowLong(hWnd,GWL_STYLE);
	if( lStylesValue == 0 )
	{
		bRet = pfnSetWindowTextA(
			hWnd,
			lpString
			);

		return bRet;
	}
	if( (lStylesValue & WS_CAPTION) == 0 )
	{
		bRet = pfnSetWindowTextA(
			hWnd,
			lpString
			);

		return bRet;
	}

	//
	//Set new window title
	//
	char szNewlpString[1024] = {0};
	wsprintfA(szNewlpString,"[#] [%s] %s [#]","wdad",lpString);

	bRet = pfnSetWindowTextA(
		hWnd,
		szNewlpString
		);

#ifdef Dbg
	OutputDebugStringA("SetWindowTextA szNewlpString=");
	OutputDebugStringA(szNewlpString);
#endif

	return bRet;
}

BOOL
WINAPI
OnSetWindowTextW(
    IN HWND hWnd,
    IN LPCWSTR lpString)
{
	BOOL bRet;


	//
	//Check if includes [WS_CAPTION] Window Styles
	//
	LONG lStylesValue = GetWindowLong(hWnd,GWL_STYLE);
	if( lStylesValue == 0 )
	{
		bRet = pfnSetWindowTextW(
			hWnd,
			lpString
			);

		return bRet;
	}
	if( (lStylesValue & WS_CAPTION) == 0 )
	{
		bRet = pfnSetWindowTextW(
			hWnd,
			lpString
			);

		return bRet;
	}

	//
	//Set new window title
	//
	WCHAR szNewlpString[1024] = {0};
	wsprintfW(szNewlpString,L"[#] [%s] %s [#]",TEXT("dasda"),lpString);

	bRet = pfnSetWindowTextW(
		hWnd,
		szNewlpString
		);

#ifdef Dbg
	OutputDebugStringW(L"SetWindowTextW szNewlpString=");
	OutputDebugStringW(szNewlpString);
#endif

	return bRet;
}