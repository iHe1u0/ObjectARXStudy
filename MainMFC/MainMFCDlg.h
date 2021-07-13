// MainMFCDlg.h: 头文件
//

#pragma once

#include "CA2RMFCDlg.h";


// CMainMFCDlg 对话框
class CMainMFCDlg : public CDialogEx
{
	// 构造
public:
	CMainMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMainMFCDlg();
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
	CA2RMFCDlg* angelToRadianDlg;
	afx_msg void InitData(CString fileName);
	afx_msg void OnSave();
	CBrush m_brush;
	CFont m_font;
	CMenu menu;
	//提示信息文本框
	CStatic INFO_TEXT;
	//更改提示文本框颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	double R1 = 0.0;
	double R2 = 0.0;
	double R3 = 0.0;
	double R4 = 0.0;
	double R5 = 0.0;
	double H1 = 0.0;
	double H2 = 0.0;
	double H_2 = 0.0;
	double RADIUS1 = 0.0;
	double RADIUS_1 = 0.0;
	double RADIUS2 = 0.0;
	double RADIUS3 = 0.0;
	double RADIUS4 = 0.0;
	double RADIUS5 = 0.0;
	//有关菜单栏的一些操作
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuToolsA2r();
	afx_msg void OnMenuShowAbout();
};
