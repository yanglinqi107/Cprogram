// CHelpDialog.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CClientDC dc(this);

	//加载图片资源
	HANDLE hBmpHelp;
	hBmpHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建兼容DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcHelp.SelectObject(hBmpHelp);

	//创建内存DC大小
	CRect rtClient;
	this->GetClientRect(rtClient);	//获得窗口大小
	m_rtHelp = rtClient;
	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	//绘制白色背景
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);

	//绘制帮助信息显示区域
	//this->GetDlgItem(IDC_STATIC_HELP)->GetWindowRect(&m_rtHelp);
	//this->ScreenToClient(&m_rtHelp);
	////绘制帮助信息
	UpdateHelp(0);

	//m_dcMem.BitBlt(0, 0, 800, 600, &m_dcHelp, 0, 0, SRCCOPY);

	//设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(hBmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);

	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	scrollinfo.nPage = 100; //设置滑块大小
	scrollinfo.nMin = 0;
	scrollinfo.nMax = bmpInfo.bmHeight; //设置滚动条的最大位置
	SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

	////设置滚动条范围
	//((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, bmpInfo.bmHeight, TRUE);
	//nMaxPos = bmpInfo.bmHeight;
	CenterWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CHelpDialog::UpdateHelp(int nPos)
{
	//将重绘区，绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制当前点的帮助信息
	m_dcMem.BitBlt(50, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	//更新界面
	InvalidateRect(m_rtHelp, FALSE);

}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

	//int pos = GetScrollPos(SB_VERT);
	switch (nSBCode)
	{
	case SB_LINEUP:			//点击向上按钮
		scrollinfo.nPos -= 1;
		UpdateHelp(scrollinfo.nPos);
		break;
	case SB_LINEDOWN:		//点击向下按钮
		scrollinfo.nPos += 1;
		UpdateHelp(scrollinfo.nPos);
		break;
	case SB_PAGEUP:			//向上翻页
		scrollinfo.nPos += 10;
		UpdateHelp(scrollinfo.nPos);
		break;
	case SB_PAGEDOWN:		//向下翻页
		scrollinfo.nPos -= 10;
		UpdateHelp(scrollinfo.nPos);
		break;
	case SB_TOP:			//顶部
		scrollinfo.nPos = scrollinfo.nMin;
		UpdateHelp(scrollinfo.nPos);
		break;
	case SB_BOTTOM:			//底部
		scrollinfo.nPos = scrollinfo.nMax;
		UpdateHelp(scrollinfo.nPos);
		break;
	case SB_THUMBPOSITION:	//点击在滑块上
	{
		scrollinfo.nPos = nPos;
		UpdateHelp(scrollinfo.nPos);
		break;
	}
	default:
		break;
	}
	SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	//UpdateHelp(scrollinfo.nPos);
	//ScrollWindow(0, unit);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

//添加鼠标滚轮事件
BOOL CHelpDialog::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//方法一：
	/*BOOL bUp = TRUE;
	int nDelta = zDelta;
	if (zDelta < 0) {
		bUp = FALSE;
		nDelta = -nDelta;
	}
	UINT nWheelScrollLines;
	::SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0,
		&nWheelScrollLines, 0);
	int nLines = (nDelta * nWheelScrollLines) / WHEEL_DELTA;
	while (nLines--)
		SendMessage(WM_VSCROLL, MAKEWPARAM(bUp ? SB_LINEUP : SB_LINEDOWN, 0), 0);
	return TRUE;*/

	//方法二：
	//SCROLLINFO scrollinfo;
	if (zDelta == 120)
	{
		OnVScroll(SB_PAGEDOWN, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}
	else if (zDelta == -120)
	{
		OnVScroll(SB_PAGEUP, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

