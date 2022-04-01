
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "SaleSystem.h"
#include "CSelectView.h"
#include "CDisplayView.h"
#include "CUserDlg.h"
#include "CSellDlg.h"
#include "CAddDlg.h"
#include "CInfoDlg.h"
#include "CDelDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
	//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)

	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32775, &CMainFrame::On32775)
	ON_COMMAND(ID_32776, &CMainFrame::On32776)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置窗口的位置和大小
	MoveWindow(0, 0, 800, 500);
	//将窗口移动到屏幕中央
	CenterWindow();

	SetTitle(TEXT("2022/3/24"));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//静态拆分窗口，1行2列，CSplitterWnd::CreateStatic
	m_splitter.CreateStatic(this, 1, 2);

	//创建视图 CSplitterWnd::CreateView
	//0,0  0行0列
	//CSize(250, 500) 指定视图宽高
	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE;  //自己拆分
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

//自定义消息处理函数
LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	//界面挂载
	switch (wParam)
	{
	case NM_A:
	{
		//MessageBox(_T("NM_A"));
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 0), &Context);
		CUserDlg* pNewView = (CUserDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
		break;
	}
	case NM_B:
	{
		//MessageBox(_T("NM_B"));
		Context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 0), &Context);
		CSellDlg* pNewView = (CSellDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
		break;
	}
	case NM_C:
	{
		//MessageBox(_T("NM_C"));
		Context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(600, 0), &Context);
		CInfoDlg* pNewView = (CInfoDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
		break;
	}
	case NM_D:
	{
		//MessageBox(_T("NM_D"));
		Context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAddDlg), CSize(600, 0), &Context);
		CAddDlg* pNewView = (CAddDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
		break;
	}
	case NM_E:
	{	
		//MessageBox(_T("NM_E"));
		Context.m_pNewViewClass = RUNTIME_CLASS(CDelDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDelDlg), CSize(600, 0), &Context);
		CDelDlg* pNewView = (CDelDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
		break;
	}
	default:
		MessageBox(_T("error"));
	}
	return LRESULT();
}


void CMainFrame::On32771()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);
}


void CMainFrame::On32772()
{
	// TODO: 在此添加命令处理程序代码
	//个人信息
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CMainFrame::On32773()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}


void CMainFrame::On32774()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
}


void CMainFrame::On32775()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
}


void CMainFrame::On32776()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
}
