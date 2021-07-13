#include <string>
#include <limits>
#include "pch.h"
#include "NumEditText.h"

using namespace std;

constexpr double MAX = DBL_MAX;
constexpr double MIN = -MAX;

BEGIN_MESSAGE_MAP(NumEditText, CEdit)
	ON_WM_CHAR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

NumEditText::NumEditText()
{
	maxValue = MAX;
	minValue = MIN;
}

NumEditText::~NumEditText()
{
}

void NumEditText::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str;
	GetWindowText(str);

	int nSource, nDestination;
	GetSel(nSource, nDestination);

	// 保证小数点最多只能出现一次
	if (nChar == '.')
	{
		//若原来的字符串中已经有一个小数点,则不将小数点输入,保证了最多只能输入一个小数点
		if (str.Find('.') != -1)
		{
		}
		// 否则就输入这个小数点
		else
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	// 保证负号只能出现一次,并且只能出现在第一个字符
	else if (nChar == '-')
	{
		// 还没有输入任何字符串
		if (str.IsEmpty())
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		else
		{
			// 此时选择了全部的内容
			if (nSource == 0 && nDestination == str.GetLength() || nSource == 0 && nDestination == 0 && str.Left(1).Compare(L"-"))
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
	}
	// 除了小数点和负号,还允许输入数字,Backspace,Delete
	else if ((nChar >= '0' && nChar <= '9') || (nChar == 0x08) || (nChar == 0x10))
	{
		//如果是第一个字符处输入，且已有'-'则不输入
		if (nSource == 0 && nDestination == 0 && !str.IsEmpty() && str.Find('-') != -1)
		{
		}
		else
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}

	}
	// 其它的键,都不响应
	else
	{
	}

	GetWindowText(str);
	if (_ttof(str) > maxValue)
	{
		CString msg;
		msg.Format(L"输入的数值不能大于 %0.1f", maxValue);
		AfxMessageBox(msg);
		SetWindowText(L"");
	}
	else if (_ttof(str) < minValue)
	{
		CString msg;
		msg.Format(L"输入的数值不能小于 %0.1f", minValue);
		AfxMessageBox(msg);
		SetWindowText(L"");
	}

}

void NumEditText::setRange(double min, double max)
{
	maxValue = max;
	minValue = min;
}

double NumEditText::GetDoubleData()
{
	CString str;
	GetWindowText(str);
	if (str.GetLength() <= 0)
	{
		return 0.0;
	}
	return  _ttof(str);
}
