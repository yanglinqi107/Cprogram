// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "CAddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(DIALOG_ADD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT5, m_num1);
	DDX_Text(pDX, IDC_EDIT8, m_name2);
	DDX_Text(pDX, IDC_EDIT3, m_price2);
	DDX_Text(pDX, IDC_EDIT7, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELENDCANCEL(IDC_COMBO1, &CAddDlg::OnCbnSelendcancelCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
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
}


void CAddDlg::OnCbnSelendcancelCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
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
			m_price1 = it->price;
			UpdateData(FALSE);
		}
	}
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//添加商品按钮功能实现
	//拿到最新数据
	UpdateData(TRUE);

	if (m_num1 <= 0)
	{
		MessageBox(_T("添加的数量要大于0"), _T("Error"));
		return;
	}

	//获取要添加商品的名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		//string -> CString
		if ((CString)it->name.c_str() == name)
		{
			it->num += m_num1;
			UpdateData(FALSE);
			MessageBox(_T("添加成功"), _T("True"));
		}
	}

	//保存到文件中
	file.WirteDocline();
}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num1 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	//添加新商品
	UpdateData(TRUE);
	//验证数据的有效性
	if (m_name2.IsEmpty())
	{
		MessageBox(_T("商品名称不能为空"), _T("Error"));
		return;
	}
	if (m_price2 <= 0)
	{
		MessageBox(_T("单价必须大于0"), _T("Error"));
		return;
	}
	if (m_num2 <= 0)
	{
		MessageBox(_T("数量必须大于0"), _T("Error"));
		return;
	}

	CInfoFile file;
	file.ReadDocline();

	file.Addline(m_name2, m_num2, m_price2);
	file.WirteDocline();
	MessageBox(_T("商品添加成功"), _T("True"));

	//同步左侧下拉框
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelendcancelCombo1();

	//清空添加的数据
	m_num2 = 0;
	m_name2.Empty();
	m_price2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	//清空添加的数据
	m_num2 = 0;
	m_name2.Empty();
	m_price2 = 0;
	UpdateData(FALSE);
}
