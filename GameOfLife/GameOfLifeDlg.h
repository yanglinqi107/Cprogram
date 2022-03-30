
// GameOfLifeDlg.h: 头文件
//

#pragma once


#include "global.h"
#include "LifeGameControl.h"

//对话层
// CGameOfLifeDlg 对话框
class CGameOfLifeDlg : public CDialogEx
{
// 构造
public:
	CGameOfLifeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOFLIFE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;	//内存dc
	CDC m_dcBG;		//背景dc

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();  
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();   //画图
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	int m_Row;			//表格行数
	int m_Col;			//表格列数
	int m_Length;		//细胞的边长
	int m_SingleSize;	//单个格子大小
	bool IsEvolution;	//是否在演化
	CRect m_rtGameRect;	//游戏区大小
	CPoint m_ptGameTop;	//游戏区起点
	LifeGameControl m_LGameC;	//游戏控制

	//将背景图片位图资源保存到位图内存中
	void InitBackground();
	//画线，表格
	void DrawLine();
	//一次演化
	void EvolutionStep();

	void DrawCells(int nRow, int nCol, bool status);
	void DrawCells();

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonClear();
	afx_msg void OnClickedButtonEnd();
	afx_msg void OnClickedButtonRangcreat();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonStep();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
