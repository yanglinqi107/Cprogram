﻿#pragma once



// CSellDlg 窗体视图

class CSellDlg : public CFormView
{
	DECLARE_DYNCREATE(CSellDlg)

protected:
	CSellDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CSellDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_SELL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo;
	int m_price;
	// 库存
	int m_stock;
	// 个数
	int m_num;
	CString m_sellInfo;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelendcancelCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
};


