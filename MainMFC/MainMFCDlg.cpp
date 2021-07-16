#include "pch.h"
#include "MainMFCDlg.h"


// CMainMFCDlg 对话框
CMainMFCDlg::CMainMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINMFC_DIALOG, pParent)
{

}

CMainMFCDlg::~CMainMFCDlg()
{

}

void DDX_TextRAD(CDataExchange* pDX, int nIDC, double& value)
{
	if (pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX, nIDC, value);
		value = value / 180.0 * PI;
	}
	else
	{
		value = value * 180.0 / PI;
		DDX_Text(pDX, nIDC, value);
	}
}



void CMainMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Data.R1);
	DDX_Text(pDX, IDC_EDIT2, m_Data.R2);
	DDX_Text(pDX, IDC_EDIT3, m_Data.R3);
	DDX_Text(pDX, IDC_EDIT4, m_Data.R4);
	DDX_Text(pDX, IDC_EDIT5, m_Data.R5);
	DDX_Text(pDX, IDC_EDIT6, m_Data.H1);
	DDX_Text(pDX, IDC_EDIT7, m_Data.H2);
	DDX_Text(pDX, IDC_EDIT8, m_Data.H_2);
	DDX_Text(pDX, IDC_EDIT11, m_Data.RADIUS1);
	DDX_Text(pDX, IDC_EDIT12, m_Data.RADIUS_1);
	DDX_Text(pDX, IDC_EDIT13, m_Data.RADIUS2);
	DDX_Text(pDX, IDC_EDIT14, m_Data.RADIUS3);
	DDX_Text(pDX, IDC_EDIT15, m_Data.RADIUS4);
	DDX_Text(pDX, IDC_EDIT16, m_Data.RADIUS5);
}

BOOL CMainMFCDlg::OnInitDialog()
{
	CString tips;
	[[maybe_unused]] BOOL tmp = tips.LoadStringW(IDS_STRING_INFO);
	GetDlgItem(IDC_STATIC_INFO)->SetWindowTextW(tips);

	//if (m_Data.Modify() != NULL)
	//{
	//	AfxMessageBox(L"read or modify");
	//}
	return CDialog::OnInitDialog();
}

BEGIN_MESSAGE_MAP(CMainMFCDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainMFCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()



//摁下保存按钮
void CMainMFCDlg::OnBnClickedButton1()
{
	//如果输入的数据不符合要求
	if (UpdateData(TRUE))
		CDialog::OnOK();
}
