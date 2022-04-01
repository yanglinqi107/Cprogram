﻿// CDelDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CDelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(DIALOG_DEL)
	, m_price(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//读取文件，获取商品名，给组合框添加字符串
	CInfoFile file;
	file.ReadDocline();	//读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		m_combo.AddString((CString)it->name.c_str());
	}

	//将第一个商品名设为默认选中项
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//获取控件上的内容，更新到对应关联的变量中
	UpdateData(TRUE);

	if (m_num <= 0)
	{
		MessageBox(TEXT("个数不能小于等于0"), _T("提示"));
		return;
	}

	if (m_num > m_curNum)
	{
		CString tmp;
		tmp.Format(_T("该商品库存只有%d"), m_curNum);
		MessageBox(tmp, _T("提示"));
		return;
	}

	CString type;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取组合框当前内容
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("删除商品：%s \r\n单价：%d \r\n个数：%d "), type, m_price, m_num);
	MessageBox(str, _T("提示"));


	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num = it->num - m_num;
		}
	}
	file.WirteDocline(); //更新文件内容

	m_num = 0;
	UpdateData(FALSE); //更新到对应的控件
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	m_combo.SetCurSel(0); //选择第0项目
	m_num = 0;
	OnCbnSelchangeCombo1();
}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString text;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取当前内容
	m_combo.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_price = it->price;
			m_curNum = it->num; //保存当前商品的库存
			m_num = 0;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}
