#pragma once
#include "global.h"
#include "CGameControl.h"

//界面层
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

protected:
	CDC m_dcMem;		//内存DC
	CDC m_dcBG;			//背景DC
	CDC m_dcElement;	//元素内存DC
	CDC m_dcMask;		//掩码内存DC
	CDC m_dcCache;		//缓存的内存DC
	CDC m_dcPause;		//暂停图片的内存DC

	bool m_bFirstPoint;		//图片是否是第一次选中
	CPoint m_ptGameTop;	//游戏区起点
	CSize m_sizeElem;	//元素图片大小
	CRect m_rtGameRect;	//游戏区大小

	CGameControl m_GameC;	//游戏控制类

	bool m_bPlaying;		//是否正在游戏
	bool m_bPause;			//游戏是否暂停

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitElement();
	void InitBackground();

	//绘制边框
	void DrawTipFrame(int nRow, int nCol);	
	//绘制连接线
	void DrawTipLine(Vertex avPath[AVPATHNUM], int nVexNum);	
	//绘制显示时间
	void DrawGameTime();
	//判断胜负
	void JudgeWin();
	//保存游戏界面
	void SaveMap();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();
	void UpdateMap(void);
	void UpdateWindow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonPrompt();
	afx_msg void OnClickedButtonReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonStop();

	virtual BOOL OnInitDialog();

protected:
	CProgressCtrl m_GameProgress;
public:
	afx_msg void OnBnClickedButtonHelp();
};
