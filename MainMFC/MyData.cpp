
#include "pch.h"
#include "MyData.h"
#include "resource.h"
#include <string>


DataStruct::DataStruct(CString filePath) {
	this->filePath = filePath;
}

CString DataStruct::Save(DataStruct data)
{
	CString formatData;
	formatData.Format(L"%d %f", data.version, data.r1);
	CFile file;
	file.Open(filePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(formatData, formatData.GetLength() * 2 + 1);
	//file.Write(formatData, sizeof(double));
	file.Close();
	return filePath;
}



void DataStruct::Read(DataStruct data, double result[14])
{
	CStringA stra(this->filePath.GetBuffer(0));
	std::string path = stra.GetBuffer(0);
	stra.ReleaseBuffer();
	FILE* f;
	int errCode = fopen_s(&f, path.c_str(), "r");
	if (errCode == 0)
	{
		for (int i = 0; i < 14; i++) {
			fscanf_s(f, "%lf", &result[i]);
		}

	}
}

