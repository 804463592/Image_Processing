// DownTimes.cpp : ʵ���ļ�

#include "stdafx.h"
#include "Image_Processing.h"
#include "DownTimes.h"
#include "afxdialogex.h"

// DownTimes �Ի���

IMPLEMENT_DYNAMIC(DownTimes, CDialogEx)

DownTimes::DownTimes(CWnd* pParent /*=NULL*/)
	: CDialogEx(DownTimes::IDD, pParent)
{
	m_downtimes = 0;
}

DownTimes::~DownTimes()
{
}

void DownTimes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIMES1, m_downtimes);  
}

BEGIN_MESSAGE_MAP(DownTimes, CDialogEx)
	/*
	��BEGIN_MESSAGE_MAP()��END_MESSAGE_MAP()���Ǻ궨��,����֮����������Ϣ��Ӧ����,Ϊÿ����Ϣ����������һ����ڡ�
	*/
END_MESSAGE_MAP()


// DownTimes ��Ϣ�������
