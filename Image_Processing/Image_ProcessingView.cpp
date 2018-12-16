
//修改的小细节~

//使用了github仓库 ~~~

//包含了github中图片文件

// Image_ProcessingView.cpp : CImage_ProcessingView 类的实现

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif
#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"

//自己添加的头文件,注意头文件的顺序,顺序不对有时候会产生莫名其妙的问题
#include "DownTimes.h"   //降低分辨率的对话框
#include "WarnDlg.h"     //降灰度级时,会将彩色图像转为灰度级,给出的警告窗口
#include "CDownGrey.h"     //用于获取降质后灰度级总数
#include "HistDrawDialg.h"  //由于HistDrawDialg中的定义,依赖于Image_ProcessingView,所以放在Image_ProcessingView前面的话,会出错
#include "MainFrm.h"
#include "Math.h"
#include "Dlg_GetFilterSize.h"  //对话框,用于获取滤波器模板大小
#include <algorithm>    //为了使用sort排序模板算法
#include "ComplexNum.h" //复数类
#include "DFT.h"    //使用FFT计算傅里叶变换的类
#include "Calculate.h"

#include "Dlg_LowPassParameter.h"  //用于理想滤波器
#include "Dlg_ButterWorthFilter.h"  //巴特沃斯滤波器
#include "Dlg_GaussianFilter.h"    //高斯滤波器
#include "Dlg_HarmonicFilter.h"      //谐波滤波器
#include "Dlg_ContraHarmonicMeanFilter.h"   //逆谐波滤波器

#include <vector>  //产生噪声时用到vector
using namespace std;
#include "Dlg_SaltPepperNoise.h"

#include "Dlg_MaxMinValueFilter.h"
#include "Dlg_AdaptiveMedianFilter.h"
#include "Dlg_GaussianNoise.h"
#include "Dlg_ShowRGB.h"
#include "Dlg_RgbToHSI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImage_ProcessingView

IMPLEMENT_DYNCREATE(CImage_ProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImage_ProcessingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImage_ProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CImage_ProcessingView::OnFileOpen)
	ON_COMMAND(IDM_DRAWLINE, &CImage_ProcessingView::OnDrawline)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImage_ProcessingView::OnFileSaveAs)
	ON_COMMAND(IDM_SHOWRED, &CImage_ProcessingView::OnShowred)
	//	ON_COMMAND(ID_VIEW_TOOLBAR, &CImage_ProcessingView::OnViewToolbar)


	ON_COMMAND(ID_TOGREY, &CImage_ProcessingView::OnTogrey)
	ON_COMMAND(ID_Down_sample, &CImage_ProcessingView::OnDownsample)
	ON_COMMAND(ID_Downgrey, &CImage_ProcessingView::OnDowngrey)
	ON_COMMAND(ID_IMG_Addition, &CImage_ProcessingView::OnImgAddition)
	ON_COMMAND(ID_Histgram, &CImage_ProcessingView::OnHistgram)
	ON_COMMAND(ID_HistBalance, &CImage_ProcessingView::OnHistbalance)
	ON_COMMAND(ID_HistMatch, &CImage_ProcessingView::OnHistmatch)
	ON_COMMAND(ID_MeanFilter, &CImage_ProcessingView::OnMeanfilter)
	ON_COMMAND(ID_MeadianFilter, &CImage_ProcessingView::OnMeadianfilter)
	ON_COMMAND(ID_FFT, &CImage_ProcessingView::OnFft)
	ON_COMMAND(ID_IFFT, &CImage_ProcessingView::OnIfft)
	ON_COMMAND(ID_LowPassFilter, &CImage_ProcessingView::OnLowpassfilter)
	ON_COMMAND(ID_ButterWorthFilter, &CImage_ProcessingView::OnButterworthfilter)
	ON_COMMAND(ID_Gaussian_Filter, &CImage_ProcessingView::OnGaussianFilter)
	ON_COMMAND(ID_Frequency_Domain_Shift, &CImage_ProcessingView::OnFrequencyDomainShift)
	ON_COMMAND(ID_GeometricMeanFilter, &CImage_ProcessingView::OnGeometricmeanfilter)
	ON_COMMAND(ID_HarmonicMeanFilter, &CImage_ProcessingView::OnHarmonicmeanfilter)
	ON_COMMAND(ID_ContraHarmonicMeanFilter, &CImage_ProcessingView::OnContraharmonicmeanfilter)
	ON_COMMAND(ID_SaltPepperNoise, &CImage_ProcessingView::OnSaltpeppernoise)
	ON_COMMAND(ID_ShowCopyImage, &CImage_ProcessingView::OnShowcopyimage)
	ON_COMMAND(ID_ShowProcessedImage, &CImage_ProcessingView::OnShowprocessedimage)
	ON_COMMAND(ID_ProcessImageBackup, &CImage_ProcessingView::OnProcessimagebackup)
	ON_COMMAND(ID_RestoreImage, &CImage_ProcessingView::OnRestoreimage)
	ON_COMMAND(ID_ContrastDisplay, &CImage_ProcessingView::OnContrastdisplay)
	ON_COMMAND(ID_MaxMinValueFilter, &CImage_ProcessingView::OnMaxMinvaluefilter)
	ON_COMMAND(ID_AdaptiveMedianFilter, &CImage_ProcessingView::OnAdaptivemedianfilter)
	ON_COMMAND(ID_GaussianNoise, &CImage_ProcessingView::OnGaussiannoise)
	ON_COMMAND(ID_HoughLineDetection, &CImage_ProcessingView::OnHoughlinedetection)
	ON_COMMAND(ID_SobleGrad, &CImage_ProcessingView::OnSoblegrad)
	ON_COMMAND(ID_ShowRGB, &CImage_ProcessingView::OnShowrgb)
	ON_COMMAND(ID_RGBToHSI, &CImage_ProcessingView::OnRgbtohsi)
END_MESSAGE_MAP()

// CImage_ProcessingView 构造/析构
CImage_ProcessingView::CImage_ProcessingView()
	: Times(1)
	, w(0)
	, h(0)
	, FTResult(NULL)
	, FftTime(0)
	, MouseX(0)
	, MouseY(0)
	, MouseX2(0)
	, MouseY2(0)
{
	// TODO: 在此处添加构造代码

}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//cs.lpszClass = _T("MyClassName");

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView 绘制 OnDraw()函数
void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//if (!m_Image.IsNull())
	//{
	//	m_Image.Draw(pDC->m_hDC,0,0); 
	//}


	//return;
	/////////////////////////////////////////设置背景颜色
	CRect   rect1;
	GetClientRect(rect1);
	if (m_Image.IsNull())
	{
		CRect   rect2;
		rect2.left = rect1.right / 3;
		rect2.top = rect1.bottom / 4;
		rect2.right = rect1.right * 2 / 3;
		rect2.bottom = rect1.bottom * 3 / 4;
		pDC->FillSolidRect(rect1, RGB(128, 128, 128));
		pDC->FillSolidRect(rect2, RGB(169, 169, 169));
	}

	//////////////////////////////////////////画图
	//Image_ProcessingDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	if (!m_Image.IsNull())
	{
		//CRect rect;
		//GetClientRect(&rect);
		//m_Image.X=rect.right/2-w/2;
		//m_Image.Y=rect.bottom/2-h/2;//重画时调整位置

		if (m_Image.Flag == 0)//FLAG为0,默认的显示方式
		{
			if (m_Image.GetWidth() > rect1.right)///////
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //重新设置背景颜色

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy显示

		}
		else if (m_Image.Flag == 1)//FLAG显示源图m_Image,与处理后的m_Imagecp,主要是进行对比,直方图匹配
		{
			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //重新设置背景颜色

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//显示处理图
			pDC->TextOut(m_Image.X + m_Image.GetWidth() / 2, m_Image.Y - 30, _T("处理图"));

			m_Imagecp.Draw(pDC->m_hDC, m_Imagecp.X, m_Imagecp.Y);//xy显示//原图的副本
			pDC->TextOut(m_Imagecp.X + m_Imagecp.GetWidth() / 2, m_Imagecp.Y - 30, _T("原始图"));

		}
		else if (m_Image.Flag == 2)//显示下采样图像,下采样相当于缩小图像尺寸
		{
			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}

			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //重新设置背景颜色

			image2.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);
			pDC->TextOut(m_Image.X + int(0.5*image2.GetWidth()), m_Image.Y - 30, _T("空间下采样图"));

			m_Imagecp.Draw(pDC->m_hDC, m_Imagecp.X, m_Imagecp.Y);//显示源图
			pDC->TextOut(m_Imagecp.X + m_Imagecp.GetWidth() / 2, m_Imagecp.Y - 30, _T("原始图"));

		}

		else if (m_Image.Flag == 3)//rgb分割前，取框中
		{
			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1, RGB(169, 169, 169)); //重新设置背景颜色

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy显示

			CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush = pDC->SelectObject(pBrush);
			pDC->Rectangle(CRect(CPoint(MouseX, MouseY), CPoint(MouseX2, MouseY2)));
			pDC->SelectObject(pOldBrush);
		}

		else if (m_Image.Flag == 4) { //用于直方图均衡后的显示

			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //重新设置背景颜色

			m_Imagecp.Draw(pDC->m_hDC, m_Imagecp.X, m_Imagecp.Y);//显示源图
			pDC->TextOut(m_Imagecp.X + m_Imagecp.GetWidth() / 2, m_Imagecp.Y - 30, _T("未均衡前的原始图"));

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy显示
			pDC->TextOut(m_Image.X + m_Image.GetWidth() / 2, m_Image.Y - 30, _T("直方图均衡效果图"));
		}

		if (m_Image.Flag == 5)//FLAG为5,显示m_Imagecp,拷贝图
		{
			if (m_Imagecp.GetWidth() > rect1.right)///////
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Imagecp.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Imagecp.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //重新设置背景颜色

			m_Imagecp.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy显示

		}


	}




	return;

}

void CImage_ProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

// CImage_ProcessingView 打印

void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImage_ProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImage_ProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CImage_ProcessingView 诊断

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

// CImage_ProcessingView 消息处理程序

