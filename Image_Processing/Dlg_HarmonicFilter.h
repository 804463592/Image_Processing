#pragma once


// Dlg_HarmonicFilter 对话框

class Dlg_HarmonicFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_HarmonicFilter)

public:
	Dlg_HarmonicFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_HarmonicFilter();
	int m, n;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_HarmonicFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
