#pragma once


// Dlg_RgbToHSI 对话框

class Dlg_RgbToHSI : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_RgbToHSI)

public:
	Dlg_RgbToHSI(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_RgbToHSI();
	BOOL H, S, I;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_RgbToHSI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
