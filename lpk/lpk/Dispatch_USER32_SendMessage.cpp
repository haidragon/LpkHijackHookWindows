#include <windows.h>
#include <ntsecapi.h>

#include "Dispatch_USER32_SendMessage.h"



//
//Global
//
__pfnSendMessageA pfnSendMessageA = NULL;
__pfnSendMessageW pfnSendMessageW = NULL;



//
//Dispatch_USER32_SendMessage Functions
//
LRESULT
WINAPI
OnSendMessageA(
    IN HWND hWnd,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam)
{
	LRESULT lRet;





	//
	//Check if is [WM_SETTEXT] command
	//
	if( Msg != WM_SETTEXT )
	{
		lRet = pfnSendMessageA(
			hWnd,
			Msg,
			wParam,
			lParam
			);

		return lRet;
	}

	//
	//Check if includes [WS_CAPTION]&[WS_VISIBLE]&[WS_SYSMENU]&[WS_CLIPSIBLINGS] Window Styles
	//
	LONG lStylesValue = GetWindowLong(hWnd,GWL_STYLE);
	if( lStylesValue == 0 )
	{
		lRet = pfnSendMessageA(
			hWnd,
			Msg,
			wParam,
			lParam
			);

		return lRet;
	}
	if( (lStylesValue & WS_CAPTION) == 0 ||
		(lStylesValue & WS_VISIBLE) == 0 ||
		(lStylesValue & WS_SYSMENU) == 0
		)
	{
		lRet = pfnSendMessageA(
			hWnd,
			Msg,
			wParam,
			lParam
			);

		return lRet;
	}

	//
	//Set new window title
	//
	char strNewWindowTitle[1024] = {NULL};
	wsprintfA(strNewWindowTitle,"[#] [%s] %s [#]","dasdas",(LPCTSTR)lParam);

//#ifdef Dbg
//	OutputDebugStringA("\r\nSendMessageA strNewWindowTitle=");
//	OutputDebugStringA(strNewWindowTitle);
//#endif

	lRet = pfnSendMessageA(
		hWnd,
		Msg,
		wParam,
		(LPARAM)strNewWindowTitle
		);

	return lRet;
}

LRESULT
WINAPI
OnSendMessageW(
    IN HWND hWnd,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam)
{
	LRESULT lRet;



	//
	//Check if is [WM_SETTEXT] command
	//
	if( Msg != WM_SETTEXT )
	{
		lRet = pfnSendMessageW(
			hWnd,
			Msg,
			wParam,
			lParam
			);

		return lRet;
	}

	//
	//Check if includes [WS_CAPTION]&[WS_VISIBLE]&[WS_SYSMENU]&[WS_CLIPSIBLINGS] Window Styles
	//
	LONG lStylesValue = GetWindowLong(hWnd,GWL_STYLE);
	if( lStylesValue == 0 )
	{
		lRet = pfnSendMessageW(
			hWnd,
			Msg,
			wParam,
			lParam
			);

		return lRet;
	}
	if( (lStylesValue & WS_CAPTION) == 0 ||
		(lStylesValue & WS_VISIBLE) == 0 ||
		(lStylesValue & WS_SYSMENU) == 0
		)
	{
		lRet = pfnSendMessageW(
			hWnd,
			Msg,
			wParam,
			lParam
			);

		return lRet;
	}

	//
	//Set new window title
	//
	WCHAR szNewWindowTitle[1024] = {NULL};
	wsprintfW(szNewWindowTitle,L"[#] [%s] %s [#]",TEXT("sasdasda"),(LPCWSTR)lParam);

//#ifdef Dbg
//	OutputDebugStringW(L"\r\nSendMessageW szNewWindowTitle=");
//	OutputDebugStringW(szNewWindowTitle);
//#endif

	lRet = pfnSendMessageW(
		hWnd,
		Msg,
		wParam,
		(LPARAM)szNewWindowTitle
		);

	return lRet;
}