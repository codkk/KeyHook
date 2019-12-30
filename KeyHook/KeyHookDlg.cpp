
// KeyHookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KeyHook.h"
#include "KeyHookDlg.h"
#include "afxdialogex.h"
#include "LaunchDll.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyHookDlg 对话框



CKeyHookDlg::CKeyHookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KEYHOOK_DIALOG, pParent)
	, m_strRev(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CKeyHookDlg::~CKeyHookDlg()
{
	UninstallLaunch();
}

void CKeyHookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_REV, m_strRev);
}

BEGIN_MESSAGE_MAP(CKeyHookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_KEYDATA, OnKeyData)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyHookDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeyHookDlg 消息处理程序

BOOL CKeyHookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	RegistMsg(this->m_hWnd, WM_KEYDATA);
	InstallLaunchEv();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyHookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKeyHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CKeyHookDlg::OnKeyData(WPARAM wParam, LPARAM lParam)
{
	char c[2];
	memset(c, 0, 2);
	c[0] = wParam;
	CString str;
	str.Format("%s", c);
	m_strRev += str;
	UpdateData(FALSE);
	return 0;
}



void CKeyHookDlg::OnBnClickedButton1()
{
	m_strRev.Empty();
	UpdateData(FALSE);
}
