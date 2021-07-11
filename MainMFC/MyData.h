#pragma once
class MyData :public CObject
{
	DECLARE_SERIAL(MyData)
public:
	virtual void Serialize(CArchive& ar);
	CString r1, r2, r3, r4;
};

