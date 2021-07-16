// SplashDlg.cpp: 实现文件
//

#include "pch.h"
#include "SplashDlg.h"
#include "afxdialogex.h"
#include "SdNeiKuo.h"
#include <string>

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



void SplashDlg::OnBnClickedRead()
{
	CFileDialog fileDlg(TRUE, L".txt", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, L"文本文件(*.txt)|*.txt");
	if (fileDlg.DoModal() == IDOK)
	{
		Tunnel::m_Sd.m_nk.Read(fileDlg.GetPathName(), NULL);
	}
}

void SplashDlg::OnBnClickedWrite()
{
	CFileDialog fileDlg(FALSE, L".txt", L"default.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT, L"文本文件(*.txt)|*.txt");
	if (fileDlg.DoModal() == IDOK)
	{
		CStdioFile writeFile;
		writeFile.Open(fileDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		Tunnel::m_Sd.m_nk.Write(&writeFile);
	}
}


void SplashDlg::OnBnClickedModify()
{

	
	CFileDialog fileDlg(TRUE, L".txt", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, L"文本文件(*.txt)|*.txt");
	if (fileDlg.DoModal() == IDOK)
	{
		Tunnel::m_Sd.m_nk.Modify(fileDlg.GetPathName());
	}
}
