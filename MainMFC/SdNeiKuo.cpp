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

BOOL Tunnel::Read(CFile* pFile)
{
	return 0;
}

void Tunnel::Write(CFile* pFile)
{
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

BOOL SdNeiKuo::Read(CFile* pFile)
{
	return 0;
}

void SdNeiKuo::Write(CFile* pFile)
{
}


BOOL  SdNeiKuo::Modify()
{
	CMainMFCDlg  TDlg;
	TDlg.m_Data = *this;
	if (TDlg.DoModal() == IDOK)
	{
		*this = TDlg.m_Data;
		return TRUE;
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



//加载指定文件
void ReadData(CString fileName)
{
	//FILE* file;
	//CStringA stra(fileName.GetBuffer(0));
	//std::string path = stra.GetBuffer(0);
	//stra.ReleaseBuffer();
	//int errCode = fopen_s(&file, path.c_str(), "r");
	//double* data = new double[20];
	//if (errCode != 0)
	//{
	//	AfxMessageBox(L"打开文件失败！");
	//	return;
	//}
	//for (int index = 0; index <= 14; index++) {
	//	fscanf_s(file, "%lf", &data[index]);
	//}
	//fclose(file);
	//double version = *data;
	//R1 = *(data + 1);
	//R2 = *(data + 2);
	//R3 = *(data + 3);
	//R4 = *(data + 4);
	//R5 = *(data + 5);
	//H1 = *(data + 6);
	//H2 = *(data + 7);
	//H_2 = *(data + 8);
	//RADIUS1 = *(data + 9);
	//RADIUS_1 = *(data + 10);
	//RADIUS2 = *(data + 11);
	//RADIUS3 = *(data + 12);
	//RADIUS4 = *(data + 13);
	//RADIUS5 = *(data + 14);
	//this->SetWindowTextW(fileName);
	//UpdateData(FALSE);
}

//保存各项数据到文件
void  OnSave()
{
	//如果输入的数据不符合要求
	//if (!UpdateData(TRUE))
	//{
	//	return;
	//}
	//CString fileName;
	//CFileDialog dlg(FALSE, L".txt", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"配置文件|*.txt");
	//if (dlg.DoModal() == IDOK)
	//{
	//	CString ext = dlg.GetFileExt();
	//	fileName = dlg.GetPathName();
	//}
	//else
	//{
	//	return;
	//}
	//CStdioFile file;
	//file.Open(fileName, CFile::modeCreate | CFile::modeWrite);
	////写入文件
	//CString str;
	//str.Format(L"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
	//	VERSION,
	//	R1, R2, R3, R4, R5,
	//	H1, H2, H_2,
	//	RADIUS1, RADIUS_1, RADIUS2, RADIUS3, RADIUS4, RADIUS5);
	//file.Seek(0, CFile::end);
	//file.WriteString(str);
	//file.Close();
	//MessageBox(L"保存成功", L"提示", MB_OK);
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

BOOL SdProp::Read(CFile* pFile)
{
	return 0;
}

BOOL SdProp::Write(CFile* pFile)
{
	return FALSE;
}

BOOL SdProp::Modify()
{
	return FALSE;
}
