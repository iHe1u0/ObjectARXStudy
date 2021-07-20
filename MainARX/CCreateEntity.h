#pragma once
class CCreateEntity {
    public:
	static void CreateArc(AcGePoint2d ptStart, AcGePoint2d ptCenter, AcGePoint2d ptCenterPoint);
	static void CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd);
};