void CImage_ProcessingView::OnFileOpen()
{
	//// TODO: 在此添加命令处理程序代码
	//CFileDialog dlg(TRUE);    //为打开文件创建一个变量

	//if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	//{
	//	if(!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
	//	m_Image.Load(dlg.GetPathName());//获得图片的地址，并且加载图片

	//	//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
	//	CSize sizeTotal;
	//	int w=m_Image.GetWidth();
	//	int h=m_Image.GetHeight();

	//	sizeTotal.cx =w;
	//	sizeTotal.cy =h;
	//	SetScrollSizes(MM_TEXT, sizeTotal);

	//	//Window_Image_w=m_Image.GetWidth();//获得图片的初始大小，为放大缩小功能做准备
	//	//Window_Image_h=m_Image.GetHeight();//

	//	Invalidate(1); //强制调用ONDRAW函数
	//}

	BOOL OpenFlage = 1;//记录是否成功打开了图片

	m_Image.Flag = 0;//设置FLAG

	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		if (!m_Imagecp.IsNull()) m_Imagecp.Destroy();//判断是否已经有图片，有的话进行清除

		while (S_FALSE == m_Image.Load(dlg.GetPathName()))
		{
			MessageBox(_T("打开的不是24位真彩色图！"));
			if (IDCANCEL == dlg.DoModal()) //重新打开图片；点击取消则跳出循环   
			{
				OpenFlage = 0;//没有打开图片就跳出循环
				break;
			}
		}//确保是24位彩色图片

		m_Imagecp.Load(dlg.GetPathName());//对原始图片备份,m_Image和m_Imagecp有同样的长宽,参数


		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		if (OpenFlage == 1)
		{
			CSize sizeTotal;
			w = m_Image.GetWidth();
			h = m_Image.GetHeight();


			CRect rect;
			GetClientRect(&rect);
			m_Image.X = max(0, rect.right / 2 - w / 2);
			m_Image.Y = max(0, rect.bottom / 2 - h / 2);//设置显示图片的左上角位置
			m_Imagecp.X = max(0, rect.right / 2 - w / 2);
			m_Imagecp.Y = max(0, rect.bottom / 2 - h / 2);//设置显示图片的左上角位置

			sizeTotal.cx = w;
			sizeTotal.cy = h;
			SetScrollSizes(MM_TEXT, sizeTotal);
		}

		//Window_Image_w=m_Image.GetWidth();//获得图片的初始大小，为放大缩小功能做准备
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //强制调用ONDRAW函数
	}

}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;

	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();

	for (int k = 0; k < w; k++)
	{
		m_Image.m_pBits[0][50][k] = 0;//B
		m_Image.m_pBits[1][50][k] = 0;//G
		m_Image.m_pBits[2][50][k] = 0;//R

	}


	Invalidate(1); //强制调用ONDRAW函数

}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {
		MessageBox(_T("你还没有打开一个要保存的图像文件！"));
		return;
	}
	CString strFilter;
	//strFilter ="位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";   
	strFilter = "所有文件|*.*||";   //

	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if (IDOK != dlg.DoModal())
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	//CString strExtension;
	//strFileName = dlg.m_ofn.lpstrFile;   //  获得文件名
	//if(dlg.m_ofn.nFileExtension == 0)     //获得文件扩展名
	//{
	//	switch (dlg.m_ofn.nFilterIndex)
	//	{
	//	case 1:
	//		strExtension = "bmp"; break;
	//	case 2:
	//		strExtension = "jpg"; break;
	//	case 3:
	//		strExtension = "gif"; break;
	//	case 4:
	//		strExtension = "png"; break;
	//	default:
	//		break;
	//	}
	//	strFileName = strFileName + _T(".") + strExtension;
	//	//strFileName="C:\\Users\\Lenovo\\Desktop\\QSanguosha-Qingming\\abc.bmp";
	//}

	// 图像保存
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image.m_pBits[0][j][k] = 0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image.m_pBits[1][j][k] = 0;//G


		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


//void CImage_ProcessingView::OnViewToolbar()
//{
//	// TODO: 在此添加命令处理程序代码
//}

void CImage_ProcessingView::OnTogrey()
{
	//// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;//恢复设置FLAG

	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < w; i++) {   //由于下面的m_pBits[][][]索引是按照通道,高度,宽度的方式索引的,因此两个for循环最好是先h,再w
		for (int j = 0; j < h; j++) {

			int b = (int)m_Image.m_pBits[0][j][i];
			int g = (int)m_Image.m_pBits[1][j][i];
			int r = (int)m_Image.m_pBits[2][j][i];
			int ave = (20 * r + 50 * g + 30 * b) / 100;
			m_Image.m_pBits[0][j][i] = (BYTE)ave;
			m_Image.m_pBits[1][j][i] = (BYTE)ave;
			m_Image.m_pBits[2][j][i] = (BYTE)ave;

		}
	}


	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像

}


void CImage_ProcessingView::OnDownsample()
{
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!image2.IsNull())//如果前面已经下采样过了，则此销毁旧的下采样保存的图片
	{
		image2.Destroy();
	}

	w = m_Image.GetWidth();//获得图像的宽度
	h = m_Image.GetHeight();//获得图像的高度

	DownTimes dlg;//建立对话框对象
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

		while (dlg.m_downtimes <= 0 || pow((double)2, (int)dlg.m_downtimes) > w || pow((double)2, (int)dlg.m_downtimes) > h)//判断是否输入有效的数字
		{
			MessageBox(_T("输入无效\n请重新输入有效的下采样次数"));
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		m_Image.Flag = 2;//记录FLAG,以便于在draw函数中画出下采样后的图

		//int T = pow((double)2, (int)dlg.m_downtimes);//下采样次数*2

		int T = (int)dlg.m_downtimes;

		image2.Create(w / T, h / T, 24);//全局变量Create后需要delete

		int nrow = image2.GetPitch();//获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc = (BYTE *)image2.GetBits();//获得CImage最后一行的像素地址
		/*将三维数组复制进m_CImage*/
		for (int j = 0; j < h / T; j++)
		{
			for (int k = 0; k < w / T; k++)
			{
				psrc[j*nrow + k * 3] = m_Image.m_pBits[0][j*T][k*T];//B
				psrc[j*nrow + k * 3 + 1] = m_Image.m_pBits[1][j*T][k*T];//G
				psrc[j*nrow + k * 3 + 2] = m_Image.m_pBits[2][j*T][k*T];//R

			}
		}

		m_Imagecp.X = 100;               //给出绘图位置,对比处理的效果
		m_Imagecp.Y = 100;
		m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
		m_Image.Y = m_Imagecp.Y;

		/*将三维数组复制进image2*/
		Invalidate(1);//强制调用ONDRAW函数，ONDRAW会绘制图像
	}
}


void CImage_ProcessingView::OnDowngrey()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;//设置FLAG,Flag=0表示默认的draw方式,显示m_Image

	//判断是否为彩色图片，若是则弹出降质警告///
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}
	//OnTogrey();//如果是彩色图：先转化为灰度图,当然,也可以不用这一步,毕竟最后的结果也是灰度图
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	CDownGrey dlg;   //对话框
	if (IDOK == dlg.DoModal())
	{
		UpdateData();
		while (dlg.Lowgrey <= 0 || dlg.Lowgrey > 256)
		{
			MessageBox(_T("灰度级无效，请重新输入灰度级！"));
			dlg.DoModal();
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}
		int Time = 256 / dlg.Lowgrey;//判断下采样次数  (采用最接近的灰度级)
	//int Time = 128;
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				BYTE b = m_Image.m_pBits[0][j][k];
				BYTE g = m_Image.m_pBits[1][j][k];
				BYTE r = m_Image.m_pBits[2][j][k];

				int average = (b + g + r) / 3;//随着降低次数增加，不断改变灰度值
				////ave必须是int类型////

				if (average > 255 / 2)//进行灰度变换算法
				{
					average = (average / Time + 1)*Time;
					if (average > 255)
						average = 255;
				}
				else
				{
					average = (average / Time)*Time;
					if (average < 0)
						average = 0;
				}

				m_Image.m_pBits[0][j][k] = average;
				m_Image.m_pBits[1][j][k] = average;
				m_Image.m_pBits[2][j][k] = average;
			}
		}
		Invalidate(1); //强制调用ONDRAW函数
	}
	//Times=1;//恢复Timees初值，图片相加要用！

}


void CImage_ProcessingView::OnImgAddition()
{
	// TODO: 在此添加命令处理程序代码
	Times++;
	float k = Times;
	//k=(k-1)/k;
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;//恢复设置FLAG
	w = m_Image.GetWidth();//获得第一幅图像的宽度
	h = m_Image.GetHeight();//获得图像的高度

	MyImage_ Image_Second;
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!Image_Second.IsNull()) Image_Second.Destroy();//判断是否已经有图片，有的话进行清除
		Image_Second.Load(dlg.GetPathName());//调用对话框的GetPathName获得图片的位置，并且调用Load加载图片
		if (Image_Second.IsNull()) return;
		if (w != Image_Second.GetWidth() || h != Image_Second.GetHeight())//判断两幅图像大小是否一致
		{
			MessageBox(_T("两幅图像大小不一致！"));
			return;
		}
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)//两幅图像做简单相加减操作
			{
				int tt = m_Image.m_pBits[0][j][i];
				//图像差分
				/*m_Image.m_pBits[0][j][i] = m_Image.m_pBits[0][j][i] - Image_Second.m_pBits[0][j][i];
				m_Image.m_pBits[1][j][i] = m_Image.m_pBits[1][j][i] - Image_Second.m_pBits[1][j][i];
				m_Image.m_pBits[2][j][i] = m_Image.m_pBits[2][j][i] - Image_Second.m_pBits[2][j][i];*/

				//图像相加去噪
				m_Image.m_pBits[0][j][i] = m_Image.m_pBits[0][j][i] * ((k - 1) / k) + Image_Second.m_pBits[0][j][i] * (1 / (k));
				m_Image.m_pBits[1][j][i] = m_Image.m_pBits[1][j][i] * ((k - 1) / k) + Image_Second.m_pBits[1][j][i] * (1 / (k));
				m_Image.m_pBits[2][j][i] = m_Image.m_pBits[2][j][i] * ((k - 1) / k) + Image_Second.m_pBits[2][j][i] * (1 / (k));

				tt = m_Image.m_pBits[0][j][i];
			}
		}
		Invalidate(1);
	}
}


