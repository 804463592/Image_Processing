// Dlg_RgbToHSI.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_RgbToHSI.h"
#include "afxdialogex.h"


// Dlg_RgbToHSI 对话框

IMPLEMENT_DYNAMIC(Dlg_RgbToHSI, CDialogEx)

Dlg_RgbToHSI::Dlg_RgbToHSI(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_RgbToHSI, pParent),H(TRUE),S(FALSE),I(FALSE)
{

}

Dlg_RgbToHSI::~Dlg_RgbToHSI()
{
}

void Dlg_RgbToHSI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_RADIO_H, H);
	DDX_Check(pDX, IDC_RADIO_S, S);
	DDX_Check(pDX, IDC_RADIO_I, I);


}


BEGIN_MESSAGE_MAP(Dlg_RgbToHSI, CDialogEx)
END_MESSAGE_MAP()


// Dlg_RgbToHSI 消息处理程序
