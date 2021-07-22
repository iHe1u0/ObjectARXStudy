#pragma once


class CCreateEntity {
    public:
	static Acad::ErrorStatus CreateLayer(const TCHAR *layerName, AcDbObjectId &layerId);
};
