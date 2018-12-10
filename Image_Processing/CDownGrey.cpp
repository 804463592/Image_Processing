// CDownGrey.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "CDownGrey.h"
#include "afxdialogex.h"


// CDownGrey 对话框

IMPLEMENT_DYNAMIC(CDownGrey, CDialogEx)

CDownGrey::CDownGrey(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DownGrey, pParent)
{
	Lowgrey = 64;
}

CDownGrey::~CDownGrey()
{
}

void CDownGrey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Lowgrey);
}


BEGIN_MESSAGE_MAP(CDownGrey, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CDownGrey::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDownGrey 消息处理程序


void CDownGrey::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
