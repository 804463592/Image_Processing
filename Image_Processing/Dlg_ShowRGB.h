#pragma once


// Dlg_ShowRGB 对话框

class Dlg_ShowRGB : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_ShowRGB)

public:
	Dlg_ShowRGB(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_ShowRGB();
	BOOL r_check, g_check, b_check;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_ShowRGB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
