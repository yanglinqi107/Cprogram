// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "CUserDlg.h"
#include "InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT3, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//初始化
	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//修改密码
	UpdateData(TRUE);	//拿到最新值

	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("密码不能为空"), TEXT("Error"));
		return;
	}
	//新密码和确定密码一致
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码与确定密码要一致"), TEXT("Error"));
		return;
	}
	//新密码与旧密码不能一致
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (pwd == m_newPwd)
	{
		MessageBox(_T("新密码与旧密码不能一致"), _T("Error"));
		return;
	}
	//CString 转 char*
	CStringA tmp1, tmp2;
	tmp1 = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp1.GetBuffer(), tmp2.GetBuffer());
	MessageBox(_T("修改成功"), _T("True"));

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	//取消按钮
	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
