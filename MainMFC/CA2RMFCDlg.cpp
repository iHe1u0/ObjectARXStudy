#include "pch.h"
#include "CA2RMFCDlg.h"
#include "resource.h"

constexpr double PI = 3.14159265358979323846;

CA2RMFCDlg::CA2RMFCDlg(CWnd* pParent)
{
	result = 0.0;
	icon = AfxGetApp()->LoadIcon(IDB_BITMAP_A2R_BMP);
}

CA2RMFCDlg::~CA2RMFCDlg()
{
}

void CA2RMFCDlg::DoDataExchange(CDataExchange* pDX)
{

	DDX_Control(pDX, IDC_EDIT1, Deg);
	DDX_Control(pDX, IDC_EDIT4, Min);
	DDX_Control(pDX, IDC_EDIT5, Sec);
	DDX_Text(pDX, IDC_STATIC_A2R_RESULT, result);
}

BOOL CA2RMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//SetIcon(icon, TRUE); // Set big icon 
	SetIcon(icon, TRUE); // Set small icon;
	return 0;
}

BEGIN_MESSAGE_MAP(CA2RMFCDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CA2RMFCDlg::OnDataChanged)
	ON_EN_CHANGE(IDC_EDIT4, &CA2RMFCDlg::OnDataChanged)
	ON_EN_CHANGE(IDC_EDIT5, &CA2RMFCDlg::OnDataChanged)
	ON_STN_CLICKED(IDC_STATIC_A2R_RESULT, &CA2RMFCDlg::OnResultClicked)
END_MESSAGE_MAP()

void CA2RMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, icon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CA2RMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(icon);
}

void CA2RMFCDlg::OnDataChanged()
{
	calculateResult();
}

double CA2RMFCDlg::angle_to_radian(double degree, double min, double second)
{
	double flag = (degree < 0) ? -1.0 : 1.0;
	if (degree < 0)
	{
		degree = degree * (-1.0);
	}
	double angle = degree + min / 60 + second / 3600;
	double result = flag * (angle * PI) / 180;
	return result;
}

void CA2RMFCDlg::calculateResult()
{
	UpdateData(true);
	result = angle_to_radian(Deg.GetDoubleData(), Min.GetDoubleData(), Sec.GetDoubleData());
	UpdateData(false);
}


void CA2RMFCDlg::OnResultClicked()
{
	CString strData;
	strData.Format(L"%lf", result);
	if (!OpenClipboard())
		return;
	EmptyClipboard();
	int length = strData.GetLength() + 1;
	HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (length));
	if (hglbCopy == NULL)
	{
		CloseClipboard();
		return;
	}
	char* lptstrCopy = (char*)GlobalLock(hglbCopy);
	if (lptstrCopy != 0)
	{
		strcpy_s(lptstrCopy, length, (CStringA)strData);
		GlobalUnlock(hglbCopy);
		SetClipboardData(CF_TEXT, hglbCopy);
	}
	CloseClipboard();
}

void CA2RMFCDlg::OnCancel()
{
	DestroyWindow();
}
