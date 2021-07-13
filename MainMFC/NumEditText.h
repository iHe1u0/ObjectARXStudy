#pragma once
#include <afxwin.h>
class NumEditText : public CEdit
{
	//构造和析构函数
public:
	NumEditText();
	~NumEditText();

public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void setRange(double min, double max);
	double GetDoubleData();

protected:
	DECLARE_MESSAGE_MAP()

private:
	double maxValue;
	double minValue;

};

