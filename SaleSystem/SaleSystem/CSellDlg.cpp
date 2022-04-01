// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "CSellDlg.h"
#include "InfoFile.h"

// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_price(0)
	, m_stock(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_stock);
	DDX_Text(pDX, IDC_EDIT5, m_num);
	DDX_Text(pDX, IDC_EDIT6, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELENDCANCEL(IDC_COMBO1, &CSellDlg::OnCbnSelendcancelCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化消息订单窗口

	//初始化下拉框
	CInfoFile file;
	//把商品读到file中
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		//遍历商品容器 把容器名称放到下拉框中
		//string -> CString
		m_combo.AddString(CString(it->name.c_str()));
	}
	//默认选中第一个商品
	m_combo.SetCurSel(0);
	OnCbnSelendcancelCombo1();
	file.ls.clear(); //清空list的内容
}


void CSellDlg::OnCbnSelendcancelCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//切换商品 触发事件
	// 
	//获取商品名
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	//把商品读到file中
	file.ReadDocline();
	//根据商品名称获取到该商品的价格和库存 显示到控件中
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		//string -> CString
		if ((CString)it->name.c_str() == name)
		{
			m_price = it->price;
			m_stock = it->num;
			UpdateData(FALSE);
			break;
		}
	}
	file.ls.clear(); //清空list的内容
}


void CSellDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num <= 0)
	{
		MessageBox(_T("购买数量要大于0"), _T("Error"));
		return;
	}
	if (m_num > m_stock)
	{
		MessageBox(_T("购买数量不能大于库存"), _T("Error"));
		return;
	}
	//购买 获取具体要买的商品
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		if ((CString)it->name.c_str() == name)
		{
			it->num -= m_num; //库存量减少
			m_stock = it->num; //控件上库存量同步
			//告诉用户具体的购买信息
			//CString str;
			m_sellInfo.Format(_T("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_price * m_num);
			UpdateData(FALSE);
			MessageBox(_T("购买成功"), _T("True"));
		}
	}
	//把最新信息写入文件
	file.WirteDocline();
	//清空
	m_num = 0;
	//m_sellInfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}
