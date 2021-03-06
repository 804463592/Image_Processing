#pragma once


// Dlg_LowPassParameter 对话框

class Dlg_LowPassParameter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_LowPassParameter)

public:
	Dlg_LowPassParameter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_LowPassParameter();
	double Get_D0();
	BOOL Get_CheckBox_State();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_LowPassParameter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	double D0;
public:
	BOOL is_HighPass;

};
