#pragma once
class Dimension
{
	//添加标注样式
	static Acad::ErrorStatus addStyle();
	//绘制半径标注
	static void addAcDbRadialDimension(const AcGePoint3d& center, const AcGePoint3d& chordPoint,
		double leaderLength, const ACHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);


};

