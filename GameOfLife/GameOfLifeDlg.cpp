
// GameOfLifeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GameOfLife.h"
#include "afxdialogex.h"
#include "GameOfLifeDlg.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <thread>
#include <iostream>


// CGameOfLifeDlg 对话框

CGameOfLifeDlg::CGameOfLifeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEOFLIFE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_Row = MAX_ROW;
	m_Col = MAX_COL;
	m_Length = CELL_LENGTH;

	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	//m_SingleSize = m_Length + 2;
	m_SingleSize = CELLPRO;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_Col * m_SingleSize;
	m_rtGameRect.bottom = m_rtGameRect.top + m_Row * m_SingleSize;

	IsEvolution = false;
}

void CGameOfLifeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameOfLifeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CGameOfLifeDlg::OnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_END, &CGameOfLifeDlg::OnClickedButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_RANGCREAT, &CGameOfLifeDlg::OnClickedButtonRangcreat)
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameOfLifeDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STEP, &CGameOfLifeDlg::OnClickedButtonStep)
	ON_WM_TIMER()
//	ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CGameOfLifeDlg 消息处理程序

void CGameOfLifeDlg::InitBackground()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE bmpBG = ::LoadImage(NULL, _T("res\\BG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_MAIN_BG);

	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(bmpBG);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 1000, 800);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 1000, 800, &m_dcBG, 0, 0, SRCCOPY);

	//调整窗体大小
	CRect rtWin;
	CRect rtClient;
	
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetClientRect(rtClient);	//获得客户区大小
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeigth = rtWin.Height() - rtClient.Height();

	//设置窗体大小
	MoveWindow(0, 0, 1000 + nSpanWidth, 800 + nSpanHeigth);

	//绘制连接线
	//DrawLine();

	CenterWindow();
}

void CGameOfLifeDlg::DrawLine()
{
	//获取DC
	CClientDC dc(this);

	//设置画笔，白色
	//CPen penLine(PS_SOLID, 2, RGB(233, 43, 43));
	CPen penLine(PS_SOLID, 2, RGB(255, 255, 255));

	//将画笔选入DC
	CPen* pPen = dc.SelectObject(&penLine);

	////绘制表格内的线为白色
	//for (int i = 1; i < m_Row; ++i)
	//{
	//	dc.MoveTo(m_ptGameTop.x, m_ptGameTop.y + i * m_SingleSize);
	//	dc.LineTo(m_ptGameTop.x + m_Col * m_SingleSize, m_ptGameTop.y + i * m_SingleSize);
	//}
	//for (int i = 1; i < m_Col; ++i)
	//{
	//	dc.MoveTo(m_ptGameTop.x + i * m_SingleSize, m_ptGameTop.y);
	//	dc.LineTo(m_ptGameTop.x + i * m_SingleSize, m_ptGameTop.y + m_Row * m_SingleSize);
	//}
	
	//改变笔的颜色，黑色
	penLine.DeleteObject();
	penLine.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pPen = dc.SelectObject(&penLine);

	//绘制表格边框为黑色
	//上横线
	dc.MoveTo(m_ptGameTop.x, m_ptGameTop.y);
	dc.LineTo(m_ptGameTop.x + m_Col * m_SingleSize, m_ptGameTop.y);
	//下横线
	dc.MoveTo(m_ptGameTop.x, m_ptGameTop.y + m_Row * m_SingleSize);
	dc.LineTo(m_ptGameTop.x + m_Col * m_SingleSize, m_ptGameTop.y + m_Row * m_SingleSize);
	//左竖线
	dc.MoveTo(m_ptGameTop.x, m_ptGameTop.y);
	dc.LineTo(m_ptGameTop.x, m_ptGameTop.y + m_Row * m_SingleSize);
	//右竖线
	dc.MoveTo(m_ptGameTop.x + m_Col * m_SingleSize, m_ptGameTop.y);
	dc.LineTo(m_ptGameTop.x + m_Col * m_SingleSize, m_ptGameTop.y + m_Row * m_SingleSize);

	dc.SelectObject(pPen);
}

void CGameOfLifeDlg::DrawCells(int nRow, int nCol, bool status)
{
	CClientDC dc(this);
	CBrush brush(RGB(255, 255, 255));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_SingleSize + 1;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_SingleSize + 1;
	rtTipFrame.right = rtTipFrame.left + m_Length;
	rtTipFrame.bottom = rtTipFrame.top + m_Length;
	//dc.FrameRect(rtTipFrame, &brush);
	if (status)
	{
		dc.PatBlt(rtTipFrame.left, rtTipFrame.top, m_Length, m_Length, BLACKNESS);
	}
	else
	{
		dc.PatBlt(rtTipFrame.left, rtTipFrame.top, m_Length, m_Length, WHITENESS);
	}
	dc.SelectObject(brush);
}