void CImage_ProcessingView::OnHistgram()
{

	/*
直方图统计:
在原图m_Image上进行统计,并新建对话框显示
*/
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}
	//OnTogrey();//如果是彩色图：先转化为灰度图

	m_Image.GetHistgram();//调用成员函数,统计直方图

	//使用Dialg绘图
	HistDrawDialg dlg(this);
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistbalance()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	//判断是否为彩色图片，若是则弹出降质警告//
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}

	//OnTogrey();//如果是彩色图：将m_Image转化为灰度图,并保存在m_Image中,同时flag会变为1

	m_Image.Flag = 4;	//恢复FLAG为4,以对比的特殊方式显示

	m_Image.GetHistgram();//获取概率直方图统计,保存在m_Image.probability数组中

	long i, j;		//循环计数
	BYTE pixel1, pixel2, pixel3;		//像素值

	float temp[3][256];
	int   nRst[3][256];//映射表
	int nrow = m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();


	for (i = 0; i < 256; i++)
	{

		if (0 == i)
		{
			temp[0][0] = m_Image.probability[0][0];
			temp[1][0] = m_Image.probability[1][0];
			temp[2][0] = m_Image.probability[2][0];

		}
		else
		{
			temp[0][i] = temp[0][i - 1] + m_Image.probability[0][i];  //r通道,累积像素函数temp中的是概率,小于1的
			temp[1][i] = temp[1][i - 1] + m_Image.probability[0][i];  //g通道,累积像素函数
			temp[2][i] = temp[2][i - 1] + m_Image.probability[0][i];  //b通道,累积像素函数
		}
	}

	for (i = 0; i < 256; i++)
	{
		nRst[0][i] = (int)(255.0f * temp[0][i] + 0.5f);      //nRst[i],直方图均衡灰度变换映射
		nRst[1][i] = (int)(255.0f * temp[1][i] + 0.5f);
		nRst[2][i] = (int)(255.0f * temp[2][i] + 0.5f);

	}

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pixel1 = m_Image.m_pBits[0][j][i];
			pixel2 = m_Image.m_pBits[1][j][i];
			pixel3 = m_Image.m_pBits[2][j][i];

			m_Image.m_pBits[0][j][i] = (BYTE)(nRst[0][pixel1]);//注意是使用m_pBits
			m_Image.m_pBits[1][j][i] = (BYTE)(nRst[0][pixel1]);//不使用CImage的Getbits
			m_Image.m_pBits[2][j][i] = (BYTE)(nRst[0][pixel1]);//三个通道值一样
			//全部使用同一个通道的累积函数,如若各通道单独均衡化,最后显示会失真
			//彩色图像均衡化,可以转到hsv空间进行

		}
	}

	m_Imagecp.X = 100;               //给出绘图位置,对比处理的效果
	m_Imagecp.Y = 100;
	m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
	m_Image.Y = m_Imagecp.Y;

	Invalidate(1);

}


void CImage_ProcessingView::OnHistmatch()
{
	// TODO: 在此添加命令处理程序代码
	BOOL OpenFlage = 1;//记录是否成功打开了图片

	//获取目标直方图
	MyImage_  MatchImage;
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!MatchImage.IsNull())
			MatchImage.Destroy();//判断是否已经有图片，有的话进行清除

		while (S_FALSE == MatchImage.Load(dlg.GetPathName()))
		{
			MessageBox(_T("打开的不是24位真彩色图！"));
			if (IDCANCEL == dlg.DoModal()) //重新打开图片；点击取消则跳出循环   
			{
				OpenFlage = 0;
				return;
			}
		}
	}
	else
	{
		return;
	}

	MatchImage.GetHistgram();//获取Match概率直方图

	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}


	//判断是否为彩色图片，若是则弹出降质警告//
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}

	m_Image.GetHistgram();//获取概率直方图
	OnTogrey();//如果是彩色图：先转化为灰度图
	m_Image.Flag = 1;	//恢复FLAG

	float temp[3][256];
	long i, j;		//循环计数
	BYTE pixel;		//像素值
	int   nMap[3][256];//待求映射表
	int   npMap[3][256];//规定直方图的均衡化的映射表
	float fpPro[3][256];
	float  k = 1.0f / 256;
	for (i = 0; i < 256; i++)
	{
		fpPro[0][i] = MatchImage.probability[0][i];//规定化的概率
	}
	int MatchGrayRank = 256;//规定化的灰度级

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();


	//计算源图累计直方图 m_Image.probability
	for (i = 0; i < 256; i++)
	{
		if (0 == i)
		{
			temp[0][0] = m_Image.probability[0][0];
		}
		else
		{
			temp[0][i] = temp[0][i - 1] + m_Image.probability[0][i];
		}
		m_Image.probability[0][i] = temp[0][i];
	}

	//计算规定后的累计直方图
	for (i = 0; i < MatchGrayRank; i++)
	{
		if (i == 0)
		{
			temp[0][0] = fpPro[0][0];
		}
		else
		{
			temp[0][i] = temp[0][i - 1] + fpPro[0][i];
		}
		fpPro[0][i] = temp[0][i];
	}

	//计算规定化概率 经均衡化的映射表：npMap
	for (i = 0; i < MatchGrayRank; i++)
	{
		npMap[0][i] = (int)((MatchGrayRank - 1) * fpPro[0][i] + 0.5f);//必须减1！
	}

	//按照累积直方图概率的差值最小的原则,建立映射关系
	for (i = 0; i < 256; i++)
	{
		int m = 0;
		float min_value = 1.0f;//float型最小差值
		for (j = 0; j < MatchGrayRank; j++)
		{
			float now_value = 0.0f;
			if (m_Image.probability[0][i] - fpPro[0][j] >= 0.0f)
			{
				now_value = m_Image.probability[0][i] - fpPro[0][j];
			}
			else
			{
				now_value = fpPro[0][j] - m_Image.probability[0][i];
			}
			if (now_value < min_value)
			{
				m = j;//记录最小值位置
				min_value = now_value;//不断更新最小差值
			}
		}
		nMap[0][i] = npMap[0][m];//建立灰度映射表,有可能多个npMap的值对应一个nMap
	}

	//对个像素进行直方图规定化映射处理
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pixel = m_Image.m_pBits[0][j][i];

			m_Image.m_pBits[0][j][i] = (BYTE)(nMap[0][pixel]);//注意是使用m_pBits
			m_Image.m_pBits[1][j][i] = (BYTE)(nMap[0][pixel]);//不使用CImage的Getbits
			m_Image.m_pBits[2][j][i] = (BYTE)(nMap[0][pixel]);
		}
	}

	m_Imagecp.X = 100;               //给出绘图位置,对比处理的效果,否则无法显示
	m_Imagecp.Y = 100;
	m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
	m_Image.Y = m_Imagecp.Y;

	Invalidate(1);

}


void CImage_ProcessingView::OnMeanfilter()
{
	//均值滤波:m_Image上修改,也有点耗时,不过比中值滤波快
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();

	Dlg_GetFilterSize dlg;//建立对话框对象

	if (IDOK == dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if (m_Image.IsNull()) return;//判断图像是否为空,否则易出错

		//判断是否输入有效的数字
		while (dlg.filterSize % 2 == 0 || dlg.filterSize<0 || dlg.filterSize>w || dlg.filterSize > h)
		{
			MessageBox(_T("输入模板尺寸无效,请重新输入合适的正奇数值"));
			if (IDOK == dlg.DoModal())
			{
				//UpdateData();
			}
			else
			{
				return;
			}
		}

		long B = 0, G = 0, R = 0;//累加存储，使用BYTE类型会产生溢出,因为BYTE（unsigned char）最大只能等于255

		//创建新三维数组，用于暂存新图、没有初始化！
		BYTE *** newImageArr;
		newImageArr = new  BYTE **[3];//3个维度；分配内存  
		for (int i = 0; i < 3; i++)
		{
			newImageArr[i] = new  BYTE*[h];   //先H
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{
				newImageArr[i][j] = new BYTE[w];   //后W
			}
		}
		//int filter_size =13;  //先设定一个默认值,然后再考虑通过对话框来获取
		int filter_size = (int)dlg.filterSize;

		//由于处理速度不快,考虑创建一个进度条
		CProgressCtrl myProCtrl;
		CRect rect, proRect;
		GetClientRect(&rect);
		proRect.left = rect.left + rect.Width() / 2 - 100;
		proRect.top = rect.top + rect.Height() / 2 - 20;
		proRect.right = rect.right - rect.Width() / 2 + 100;
		proRect.bottom = rect.bottom - rect.Height() / 2 + 20;
		//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
		myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //创建位置、大小

		//均值滤波
		//设定i，j合理的取值范围，防止超出图片范围
		for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)

		{
			for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
			{
				R = 0, G = 0, B = 0;//新模板归零
				for (int k = -((filter_size - 1) / 2); k < (((filter_size - 1) / 2) + 1); k++)
				{
					for (int kk = -((filter_size - 1) / 2); kk < (((filter_size - 1) / 2) + 1); kk++)
					{
						B += m_Image.m_pBits[0][j + k][i + kk];//累加求和
						G += m_Image.m_pBits[1][j + k][i + kk];//累加求和
						R += m_Image.m_pBits[2][j + k][i + kk];//累加求和
					}
				}
				newImageArr[0][j][i] = B / (filter_size*filter_size);
				newImageArr[1][j][i] = G / (filter_size*filter_size);
				newImageArr[2][j][i] = R / (filter_size*filter_size);
			}
			double p;
			p = (double)j / (double)(h - ((filter_size - 1) / 2));
			int k = p * 100;

			myProCtrl.SetPos(k);  //更新进度条进度

		}

		//将新图赋予源图
		for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)//新图是没有初始化的!
		{
			for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
			{
				m_Image.m_pBits[0][j][i] = newImageArr[0][j][i];
				m_Image.m_pBits[1][j][i] = newImageArr[1][j][i];
				m_Image.m_pBits[2][j][i] = newImageArr[2][j][i];
			}
		}


		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < h; j++)
			{
				delete[] newImageArr[k][j];//回收内存
			}
			delete[] newImageArr[k];
		}
		delete[] newImageArr;


		Invalidate(1);
	}

}


