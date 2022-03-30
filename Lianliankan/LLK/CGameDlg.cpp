// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "CHelpDialog.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	m_bFirstPoint = true;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bPlaying = false;
	m_bPause = false;
}

CGameDlg::~CGameDlg()
{
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();

	InitElement();

	return TRUE;
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

void CGameDlg::InitBackground()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE bmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmpBG);
	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	CenterWindow();
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_PROMPT, &CGameDlg::OnClickedButtonPrompt)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameDlg::OnClickedButtonReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CGameDlg::OnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcElement.SelectObject(hBmp);

	//加载掩码BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加载暂停图片资源
	HANDLE hPause = ::LoadImage(NULL, _T("theme\\picture\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcPause.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcPause.SelectObject(hPause);
}

void CGameDlg::OnClickedButtonStart()
{
	if (m_bPlaying || m_bPause)
	{
		return;
	}

	//初始化游戏地图
	m_GameC.StartGame();

	m_bPlaying = true;
	//将开始按钮设为不可用
	//this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	//更新界面
	UpdateMap();

	//更新窗口
	InvalidateRect(m_rtGameRect, FALSE);

	//设置范围为0~300，nLower,nUpper
	m_GameProgress.SetRange32(0, MAX_TIME);
	//设置进度条步长为-1,nStep
	//m_GameProgress.SetStep(-1);
	//设置开始位置300,nPos
	m_GameProgress.SetPos(MAX_TIME);
	
	//启动计时器
	this->SetTimer(PLAY_TIME_ID, 1000, NULL);
	
	//绘制显示时间
	DrawGameTime();
}

void CGameDlg::UpdateMap(void)
{
	int nTop = m_ptGameTop.x;
	int nLeft = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < MAX_ROW; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == BLANK)	continue;
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
}

