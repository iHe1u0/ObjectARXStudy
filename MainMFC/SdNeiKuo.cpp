#include "pch.h"
#include "SdNeiKuo.h"
#include "MainMFCDlg.h"
#include <iostream>

Tunnel  Tunnel::m_Sd;

Tunnel::Tunnel()
{

}

Tunnel::~Tunnel()
{

}

BOOL Tunnel::Read(CStdioFile* pFile)
{
	return 0;
}

BOOL Tunnel::Write(CStdioFile* pFile)
{
	return TRUE;
}


SdNeiKuo::SdNeiKuo()
{
}

SdNeiKuo::~SdNeiKuo()
{
}

SdNeiKuo& SdNeiKuo::operator=(const SdNeiKuo& data)
{
	R1 = data.R1;

	return *this;
}

BOOL SdNeiKuo::Read(FILE* pFile)
{
	///////////////////

	CMainMFCDlg  readDlg;
	readDlg.m_Data = *this;
	if (readDlg.DoModal() == IDOK)
	{
		*this = readDlg.m_Data;
		CFileDialog dlg(FALSE, L".txt", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"配置文件|*.txt");
		if (dlg.DoModal() == IDOK)
		{
			CString fileName = dlg.GetPathName();
			CStdioFile file;
			file.Open(fileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
			if (Write(&file))
			{
				file.Close();
				AfxMessageBox(L"保存成功", MB_OK);
				return TRUE;
			}
			else {
				AfxMessageBox(L"保存失败", MB_OK);
			}
		}
	}
	return FALSE;



	/////////////////
	FILE* file;
	CFileDialog fileDlg(TRUE, L".txt", nullptr,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT| OFN_FILEMUSTEXIST,
		L"文本文件(*.txt)|*.txt");
	if (fileDlg.DoModal() == IDOK)
	{
		CString fileName = fileDlg.GetFileName();
		CStringA stra(fileName.GetBuffer(0));
		std::string path = stra.GetBuffer(0);
		stra.ReleaseBuffer();
		if (fopen_s(&file, path.c_str(), "r") == 0)
		{
			Tunnel::m_Sd.m_nk.Read(file);
			//this->SetWindowTextW(fileName);
			//UpdateData(FALSE);
		}
	}
	double* data = new double[20];
	for (int index = 0; index <= 14; index++) {
		fscanf_s(pFile, "%lf", &data[index]);
	}
	fclose(pFile);
	double version = *data;
	R1 = *(data + 1);
	R2 = *(data + 2);
	R3 = *(data + 3);
	R4 = *(data + 4);
	R5 = *(data + 5);
	H1 = *(data + 6);
	H2 = *(data + 7);
	H_2 = *(data + 8);
	RADIUS1 = *(data + 9);
	RADIUS_1 = *(data + 10);
	RADIUS2 = *(data + 11);
	RADIUS3 = *(data + 12);
	RADIUS4 = *(data + 13);
	RADIUS5 = *(data + 14);
	return 0;
}

BOOL SdNeiKuo::Write(CStdioFile* pFile)
{
	//写入文件
	CString str;
	str.Format(L"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
		VERSION,
		R1, R2, R3, R4, R5,
		H1, H2, H_2,
		RADIUS1, RADIUS_1, RADIUS2, RADIUS3, RADIUS4, RADIUS5);
	pFile->Seek(0, CStdioFile::end);
	pFile->WriteString(str);
	return TRUE;
}


BOOL SdNeiKuo::Modify()
{
	CMainMFCDlg  modifyDlg;
	modifyDlg.m_Data = *this;
	if (modifyDlg.DoModal() == IDOK)
	{
		*this = modifyDlg.m_Data;
		CFileDialog dlg(FALSE, L".txt", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"配置文件|*.txt");
		if (dlg.DoModal() == IDOK)
		{
			CString fileName = dlg.GetPathName();
			CStdioFile file;
			file.Open(fileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
			if (Write(&file))
			{
				file.Close();
				AfxMessageBox(L"保存成功", MB_OK);
				return TRUE;
			}
			else {
				AfxMessageBox(L"保存失败", MB_OK);
			}
		}
	}
	return FALSE;
}



BOOL  Draw_Tunnel::Draw()
{
	Draw_SdNeiKuo  TmpDraw;
	TmpDraw.m_data = m_data.m_nk;
	TmpDraw.Draw();

	return FALSE;
}



BOOL Draw_SdNeiKuo::Draw()
{
	return 0;
}

SdProp::SdProp()
{
}

SdProp::~SdProp()
{
}

BOOL SdProp::Read(CStdioFile* pFile)
{
	return 0;
}

BOOL SdProp::Write(CStdioFile* pFile)
{
	return FALSE;
}

BOOL SdProp::Modify()
{
	return FALSE;
}
