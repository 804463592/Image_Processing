#pragma once


// Dlg_ContraHarmonicMeanFilter 对话框

class Dlg_ContraHarmonicMeanFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_ContraHarmonicMeanFilter)

public:
	Dlg_ContraHarmonicMeanFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_ContraHarmonicMeanFilter();
	int m, n;
	double Q;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_ContraHarmonicMeanFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
