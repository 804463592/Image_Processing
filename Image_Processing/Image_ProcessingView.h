
// Image_ProcessingView.h : CImage_ProcessingView 类的接口
//

#pragma once
#include "MyImage_.h"
#include "atlimage.h"
#include "Image_ProcessingDoc.h"
#include "ComplexNum.h"

class CImage_ProcessingView : public CScrollView
{
protected: // 仅从序列化创建
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView)

// 特性
public:
	CImage_ProcessingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:


	MyImage_ m_Image;
	MyImage_ m_Imagecp;//用于复原图像

	CImage image2;//CImage新对象，用于保存下采样数据
	int w;//图像尺寸
	int h;//图像尺寸

	//下面的变量,用于彩色图像分割时,选取初始的中心位置
	bool m_bClickEmpty =false; //判断是否点击了空白的地方，以实现拖动框选择 
	CPoint OldEmptyBegin;//点击空白开始的座标
	CPoint NowEmptyEnd;//移动时保存座标
	CPoint LastEmptyEnd;  //鼠标松开时保存的坐标
	BOOL IsROIChoosed =FALSE; //标志,表示用户是否已经选取了彩色图像分割的区域中心
	int x_start, y_start, x_end, y_end;//变量,用以表示图片中,选中区域的相对坐标起始点,在OnLButtonUp中修改其值


	/*afs_msg 其中 afx_msg为消息标志，它向系统声明：有消息映射到函数实现体；
	而在map宏定义中，就有具体消息和此函数的映射定义*/
	afx_msg void OnDrawline();   
	afx_msg void OnFileSaveAs();
	afx_msg void OnShowred();
//	afx_msg void OnViewToolbar();

	afx_msg void OnTogrey();
	afx_msg void OnDownsample();

	// 记录鼠标x坐标
	int MouseX;
	// 记录鼠标Y坐标
	int MouseY;

	// 保存框框第二个点
	int MouseX2;
	// 保存框框第二个点
	int MouseY2;

	// 傅立叶变换的次数

	int FftTime;
	ComplexNum *FTResult;// = NULL;//傅立叶变换结果

	afx_msg void OnDowngrey();
	afx_msg void OnImgAddition();
	int Times=0;
	afx_msg void OnHistgram();
	afx_msg void OnHistbalance();
	afx_msg void OnHistmatch();
	afx_msg void OnMeanfilter();
	afx_msg void OnMeadianfilter();
	afx_msg void OnFft();
	afx_msg void OnIfft();
	afx_msg void OnLowpassfilter();
	afx_msg void OnButterworthfilter();
	afx_msg void OnGaussianFilter();
	afx_msg void OnFrequencyDomainShift();
	afx_msg void OnGeometricmeanfilter();
	afx_msg void OnHarmonicmeanfilter();
	afx_msg void OnContraharmonicmeanfilter();
	afx_msg void OnSaltpeppernoise();
	afx_msg void OnShowcopyimage();
	afx_msg void OnShowprocessedimage();
	afx_msg void OnProcessimagebackup();
	afx_msg void OnRestoreimage();
	afx_msg void OnContrastdisplay();
	afx_msg void OnMaxMinvaluefilter();
	afx_msg void OnAdaptivemedianfilter();
	afx_msg void OnGaussiannoise();
	afx_msg void OnHoughlinedetection();
	afx_msg void OnSoblegrad();
	afx_msg void OnShowrgb();
	afx_msg void OnRgbtohsi();
	afx_msg void OnRgbHistBalance();
	afx_msg void OnHsiHistBalance();
	afx_msg void OnColorimgsegment();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  //响应鼠标按下事件
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);  
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	afx_msg void OnGlobalThreshold();
	afx_msg void OnOtsusegment();
};

#ifndef _DEBUG  // Image_ProcessingView.cpp 中的调试版本
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

