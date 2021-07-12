#pragma once

#define VERSION 1
class MyData :public CObject
{
	DECLARE_SERIAL(MyData)
public:
	virtual void Serialize(CArchive& ar);
	CString r1, r2, r3, r4, r5;
	CString h1, h2, h_2;
	CString radius1, radius_1, radius2, radius3, radius4, radius5;
};

