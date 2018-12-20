
// Image_ProcessingView.h : CImage_ProcessingView ��Ľӿ�
//

#pragma once
#include "MyImage_.h"
#include "atlimage.h"
#include "Image_ProcessingDoc.h"
#include "ComplexNum.h"

class CImage_ProcessingView : public CScrollView
{
protected: // �������л�����
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView)

// ����
public:
	CImage_ProcessingDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:


	MyImage_ m_Image;
	MyImage_ m_Imagecp;//���ڸ�ԭͼ��

	CImage image2;//CImage�¶������ڱ����²�������
	int w;//ͼ��ߴ�
	int h;//ͼ��ߴ�

	//����ı���,���ڲ�ɫͼ��ָ�ʱ,ѡȡ��ʼ������λ��
	bool m_bClickEmpty =false; //�ж��Ƿ����˿հ׵ĵط�����ʵ���϶���ѡ�� 
	CPoint OldEmptyBegin;//����հ׿�ʼ������
	CPoint NowEmptyEnd;//�ƶ�ʱ��������
	CPoint LastEmptyEnd;  //����ɿ�ʱ���������
	BOOL IsROIChoosed =FALSE; //��־,��ʾ�û��Ƿ��Ѿ�ѡȡ�˲�ɫͼ��ָ����������
	int x_start, y_start, x_end, y_end;//����,���Ա�ʾͼƬ��,ѡ����������������ʼ��,��OnLButtonUp���޸���ֵ


	/*afs_msg ���� afx_msgΪ��Ϣ��־������ϵͳ����������Ϣӳ�䵽����ʵ���壻
	����map�궨���У����о�����Ϣ�ʹ˺�����ӳ�䶨��*/
	afx_msg void OnDrawline();   
	afx_msg void OnFileSaveAs();
	afx_msg void OnShowred();
//	afx_msg void OnViewToolbar();

	afx_msg void OnTogrey();
	afx_msg void OnDownsample();

	// ��¼���x����
	int MouseX;
	// ��¼���Y����
	int MouseY;

	// ������ڶ�����
	int MouseX2;
	// ������ڶ�����
	int MouseY2;

	// ����Ҷ�任�Ĵ���

	int FftTime;
	ComplexNum *FTResult;// = NULL;//����Ҷ�任���

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

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  //��Ӧ��갴���¼�
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);  
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	afx_msg void OnGlobalThreshold();
	afx_msg void OnOtsusegment();
};

#ifndef _DEBUG  // Image_ProcessingView.cpp �еĵ��԰汾
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

