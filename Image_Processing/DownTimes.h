#pragma once


// DownTimes �²����Ի���

class DownTimes : public CDialogEx
{
	DECLARE_DYNAMIC(DownTimes)

public:
	DownTimes(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DownTimes();

	// �Ի�������
	enum { IDD = IDD_DownTimes };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_downtimes;  //�����²�������
};
