#pragma once


// CDownGrey 对话框

class CDownGrey : public CDialogEx
{
	DECLARE_DYNAMIC(CDownGrey)

public:
	CDownGrey(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDownGrey();
	int Lowgrey;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DownGrey };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
};
