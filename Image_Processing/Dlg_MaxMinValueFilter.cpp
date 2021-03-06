// Dlg_MaxMinValueFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_MaxMinValueFilter.h"
#include "afxdialogex.h"


// Dlg_MaxMinValueFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_MaxMinValueFilter, CDialogEx)

Dlg_MaxMinValueFilter::Dlg_MaxMinValueFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_MaxMinValueFilter, pParent),maxcheck(1),mincheck(0),midcheck(0),m(5),n(5)
{
	
}

Dlg_MaxMinValueFilter::~Dlg_MaxMinValueFilter()
{
}

void Dlg_MaxMinValueFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//((CButton *)GetDlgItem(IDC_MaxValueFilter))->SetCheck(TRUE);

	DDX_Check(pDX, IDC_MaxValueFilter, maxcheck);

	DDX_Check(pDX, IDC_MinValueFilter, mincheck);

	DDX_Check(pDX, IDC_MidpointFilter, midcheck);

	DDX_Text(pDX, IDC_EDIT_MaxMinFilter_m, m);

	DDX_Text(pDX, IDC_EDIT_MaxMinFilter_n, n);

	//DDX_Control(pDX, IDC_MaxValueFilter, );

}


BEGIN_MESSAGE_MAP(Dlg_MaxMinValueFilter, CDialogEx)   //将控件与消息函数绑定

	ON_BN_CLICKED(IDC_MaxValueFilter, &Dlg_MaxMinValueFilter::OnBnClickedMaxRadio)   

	ON_BN_CLICKED(IDC_MinValueFilter, &Dlg_MaxMinValueFilter::OnBnClickedMinRadio)

	ON_BN_CLICKED(IDC_MidpointFilter, &Dlg_MaxMinValueFilter::OnBnClickedMIdpointRadio)

	ON_BN_CLICKED(IDC_BtnAddValue, &Dlg_MaxMinValueFilter::OnBnClickedAddValueBtn)  //不能写成::OnBnClickedAddValueBtn(),即不能加括号,使用的是函数名绑定的

	ON_BN_CLICKED(IDC_BtnSubValue, &Dlg_MaxMinValueFilter::OnBnClickedSubValueBtn)
	
END_MESSAGE_MAP()


// Dlg_MaxMinValueFilter 消息处理程序
void Dlg_MaxMinValueFilter::OnBnClickedMaxRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"选择了最大值滤波器");
}


void Dlg_MaxMinValueFilter::OnBnClickedMinRadio()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Dlg_MaxMinValueFilter::OnBnClickedMIdpointRadio()
{
	// TODO: 在此添加控件通知处理程序代码

	MessageBox(L"选择了中点滤波器");
}

void Dlg_MaxMinValueFilter::OnBnClickedAddValueBtn()
{
	//这两个加减按钮就是做着玩的,就当是学习下响应事件咯~~~~~~
	m++;
	UpdateData(FALSE); //FALSE才可以更新数据到控件显示,
	//如果UpdateData(TRUE) == 将控件的值赋值给成员变量;UpdateData(FALSE) == 将成员变量的值赋值给控件。
	if (m > 25) {

		MessageBox(L"m值已经过大,不能继续增加!!!");
		m = 25;
		UpdateData(FALSE);
	}

}

void Dlg_MaxMinValueFilter::OnBnClickedSubValueBtn()
{
	m--;
	UpdateData(FALSE); //FALSE才可以更新数据到控件显示,
	//如果UpdateData(TRUE) == 将控件的值赋值给成员变量;UpdateData(FALSE) == 将成员变量的值赋值给控件。
	
	if (0 > m) {
		MessageBox(L"m值过小,不能再继续减小!!!");
		m = 0;
		UpdateData(FALSE);
	}

}