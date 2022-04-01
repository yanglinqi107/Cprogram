// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetWindowText(TEXT("登录界面"));

	CInfoFile file;	//创建操作文件类对象
	CString user, pwd;

	file.ReadLogin(user, pwd);

	m_user = user;
	m_pwd = pwd;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE); //更新控件的数据到对应的变量

	CInfoFile file;	//创建操作文件类对象
	CString user, pwd;
	
	file.ReadLogin(user, pwd); //读取配置文件，获取用户名密码

	if (m_user == user) //用户名相等
	{
		if (m_pwd != pwd) //密码不等
		{
			MessageBox(TEXT("密码错误"), TEXT("Error"));
			m_pwd.Empty(); //清空
			m_user.Empty();
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
	else
	{
		MessageBox(_T("用户名不存在"), TEXT("Error"));
		m_user.Empty();
		m_pwd.Empty();
	}

}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