void CImage_ProcessingView::OnMeadianfilter()
{
	//中值滤波:在m_Image上修改原图
	//注意:中值滤波很耗时
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	Dlg_GetFilterSize dlg; //用于获取滤波模板大小对话框

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();

	if (IDOK == dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while (dlg.filterSize % 2 == 0 || dlg.filterSize<0 || dlg.filterSize>w || dlg.filterSize > h)
		{
			MessageBox(_T("输入模板尺寸无效\n请重新输入合适的正奇数值"));
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}
	}
	else {
		return;
	}


	int filter_size = (int)dlg.filterSize;

	//不用在资源视图里面拖控件,直接生成一个进度条
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	GetClientRect(&rect);
	proRect.left = rect.left + rect.Width() / 2 - 100;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
	//myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //创建位置、大小
	myProCtrl.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTHREVERSE, proRect, this, 99); //创建位置、大小

	//三维数组存新图！
	BYTE *** newImageArr = nullptr;
	newImageArr = new  BYTE **[3];//3个维度；分配内存  
	for (int i = 0; i < 3; i++)
	{
		newImageArr[i] = new  BYTE*[h];   //先H
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			newImageArr[i][j] = new BYTE[w];   //后W
		}
	}

	//暂存数组，求取中值
	int *B, *G, *R;
	B = new int[filter_size*filter_size];
	G = new int[filter_size*filter_size];
	R = new int[filter_size*filter_size];

	int sz;//数组下标

	for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)//设定i，j合理的取值范围，防止超出图片范围
	{
		for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
		{
			sz = 0;
			for (int k = -((filter_size - 1) / 2); k < (((filter_size - 1) / 2) + 1); k++)//模板内循环
			{
				for (int kk = -((filter_size - 1) / 2); kk < (((filter_size - 1) / 2) + 1); kk++)
				{
					B[sz] = m_Image.m_pBits[0][j + k][i + kk];
					G[sz] = m_Image.m_pBits[1][j + k][i + kk];
					R[sz] = m_Image.m_pBits[2][j + k][i + kk];
					sz++;
				}
			}

			std::sort(B, B + filter_size * filter_size);//sort排序,需要 #include <algorithm>
			std::sort(G, G + filter_size * filter_size);//因为需要大量的排序,因此速度很慢
			std::sort(R, R + filter_size * filter_size);
			newImageArr[0][j][i] = B[(filter_size*filter_size - 1) / 2 + 1];//取中值
			newImageArr[1][j][i] = G[(filter_size*filter_size - 1) / 2 + 1];
			newImageArr[2][j][i] = R[(filter_size*filter_size - 1) / 2 + 1];
		}

		double p;
		p = (double)j / (double)(h - ((filter_size - 1) / 2));
		int k = p * 100;

		myProCtrl.SetPos(k);//因为处理速度很慢,故设置进度条显示进度！！

	}

	//将新图赋予源图
	for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)//新图是没有初始化的!
	{
		for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
		{
			m_Image.m_pBits[0][j][i] = newImageArr[0][j][i];
			m_Image.m_pBits[1][j][i] = newImageArr[1][j][i];
			m_Image.m_pBits[2][j][i] = newImageArr[2][j][i];
		}
	}

	//回收指针

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] newImageArr[i][j];//回收内存
		}
	}
	for (int i = 0; i < 3; i++)
	{
		delete[] newImageArr[i];
	}
	delete[] newImageArr;

	Invalidate(1);

}


void CImage_ProcessingView::OnFft()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();


	long i, j;					//i:行循环变量 ,j:列循环变量
	double dTmp;				//临时变量
	//w宽；h高
	long width = 1, height = 1;		//进行傅立叶变换的宽度和高度
	int width_power = 0, height_power = 0;		//wid hei :2的幂次数

	ComplexNum *pTd = new ComplexNum[sizeof(ComplexNum)*w*h];//为指向时域的指针分配内存
	ComplexNum *pFd = new ComplexNum[sizeof(ComplexNum)*w*h];//为指向频域的指针分配内存


////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）,同时可以保证边长全变为2的幂次方//////
	while (width * 2 <= w)
	{
		width *= 2;
		width_power++;
	}
	while (height * 2 <= h)
	{
		height *= 2;
		width_power++;
	}

	/////////初始化pTd//////////////
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pTd[i*width + j].re = 0;
			pTd[i*width + j].im = 0;
		}
	}

	/////////图像赋予pTd指针////////////////////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			pTd[j*width + i].re = pow((double)-1, (double)(i + j))*m_Image.m_pBits[0][j][i];//（-1)^(i+j)移动变换中心
		}
	}
	++FftTime;

	if (FTResult)  //如果FTResult不给初始化的话,在这里会出现异常
	{
		delete[]FTResult;								//如果变换结果指针有效，删除内存
	}

	FTResult = new ComplexNum[sizeof(ComplexNum)*w*h];	//为变换结果重新分配内存


//////////调用傅立叶变化函数Fourier////////////////////
	fourierTransform(pTd, w, h, pFd, this);

	/////////////保存结果/////////////

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			FTResult[width *i + j] = pTd[width *i + j];
		}


	////////////对数变换后显示结果/////////////////////////
	int **Ftmp;			//暂存二维数组wid*hei -> 【i】【j】
						//三维数组  是hei*wid -> 【j】【i】

	//////////////分配内存/////////////////////
	Ftmp = new int *[width];
	double maxF(1);//变换后最大的系数
	int s(1);	//对数变换系数
	for (i = 0; i < width; i++)
	{
		Ftmp[i] = new int[height];
	}

	//////////////导入暂存二维数组///////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			dTmp = pTd[j*width + i].re*pTd[j*width + i].re + pTd[j*width + i].im*pTd[j*width + i].im;
			dTmp = sqrt(dTmp) / 100;
			if (maxF < dTmp)
			{
				maxF = dTmp;//保存最大值
			}
			Ftmp[i][j] = dTmp;
		}
	}
	double maxx = 0;
	double v = 2;//底数
	///////////////进行对数变换///////////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			long double p = Ftmp[i][j];
			//p=p/maxF;
			//p=(log(1+v*p)/log(v));
			Ftmp[i][j] = (log(1 + p) / log(v));
			if (maxx < Ftmp[i][j])
			{
				maxx = Ftmp[i][j];
			}

		}
	}
	double pq = 255 / maxx;//占比例
   ///////////////////返回至源图////////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			double p = Ftmp[i][j];
			m_Image.m_pBits[2][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[0][j][i] = min(pq*Ftmp[i][j], 255);

		}
	}

	//////////////////回收暂存数组指针////////////////
	for (i = 0; i < width; i++)
	{
		delete[]Ftmp[i];
	}
	delete[]Ftmp;

	delete[]pTd;
	delete[]pFd;
	Invalidate(TRUE);

}


void CImage_ProcessingView::OnIfft()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	if (!FftTime) //判断图像是否为空
	{
		MessageBox(_T("请先傅立叶变换！"));
		return;
	}

	m_Image.Flag = 0;	//恢复FLAG
	--FftTime;

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();


	double dTmp;				//临时变量
	long i, j;					//i:行循环变量 ,j:列循环变量
	//w宽；h高
	long wid = 1, hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor = 0, heipor = 0;		//wid hei :2的幂次数

	ComplexNum *pTd = new ComplexNum[sizeof(ComplexNum)*w*h];//为指向时域的指针分配内存
	ComplexNum *pFd = new ComplexNum[sizeof(ComplexNum)*w*h];//为指向频域的指针分配内存

//////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
	while (wid * 2 <= w)
	{
		wid *= 2;
		widpor++;
	}
	while (hei * 2 <= h)
	{
		hei *= 2;
		heipor++;
	}

	/////////初始化pTd//////////////
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = FTResult[i*wid + j].re;
			pTd[i*wid + j].im = -FTResult[i*wid + j].im;//共轭
		}
	}

	//////////调用傅立叶变化函数Fourier////////////////////
	fourierTransform(pTd, w, h, pFd, this);

	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			dTmp = pTd[i*wid + j].re;
			dTmp = pTd[i*wid + j].im;
			pTd[i*wid + j].re = pTd[i*wid + j].re / (double)(wid*hei);
			pTd[i*wid + j].im = -pTd[i*wid + j].im / (double)(wid*hei);//共轭
		}
	}

	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{

			m_Image.m_pBits[2][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[0][j][i] = pow((double)-1, (double)(i + j))*pTd[j*wid + i].re;
			//m_Image.m_pBits[1][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
			//m_Image.m_pBits[2][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
		}
	}

	///////////回收指针内存/////////////
	delete[]pTd;
	delete[]pFd;

	Invalidate(TRUE);

}


