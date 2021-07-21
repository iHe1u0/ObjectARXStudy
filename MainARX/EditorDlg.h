#pragma once

// CEditorDlg 对话框
class CEditorDlg : public CDialogEx
{
	// 构造
public:
	CEditorDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CEditorDlg();
	// 对话框数据
	enum { IDD = IDD_MAINMFC_DIALOG };
	SdNeiKuo  m_Data;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
