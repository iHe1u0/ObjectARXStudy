#pragma once


class CCreateEntity {
    public:
	static Acad::ErrorStatus CreateArc(AcGePoint3d ptCenter, double radius, double startRadius, double endRadius);
	static Acad::ErrorStatus CreateLine(AcGePoint2d ptStart, AcGePoint2d ptEnd);
	static Acad::ErrorStatus CreateLayer(const TCHAR *layerName, AcDbObjectId &layerId);
};
