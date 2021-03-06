// Dlg_GetFilterSize.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_GetFilterSize.h"
#include "afxdialogex.h"


// Dlg_GetFilterSize 对话框

IMPLEMENT_DYNAMIC(Dlg_GetFilterSize, CDialogEx)

Dlg_GetFilterSize::Dlg_GetFilterSize(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_GetFilterSize, pParent)
{
	filterSize = 5;
}

Dlg_GetFilterSize::~Dlg_GetFilterSize()
{
}

void Dlg_GetFilterSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GetFIlterSize, filterSize);
}


BEGIN_MESSAGE_MAP(Dlg_GetFilterSize, CDialogEx)
END_MESSAGE_MAP()


// Dlg_GetFilterSize 消息处理程序
