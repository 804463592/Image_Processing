// Dlg_ButterWorthFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_ButterWorthFilter.h"
#include "afxdialogex.h"


// Dlg_ButterWorthFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_ButterWorthFilter, CDialogEx)

Dlg_ButterWorthFilter::Dlg_ButterWorthFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_ButterWorthFilter, pParent)
{
	D0 = 50;
	n = 3;
	is_HighPass = FALSE;
}

Dlg_ButterWorthFilter::~Dlg_ButterWorthFilter()
{
}

void Dlg_ButterWorthFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_ButterWorth_D0, D0);
	DDX_Text(pDX, IDC_EDIT_ButterWorth_N, n);
	DDX_Check(pDX, IDC_CHECK_ButterWorth_HighPass, is_HighPass);  //可以使check控件关联一个bool变量,也可以通过其他方法


}


BEGIN_MESSAGE_MAP(Dlg_ButterWorthFilter, CDialogEx)
END_MESSAGE_MAP()


// Dlg_ButterWorthFilter 消息处理程序
