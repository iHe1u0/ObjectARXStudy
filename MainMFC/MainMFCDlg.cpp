
// MainMFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MainMFC.h"
#include "MainMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MyData.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainMFCDlg 对话框



CMainMFCDlg::CMainMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, R1);
	DDX_Control(pDX, IDC_EDIT2, R2);
	DDX_Control(pDX, IDC_EDIT3, R3);
	DDX_Control(pDX, IDC_EDIT4, R4);
	DDX_Control(pDX, IDC_EDIT5, R5);
	DDX_Control(pDX, IDC_EDIT6, H1);
	DDX_Control(pDX, IDC_EDIT7, H2);
	DDX_Control(pDX, IDC_EDIT8, H_2);
	DDX_Control(pDX, IDC_EDIT11, RADIUS1);
	DDX_Control(pDX, IDC_EDIT12, RADIUS_1);
	DDX_Control(pDX, IDC_EDIT13, RADIUS2);
	DDX_Control(pDX, IDC_EDIT14, RADIUS3);
	DDX_Control(pDX, IDC_EDIT15, RADIUS4);
	DDX_Control(pDX, IDC_EDIT16, RADIUS5);
	DDX_Control(pDX, IDC_STATIC_INFO, INFO_TEXT);
}

BEGIN_MESSAGE_MAP(CMainMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMainMFCDlg::OnSave)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMainMFCDlg 消息处理程序

BOOL CMainMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

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
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 反序列化读取并赋值
	InitData();
	//字的大小和格式
	m_font.CreatePointFont(125, L"微软雅黑");
	//画刷的颜色，GetSysColor(COLOR_3DFACE)是当前对话框的背景颜色
	m_brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	CString info;
	info.LoadStringW(IDS_STRING_INFO);
	INFO_TEXT.SetWindowTextW(info);
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



void CMainMFCDlg::InitData()
{
	MyData mydata;
	CString fileName = L"D:\\mydata\\tmp.dat";
	CFile file;
	file.Open(fileName, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	mydata.Serialize(ar);
	R1.SetWindowTextW(mydata.r1);
	R2.SetWindowTextW(mydata.r2);
	R3.SetWindowTextW(mydata.r3);
	R4.SetWindowTextW(mydata.r4);
	R5.SetWindowTextW(mydata.r5);
	H1.SetWindowTextW(mydata.h1);
	H2.SetWindowTextW(mydata.h2);
	H_2.SetWindowTextW(mydata.h_2);
	RADIUS1.SetWindowTextW(mydata.radius1);
	RADIUS_1.SetWindowTextW(mydata.radius_1);
	RADIUS2.SetWindowTextW(mydata.radius2);
	RADIUS3.SetWindowTextW(mydata.radius3);
	RADIUS4.SetWindowTextW(mydata.radius4);
	RADIUS5.SetWindowTextW(mydata.radius5);
	file.Close();
	ar.Close();
}

void CMainMFCDlg::OnSave()
{
	MyData mydata;
	CString fileName = L"D:\\mydata\\tmp.dat";
	CFile file;
	//获取数据
	R1.GetWindowText(mydata.r1);
	R2.GetWindowText(mydata.r2);
	R3.GetWindowText(mydata.r3);
	R4.GetWindowText(mydata.r4);
	R5.GetWindowText(mydata.r5);
	H1.GetWindowText(mydata.h1);
	H2.GetWindowText(mydata.h2);
	H_2.GetWindowText(mydata.h_2);
	RADIUS1.GetWindowText(mydata.radius1);
	RADIUS_1.GetWindowText(mydata.radius_1);
	RADIUS2.GetWindowText(mydata.radius2);
	RADIUS3.GetWindowText(mydata.radius3);
	RADIUS4.GetWindowText(mydata.radius4);
	RADIUS5.GetWindowText(mydata.radius5);
	//打开文件
	file.Open(fileName, CFile::modeCreate | CFile::modeReadWrite);
	CArchive ar(&file, CArchive::store);
	mydata.Serialize(ar);
	ar.Close();
	file.Close();
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
