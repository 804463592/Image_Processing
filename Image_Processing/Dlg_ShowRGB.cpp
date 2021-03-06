// Dlg_ShowRGB.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_ShowRGB.h"
#include "afxdialogex.h"


// Dlg_ShowRGB 对话框

IMPLEMENT_DYNAMIC(Dlg_ShowRGB, CDialogEx)

Dlg_ShowRGB::Dlg_ShowRGB(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_ShowRGB, pParent), r_check(1), g_check(1), b_check(1)
{

}

Dlg_ShowRGB::~Dlg_ShowRGB()
{
}

void Dlg_ShowRGB::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_R, r_check);
	DDX_Check(pDX, IDC_CHECK_G, g_check);
	DDX_Check(pDX, IDC_CHECK_B, b_check);

}


BEGIN_MESSAGE_MAP(Dlg_ShowRGB, CDialogEx)
	
END_MESSAGE_MAP()


// Dlg_ShowRGB 消息处理程序
