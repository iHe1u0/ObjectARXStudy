#include "StdAfx.h"
#include "SdNeiKuo.h"
#include "CCreateEntity.h"
#include "EditorDlg.h"
#include <acedCmdNF.h>
#include <iostream>
#include <objectarxutilslib.h>

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
	ANGLE1 = data.ANGLE1;
	ANGLE_1 = data.ANGLE_1;
	ANGLE2 = data.ANGLE2;
	ANGLE3 = data.ANGLE3;
	ANGLE4 = data.ANGLE4;
	ANGLE5 = data.ANGLE5;
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
		ANGLE1 = *(resultData + 9);
		ANGLE_1 = *(resultData + 10);
		ANGLE2 = *(resultData + 11);
		ANGLE3 = *(resultData + 12);
		ANGLE4 = *(resultData + 13);
		ANGLE5 = *(resultData + 14);
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
			   H1, H2, H_2, ANGLE1, ANGLE_1, ANGLE2, ANGLE3, ANGLE4, ANGLE5);
		pFile.Seek(0, CStdioFile::begin);
		pFile.WriteString(str);
		pFile.Close();
		ads_prompt(L"保存成功");
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
			   H1, H2, H_2, ANGLE1, ANGLE_1, ANGLE2, ANGLE3, ANGLE4, ANGLE5);
		pFile->Seek(0, CStdioFile::end);
		pFile->WriteString(str);
		pFile->Close();
		ads_prompt(L"保存成功");
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
	AcGePoint3d ptStart;
	AcGePoint3d ptEnd;
	AcGePoint3d ptCenter;
	double radius;

	// 路基
	ptStart.set(-m_data.R1, 0, 0);
	ptEnd.set(m_data.R1, 0, 0);
	CLineUtil::add(ptStart, ptEnd);

	// 起拱线
	CLayerUtil::add(L"起拱线", CEntityUtil::Color::Green);
	AcDbObjectId layerId = CLayerUtil::GetLayerID(L"起拱线");
	ptStart.set(-m_data.R1, m_data.H1, 0);
	ptEnd.set(m_data.R1, m_data.H1, 0);
	AcDbObjectId objId = CLineUtil::add(ptStart, ptEnd, L"DASHED");
	CEntityUtil::setLayer(objId, L"起拱线");

	// 拱部
	ptCenter.set(0, m_data.H1, 0);
	CArcUtil::add(ptCenter, m_data.R1, 0, 180, FALSE);

	//添加仰拱
	//左侧
	ptStart.set(-m_data.R1, m_data.H1, 0);
	ptCenter.set(m_data.R1, m_data.H1, 0);
	radius = CPointUtil::getDistanceOfTwoPoints(ptStart, ptCenter);
	//acutPrintf(L"半径为：%lf \n", radius);
	CArcUtil::add(ptCenter, radius, 180, 180 + m_data.ANGLE1);
	//右侧
	ptCenter.set(-m_data.R1, m_data.H1, 0);
	//acutPrintf(L"半径为：%lf \n", radius);
	//CArcUtil::add(ptCenter, radius, -m_data.ANGLE1, 0);
	ads_real startAngel = CCalculation::GtoR(-m_data.ANGLE1);
	ads_real endAngel = CCalculation::GtoR(0);
	AcDbArc *pArc = new AcDbArc(ptCenter, radius, startAngel, endAngel);
	CDwgDatebaseUtil::PostToModelSpace(pArc);
	pArc->close();

	//绘制R3
	//获取R3的起点
	AcGePoint3dArray snapPoints;
	AcDbIntArray geomIds;
	pArc->getOsnapPoints(OsnapMode::kOsModeEnd, 0, ptCenter, ptCenter, AcGeMatrix3d::kIdentity, snapPoints,
			     geomIds);
	radius = m_data.R3;
	ptStart.set(snapPoints[0].x, snapPoints[0].y, 0);
	ptCenter.set(snapPoints[0].x - radius, snapPoints[0].y, 0);
	startAngel = CCalculation::GtoR(0 - m_data.ANGLE3);
	endAngel = CCalculation::GtoR(0);
	pArc = new AcDbArc(ptCenter, radius, startAngel, endAngel);
	CDwgDatebaseUtil::PostToModelSpace(pArc);
	pArc->close();

	return true;
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
