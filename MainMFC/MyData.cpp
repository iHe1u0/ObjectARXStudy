#include "pch.h"
#include "MyData.h"

IMPLEMENT_SERIAL(MyData, CObject, 1)

void MyData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//序列化
		ar << r1 << r2 << r3 << r4;

	}
	else {
		//反序列化
		ar >> r1 >> r2 >> r3 >> r4;
	}
}
