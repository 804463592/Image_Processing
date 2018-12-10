// Dlg_ContraHarmonicMeanFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_ContraHarmonicMeanFilter.h"
#include "afxdialogex.h"


// Dlg_ContraHarmonicMeanFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_ContraHarmonicMeanFilter, CDialogEx)

Dlg_ContraHarmonicMeanFilter::Dlg_ContraHarmonicMeanFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_ContraHarmonicMeanFilter, pParent),m(5),n(5),Q(1.5)
{

}

Dlg_ContraHarmonicMeanFilter::~Dlg_ContraHarmonicMeanFilter()
{
}

void Dlg_ContraHarmonicMeanFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ContraHarmonic_m,m);
	DDX_Text(pDX, IDC_EDIT_ContraHarmonic_n, n);
	DDX_Text(pDX, IDC_EDIT_ContraHarmonic_Q, Q);

}


BEGIN_MESSAGE_MAP(Dlg_ContraHarmonicMeanFilter, CDialogEx)
END_MESSAGE_MAP()


// Dlg_ContraHarmonicMeanFilter 消息处理程序
