// Dlg_SaltPepperNoise.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_SaltPepperNoise.h"
#include "afxdialogex.h"


// Dlg_SaltPepperNoise 对话框

IMPLEMENT_DYNAMIC(Dlg_SaltPepperNoise, CDialogEx)

Dlg_SaltPepperNoise::Dlg_SaltPepperNoise(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_SaltPepperNoise, pParent),Pa(0.3),Pb(0.3),Pn(0.2)
{

}

Dlg_SaltPepperNoise::~Dlg_SaltPepperNoise()
{
}

void Dlg_SaltPepperNoise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SaltPepperNoise_Pa, Pa);
	DDX_Text(pDX, IDC_EDIT_SaltPepperNoise_Pb, Pb);
	DDX_Text(pDX, IDC_EDIT_SaltPepperNoise_Pn, Pn);
}


BEGIN_MESSAGE_MAP(Dlg_SaltPepperNoise, CDialogEx)
END_MESSAGE_MAP()


// Dlg_SaltPepperNoise 消息处理程序
