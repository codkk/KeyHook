// LaunchDll.h : LaunchDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#define DllExport __declspec(dllexport) 
#include "resource.h"		// ������


// CLaunchDllApp
// �йش���ʵ�ֵ���Ϣ������� LaunchDll.cpp
//

class CLaunchDllApp : public CWinApp
{
public:
	CLaunchDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// �������ݶ�
#pragma data_seg("YCIShared")
HWND hWnd = 0;
long Msg = 0;
bool shift = false;
HHOOK Hook;
#pragma data_seg()
#pragma comment(linker, "/SECTION:YCIShared,rws")
DllExport bool WINAPI InstallLaunchEv();        //��װ����
DllExport void RegistMsg(HWND hwnd, long Msg);  //ע��������Ϣ
DllExport void UninstallLaunch();				//ж�ع���
LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam);
void SaveLog(char* c);