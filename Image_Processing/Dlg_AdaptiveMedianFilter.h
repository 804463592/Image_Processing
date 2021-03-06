#pragma once


// Dlg_AdaptiveMedianFilter 对话框

class Dlg_AdaptiveMedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_AdaptiveMedianFilter)

public:
	Dlg_AdaptiveMedianFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_AdaptiveMedianFilter();

	int m_max, n_max;
	int m_start, n_start;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_AdaptiveMedianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

};
