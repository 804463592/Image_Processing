#pragma once


// Dlg_ButterWorthFilter 对话框

class Dlg_ButterWorthFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_ButterWorthFilter)

public:
	Dlg_ButterWorthFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_ButterWorthFilter();
	double D0;
	int n;
	BOOL is_HighPass;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { 
		IDD = IDD_Dlg_ButterWorthFilter
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


};
