#include "pch.h"
#include "MyData.h"

IMPLEMENT_SERIAL(MyData, CObject, VERSION)

void MyData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//序列化
		//CString r1, r2, r3, r4, r5;
		//CString h1, h2, h_2;
		//CString radius1, radius_1, radius2, radius3, radius4, radius5;
		ar << r1 << r2 << r3 << r4 << r5;
		ar << h1 << h2 << h_2;
		ar << radius1 << radius_1 << radius2 << radius3 << radius4 << radius5;

	}
	else {
		//反序列化
		ar >> r1 >> r2 >> r3 >> r4 >> r5;
		ar >> h1 >> h2 >> h_2;
		ar >> radius1 >> radius_1 >> radius2 >> radius3 >> radius4 >> radius5;
	}
}
