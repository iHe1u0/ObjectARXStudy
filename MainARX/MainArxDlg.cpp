// (C) Copyright 2002-2007 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- MainArxDlg.cpp : Implementation of MainArxDlg
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "MainArxDlg.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(MainArxDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(MainArxDlg, CAcUiDialog)
ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
ON_BN_CLICKED(ID_WRITE, &MainArxDlg::OnBnClickedWrite)
ON_BN_CLICKED(IDC_READ, &MainArxDlg::OnBnClickedRead)
ON_BN_CLICKED(ID_MODIFY, &MainArxDlg::OnBnClickedModify)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
MainArxDlg::MainArxDlg(CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/)
	: CAcUiDialog(MainArxDlg::IDD, pParent, hInstance)
{
}

//-----------------------------------------------------------------------------
void MainArxDlg::DoDataExchange(CDataExchange *pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT MainArxDlg::OnAcadKeepFocus(WPARAM, LPARAM)
{
	return (TRUE);
}

void MainArxDlg::OnBnClickedWrite()
{
	CFileDialog fileDlg(FALSE, FILE_EXT, L"default.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT,
			    FILE_EXT_DESCRIPTION);
	if (fileDlg.DoModal() == IDOK) {
		CStdioFile writeFile;
		writeFile.Open(fileDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		Tunnel::m_Sd.m_nk.Write(&writeFile);
	}
}

void MainArxDlg::OnBnClickedRead()
{
	CFileDialog fileDlg(TRUE, FILE_EXT, L"default.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST,
			    FILE_EXT_DESCRIPTION);
	if (fileDlg.DoModal() == IDOK) {
		Draw_SdNeiKuo *m_SdNeiKuo = new Draw_SdNeiKuo;
		Tunnel::m_Sd.m_nk.Read(fileDlg.GetPathName(), &m_SdNeiKuo->m_data);
		//print the version of file.
		acutPrintf(L"Version:%lf \n", m_SdNeiKuo->m_data.Version);
		//draw to cad with data.
		m_SdNeiKuo->Draw();
	}
}

void MainArxDlg::OnBnClickedModify()
{
	CFileDialog fileDlg(TRUE, FILE_EXT, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST,
			    FILE_EXT_DESCRIPTION);
	if (fileDlg.DoModal() == IDOK) {
		Tunnel::m_Sd.m_nk.Modify(fileDlg.GetPathName());
	}
}
