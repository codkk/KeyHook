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

class CLaunchDllApp : public CWinApp
{
public:
	CLaunchDllApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// 共享数据段
#pragma data_seg("YCIShared")
HWND hWnd = 0;
long Msg = 0;
bool shift = false;
HHOOK Hook;
#pragma data_seg()
#pragma comment(linker, "/SECTION:YCIShared,rws")
DllExport bool WINAPI InstallLaunchEv();        //安装钩子
DllExport void RegistMsg(HWND hwnd, long Msg);  //注册句柄和消息
DllExport void UninstallLaunch();				//卸载钩子
LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam);
void SaveLog(char* c);