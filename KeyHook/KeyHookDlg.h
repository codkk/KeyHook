
// KeyHookDlg.h : ͷ�ļ�
//

#pragma once


// CKeyHookDlg �Ի���
class CKeyHookDlg : public CDialogEx
{
// ����
public:
	CKeyHookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEYHOOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnKeyData(WPARAM wParam, LPARAM lParam);
public:
	CString m_strRev;
	afx_msg void OnBnClickedButton1();
};
