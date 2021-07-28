#include "pch.h"
#include "Dimension.h"
#include "CEntityUtil.h"

Acad::ErrorStatus Dimension::addStyle(AcDbObjectId objID, TCHAR* styleName, ads_real scale, int colorIndex = CEntityUtil::Color::Green)
{
	////获得当前图形的标注样式表  
	AcDbDimStyleTable* pDimStyleTable;
	AcDbDimStyleTableRecord* pDimStyleTblRcd;
	acdbHostApplicationServices()->workingDatabase()->getDimStyleTable(pDimStyleTable, AcDb::kForWrite);


	////是否已包含  
	if (pDimStyleTable->has(styleName)) {
		AcDbEntity* pEntity;
		if (acdbOpenAcDbEntity(pEntity, objID, AcDb::kForWrite) == Acad::eOk)
		{

		}
		pEntity->close();
		//TODO: fix function of add dimesion.
		//pDimStyleTblRcd=pDimStyleTable->getAt(styleName,)
	}
	else
	{
		////创建新的标注样式表  
		pDimStyleTblRcd = new AcDbDimStyleTableRecord();
		////设置标注样式的特性  
		pDimStyleTblRcd->setName(styleName);
		pDimStyleTblRcd->setDimasz(50 * scale); // 箭头长度
		pDimStyleTblRcd->setDimblk(L"_ARCHTICK");//设置箭头的形状为建筑标记
		pDimStyleTblRcd->setDimexe(30 * scale); // 指定尺寸界线超出尺寸线的距离
		pDimStyleTblRcd->setDimlfac(1);//比例因子
		AcCmColor dimensionColor;
		dimensionColor.setColorIndex(colorIndex);
		pDimStyleTblRcd->setDimclrd(dimensionColor);//为尺寸线、箭头和标注引线指定颜色，0为随图层
		pDimStyleTblRcd->setDimclre(dimensionColor);//为尺寸界线指定颜色。此颜色可以是任意有效的颜色编号
		pDimStyleTblRcd->setDimclrt(dimensionColor);//为标注文字指定颜色，0为随图层
		pDimStyleTblRcd->setDimdec(0);//设置标注主单位显示的小数位位数，0为随图层

		pDimStyleTblRcd->setDimexo(30 * scale);//指定尺寸界线偏移原点的距离

		pDimStyleTblRcd->setDimgap(10 * scale);//文字从尺寸线偏移 '当尺寸线分成段以在两段之间放置标注文字时，设置标注文字周围的距离
		pDimStyleTblRcd->setDimjust(0);//控制标注文字的水平位置
		pDimStyleTblRcd->setDimtix(1);//设置标注文字始终绘制在尺寸界线之间

		//'.SetVariable "DimJust", 0       '控制标注文字的水平位置
		// '0  将文字置于尺寸线之上，并在尺寸界线之间置中对正
		// '1  紧邻第一条尺寸界线放置标注文字
		// '2  紧邻第二条尺寸界线放置标注文字
		// '3  将标注文字放在第一条尺寸界线以上，并与之对齐
		//'4  将标注文字放在第二条尺寸界线以上，并与之对齐
		pDimStyleTblRcd->setDimtmove(0);//设置标注文字的移动规则
										//'0  尺寸线和标注文字一起移动
										//'1  在移动标注文字时添加一条引线
										//'2  允许标注文字自由移动而不用添加引线
		pDimStyleTblRcd->setDimtxt(100);//指定标注文字的高度，除非当前文字样式具有固定的高度
		pDimStyleTblRcd->setDimtad(1 * scale); // 文字位于标注线的上方
		//将标注样式表记录添加到标注样式表中
		pDimStyleTable->add(pDimStyleTblRcd);
	}
	pDimStyleTblRcd->setDimtxsty(objID);
	pDimStyleTblRcd->close();
	pDimStyleTable->close();
	return Acad::eOk;
}

void Dimension::addAcDbRadialDimension(const AcGePoint3d& center, const AcGePoint3d& chordPoint, double leaderLength, const ACHAR* dimText, AcDbObjectId dimStyle)
{
	AcDbRadialDimension(center, chordPoint, leaderLength);
}
