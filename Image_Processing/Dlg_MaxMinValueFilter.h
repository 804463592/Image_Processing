#pragma once


// Dlg_MaxMinValueFilter 对话框

class Dlg_MaxMinValueFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_MaxMinValueFilter)

public:
	Dlg_MaxMinValueFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_MaxMinValueFilter();
	BOOL maxcheck, mincheck,midcheck;
	int m, n;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_MaxMinValueFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedMaxRadio();

	afx_msg void OnBnClickedMinRadio();
	
	afx_msg void OnBnClickedMIdpointRadio();  //添加消息处理程序,afx_msg表示是消息函数

	afx_msg void OnBnClickedAddValueBtn();

	afx_msg void OnBnClickedSubValueBtn();
};
