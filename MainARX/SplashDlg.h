#pragma once

// SplashDlg 对话框

class SplashDlg : public CDialogEx {
	DECLARE_DYNAMIC(SplashDlg)
    public:
	SplashDlg(CWnd *pParent = nullptr); // 标准构造函数
	virtual ~SplashDlg();

	// 对话框数据
	enum { IDD = IDD_DIALOG_SPLASH };

    protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV 支持

    public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	afx_msg void OnBnClickedModify();
};
