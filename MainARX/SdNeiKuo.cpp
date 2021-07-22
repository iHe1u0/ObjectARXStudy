#include "StdAfx.h"
#include "SdNeiKuo.h"
#include "CCreateEntity.h"
#include "EditorDlg.h"
#include <iostream>
#include <CArcUtil.h>
#include <CLineUtil.h>

Tunnel Tunnel::m_Sd;

Tunnel::Tunnel()
{
}

Tunnel::~Tunnel()
{
}

BOOL Tunnel::Read(CStdioFile *pFile)
{
	return 0;
}

BOOL Tunnel::Write(CStdioFile *pFile)
{
	return TRUE;
}

SdNeiKuo::SdNeiKuo()
{
}

SdNeiKuo::~SdNeiKuo()
{
}

SdNeiKuo &SdNeiKuo::operator=(const SdNeiKuo &data)
{
	Version = data.Version;
	R1 = data.R1;
	R2 = data.R2;
	R3 = data.R3;
	R4 = data.R4;
	R5 = data.R5;
	H1 = data.H1;
	H2 = data.H2;
	H_2 = data.H_2;
	RADIUS1 = data.RADIUS1;
	RADIUS_1 = data.RADIUS_1;
	RADIUS2 = data.RADIUS2;
	RADIUS3 = data.RADIUS3;
	RADIUS4 = data.RADIUS4;
	RADIUS5 = data.RADIUS5;
	return *this;
}

BOOL SdNeiKuo::Read(CString filePath, SdNeiKuo *pData)
{
	FILE *file;
	CStringA stra(filePath.GetBuffer(0));
	std::string path = stra.GetBuffer(0);
	stra.ReleaseBuffer();
	int errorCode = fopen_s(&file, path.c_str(), "r");
	if (!errorCode) {
		double *resultData = new double[20];
		for (int index = 0; index <= 14; index++) {
			fscanf_s(file, "%lf", &resultData[index]);
		}
		fclose(file);
		Version = *resultData;
		R1 = *(resultData + 1);
		R2 = *(resultData + 2);
		R3 = *(resultData + 3);
		R4 = *(resultData + 4);
		R5 = *(resultData + 5);
		H1 = *(resultData + 6);
		H2 = *(resultData + 7);
		H_2 = *(resultData + 8);
		RADIUS1 = *(resultData + 9);
		RADIUS_1 = *(resultData + 10);
		RADIUS2 = *(resultData + 11);
		RADIUS3 = *(resultData + 12);
		RADIUS4 = *(resultData + 13);
		RADIUS5 = *(resultData + 14);
		if (pData == NULL) {
			CEditorDlg readDlg;
			readDlg.m_Data = *this;
			readDlg.DoModal();
		} else {
			*pData = *this;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL SdNeiKuo::Modify(CString filePath)
{
	CEditorDlg modifyDlg;
	Read(filePath, this);
	modifyDlg.m_Data = *this;
	if (modifyDlg.DoModal() == IDOK) {
		CStdioFile pFile;
		pFile.Open(filePath, CFile::modeWrite);
		*this = modifyDlg.m_Data;
		CString str;
		str.Format(L"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", VERSION, R1, R2, R3, R4, R5,
			   H1, H2, H_2, RADIUS1, RADIUS_1, RADIUS2, RADIUS3, RADIUS4, RADIUS5);
		pFile.Seek(0, CStdioFile::begin);
		pFile.WriteString(str);
		pFile.Close();
		AfxMessageBox(L"保存成功", MB_OK);
		return TRUE;
	}
	return FALSE;
}

BOOL SdNeiKuo::Write(CStdioFile *pFile)
{
	CEditorDlg writeDlg;
	if (writeDlg.DoModal() == IDOK) {
		*this = writeDlg.m_Data;
		//写入文件
		CString str;
		str.Format(L"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", VERSION, R1, R2, R3, R4, R5,
			   H1, H2, H_2, RADIUS1, RADIUS_1, RADIUS2, RADIUS3, RADIUS4, RADIUS5);
		pFile->Seek(0, CStdioFile::end);
		pFile->WriteString(str);
		pFile->Close();
		AfxMessageBox(L"保存成功", MB_OK);
		return TRUE;
	}
	return false;
}

BOOL Draw_Tunnel::Draw()
{
	Draw_SdNeiKuo TmpDraw;
	TmpDraw.m_data = m_data.m_nk;
	TmpDraw.Draw();

	return FALSE;
}

BOOL Draw_SdNeiKuo::Draw()
{
	AcGePoint3d ptStart(-m_data.R1, m_data.H1, 0);
	AcGePoint3d ptEnd(m_data.R1, m_data.H1, 0);

	// 起拱线
	ptStart.set(-m_data.R1, 0, 0);
	ptEnd.set(m_data.R1, 0, 0);
	CLineUtil::add(ptStart, ptEnd);

	// 拱部
	AcGePoint3d ptCenter(0, m_data.H1, 0);
	CArcUtil::add(ptCenter, m_data.R1, 0, 180);

	//添加仰拱
	//ptStart.set()
	CArcUtil::add(ptStart, ptCenter, ptEnd);

	return 0;
}

BOOL SdProp::Read(CStdioFile *pFile)
{
	return 0;
}

BOOL SdProp::Write(CStdioFile *pFile)
{
	return FALSE;
}

BOOL SdProp::Modify()
{
	return FALSE;
}