void CImage_ProcessingView::OnLowpassfilter()
{
	//函数名为低通滤波器,但是可以变为高通

	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//MessageBox(_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("请先进行傅立叶变换！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();
	//制作滤波器模板
	double **lpfilter;
	lpfilter = new double*[w];
	for (int i = 0; i < w; i++)
	{
		lpfilter[i] = new double[h];
	}

	double D;     //定义D0
	BOOL IsHighPass;
	Dlg_LowPassParameter dlg_lowpass;
	if (IDOK == dlg_lowpass.DoModal()) {

		UpdateData();

		D = dlg_lowpass.Get_D0();
		IsHighPass = dlg_lowpass.is_HighPass;

	}
	else {

		return;
	}

	//频率滤波函数H(u,v),使用lpfilter表示
	int high_end(1), low_end(0);
	if (TRUE == IsHighPass) {  //判断是否需要反转变为高通滤波器
		high_end = 0;
		low_end = 1;
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if ((pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)) <= D * D)
			{
				lpfilter[i][j] = high_end;   //理想低(高)通滤波器,因此小(高)于截至频率则通过
			}
			else {

				lpfilter[i][j] = low_end;
			}

		}
	}

	//进行理想低通滤波,H(u,v)与傅里叶变换结果FTResult相乘
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = lpfilter[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = lpfilter[j][i] * FTResult[w *i + j].re;
		}


	//回收指针内存
	for (int i = 0; i < w; i++)
	{
		delete[]lpfilter[i];
	}
	delete[]lpfilter;

	//调用IFFT进行反变换,得到空间域的结果
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnButterworthfilter()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("请先进行傅立叶变换！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();
	//制作模板
	double **btw_filter;
	btw_filter = new double*[w];
	for (int i = 0; i < w; i++)
	{
		btw_filter[i] = new double[h];
	}

	int n;
	double D;
	BOOL isHighPass(FALSE);

	Dlg_ButterWorthFilter dlg_butterworth;

	if (IDOK == dlg_butterworth.DoModal()) {

		UpdateData();

		D = dlg_butterworth.D0;
		n = dlg_butterworth.n;
		isHighPass = dlg_butterworth.is_HighPass;
	}
	else {
		return;
	}


	if (!isHighPass) { //低通

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				btw_filter[i][j] = 1.0 / (pow((pow((pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)), 0.5) / D), (double)2 * n) + 1);

			}
		}
	}
	else { //高通

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				btw_filter[i][j] = 1.0 / (pow((pow(D / (pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)), 0.5)), (double)2 * n) + 1);

			}
		}

	}
	//ButterWorth滤波
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = btw_filter[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = btw_filter[j][i] * FTResult[w *i + j].re;
		}



	//回收指针内存
	for (int i = 0; i < w; i++)
	{
		delete[]btw_filter[i];
	}
	delete[]btw_filter;

	//调用IFFT,进行反变换
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnGaussianFilter()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("请先进行傅立叶变换！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();
	//制作模板
	double **gaussian_filter;
	gaussian_filter = new double*[w];
	for (int i = 0; i < w; i++)
	{
		gaussian_filter[i] = new double[h];
	}


	double D;
	BOOL isHighPass;

	Dlg_GaussianFilter dlg_Gauss;
	if (IDOK == dlg_Gauss.DoModal()) {

		UpdateData(); //貌似没有这句,也正常???
		D = dlg_Gauss.D0;
		isHighPass = dlg_Gauss.is_HighPass;
	}
	else {
		return;
	}
	//判断是否为高通滤波器
	if (!isHighPass) {

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				double r1, r2;
				r1 = (pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2));
				r2 = (double)2 * D*D;
				gaussian_filter[i][j] = exp(-r1 / r2);
			}
		}
	}
	else {

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				double r1, r2;
				r1 = (pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2));
				r2 = (double)2 * D*D;
				gaussian_filter[i][j] = 1 - exp(-r1 / r2);

			}
		}

	}
	//Gaussian滤波
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = gaussian_filter[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = gaussian_filter[j][i] * FTResult[w *i + j].re;
		}

	//回收指针内存
	for (int i = 0; i < w; i++)
	{
		delete[]gaussian_filter[i];
	}
	delete[]gaussian_filter;

	//调用IFFT
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnFrequencyDomainShift()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("请先进行傅立叶变换！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	w = m_Image.GetWidth();//获取高度和宽度
	h = m_Image.GetHeight();

	ComplexNum **pCS;

	pCS = new ComplexNum *[sizeof(ComplexNum)*w*h];//为指向时域的指针分配内存
	for (int i = 0; i < w; i++)
	{
		pCS[i] = new ComplexNum[h];
	}

	int u0(10), v0(10);

	//////频域平移,为什么会出现很多条纹????
	//for (int i = 0; i < h; i++)
	//	for (int j = 0; j < w; j++)
	//	{
	//		FTResult[w *i + j].im = FTResult[w *((i + u0) % h) + (j + v0) % w].im;
	//		FTResult[w *i + j].re = FTResult[w *((i + u0) % h) + (j + v0) % w].re;
	//	}

	/////频域旋转,为啥不影响原图????
	double D;
	double Pi = 3.141592653;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{

			double o1, o2;
			o1 = u0 * i / w + v0 * j / h;
			o2 = -2 * Pi*o1;
			pCS[i][j].re = cos(o2);
			pCS[i][j].im = sin(o2);

		}

	}

	//修改傅里叶变换结果 
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			/*	FTResult[w *i + j].im = FSMul(pCS[i][j], FTResult[w *i + j]).im;
				FTResult[w *i + j].re = FSMul(pCS[i][j], FTResult[w *i + j]).re;*/
			FTResult[w *i + j].im = pCS[i][j].im*FTResult[w *i + j].im;
			FTResult[w *i + j].re = pCS[i][j].re* FTResult[w *i + j].re;
		}


	//回收指针内存
	for (int i = 0; i < w; i++)
	{
		delete[]pCS[i];
	}
	delete[]pCS;

	//调用IFFT
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnGeometricmeanfilter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//定义几何均值滤波器需要的参数,滤波模板长宽m,n,正奇数

	int m = 5, n = 9;  //必须为正奇数,否则后面滤波的时候会出错

	//TODO:建立对话框,并判断参数合法性
	Dlg_GetFilterSize size_dlg;

	if (IDOK == size_dlg.DoModal()) {

		//TODO:判断m,n是否为正奇数
		//判断是否输入有效的数字
		while (size_dlg.filterSize % 2 == 0 || size_dlg.filterSize<0 || size_dlg.filterSize>w || size_dlg.filterSize > h)
		{
			MessageBox(_T("输入模板尺寸无效\n请重新输入合适的正奇数值"));
			if (IDOK == size_dlg.DoModal())
			{
				UpdateData();
			}
		}
		UpdateData();
		m = size_dlg.filterSize;
		n = m;
	}
	else {
		return;//不带返回值的return语句只能用于返回类型为void的函数，return语句是为了引起函数的强制结束，这种用法类似于循环结构中的break语句的作用。
	}

	//定义一些迭代参数
	long  double R = 1, G = 1, B = 1;  //如果不加double,处理后结果为全黑的,因为长整形R,G,B如果乘以小数,结果为0的

	BYTE*** newImagePtr = new BYTE**[3]; //三维数组分配内存,释放内存时顺序要相反  
	for (int i = 0; i < 3; i++)
	{
		newImagePtr[i] = new  BYTE*[h];   //先H

		for (int j = 0; j < h; j++)
		{
			newImagePtr[i][j] = new BYTE[w];   //后W
		}
	}

	//TODO:几何均值滤波
	for (int i = int((m - 1) / 2); i < (h - (m - 1) / 2); i++)
	{
		for (int j = int((n - 1) / 2); j < (w - (n - 1) / 2); j++) {
			R = 1.0;
			G = 1.0;
			B = 1.0;
			for (int p = -(m - 1) / 2; p < ((m - 1) / 2 + 1); p++) {

				for (int q = -(n - 1) / 2; q < ((n - 1) / 2 + 1); q++)
				{
					//如果先乘起来,最后再开方,值会过大,毕竟最大可以达到255^(m*n);因此每次先开方那个,最后再乘起来
					B = (double)B * pow((double)m_Image.m_pBits[0][i + p][j + q], (double)1.0 / (double)(m*n));//R,G,B如果为long, 乘以一个小数就为0了
					G = (double)G * pow((double)m_Image.m_pBits[1][i + p][j + q], (double)1.0 / (double)(m*n));
					R = (double)R * pow((double)m_Image.m_pBits[2][i + p][j + q], (double)1.0 / (double)(m*n));

				}
			}
			//R =(int)pow((double)R, (double)(1.0 / (m*n))); //如果要这么做,前面就需要直接灰度值累乘,数值过大,最好不要这么做
			//G =(int)pow((double)G, (double)(1.0 / (m*n)));
			//B =(int)pow((double)B, (double)(1.0 / (m*n)));

			newImagePtr[0][i][j] = B;
			newImagePtr[1][i][j] = G;
			newImagePtr[2][i][j] = R;

		}
	}

	for (int i = int((m - 1) / 2); i < (h - (m - 1) / 2); i++)  //修改源图
	{
		for (int j = int((n - 1) / 2); j < (w - (n - 1) / 2); j++) {


			m_Image.m_pBits[0][i][j] = newImagePtr[0][i][j];
			m_Image.m_pBits[1][i][j] = newImagePtr[1][i][j];
			m_Image.m_pBits[2][i][j] = newImagePtr[2][i][j];

		}
	}

	////回收指针,三维数组的内存释放,delete

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] newImagePtr[i][j];//回收内存
		}
		delete[] newImagePtr[i];

	}
	delete[] newImagePtr;

	Invalidate(1);

}


void CImage_ProcessingView::OnHarmonicmeanfilter()
{
	// TODO: 在此添加命令处理程序代码，谐波均值滤波
	if (m_Image.IsNull()) {

		OnFileOpen();
		//return;//可以不return,打开图片就直接滤波了
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	int m = 5, n = 3; //正奇数

	Dlg_HarmonicFilter har_dlg;

	if (IDOK == har_dlg.DoModal()) {

		while (har_dlg.m % 2 == 0 || har_dlg.m<0 || har_dlg.m>w || har_dlg.m > h || har_dlg.n % 2 == 0 || har_dlg.n<0 || har_dlg.n>w || har_dlg.n > h)
		{
			MessageBox(_T("输入的滤波参数无效,请重新输入合适的正奇数值"));
			if (IDOK == har_dlg.DoModal())
			{
				UpdateData();
			}
		}
		m = har_dlg.m;
		n = har_dlg.n;

	}
	else {
		return;
	}

	double B = 0, G = 0, R = 0;

	//分配数组内存

	BYTE *** newImageArray = new BYTE**[3];

	for (int i = 0; i < 3; i++) {

		newImageArray[i] = new BYTE*[h];
		for (int j = 0; j < h; j++) {

			newImageArray[i][j] = new BYTE[w];
		}

	}

	//初始化为一个全黑的图像
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int k = 0; k < 3; k++) {

				newImageArray[k][i][j] = 1;
			}
		}

	}

	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++) {
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++) {
			B = 0;
			G = 0;
			R = 0;

			for (int p = -(m - 1) / 2; p < ((m - 1) / 2 + 1); p++) {
				for (int q = -(n - 1) / 2; q < ((n - 1) / 2 + 1); q++)
				{
					B += (double)1 / m_Image.m_pBits[0][i + p][j + q]; //倒数求和
					G += (double)1 / m_Image.m_pBits[1][i + p][j + q];
					R += (double)1 / m_Image.m_pBits[2][i + p][j + q];
				}
			}
			newImageArray[0][i][j] = (BYTE)m*n / B;//谐波均值滤波

			newImageArray[1][i][j] = (BYTE)m*n / G;
			newImageArray[2][i][j] = (BYTE)m*n / R;

		}
	}

	//将滤波结果赋予原图
	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
	{
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
		{
			m_Image.m_pBits[0][i][j] = newImageArray[0][i][j];
			m_Image.m_pBits[1][i][j] = newImageArray[1][i][j];
			m_Image.m_pBits[2][i][j] = newImageArray[2][i][j];

		}
	}

	//TODO:释放newImageArray数组内存,与new的顺序刚好相反
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < h; j++) {

			delete[] newImageArray[i][j];
		}
		delete[]newImageArray[i];
	}
	delete[]newImageArray;

	Invalidate(1);
}


