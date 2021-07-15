// MainMFCDlg.h: 头文件
//

#pragma once

// CMainMFCDlg 对话框
class CMainMFCDlg : public CDialogEx
{
	// 构造
public:
	CMainMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMainMFCDlg();
	// 对话框数据
	enum { IDD = IDD_MAINMFC_DIALOG };

	SdNeiKuo  m_Data;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
