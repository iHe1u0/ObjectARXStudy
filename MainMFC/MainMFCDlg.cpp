﻿
// MainMFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MainMFC.h"
#include "MainMFCDlg.h"
#include "afxdialogex.h"
#include "MyData.h"
#include "CAboutDlg.h"
#include "CA2RMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainMFCDlg 对话框
CMainMFCDlg::CMainMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	angelToRadianDlg = NULL;

}

CMainMFCDlg::~CMainMFCDlg()
{
	if (angelToRadianDlg != NULL)
	{
		delete angelToRadianDlg;
	}
}


void CMainMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, R1);
	DDX_Text(pDX, IDC_EDIT2, R2);
	DDX_Text(pDX, IDC_EDIT3, R3);
	DDX_Text(pDX, IDC_EDIT4, R4);
	DDX_Text(pDX, IDC_EDIT5, R5);
	DDX_Text(pDX, IDC_EDIT6, H1);
	DDX_Text(pDX, IDC_EDIT7, H2);
	DDX_Text(pDX, IDC_EDIT8, H_2);
	DDX_Text(pDX, IDC_EDIT11, RADIUS1);
	DDX_Text(pDX, IDC_EDIT12, RADIUS_1);
	DDX_Text(pDX, IDC_EDIT13, RADIUS2);
	DDX_Text(pDX, IDC_EDIT14, RADIUS3);
	DDX_Text(pDX, IDC_EDIT15, RADIUS4);
	DDX_Text(pDX, IDC_EDIT16, RADIUS5);
	DDX_Control(pDX, IDC_STATIC_INFO, INFO_TEXT);
}

BEGIN_MESSAGE_MAP(CMainMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMainMFCDlg::OnSave)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENU_SHOW_ABOUT, &CMainMFCDlg::OnMenuShowAbout)
	ON_COMMAND(ID_MENU_OPEN, &CMainMFCDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_EXIT, &CMainMFCDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_TOOLS_A2R, &CMainMFCDlg::OnMenuToolsA2r)
	ON_COMMAND(ID_MENU_SAVE, &CMainMFCDlg::OnMenuSave)
END_MESSAGE_MAP()


// CMainMFCDlg 消息处理程序

BOOL CMainMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, TRUE);		// 设置小图标
	m_font.CreatePointFont(125, L"微软雅黑");
	//画刷的颜色，GetSysColor(COLOR_3DFACE)是当前对话框的背景颜色
	m_brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	CString info;
	info.LoadStringW(IDS_STRING_INFO);
	INFO_TEXT.SetWindowTextW(info);
	//添加菜单
	menu.LoadMenuW(IDR_MENU_MAIN);
	SetMenu(&menu);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMainMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainMFCDlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//加载指定文件
void CMainMFCDlg::InitData(CString fileName)
{
	DataStruct dataStruct(fileName);
	double data[14]{ 0 };
	dataStruct.Read(dataStruct, data);
	int version = data[0];
	R1 = data[1];
	R2 = data[2];
	R3 = data[3];
	R4 = data[4];
	R5 = data[5];
	H1 = data[6];
	H2 = data[7];
	H_2 = data[8];
	RADIUS1 = data[9];
	RADIUS_1 = data[10];
	RADIUS2 = data[11];
	RADIUS3 = data[12];
	RADIUS4 = data[13];
	RADIUS5 = data[14];

	UpdateData(FALSE);
}

//保存各项数据到文件
void CMainMFCDlg::OnSave()
{
	UpdateData(TRUE);
	if (mydata == NULL)
	{
		CFileDialog dlg(FALSE);
		dlg.m_ofn.lpstrTitle = L"保存文件";
		dlg.m_ofn.lpstrFilter = CONFIG_EXT_NAME;
		CString fileName;
		if (dlg.DoModal() == IDOK)
		{
			fileName = dlg.GetPathName() + CONFIG_EXT;
			mydata = new DataStruct(fileName);
		}
		else
		{
			return;
		}
	}
	mydata->r1 = R1;
	mydata->r2 = R2;
	mydata->r3 = R3;
	mydata->r4 = R4;
	mydata->r5 = R5;
	mydata->h1 = H1;
	mydata->h2 = H2;
	mydata->h_2 = H_2;
	mydata->radius1 = RADIUS1;
	mydata->radius_1 = RADIUS_1;
	mydata->radius2 = RADIUS2;
	mydata->radius3 = RADIUS3;
	mydata->radius4 = RADIUS4;
	mydata->radius5 = RADIUS5;
	mydata->Save(*mydata);
	MessageBox(L"保存成功", L"提示", MB_OK);
}


HBRUSH CMainMFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFO)
	{

		pDC->SetBkColor(RGB(255, 255, 255));//背景色
		pDC->SetTextColor(RGB(0, 0, 0));//文字颜色
		pDC->SelectObject(&m_font);//文字为初始化文字
		return m_brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMainMFCDlg::OnMenuShowAbout()
{
	CAboutDlg* dlg = new CAboutDlg;
	dlg->Create(IDD_ABOUTBOX, NULL);
	dlg->ShowWindow(SW_SHOW);
}


void CMainMFCDlg::OnMenuOpen()
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle = L"选择配置文件";
	dlg.m_ofn.lpstrFilter = CONFIG_EXT_NAME;
	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetPathName();
		InitData(path);
	}
}



void CMainMFCDlg::OnMenuSave()
{
	this->OnSave();
}

void CMainMFCDlg::OnMenuToolsA2r()
{
	if (angelToRadianDlg != NULL)
	{
		delete angelToRadianDlg;
	}
	angelToRadianDlg = new CA2RMFCDlg();
	angelToRadianDlg->Create(IDD_DIALOG_A2RTools);
	angelToRadianDlg->ShowWindow(SW_SHOWNORMAL);
}

void CMainMFCDlg::OnMenuExit()
{
	SendMessage(WM_CLOSE);
}
