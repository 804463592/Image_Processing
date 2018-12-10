#pragma once


// DownTimes 下采样对话框

class DownTimes : public CDialogEx
{
	DECLARE_DYNAMIC(DownTimes)

public:
	DownTimes(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DownTimes();

	// 对话框数据
	enum { IDD = IDD_DownTimes };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_downtimes;  //保存下采样次数
};
