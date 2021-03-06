// Dlg_HarmonicFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_HarmonicFilter.h"
#include "afxdialogex.h"


// Dlg_HarmonicFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_HarmonicFilter, CDialogEx)

Dlg_HarmonicFilter::Dlg_HarmonicFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_HarmonicFilter, pParent),m(3),n(3)
{

}

Dlg_HarmonicFilter::~Dlg_HarmonicFilter()
{
}

void Dlg_HarmonicFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Harmonic_m, m);
	DDX_Text(pDX, IDC_EDIT_Harmonic_n, n); 

}


BEGIN_MESSAGE_MAP(Dlg_HarmonicFilter, CDialogEx)
END_MESSAGE_MAP()


// Dlg_HarmonicFilter 消息处理程序
