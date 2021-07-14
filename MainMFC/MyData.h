#pragma once

#define VERSION 20210714
class DataStruct
{

public:
	DataStruct(CString configFilePath);
	//保存
	CString Save(DataStruct data);
	//读取
	void Read(DataStruct data, double result[14]);
	//版本信息
	int version;
	//数据
	double r1, r2, r3, r4, r5;
	double h1, h2, h_2;
	double radius1, radius_1, radius2, radius3, radius4, radius5;
private:
	CString filePath;
};