void CImage_ProcessingView::OnContraharmonicmeanfilter()
{

	// TODO: 在此添加命令处理程序代码：逆谐波均值滤波器
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;//可以不return,打开图片就直接滤波了
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	int m = 5, n = 5; //正奇数
	double Q = 1.5;

	Dlg_ContraHarmonicMeanFilter contra_dlg;

	if (IDOK == contra_dlg.DoModal()) {

		while (contra_dlg.m % 2 == 0 || contra_dlg.m<0 || contra_dlg.m>w || contra_dlg.m > h || contra_dlg.n % 2 == 0 || contra_dlg.n<0 || contra_dlg.n>w || contra_dlg.n > h)
		{
			MessageBox(_T("输入的滤波参数m,n无效,请重新输入合适的正奇数值"));
			if (IDOK == contra_dlg.DoModal())
			{
				UpdateData();
			}
		}
		m = contra_dlg.m;
		n = contra_dlg.n;
		Q = contra_dlg.Q;

	}
	else {
		return;
	}

	//每次累加的分子和分母,up和low
	long double Bu = 0, Gu = 0, Ru = 0;
	long double Bl = 0, Gl = 0, Rl = 0;

	//分配数组内存

	BYTE *** newImageArray = new BYTE**[3];

	for (int i = 0; i < 3; i++) {

		newImageArray[i] = new BYTE*[h];
		for (int j = 0; j < h; j++) {

			newImageArray[i][j] = new BYTE[w];
		}

	}

	//初始化为一个全黑的图像
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int k = 0; k < 3; k++) {

				newImageArray[k][i][j] = 1;
			}
		}

	}

	//不用在资源视图里面拖控件,直接生成一个进度条
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	GetClientRect(&rect);
	proRect.left = rect.left + rect.Width() / 2 - 80;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
	myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //创建位置、大小
	//myProCtrl.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTHREVERSE, proRect, this, 99); //创建位置、大小


	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++) {
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++) {
			Bu = 0;
			Gu = 0;
			Ru = 0;
			Bl = 0;
			Gl = 0;
			Rl = 0;

			for (int p = -(m - 1) / 2; p < ((m - 1) / 2 + 1); p++) {
				for (int q = -(n - 1) / 2; q < ((n - 1) / 2 + 1); q++)
				{
					Bu += (double)pow(m_Image.m_pBits[0][i + p][j + q], Q + 1); //幂次项求和
					Gu += (double)pow(m_Image.m_pBits[1][i + p][j + q], Q + 1);
					Ru += (double)pow(m_Image.m_pBits[2][i + p][j + q], Q + 1);

					Bl += (double)pow(m_Image.m_pBits[0][i + p][j + q], Q); //幂次项求和
					Gl += (double)pow(m_Image.m_pBits[1][i + p][j + q], Q);
					Rl += (double)pow(m_Image.m_pBits[2][i + p][j + q], Q);
				}
			}

			newImageArray[0][i][j] = (BYTE)(Bu / Bl);//逆谐波均值滤波
			newImageArray[1][i][j] = (BYTE)(Gu / Gl);
			newImageArray[2][i][j] = (BYTE)(Ru / Rl);

		}

		//因为处理速度很慢,故设置进度条显示进度！！
		double p = (double)i / (double)((m + n - 2) / 2); //这个可以任意修改,只要进度条速度与实际处理速度差不多就行
		myProCtrl.SetPos(p);//如果直接SetPos(i)会导致,进度条已经到底了,但是还没有处理完

	}

	//将滤波结果赋予原图
	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
	{
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
		{
			m_Image.m_pBits[0][i][j] = newImageArray[0][i][j];
			m_Image.m_pBits[1][i][j] = newImageArray[1][i][j];
			m_Image.m_pBits[2][i][j] = newImageArray[2][i][j];

		}
	}

	//TODO:释放newImageArray数组内存,与new的顺序刚好相反
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < h; j++) {

			delete[] newImageArray[i][j];
		}
		delete[]newImageArray[i];
	}
	delete[]newImageArray;

	Invalidate(1);
}


void CImage_ProcessingView::OnSaltpeppernoise()
{
	// TODO: 在此添加命令处理程序代码
	if (true == m_Image.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	double p_salt(0.4), p_pepper(0.4);
	int n = 10000;

	//TODO:建立对话框,并判断p_salt与p_pepper,以及n的合法性
	Dlg_SaltPepperNoise sp_dlg;
	if (IDOK == sp_dlg.DoModal()) {

		while (sp_dlg.Pa < 0 || sp_dlg.Pb < 0 || sp_dlg.Pn < 0 || sp_dlg.Pa >1 || sp_dlg.Pb >1 || sp_dlg.Pn >1 || (sp_dlg.Pa + sp_dlg.Pb) > 1)
		{
			if (sp_dlg.Pa < 0 || sp_dlg.Pb < 0 || sp_dlg.Pn < 0 || sp_dlg.Pa >1 || sp_dlg.Pb >1 || sp_dlg.Pn >1)
			{
				MessageBox(L"概率与受污染程度均必须在0~1之间,请重新输入!");
				//sp_dlg.DoModal();  //DoModal()会自动调用UpdateData(),不必写UpdateData()
				if (IDOK == sp_dlg.DoModal())
				{
					//UpdateData();
				}
				else
				{
					return;
				}
			}
			if ((sp_dlg.Pa + sp_dlg.Pb) > 1)
			{
				MessageBox(L"Pa与Pb之和必须小于1,请重新输入!");
				//sp_dlg.DoModal();

				if (IDOK == sp_dlg.DoModal())
				{
					//UpdateData();
				}
				else {
					return;
				}
			}
		}

		p_pepper = sp_dlg.Pa;
		p_salt = sp_dlg.Pb;
		n = (int)(w*h*sp_dlg.Pn);

	}
	else {
		return;  //没有这句的话,点"取消"都无法取消
	}

	//直接定义数组要求使用常数,不能外部输入,因此使用vector是为了动态增加,可以控制椒盐噪声各自出现的概率,以及控制噪声程度
	std::vector<int> idxSalt_x, idxSalt_y;
	std::vector<int> idxPepper_x, idxPepper_y;//好像使用动态数组分配也可以,new,delete,忘了

	for (int k = 0; k < n; k++) {
		int ran = rand() % n;  //rand()产生0~???之间的整数
		if (ran < (int)(n*p_salt)) {
			idxSalt_x.push_back(rand() % w); //产生一个盐噪声的坐标
			idxSalt_y.push_back(rand() % h);
		}
		else if (ran > (int)(n*p_salt) && ran < (int)(n*(p_pepper + p_salt)))
		{
			idxPepper_x.push_back(rand() % w); //产生一个胡椒噪声的坐标点
			idxPepper_y.push_back(rand() % h);
		}
		else {
			//do nothing
		}

	}

	//使用vector下标操作虽然简单,但是使用迭代器效率更高,这里要注意,iter1,iter2必须同步增加,因此写在一个for循环而不是两个

	for (std::vector<int>::iterator
		iter1 = idxSalt_x.begin(), iter2 = idxSalt_y.begin();
		iter1 != idxSalt_x.end(), iter2 != idxSalt_y.end();  //使用动态数组,代码就会简单很多啊!!!!!!!!当时忘了
		iter1++, iter2++)
	{
		for (int i = 0; i < 3; i++) {
			m_Image.m_pBits[i][*iter2][*iter1] = 255; //盐噪声

		}
	}
	//必须与上面的for循环分开写,因为两个当Pa !=Pb时,vector可能size不一样

	for (std::vector<int>::iterator iter3 = idxPepper_x.begin(), iter4 = idxPepper_y.begin();
		iter3 != idxPepper_x.end(), iter4 != idxPepper_y.end(); iter3++, iter4++)
	{
		for (int i = 0; i < 3; i++)
		{
			m_Image.m_pBits[i][*iter4][*iter3] = 1;  //胡椒噪声
		}

	}

	Invalidate(1);
}


void CImage_ProcessingView::OnGaussiannoise()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	double mean(2);
	double sigma(1.8);
	int T(50);

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	Dlg_GaussianNoise dlg;
	if (IDOK == dlg.DoModal())
	{

		while (dlg.T < 0 || dlg.T > 100 || dlg.sigma < 0)
		{
			MessageBox(L"请输入合法的噪声参数!");
			if (IDOK == dlg.DoModal())
			{
				//UpdateData();
			}
			else {
				return;
			}
		}

		mean = dlg.mean;
		sigma = dlg.sigma;
		T = dlg.T;
	}
	else {

		return;
	}


	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			//产生高斯随机序列
			//方法由Marsaglia和Bray在1964年提出,C++版本: mu是均值,sigma是方差,X服从N(0,1)分布
			static double V1, V2, S;
			static int phase = 0;
			double X;
			double U1, U2;
			if (phase == 0)
			{
				do
				{
					U1 = (double)rand() / RAND_MAX;
					U2 = (double)rand() / RAND_MAX;
					V1 = 2 * U1 - 1;
					V2 = 2 * U2 - 1;
					S = V1 * V1 + V2 * V2;
				} while (S >= 1 || S == 0);
				X = V1 * sqrt(-2 * log(S) / S);
			}
			else
			{
				X = V2 * sqrt(-2 * log(S) / S);

			}
			phase = 1 - phase;

			int g_noise = (int)(mean + sigma * X) *T;


			//三个通道,各自处理
			for (int k = 0; k < 3; k++)
			{
				if (m_Image.m_pBits[k][i][j] + g_noise > 255)
				{
					m_Image.m_pBits[k][i][j] = 255;

				}
				else if (m_Image.m_pBits[k][i][j] + g_noise < 0)
				{
					m_Image.m_pBits[k][i][j] = 0;
				}
				else
				{
					m_Image.m_pBits[k][i][j] = m_Image.m_pBits[k][i][j] + g_noise;
				}

			}

		}

	}

	Invalidate(TRUE);
}


void CImage_ProcessingView::OnShowcopyimage()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 5;

	Invalidate(1);
}


void CImage_ProcessingView::OnShowprocessedimage()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	Invalidate(1);
}


