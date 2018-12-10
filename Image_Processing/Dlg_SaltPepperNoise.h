#pragma once


// Dlg_SaltPepperNoise 对话框

class Dlg_SaltPepperNoise : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_SaltPepperNoise)

public:
	Dlg_SaltPepperNoise(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_SaltPepperNoise();
	double Pa, Pb, Pn;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_SaltPepperNoise };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
