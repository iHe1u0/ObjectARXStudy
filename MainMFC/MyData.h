#pragma once

class MyData
{

public:
	MyData(CString configFilePath);
	//保存
	CString Save(MyData data);
	//读取
	void Read(MyData data, CString key, double& re);
	//数据
	double r1, r2, r3, r4, r5;
	double h1, h2, h_2;
	double radius1, radius_1, radius2, radius3, radius4, radius5;
private:
	CString filePath;
};

