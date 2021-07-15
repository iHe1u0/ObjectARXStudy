// SplashDlg.cpp: 实现文件
//

#include "pch.h"
#include "SplashDlg.h"
#include "afxdialogex.h"
#include "SdNeiKuo.h"

// SplashDlg 对话框

IMPLEMENT_DYNAMIC(SplashDlg, CDialogEx)

SplashDlg::SplashDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SplashDlg::~SplashDlg()
{
}

void SplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SplashDlg, CDialogEx)
	ON_BN_CLICKED(ID_WRITE, &SplashDlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_READ, &SplashDlg::OnBnClickedRead)
	ON_BN_CLICKED(ID_MODIFY, &SplashDlg::OnBnClickedModify)
END_MESSAGE_MAP()


// SplashDlg 消息处理程序


void SplashDlg::OnBnClickedWrite()
{
	CFile TFile;

	Tunnel::m_Sd.Write(&TFile);
}


void SplashDlg::OnBnClickedRead()
{
	CFile TFile;

	Tunnel::m_Sd.Read(&TFile);
}


void SplashDlg::OnBnClickedModify()
{
	Tunnel::m_Sd.m_nk.Modify();
}