void CImage_ProcessingView::OnProcessimagebackup()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Imagecp.m_pBits[k][i][j] = m_Image.m_pBits[k][i][j];
			}
		}
	}

	Invalidate(1);
}


void CImage_ProcessingView::OnRestoreimage()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[k][i][j] = m_Imagecp.m_pBits[k][i][j];
			}
		}
	}

	Invalidate(1);

}


void CImage_ProcessingView::OnContrastdisplay()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 1;

	m_Imagecp.X = 100;               //给出绘图位置,对比处理的效果
	m_Imagecp.Y = 100;
	m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
	m_Image.Y = m_Imagecp.Y;

	Invalidate(1);
}


void CImage_ProcessingView::OnMaxMinvaluefilter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}

	Dlg_MaxMinValueFilter dlg;
	BOOL maxcheck, mincheck, midcheck;
	int m(5), n(5);  //滤波模板边长

	if (IDOK == dlg.DoModal()) {

		maxcheck = dlg.maxcheck;
		mincheck = dlg.mincheck;
		midcheck = dlg.midcheck;

		while (dlg.m % 2 == 0 || dlg.n % 2 == 0 || dlg.m < 0 || dlg.n < 0 || dlg.m > h || dlg.n > w)
		{

			MessageBox(L"请输入合法的滤波模板边长!必须为正奇数!");

			if (IDOK == dlg.DoModal()) {

				//UpdateData();
			}
			else {
				return;
			}

		}

		//TODO:通过对话框来获取滤波模板的值
		m = dlg.m;
		n = dlg.n;

	}
	else {
		return;
	}

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//新建三维数组,保存新图
	BYTE *** newImageArr = new BYTE **[3];

	for (int k = 0; k < 3; k++) {

		newImageArr[k] = new BYTE *[h];

	}
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < h; i++) {

			newImageArr[k][i] = new BYTE[w];

		}
	}

	//新建一个数组,保存每次滤波掩模操作的的结果,以便于使用泛型算法排序或者找最值
	BYTE**	rgbArr = new BYTE*[3];
	for (int k = 0; k < 3; k++) {
		rgbArr[k] = new BYTE[m*n];
	}

	if (TRUE == maxcheck && FALSE == mincheck && FALSE == midcheck) {

		//MessageBox(L"选择了最大值滤波器");

		//最大值滤波
		for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
		{
			for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
			{
				int kk = 0;
				for (int p = -(m - 1) / 2; p < (m - 1) / 2 + 1; p++)
				{
					for (int q = -(n - 1) / 2; q < (n - 1) / 2 + 1; q++)
					{
						for (int k = 0; k < 3; k++)
						{
							rgbArr[k][kk] = m_Image.m_pBits[k][i + p][j + q];  //将模板内的值全部保存在数组中
						}
						kk++;
					}
				}
				for (int k = 0; k < 3; k++) {

					newImageArr[k][i][j] = *std::max_element(rgbArr[k], rgbArr[k] + m * n);
				}

			}
		}

		maxcheck = 0;

	}
	else if (TRUE == mincheck && FALSE == maxcheck && FALSE == midcheck) {
		//MessageBox(L"选择了最小值滤波器");
		for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
		{
			for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
			{
				int kk = 0;
				for (int p = -(m - 1) / 2; p < (m - 1) / 2 + 1; p++)
				{
					for (int q = -(n - 1) / 2; q < (n - 1) / 2 + 1; q++)
					{
						for (int k = 0; k < 3; k++)
						{
							rgbArr[k][kk] = m_Image.m_pBits[k][i + p][j + q];  //将模板内的值全部保存在数组中
						}
						kk++;
					}
				}
				for (int k = 0; k < 3; k++) {

					newImageArr[k][i][j] = *std::min_element(rgbArr[k], rgbArr[k] + m * n);
				}

			}
		}

		mincheck = 0;
	}
	else if (TRUE == midcheck && FALSE == maxcheck && FALSE == mincheck) {

		for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
		{
			for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
			{
				int kk = 0;
				for (int p = -(m - 1) / 2; p < (m - 1) / 2 + 1; p++)
				{
					for (int q = -(n - 1) / 2; q < (n - 1) / 2 + 1; q++)
					{
						for (int k = 0; k < 3; k++)
						{
							rgbArr[k][kk] = m_Image.m_pBits[k][i + p][j + q];  //将模板内的值全部保存在数组中
						}
						kk++;
					}
				}
				for (int k = 0; k < 3; k++)
				{
					//中点滤波
					newImageArr[k][i][j] = (BYTE)((*std::min_element(rgbArr[k], rgbArr[k] + m * n) + *std::max_element(rgbArr[k], rgbArr[k] + m * n)) / 2);

				}

			}
		}

		midcheck = FALSE;

	}


	//修改原图
	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
	{
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				m_Image.m_pBits[k][i][j] = newImageArr[k][i][j];

			}

		}
	}

	//释放内存
	for (int k = 0; k < 3; k++) {
		delete[]rgbArr[k];
	}
	delete[]rgbArr;

	//与new的顺序是恰好相反的
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < h; i++) {
			delete[]newImageArr[k][i];
		}
		delete[] newImageArr[k];
	}
	delete[]newImageArr;


	Invalidate(TRUE);
}


void CImage_ProcessingView::OnAdaptivemedianfilter()
{
	// TODO: 自适应中值滤波~~~~~~

	if (m_Image.IsNull())
	{

		OnFileOpen();
		return;

	}

	m_Image.Flag = 0;
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	int m(3), n(3);//滤波器模板
	int m_max(9);//限制的最大的模板
	int n_max(9);
	int n_start(3), m_start(3); //模板边长起始值

	Dlg_AdaptiveMedianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		while (dlg.n_max % 2 == 0 || dlg.m_max % 2 == 0 || dlg.n_max < 0 || dlg.m_max < 0 ||
			dlg.n_start % 2 == 0 || dlg.m_start % 2 == 0 || dlg.n_start < 0 || dlg.m_start < 0
			)
		{
			MessageBox(L"请输入合法的参数!!!");

			if (IDOK == dlg.DoModal())
			{

				UpdateData();
			}
			else
			{
				return;
			}
			m_max = dlg.m_max;
			n_max = dlg.n_max;

			m_start = dlg.m_start;
			n_start = dlg.n_start;
		}
	}
	else {
		return;
	}

	//分配一个三维数组,保存新图
	BYTE*** newImageArr = new BYTE **[3];
	for (int k = 0; k < 3; k++)
	{
		newImageArr[k] = new BYTE *[h];
		for (int i = 0; i < h; i++)
		{
			newImageArr[k][i] = new BYTE[w];
		}

	}

	//进度条
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	GetClientRect(&rect);
	proRect.left = rect.left + rect.Width() / 2 - 100;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
	//myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //创建位置、大小
	myProCtrl.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTHREVERSE, proRect, this, 99); //创建位置、大小


	BYTE* z_max = new BYTE[3];//实际上是unsigned char
	BYTE* z_min = new BYTE[3];
	BYTE* z_med = new BYTE[3];

	int hk = 0;
	for (int i = m_max; i < h - m_max; i++)
	{
		for (int j = n_max; j < w - n_max; j++)
		{
			for (int k = 0; k < 3; k++)  //三个通道,各自单独 处理
			{
				for (m = m_start, n = n_start; m < m_max + 1, n < n_max + 1; m++, n++)  //m,n从5开始增加,比从3开始增加,效果好一点
				{
					//动态分配一个二维数组保存模板内的图像灰度
					BYTE ** rgbArr = new BYTE *[3];
					for (int k = 0; k < 3; k++)
					{
						rgbArr[k] = new BYTE[m*n];
					}

					for (int p = (int)(1 - m) / 2; p < int((m - 1) / 2 + 1); p++)
					{
						for (int q = (int)(1 - n) / 2; q < (int)((n - 1) / 2 + 1); q++)
						{
							rgbArr[k][hk] = m_Image.m_pBits[k][i + p][j + q];
							hk++;
						}
					}

					std::sort(rgbArr[k], rgbArr[k] + m * n);  //按照升序排序

					z_max[k] = rgbArr[k][m*n - 1];   //最大值
					z_min[k] = rgbArr[k][0];           //最小值
					z_med[k] = rgbArr[k][(int)(m*n - 1) / 2]; //中值

					hk = 0;

					//释放内存
					for (int k = 0; k < 3; k++)
					{
						delete[]rgbArr[k];
					}
					delete[]rgbArr;

					newImageArr[k][i][j] = z_med[k];

					//判断中值是否是噪点
					if (z_max[k] != z_med[k] && z_min[k] != z_med[k])//B进程开始
					{
						//std::sort(rgbArr[k], rgbArr[k] + m * n);
						if (z_max[k] != m_Image.m_pBits[k][i][j] && z_min[k] != m_Image.m_pBits[k][i][j]) //原像素点不是噪点,则不变
						{

							newImageArr[k][i][j] = m_Image.m_pBits[k][i][j];

						}
						else
						{
							newImageArr[k][i][j] = z_med[k]; //原像素点是噪点,则用中值替代
						}

						break;  //加了break,速度快,不加的话,速度奇慢,但效果更好,因为此时相当于每次都用了最大的模板进行滤波
					}

				}

			}

		}

		double p;
		p = (double)i / (double)(h - ((m*n - 1) / 2));
		int kl = p * 100;

		myProCtrl.SetPos(kl);//设置进度条显示进度
	}

	//修改原图
	for (int i = 0; i < h - m_max; i++)
	{
		for (int j = 0; j < w - n_max; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				m_Image.m_pBits[k][i][j] = newImageArr[k][i][j];

			}

		}
	}

	//释放内存
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < h; i++) {
			delete[]newImageArr[k][i];
		}
		delete[] newImageArr[k];
	}
	delete[]newImageArr;

	delete[] z_max;
	delete[] z_med;
	delete[] z_min;


	Invalidate(TRUE);

}


