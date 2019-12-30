
// KeyHookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KeyHook.h"
#include "KeyHookDlg.h"
#include "afxdialogex.h"
#include "LaunchDll.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyHookDlg �Ի���



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


// CKeyHookDlg ��Ϣ�������

BOOL CKeyHookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	RegistMsg(this->m_hWnd, WM_KEYDATA);
	InstallLaunchEv();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKeyHookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
