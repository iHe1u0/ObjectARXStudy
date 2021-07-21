#pragma once


class CCreateEntity {
    public:
	static Acad::ErrorStatus CreateArc(AcGePoint2d ptStart, AcGePoint2d ptCenter, AcGePoint2d ptCenterPoint);
	static Acad::ErrorStatus CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd);
	static Acad::ErrorStatus CreateLayer(const TCHAR *layerName, AcDbObjectId &layerId);
};
