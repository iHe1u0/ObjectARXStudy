#include "pch.h"
#include "MyData.h"
#include "resource.h"


BOOL _Save(CString filePath, CString key, double value) {
	CString str;
	str.Format(_T("%lf"), value);
	return ::WritePrivateProfileString(CONFIG_NAME, key, str, filePath);
}
MyData::MyData(CString filePath) {
	this->filePath = filePath;
}

CString MyData::Save(MyData data)
{
	_Save(filePath, L"R1", data.r1);
	_Save(filePath, L"R2", data.r2);
	_Save(filePath, L"R3", data.r3);
	_Save(filePath, L"R4", data.r4);
	_Save(filePath, L"H1", data.h1);
	_Save(filePath, L"H2", data.h2);
	_Save(filePath, L"H'2", data.h_2);
	_Save(filePath, L"¦È1", data.radius1);
	_Save(filePath, L"¦È'1", data.radius_1);
	_Save(filePath, L"¦È2", data.radius2);
	_Save(filePath, L"¦È3", data.radius3);
	_Save(filePath, L"¦È4", data.radius4);
	_Save(filePath, L"¦È5", data.radius5);
	return filePath;
}



void MyData::Read(MyData data, CString key, double& re)
{
	CString content;
	GetPrivateProfileString(CONFIG_NAME, key, L"0.0000", content.GetBuffer(MAX_PATH), MAX_PATH, filePath);
	re = _tstof(content);
}