void CImage_ProcessingView::OnHoughlinedetection()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//考虑最理想的情况，先将图像全部置零
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int x = rand() % h;
			int y = rand() % w;
			if ((rand() % 3000) > 1)    //置零,但添加一定的噪声
			{
				for (int k = 0; k < 3; k++)
				{

					m_Image.m_pBits[k][i][j] = 0;

				}

			}
			else  //以一定概率加以一些噪声,噪声概率仅为1/3000
			{
				for (int k = 0; k < 3; k++)
				{

					m_Image.m_pBits[k][i][j] = 255;

				}

			}
		}
	}
	////给出四条待检测的直线
	for (int k = 0; k < 3; k++) {
		for (int p = 10; p < int(h / 10); p += 3) {

			m_Image.m_pBits[k][1 * p][2 * p] = 255;

			m_Image.m_pBits[k][4 * p][2 * p] = 255;

			m_Image.m_pBits[k][7 * p][w - p - 10] = 255;//注意别越界

			m_Image.m_pBits[k][5 * p][w - 2 * p] = 255;//这里一定注意啊,w-2*p当p从0开始增加时,w-2*p =w,这就越界了

		}
	}
	Invalidate(TRUE);


	MessageBox(L"开始直线检测！");

	////TODO：先假设待检测图像为0和255的2值图像，0为背景，255为待检测点，而且我们也暂时只考虑检测一条最长的直线
	////而且只是存在一些散点，后面再考虑加入梯度检测，去噪，二值化等

	const double PI = 3.141592;
	const int min_theta = 0;
	const int max_theta = 180;

	int max_thro = (int)sqrt(w*w + h * h);    //thro的最大值，其实就是图像的对角线距离

	//动态分配数组
	int **countArr = new int*[sizeof(int) * max_theta];
	for (int i = 0; i < max_theta; i++)
	{
		countArr[i] = new int[sizeof(int) * max_thro];
		memset(countArr[i], 0, sizeof(int)*max_thro); //初始化
	}

	//统计每个待检测点所有的theta和thro，并存在count数组中
	for (int p_theta = 0; p_theta < max_theta; p_theta++)
	{
		//cos_theta与sin_theta
		double cos_theta, sin_theta;
		cos_theta = cos(double(PI * p_theta / 180));
		sin_theta = sin(double(PI * p_theta / 180));

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (m_Image.m_pBits[0][i][j] == 255)  //已经转为灰度图，因此只考虑B通道
				{
					int thro = int(i * cos_theta + j * sin_theta);
					if (0 < thro && thro < max_thro)
					{
						countArr[p_theta][thro]++;  //统计直线的参数
					}
				}
			}
		}
	}

	//寻找theta_thro对的最大数量，也就是寻找count最大值所对应的theta_thro

	std::vector<int> v_theta(0);  //存储找到的直线所对应的参数
	std::vector<int> v_thro(0);

	for (int i = min_theta; i < max_theta; i++)
	{
		for (int j = 0; j < max_thro; j++)
		{
			if (countArr[i][j] > 6)  //超过6个点连在一起，则认为是一条直线
			{
				v_theta.push_back(i);
				v_thro.push_back(j);
			}
		}

	}

	//返回x，y平面，得到所有直线的表达式, 并遍历图像上每个点，判断是否在各直线上，并画出直线
	std::vector<int>::iterator iter1, iter2;
	for (iter1 = v_theta.begin(), iter2 = v_thro.begin(); iter1 != v_theta.end(), iter2 != v_thro.end(); iter1++, iter2++)
	{
		double costheta = cos(double(PI * (*iter1) / 180));
		double sintheta = sin(double(PI * (*iter1) / 180));

		BYTE b = rand() % 255;
		BYTE g = rand() % 255;
		BYTE r = rand() % 255;

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (*iter2 == int(i * costheta + j * sintheta))
				{
					m_Image.m_pBits[0][i][j] = b;  //彩色
					m_Image.m_pBits[1][i][j] = g;
					m_Image.m_pBits[2][i][j] = r;

				}
			}
		}
	}

	//释放动态数组countArr
	for (int i = 0; i < max_theta; i++)
	{
		delete[]countArr[i];
		countArr[i] = NULL;
	}

	delete[]countArr;
	countArr = NULL;

	Invalidate(TRUE);

}


void CImage_ProcessingView::OnSoblegrad()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();
	MessageBox(_T("将会取灰度图!"));
	OnTogrey();
	//MessageBox(_T("将会调用平滑函数~!"));
	//均值平滑
	//OnMeanfilter();

	//边缘检测,为了简单,先考虑prewitt算子
	//分配数组内存
	MessageBox(_T("将会边缘检测!"));
	BYTE *** newImageArr = new BYTE**[3];
	for (int i = 0; i < 3; i++)
	{
		newImageArr[i] = new BYTE*[h];
		for (int j = 0; j < h; j++)
		{
			newImageArr[i][j] = new BYTE[w];
			memset(newImageArr[i][j], 0, sizeof(BYTE)*w);
		}
	}
	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++)
		{
			for (int k = 0; k < 3; k++) {

				int gx = (m_Image.m_pBits[k][i + 1][j - 1] + 2 * m_Image.m_pBits[k][i + 1][j] + m_Image.m_pBits[k][i + 1][j + 1]) -
					(m_Image.m_pBits[k][i - 1][j - 1] + 2 * m_Image.m_pBits[k][i - 1][j] + m_Image.m_pBits[k][i - 1][j + 1]);
				int gy = (m_Image.m_pBits[k][i - 1][j + 1] + 2 * m_Image.m_pBits[k][i][j + 1] + m_Image.m_pBits[k][i + 1][j + 1]) -
					(m_Image.m_pBits[k][i - 1][j - 1] + 2 * m_Image.m_pBits[k][i][j - 1] + m_Image.m_pBits[k][i + 1][j - 1]);
				if (abs(gx) + abs(gy) < 255)
				{
					newImageArr[k][i][j] = abs(gx) + abs(gy);
				}
				else {
					newImageArr[k][i][j] = 255;
				}
			}
		}
	}
	//将新图赋予源图
	for (int j = 1; j < h - 1; j++)//新图是没有初始化的!
	{
		for (int i = 1; i < w - 1; i++)
		{
			m_Image.m_pBits[0][j][i] = newImageArr[0][j][i];
			m_Image.m_pBits[1][j][i] = newImageArr[1][j][i];
			m_Image.m_pBits[2][j][i] = newImageArr[2][j][i];
		}
	}
	Invalidate(TRUE);

	//二值化
	MessageBox(_T("将会0~255二值化!"));
	for (int j = 0; j < h; j++)//新图是没有初始化的!
	{
		for (int i = 0; i < w; i++)
		{
			for (int k = 0; k < 3; k++) {

				if (m_Image.m_pBits[k][j][i] > 128) {
					m_Image.m_pBits[k][j][i] = 255;
				}
				else {
					m_Image.m_pBits[k][j][i] = 0;
				}

			}

		}
	}
	Invalidate(TRUE);
}


void CImage_ProcessingView::OnShowrgb()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//恢复下原图,以防止用户多次调用此函数而造成灰度值全变为0的情况
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[k][i][j] = m_Imagecp.m_pBits[k][i][j];
			}
		}
	}

	BOOL B_check(1), G_check(1), R_check(1);
	Dlg_ShowRGB dlg;
	if (IDOK == dlg.DoModal()) {

		B_check = dlg.b_check;
		G_check = dlg.g_check;
		R_check = dlg.r_check;

	}
	else {
		return;
	}

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			m_Image.m_pBits[0][i][j] = m_Image.m_pBits[0][i][j] * B_check;
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[1][i][j] * G_check;
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[2][i][j] * R_check;
		}

	}

	Invalidate(TRUE);
}


void CImage_ProcessingView::OnRgbtohsi()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	BOOL h_check(0), s_check(0), i_check(0);
	Dlg_RgbToHSI dlg;
	if (IDOK == dlg.DoModal()) {

		h_check = dlg.H;
		s_check = dlg.S;
		i_check = dlg.I;
	}
	else {
		return;
	}


	//恢复下原图,以防止用户多次调用此函数而造成灰度值全变为0的情况
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[k][i][j] = m_Imagecp.m_pBits[k][i][j];
			}
		}
	}

	BYTE *** newImageArr = new BYTE**[3];
	for (int k = 0; k < 3; k++) {
		newImageArr[k] = new BYTE*[h];
		for (int i = 0; i < h; i++) {

			newImageArr[k][i] = new BYTE[w];

		}
	}


	BYTE R(0), G(0), B(0);
	BYTE H(0), S(0), I(0);

	const double PI = 3.141593;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			B = m_Image.m_pBits[0][i][j];
			G = m_Image.m_pBits[1][i][j];
			R = m_Image.m_pBits[2][i][j];

			double theta = acos(0.5*(2 * R - B - G) / sqrt((R - G)*(R - G) + (R - B)*(R - B) + (G - B)*(G - B)));
			if (B <= G)
			{
				H = BYTE((theta / (2 * PI)) * 255);
			}
			else
			{
				H = BYTE(((2*PI-theta) / (2 * PI)) * 255);
			}

			vector<BYTE> rgb;
			rgb.push_back(R);
			rgb.push_back(G);
			rgb.push_back(B);
			BYTE minvalue = *min_element(rgb.begin(), rgb.end());
	

			S = (1 - 3 * (minvalue) / (R + B + G + 0.0003)) * 255;

			I = BYTE((R + B + G) / 3);

			newImageArr[0][i][j] = H;
			newImageArr[1][i][j] = S;
			newImageArr[2][i][j] = I;

		}

	}

	if (h_check == 1) {  //H
		//将新图赋予源图
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[0][i][j] = newImageArr[0][i][j];
				m_Image.m_pBits[1][i][j] = newImageArr[0][i][j];
				m_Image.m_pBits[2][i][j] = newImageArr[0][i][j];
				
			}
		}
	}
	else if(s_check ==1){ //S
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[0][i][j] = newImageArr[1][i][j];
				m_Image.m_pBits[1][i][j] = newImageArr[1][i][j];
				m_Image.m_pBits[2][i][j] = newImageArr[1][i][j];

			}
		}
	
	}
	else if (i_check == 1) { //I
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[0][i][j] = newImageArr[2][i][j];
				m_Image.m_pBits[1][i][j] = newImageArr[2][i][j];
				m_Image.m_pBits[2][i][j] = newImageArr[2][i][j];

			}
		}

	}
	else {
		//do nothing 
	}

	

	//回收指针

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] newImageArr[i][j];//回收内存
		}
	}
	for (int i = 0; i < 3; i++)
	{
		delete[] newImageArr[i];
	}
	delete[] newImageArr;

	Invalidate(1);

}
