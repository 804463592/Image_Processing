#pragma once


// Dlg_GetFilterSize 对话框

class Dlg_GetFilterSize : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_GetFilterSize)

public:
	Dlg_GetFilterSize(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_GetFilterSize();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_GetFilterSize };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	int filterSize;

};
