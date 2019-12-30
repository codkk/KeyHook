
// KeyHookDlg.h : 头文件
//

#pragma once


// CKeyHookDlg 对话框
class CKeyHookDlg : public CDialogEx
{
// 构造
public:
	CKeyHookDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEYHOOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnKeyData(WPARAM wParam, LPARAM lParam);
public:
	CString m_strRev;
	afx_msg void OnBnClickedButton1();
};
