#pragma once
#include "NumEditText.h"


// CA2RMFCDlg 对话框

class CA2RMFCDlg : public CDialogEx
{
public:
	CA2RMFCDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CA2RMFCDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_A2RTools };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
public:
	// 度数
	NumEditText Deg;
	// 分
	NumEditText Min;
	// 秒
	NumEditText Sec;
	// 显示结果的static text
	double result;
	afx_msg void OnDataChanged();
	//角度转换为弧度
	double angle_to_radian(double degree, double min, double second);
	void calculateResult();
	afx_msg void OnResultClicked();
};