void CGameOfLifeDlg::DrawCells()
{
	CClientDC dc(this);
	CBrush brush(RGB(255, 255, 255));
	for (int nRow = 0; nRow < MAX_ROW; ++nRow)
	{
		for (int nCol = 0; nCol < MAX_COL; ++nCol)
		{
			bool status = m_LGameC.GetCellStatus(nRow, nCol);
			CRect rtTipFrame;
			rtTipFrame.left = m_ptGameTop.x + nCol * m_SingleSize + 1;
			rtTipFrame.top = m_ptGameTop.y + nRow * m_SingleSize + 1;
			rtTipFrame.right = rtTipFrame.left + m_Length;
			rtTipFrame.bottom = rtTipFrame.top + m_Length;
			//dc.FrameRect(rtTipFrame, &brush);
			if (status)
			{
				dc.PatBlt(rtTipFrame.left, rtTipFrame.top, m_Length, m_Length, BLACKNESS);
			}
			else
			{
				dc.PatBlt(rtTipFrame.left, rtTipFrame.top, m_Length, m_Length, WHITENESS);
			}
		}
	}
	dc.SelectObject(brush);
}


BOOL CGameOfLifeDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	InitBackground();

	//设置窗体不可被拖大
	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameOfLifeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameOfLifeDlg::OnPaint()
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
		CPaintDC dc(this);

		dc.BitBlt(0, 0, 1000, 1000, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}

	//画表格线
	DrawLine();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameOfLifeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGameOfLifeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//判断点击范围是否有效
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y || point.x >= m_rtGameRect.right || point.y >= m_rtGameRect.bottom)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_SingleSize;	//行
	int nCol = (point.x - m_ptGameTop.x) / m_SingleSize;	//列
	/*CString str;
	str.Format(_T("row = %d, col = %d"), nRow, nCol);
	MessageBox(str);*/

	//设置格子对应细胞的生命状态
	m_LGameC.SetCellStatus(nRow, nCol);
	//获取对应细胞的生命状态
	bool status = m_LGameC.GetCellStatus(nRow, nCol);
	//根据细胞生命状态，涂格子的颜色
	DrawCells(nRow, nCol, status);

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGameOfLifeDlg::EvolutionStep()
{
	m_LGameC.CellEvolution();
	DrawCells();
	/*for (int nRow = 0; nRow < MAX_ROW; ++nRow)
	{
		for (int nCol = 0; nCol < MAX_COL; ++nCol)
		{
			bool status = m_LGameC.GetCellStatus(nRow, nCol);
			DrawCells(nRow, nCol, status);
		}
	}*/
	
	//CDC MemDC; //首先定义一个显示设备对象
	//CBitmap MemBitmap;//定义一个位图对象

	////随后建立与屏幕显示兼容的内存显示设备
	//MemDC.CreateCompatibleDC(NULL);

	////下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	//MemBitmap.CreateCompatibleBitmap(&m_dcMem, 1000, 1000);

	////将位图选入到内存显示设备中
	////只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	//CBitmap* pOldBit = MemDC.SelectObject(&MemBitmap);

	////先用背景色将位图清除干净，这里我用的是白色作为背景
	////你也可以用自己应该用的颜色
	////MemDC.FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));

	////绘图
	////MemDC.MoveTo(……);
	////MemDC.LineTo(……);

	////将内存中的图拷贝到屏幕上进行显示
	//m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &MemDC, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	////绘图完成后的清理
	//MemBitmap.DeleteObject();
	//MemDC.DeleteDC();
}

void CGameOfLifeDlg::OnClickedButtonClear()
{
	IsEvolution = false;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);

	// 更新地图
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	Sleep(100);
	InvalidateRect(m_rtGameRect, FALSE);

	//将细胞的生命状态全部设为死亡
	m_LGameC.Clear();
}


void CGameOfLifeDlg::OnClickedButtonEnd()
{
	IsEvolution = false;
	//关闭定时器
	KillTimer(EVOLUTION_TIME_ID);
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
}


void CGameOfLifeDlg::OnClickedButtonRangcreat()
{
	IsEvolution = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	KillTimer(EVOLUTION_TIME_ID);

	//随机改变Cells的状态
	m_LGameC.ChangeCellsRand();

	//将Cells对应格子涂色
	/*for (int nRow = 0; nRow < MAX_ROW; ++nRow)
	{
		for (int nCol = 0; nCol < MAX_COL; ++nCol)
		{
			bool status = m_LGameC.GetCellStatus(nRow, nCol);
			DrawCells(nRow, nCol, status);
		}
	}*/

	DrawCells();
}


void CGameOfLifeDlg::OnClickedButtonStart()
{
	IsEvolution = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//启动计时器
	this->SetTimer(EVOLUTION_TIME_ID, EVOLUTION_TIME, NULL);
}

void CGameOfLifeDlg::OnClickedButtonStep()
{
	IsEvolution = false;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);

	KillTimer(EVOLUTION_TIME_ID);
	EvolutionStep();
}


void CGameOfLifeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == EVOLUTION_TIME_ID && IsEvolution)
	{	
		EvolutionStep();
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CGameOfLifeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (MK_LBUTTON & nFlags)
	{
		OnLButtonUp(nFlags, point);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
