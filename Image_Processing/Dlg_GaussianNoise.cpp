// Dlg_GaussianNoise.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_GaussianNoise.h"
#include "afxdialogex.h"


// Dlg_GaussianNoise 对话框

IMPLEMENT_DYNAMIC(Dlg_GaussianNoise, CDialogEx)

Dlg_GaussianNoise::Dlg_GaussianNoise(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_GaussianNoise, pParent)
{
	mean = 2;
	sigma = 1.8;
	T = 50;
}

Dlg_GaussianNoise::~Dlg_GaussianNoise()
{



}

void Dlg_GaussianNoise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GaussianFilter_mean, mean);
	DDX_Text(pDX, IDC_EDIT_GaussianFilter_sigma, sigma);
	DDX_Text(pDX, IDC_EDIT_GaussianFilter_T, T);



}


BEGIN_MESSAGE_MAP(Dlg_GaussianNoise, CDialogEx)
END_MESSAGE_MAP()


// Dlg_GaussianNoise 消息处理程序