void CGameDlg::UpdateWindow()
{
	//调整窗体大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);	//获得窗口大小
	this->GetClientRect(rtClient);	//获得客户区大小
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗体大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//判断是否正在游戏，且未停止
	if (!m_bPlaying || m_bPause)
	{
		return;
	}
	//判断点击范围是否有效
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y || point.x>m_rtGameRect.right || point.y>m_rtGameRect.bottom)

	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//换算点击的坐标点
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;	//行
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;	//列
	if (nRow > MAX_ROW || nCol > MAX_COL || m_GameC.GetElement(nRow, nCol) == BLANK)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nVexNum = 0;

	if (m_bFirstPoint)
	{
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
	}
	else 
	{
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecPoint(nRow, nCol);
		
		//获得路径
		Vertex avPath[AVPATHNUM];

		//判断是否连接
		if (m_GameC.Link(avPath, nVexNum))
		{

			//画边框
			DrawTipLine(avPath, nVexNum);
			//更新地图
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		
		//判断胜负
		JudgeWin();
	}
	m_bFirstPoint = !m_bFirstPoint;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine(Vertex avPath[AVPATHNUM], int nVexNum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//绘制连接线
	for (int i = 0; i < nVexNum - 1; ++i)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

void CGameDlg::OnClickedButtonPrompt()
{
	if (!m_bPlaying || m_bPause)
	{
		return;
	}
	Vertex avPath[AVPATHNUM];
	int nVexnum;
	//查找连通路径
	if (m_GameC.Help(avPath, nVexnum))
	{
		//绘制矩形框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		//绘制连接线
		DrawTipLine(avPath, nVexnum);

		//更新地图
		UpdateMap();

		Sleep(500);
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDlg::OnClickedButtonReset()
{
	if (!m_bPlaying || m_bPause)
	{
		return;
	}
	//调用GameControl::ResetGraph()
	m_GameC.ResetGraph();
	//UpdateMap()更新界面
	UpdateMap();
	//通知界面重绘
	Sleep(200);
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	JudgeWin();
	if (nIDEvent == PLAY_TIME_ID && m_bPlaying)
	{
		//游戏时间减1秒
		//m_GameProgress.StepIt();
		m_GameProgress.OffsetPos(-1);
		//绘制显示时间
		DrawGameTime();
		//m_GameProgressgress.OffsetPos(-1);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	CFont timeFont;
	CDC* pdc = this->GetDC();
	//timeFont.CreatePointFont(150, _T("Times new Roman"), pdc);
	timeFont.CreatePointFont(150, _T("宋体"), pdc);

	pdc->SelectObject(&timeFont);
	pdc->SetTextColor(RGB(0, 0, 0));
	pdc->SetBkColor(RGB(255, 255, 0));

	int t = m_GameProgress.GetPos();
	CString timeText ;
	timeText.Format(_T("%d"), t);
	if (t < 100)
	{
		CString timeTemp;
		timeTemp.Format(_T("%d"), t);
		timeText = _T("0") + timeTemp;
	}
	if (t < 10)
	{
		CString timeTemp;
		timeTemp.Format(_T("%d"), t);
		timeText = _T("00") + timeTemp;
	}


	//MessageBox(timeText);
	//pdc->GetTextExtent(timeText);

	//获取ProgressCtrl的位置
	CRect progressTime;
	this->GetDlgItem(IDC_GAME_TIME)->GetWindowRect(&progressTime);//在屏幕中的位置
	//CPoint proTimePosi;
	ScreenToClient(&progressTime);		//转化为对话框中的坐标
	//pdc->TextOut(progressTime.left, progressTime.top + 30, timeText);
	pdc->TextOut(progressTime.left, progressTime.top - 25, timeText);
}

void CGameDlg::JudgeWin()
{
	//游戏胜负判断
	BOOL bGameStatus = m_GameC.IsWin(m_GameProgress.GetPos());
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;
		//关闭定时器
		KillTimer(PLAY_TIME_ID);
		//提示获胜
		CString strTitle;
		this->GetWindowText(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("恭喜获胜"), _T("欢乐连连看——基本模式"), MB_OK);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到了"), _T("欢乐连连看——基本模式"), MB_OK);
		}
		//还原开始游戏按钮，使用按钮可以点击
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	}
}

void CGameDlg::SaveMap()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);

	//初始化内存DC
	m_dcCache.CreateCompatibleDC(&dc);
	CBitmap bCache;
	bCache.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcCache.SelectObject(&bCache);

	//绘制背景到内存DC中
	m_dcCache.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	//创建与视频内存兼容的内存DC
	//m_dcCache.CreateCompatibleDC(&dc);
	//m_dcCache.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcMem, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
}


void CGameDlg::OnClickedButtonStop()
{
	if (!m_bPlaying)
	{
		return;
	}
	if (!m_bPause)
	{
		this->SetDlgItemText(IDC_BUTTON_STOP, _T("继续游戏"));
		/*this->GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);*/
		KillTimer(PLAY_TIME_ID);
		SaveMap();
		m_dcMem.BitBlt(50, 50, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcPause, 0, 0, SRCCOPY);
	}
	else
	{
		this->SetDlgItemText(IDC_BUTTON_STOP, _T("暂停游戏"));
		/*this->GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);*/
		this->SetTimer(PLAY_TIME_ID, 1000, NULL);
		m_dcMem.BitBlt(0, 0, 800, 600, &m_dcCache, 0, 0, SRCCOPY);
		//删除暂停的内存DC
		m_dcCache.DeleteDC();
	}
	Sleep(100);
	InvalidateRect(m_rtGameRect, FALSE);
	m_bPause = !m_bPause;
}


void CGameDlg::OnBnClickedButtonHelp()
{
	//基本模式界面不可操作
	//this->EnableWindow(FALSE);
	//显示帮助界面
	CHelpDialog dlg;
	dlg.DoModal();

	//基本模式面可操作
	//this->EnableWindow(TRUE);
}
