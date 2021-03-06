#pragma once


// Dlg_GaussianNoise 对话框

class Dlg_GaussianNoise : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_GaussianNoise)

public:
	Dlg_GaussianNoise(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_GaussianNoise();
	double mean;
	double sigma;
	int T;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_GaussianNoise };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
