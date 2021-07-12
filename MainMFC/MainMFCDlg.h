
// MainMFCDlg.h: 头文件
//

#pragma once


// CMainMFCDlg 对话框
class CMainMFCDlg : public CDialogEx
{
// 构造
public:
	CMainMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void InitData();
	afx_msg void OnSave();
	CBrush m_brush;
	CFont m_font;

	CEdit R1;
	CEdit R2;
	CEdit R3;
	CEdit R4;
	CEdit R5;
	CEdit H1;
	CEdit H2;
	CEdit H_2;
	CEdit RADIUS1;
	CEdit RADIUS_1;
	CEdit RADIUS2;
	CEdit RADIUS3;
	CEdit RADIUS4;
	CEdit RADIUS5;
	CStatic INFO_TEXT;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
