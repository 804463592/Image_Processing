// Dlg_LowPassParameter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_LowPassParameter.h"
#include "afxdialogex.h"


// Dlg_LowPassParameter 对话框

IMPLEMENT_DYNAMIC(Dlg_LowPassParameter, CDialogEx)

Dlg_LowPassParameter::Dlg_LowPassParameter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_LowPassParameter, pParent)
{
	D0 = 50;
	//is_HighPass = FALSE;


}

Dlg_LowPassParameter::~Dlg_LowPassParameter()
{
}

void Dlg_LowPassParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LowPass, D0);
	//DDX_Check(pDX, IDC_CHECK_HighPass, is_HighPass);  //可以使check控件关联一个bool变量

	is_HighPass = Get_CheckBox_State();  //也可以这样来获取check_box的勾选状态

}




BOOL Dlg_LowPassParameter::Get_CheckBox_State() {

	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_HighPass); //使用CButton成员函数来操作check_box状态
	BOOL HighPass = pBtn->GetCheck();

	return HighPass;
}

double Dlg_LowPassParameter::Get_D0() {

	return D0;
}



BEGIN_MESSAGE_MAP(Dlg_LowPassParameter, CDialogEx)
END_MESSAGE_MAP()


// Dlg_LowPassParameter 消息处理程序
