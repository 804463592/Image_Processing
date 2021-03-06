// Dlg_AdaptiveMedianFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_AdaptiveMedianFilter.h"
#include "afxdialogex.h"


// Dlg_AdaptiveMedianFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_AdaptiveMedianFilter, CDialogEx)

Dlg_AdaptiveMedianFilter::Dlg_AdaptiveMedianFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_AdaptiveMedianFilter, pParent),m_max(9),n_max(9),m_start(3),n_start(3)
{

}

Dlg_AdaptiveMedianFilter::~Dlg_AdaptiveMedianFilter()
{
}

void Dlg_AdaptiveMedianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AdaptiveMedianFilter_nmax, n_max);
	DDX_Text(pDX, IDC_EDIT_AdaptiveMedianFilter_mmax, m_max);

	DDX_Text(pDX, IDC_EDIT_AdaptiveMedian_mstart, m_start);
	DDX_Text(pDX, IDC_EDIT_AdaptiveMedian_nstart, n_start);
	
}


BEGIN_MESSAGE_MAP(Dlg_AdaptiveMedianFilter, CDialogEx)
	
END_MESSAGE_MAP()


// Dlg_AdaptiveMedianFilter 消息处理程序



