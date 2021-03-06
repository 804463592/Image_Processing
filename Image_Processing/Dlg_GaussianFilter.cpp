// Dlg_GaussianFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_GaussianFilter.h"
#include "afxdialogex.h"


// Dlg_GaussianFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_GaussianFilter, CDialogEx)

Dlg_GaussianFilter::Dlg_GaussianFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_GaussianFilter, pParent)
{
	D0 = 50;
	is_HighPass = FALSE;
}

Dlg_GaussianFilter::~Dlg_GaussianFilter()
{
}

void Dlg_GaussianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GaussianFilter_D0, D0);
	DDX_Check(pDX, IDC_CHECK_GaussianFilter_IsHighPass, is_HighPass);
}


BEGIN_MESSAGE_MAP(Dlg_GaussianFilter, CDialogEx)
END_MESSAGE_MAP()


// Dlg_GaussianFilter 消息处理程序
