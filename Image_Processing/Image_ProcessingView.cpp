
//�޸ĵ�Сϸ��~

//ʹ����github�ֿ� ~~~

//������github��ͼƬ�ļ�

// Image_ProcessingView.cpp : CImage_ProcessingView ���ʵ��

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif
#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"

//�Լ���ӵ�ͷ�ļ�,ע��ͷ�ļ���˳��,˳�򲻶���ʱ������Ī�����������
#include "DownTimes.h"   //���ͷֱ��ʵĶԻ���
#include "WarnDlg.h"     //���Ҷȼ�ʱ,�Ὣ��ɫͼ��תΪ�Ҷȼ�,�����ľ��洰��
#include "CDownGrey.h"     //���ڻ�ȡ���ʺ�Ҷȼ�����
#include "HistDrawDialg.h"  //����HistDrawDialg�еĶ���,������Image_ProcessingView,���Է���Image_ProcessingViewǰ��Ļ�,�����
#include "MainFrm.h"
#include "Math.h"
#include "Dlg_GetFilterSize.h"  //�Ի���,���ڻ�ȡ�˲���ģ���С
#include <algorithm>    //Ϊ��ʹ��sort����ģ���㷨
#include "ComplexNum.h" //������
#include "DFT.h"    //ʹ��FFT���㸵��Ҷ�任����
#include "Calculate.h"

#include "Dlg_LowPassParameter.h"  //���������˲���
#include "Dlg_ButterWorthFilter.h"  //������˹�˲���
#include "Dlg_GaussianFilter.h"    //��˹�˲���
#include "Dlg_HarmonicFilter.h"      //г���˲���
#include "Dlg_ContraHarmonicMeanFilter.h"   //��г���˲���

#include <vector>  //��������ʱ�õ�vector
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
	// ��׼��ӡ����
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

// CImage_ProcessingView ����/����
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
	// TODO: �ڴ˴���ӹ������

}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//cs.lpszClass = _T("MyClassName");

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView ���� OnDraw()����
void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//if (!m_Image.IsNull())
	//{
	//	m_Image.Draw(pDC->m_hDC,0,0); 
	//}


	//return;
	/////////////////////////////////////////���ñ�����ɫ
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

	//////////////////////////////////////////��ͼ
	//Image_ProcessingDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	if (!m_Image.IsNull())
	{
		//CRect rect;
		//GetClientRect(&rect);
		//m_Image.X=rect.right/2-w/2;
		//m_Image.Y=rect.bottom/2-h/2;//�ػ�ʱ����λ��

		if (m_Image.Flag == 0)//FLAGΪ0,Ĭ�ϵ���ʾ��ʽ
		{
			if (m_Image.GetWidth() > rect1.right)///////
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //�������ñ�����ɫ

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy��ʾ

		}
		else if (m_Image.Flag == 1)//FLAG��ʾԴͼm_Image,�봦����m_Imagecp,��Ҫ�ǽ��жԱ�,ֱ��ͼƥ��
		{
			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //�������ñ�����ɫ

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//��ʾ����ͼ
			pDC->TextOut(m_Image.X + m_Image.GetWidth() / 2, m_Image.Y - 30, _T("����ͼ"));

			m_Imagecp.Draw(pDC->m_hDC, m_Imagecp.X, m_Imagecp.Y);//xy��ʾ//ԭͼ�ĸ���
			pDC->TextOut(m_Imagecp.X + m_Imagecp.GetWidth() / 2, m_Imagecp.Y - 30, _T("ԭʼͼ"));

		}
		else if (m_Image.Flag == 2)//��ʾ�²���ͼ��,�²����൱����Сͼ��ߴ�
		{
			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}

			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //�������ñ�����ɫ

			image2.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);
			pDC->TextOut(m_Image.X + int(0.5*image2.GetWidth()), m_Image.Y - 30, _T("�ռ��²���ͼ"));

			m_Imagecp.Draw(pDC->m_hDC, m_Imagecp.X, m_Imagecp.Y);//��ʾԴͼ
			pDC->TextOut(m_Imagecp.X + m_Imagecp.GetWidth() / 2, m_Imagecp.Y - 30, _T("ԭʼͼ"));

		}

		else if (m_Image.Flag == 3)//rgb�ָ�ǰ��ȡ����
		{
			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1, RGB(169, 169, 169)); //�������ñ�����ɫ

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy��ʾ

			CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush = pDC->SelectObject(pBrush);
			pDC->Rectangle(CRect(CPoint(MouseX, MouseY), CPoint(MouseX2, MouseY2)));
			pDC->SelectObject(pOldBrush);
		}

		else if (m_Image.Flag == 4) { //����ֱ��ͼ��������ʾ

			if (m_Image.GetWidth() > rect1.right)
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Image.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //�������ñ�����ɫ

			m_Imagecp.Draw(pDC->m_hDC, m_Imagecp.X, m_Imagecp.Y);//��ʾԴͼ
			pDC->TextOut(m_Imagecp.X + m_Imagecp.GetWidth() / 2, m_Imagecp.Y - 30, _T("δ����ǰ��ԭʼͼ"));

			m_Image.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy��ʾ
			pDC->TextOut(m_Image.X + m_Image.GetWidth() / 2, m_Image.Y - 30, _T("ֱ��ͼ����Ч��ͼ"));
		}

		if (m_Image.Flag == 5)//FLAGΪ5,��ʾm_Imagecp,����ͼ
		{
			if (m_Imagecp.GetWidth() > rect1.right)///////
			{
				rect1.right = m_Image.GetWidth();
			}
			if (m_Imagecp.GetHeight() > rect1.bottom)
			{
				rect1.bottom = m_Imagecp.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1, RGB(128, 128, 128)); //�������ñ�����ɫ

			m_Imagecp.Draw(pDC->m_hDC, m_Image.X, m_Image.Y);//xy��ʾ

		}


	}




	return;

}

void CImage_ProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

// CImage_ProcessingView ��ӡ

void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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

// CImage_ProcessingView ���

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

// CImage_ProcessingView ��Ϣ�������

void CImage_ProcessingView::OnFileOpen()
{
	//// TODO: �ڴ���������������
	//CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������

	//if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	//{
	//	if(!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
	//	m_Image.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

	//	//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
	//	CSize sizeTotal;
	//	int w=m_Image.GetWidth();
	//	int h=m_Image.GetHeight();

	//	sizeTotal.cx =w;
	//	sizeTotal.cy =h;
	//	SetScrollSizes(MM_TEXT, sizeTotal);

	//	//Window_Image_w=m_Image.GetWidth();//���ͼƬ�ĳ�ʼ��С��Ϊ�Ŵ���С������׼��
	//	//Window_Image_h=m_Image.GetHeight();//

	//	Invalidate(1); //ǿ�Ƶ���ONDRAW����
	//}

	BOOL OpenFlage = 1;//��¼�Ƿ�ɹ�����ͼƬ

	m_Image.Flag = 0;//����FLAG

	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		if (!m_Imagecp.IsNull()) m_Imagecp.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������

		while (S_FALSE == m_Image.Load(dlg.GetPathName()))
		{
			MessageBox(_T("�򿪵Ĳ���24λ���ɫͼ��"));
			if (IDCANCEL == dlg.DoModal()) //���´�ͼƬ�����ȡ��������ѭ��   
			{
				OpenFlage = 0;//û�д�ͼƬ������ѭ��
				break;
			}
		}//ȷ����24λ��ɫͼƬ

		m_Imagecp.Load(dlg.GetPathName());//��ԭʼͼƬ����,m_Image��m_Imagecp��ͬ���ĳ���,����


		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		if (OpenFlage == 1)
		{
			CSize sizeTotal;
			w = m_Image.GetWidth();
			h = m_Image.GetHeight();


			CRect rect;
			GetClientRect(&rect);
			m_Image.X = max(0, rect.right / 2 - w / 2);
			m_Image.Y = max(0, rect.bottom / 2 - h / 2);//������ʾͼƬ�����Ͻ�λ��
			m_Imagecp.X = max(0, rect.right / 2 - w / 2);
			m_Imagecp.Y = max(0, rect.bottom / 2 - h / 2);//������ʾͼƬ�����Ͻ�λ��

			sizeTotal.cx = w;
			sizeTotal.cy = h;
			SetScrollSizes(MM_TEXT, sizeTotal);
		}

		//Window_Image_w=m_Image.GetWidth();//���ͼƬ�ĳ�ʼ��С��Ϊ�Ŵ���С������׼��
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}

}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;

	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();

	for (int k = 0; k < w; k++)
	{
		m_Image.m_pBits[0][50][k] = 0;//B
		m_Image.m_pBits[1][50][k] = 0;//G
		m_Image.m_pBits[2][50][k] = 0;//R

	}


	Invalidate(1); //ǿ�Ƶ���ONDRAW����

}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {
		MessageBox(_T("�㻹û�д�һ��Ҫ�����ͼ���ļ���"));
		return;
	}
	CString strFilter;
	//strFilter ="λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||";   
	strFilter = "�����ļ�|*.*||";   //

	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if (IDOK != dlg.DoModal())
		return;
	// ����û�û��ָ���ļ���չ������Ϊ�����һ��
	CString strFileName;
	//CString strExtension;
	//strFileName = dlg.m_ofn.lpstrFile;   //  ����ļ���
	//if(dlg.m_ofn.nFileExtension == 0)     //����ļ���չ��
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

	// ͼ�񱣴�
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image.m_pBits[0][j][k] = 0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image.m_pBits[1][j][k] = 0;//G


		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


//void CImage_ProcessingView::OnViewToolbar()
//{
//	// TODO: �ڴ���������������
//}

void CImage_ProcessingView::OnTogrey()
{
	//// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;//�ָ�����FLAG

	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < w; i++) {   //���������m_pBits[][][]�����ǰ���ͨ��,�߶�,��ȵķ�ʽ������,�������forѭ���������h,��w
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


	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��

}


void CImage_ProcessingView::OnDownsample()
{
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!image2.IsNull())//���ǰ���Ѿ��²������ˣ�������پɵ��²��������ͼƬ
	{
		image2.Destroy();
	}

	w = m_Image.GetWidth();//���ͼ��Ŀ��
	h = m_Image.GetHeight();//���ͼ��ĸ߶�

	DownTimes dlg;//�����Ի������
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

		while (dlg.m_downtimes <= 0 || pow((double)2, (int)dlg.m_downtimes) > w || pow((double)2, (int)dlg.m_downtimes) > h)//�ж��Ƿ�������Ч������
		{
			MessageBox(_T("������Ч\n������������Ч���²�������"));
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		m_Image.Flag = 2;//��¼FLAG,�Ա�����draw�����л����²������ͼ

		//int T = pow((double)2, (int)dlg.m_downtimes);//�²�������*2

		int T = (int)dlg.m_downtimes;

		image2.Create(w / T, h / T, 24);//ȫ�ֱ���Create����Ҫdelete

		int nrow = image2.GetPitch();//���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc = (BYTE *)image2.GetBits();//���CImage���һ�е����ص�ַ
		/*����ά���鸴�ƽ�m_CImage*/
		for (int j = 0; j < h / T; j++)
		{
			for (int k = 0; k < w / T; k++)
			{
				psrc[j*nrow + k * 3] = m_Image.m_pBits[0][j*T][k*T];//B
				psrc[j*nrow + k * 3 + 1] = m_Image.m_pBits[1][j*T][k*T];//G
				psrc[j*nrow + k * 3 + 2] = m_Image.m_pBits[2][j*T][k*T];//R

			}
		}

		m_Imagecp.X = 100;               //������ͼλ��,�Աȴ����Ч��
		m_Imagecp.Y = 100;
		m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
		m_Image.Y = m_Imagecp.Y;

		/*����ά���鸴�ƽ�image2*/
		Invalidate(1);//ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
	}
}


void CImage_ProcessingView::OnDowngrey()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;//����FLAG,Flag=0��ʾĬ�ϵ�draw��ʽ,��ʾm_Image

	//�ж��Ƿ�Ϊ��ɫͼƬ�������򵯳����ʾ���///
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}
	//OnTogrey();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ,��Ȼ,Ҳ���Բ�����һ��,�Ͼ����Ľ��Ҳ�ǻҶ�ͼ
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	CDownGrey dlg;   //�Ի���
	if (IDOK == dlg.DoModal())
	{
		UpdateData();
		while (dlg.Lowgrey <= 0 || dlg.Lowgrey > 256)
		{
			MessageBox(_T("�Ҷȼ���Ч������������Ҷȼ���"));
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
		int Time = 256 / dlg.Lowgrey;//�ж��²�������  (������ӽ��ĻҶȼ�)
	//int Time = 128;
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				BYTE b = m_Image.m_pBits[0][j][k];
				BYTE g = m_Image.m_pBits[1][j][k];
				BYTE r = m_Image.m_pBits[2][j][k];

				int average = (b + g + r) / 3;//���Ž��ʹ������ӣ����ϸı�Ҷ�ֵ
				////ave������int����////

				if (average > 255 / 2)//���лҶȱ任�㷨
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
		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
	//Times=1;//�ָ�Timees��ֵ��ͼƬ���Ҫ�ã�

}


void CImage_ProcessingView::OnImgAddition()
{
	// TODO: �ڴ���������������
	Times++;
	float k = Times;
	//k=(k-1)/k;
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;//�ָ�����FLAG
	w = m_Image.GetWidth();//��õ�һ��ͼ��Ŀ��
	h = m_Image.GetHeight();//���ͼ��ĸ߶�

	MyImage_ Image_Second;
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!Image_Second.IsNull()) Image_Second.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		Image_Second.Load(dlg.GetPathName());//���öԻ����GetPathName���ͼƬ��λ�ã����ҵ���Load����ͼƬ
		if (Image_Second.IsNull()) return;
		if (w != Image_Second.GetWidth() || h != Image_Second.GetHeight())//�ж�����ͼ���С�Ƿ�һ��
		{
			MessageBox(_T("����ͼ���С��һ�£�"));
			return;
		}
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)//����ͼ��������Ӽ�����
			{
				int tt = m_Image.m_pBits[0][j][i];
				//ͼ����
				/*m_Image.m_pBits[0][j][i] = m_Image.m_pBits[0][j][i] - Image_Second.m_pBits[0][j][i];
				m_Image.m_pBits[1][j][i] = m_Image.m_pBits[1][j][i] - Image_Second.m_pBits[1][j][i];
				m_Image.m_pBits[2][j][i] = m_Image.m_pBits[2][j][i] - Image_Second.m_pBits[2][j][i];*/

				//ͼ�����ȥ��
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
ֱ��ͼͳ��:
��ԭͼm_Image�Ͻ���ͳ��,���½��Ի�����ʾ
*/
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
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
	//OnTogrey();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ

	m_Image.GetHistgram();//���ó�Ա����,ͳ��ֱ��ͼ

	//ʹ��Dialg��ͼ
	HistDrawDialg dlg(this);
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistbalance()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	//�ж��Ƿ�Ϊ��ɫͼƬ�������򵯳����ʾ���//
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}

	//OnTogrey();//����ǲ�ɫͼ����m_Imageת��Ϊ�Ҷ�ͼ,��������m_Image��,ͬʱflag���Ϊ1

	m_Image.Flag = 4;	//�ָ�FLAGΪ4,�ԶԱȵ����ⷽʽ��ʾ

	m_Image.GetHistgram();//��ȡ����ֱ��ͼͳ��,������m_Image.probability������

	long i, j;		//ѭ������
	BYTE pixel1, pixel2, pixel3;		//����ֵ

	float temp[3][256];
	int   nRst[3][256];//ӳ���
	int nrow = m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

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
			temp[0][i] = temp[0][i - 1] + m_Image.probability[0][i];  //rͨ��,�ۻ����غ���temp�е��Ǹ���,С��1��
			temp[1][i] = temp[1][i - 1] + m_Image.probability[0][i];  //gͨ��,�ۻ����غ���
			temp[2][i] = temp[2][i - 1] + m_Image.probability[0][i];  //bͨ��,�ۻ����غ���
		}
	}

	for (i = 0; i < 256; i++)
	{
		nRst[0][i] = (int)(255.0f * temp[0][i] + 0.5f);      //nRst[i],ֱ��ͼ����Ҷȱ任ӳ��
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

			m_Image.m_pBits[0][j][i] = (BYTE)(nRst[0][pixel1]);//ע����ʹ��m_pBits
			m_Image.m_pBits[1][j][i] = (BYTE)(nRst[0][pixel1]);//��ʹ��CImage��Getbits
			m_Image.m_pBits[2][j][i] = (BYTE)(nRst[0][pixel1]);//����ͨ��ֵһ��
			//ȫ��ʹ��ͬһ��ͨ�����ۻ�����,������ͨ���������⻯,�����ʾ��ʧ��
			//��ɫͼ����⻯,����ת��hsv�ռ����

		}
	}

	m_Imagecp.X = 100;               //������ͼλ��,�Աȴ����Ч��
	m_Imagecp.Y = 100;
	m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
	m_Image.Y = m_Imagecp.Y;

	Invalidate(1);

}


void CImage_ProcessingView::OnHistmatch()
{
	// TODO: �ڴ���������������
	BOOL OpenFlage = 1;//��¼�Ƿ�ɹ�����ͼƬ

	//��ȡĿ��ֱ��ͼ
	MyImage_  MatchImage;
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!MatchImage.IsNull())
			MatchImage.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������

		while (S_FALSE == MatchImage.Load(dlg.GetPathName()))
		{
			MessageBox(_T("�򿪵Ĳ���24λ���ɫͼ��"));
			if (IDCANCEL == dlg.DoModal()) //���´�ͼƬ�����ȡ��������ѭ��   
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

	MatchImage.GetHistgram();//��ȡMatch����ֱ��ͼ

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}


	//�ж��Ƿ�Ϊ��ɫͼƬ�������򵯳����ʾ���//
	if (!(m_Image.m_pBits[0][0][0] == m_Image.m_pBits[1][0][0] && m_Image.m_pBits[1][0][0] == m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL == warn.DoModal())
		{
			return;
		}
	}

	m_Image.GetHistgram();//��ȡ����ֱ��ͼ
	OnTogrey();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ
	m_Image.Flag = 1;	//�ָ�FLAG

	float temp[3][256];
	long i, j;		//ѭ������
	BYTE pixel;		//����ֵ
	int   nMap[3][256];//����ӳ���
	int   npMap[3][256];//�涨ֱ��ͼ�ľ��⻯��ӳ���
	float fpPro[3][256];
	float  k = 1.0f / 256;
	for (i = 0; i < 256; i++)
	{
		fpPro[0][i] = MatchImage.probability[0][i];//�涨���ĸ���
	}
	int MatchGrayRank = 256;//�涨���ĻҶȼ�

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();


	//����Դͼ�ۼ�ֱ��ͼ m_Image.probability
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

	//����涨����ۼ�ֱ��ͼ
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

	//����涨������ �����⻯��ӳ���npMap
	for (i = 0; i < MatchGrayRank; i++)
	{
		npMap[0][i] = (int)((MatchGrayRank - 1) * fpPro[0][i] + 0.5f);//�����1��
	}

	//�����ۻ�ֱ��ͼ���ʵĲ�ֵ��С��ԭ��,����ӳ���ϵ
	for (i = 0; i < 256; i++)
	{
		int m = 0;
		float min_value = 1.0f;//float����С��ֵ
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
				m = j;//��¼��Сֵλ��
				min_value = now_value;//���ϸ�����С��ֵ
			}
		}
		nMap[0][i] = npMap[0][m];//�����Ҷ�ӳ���,�п��ܶ��npMap��ֵ��Ӧһ��nMap
	}

	//�Ը����ؽ���ֱ��ͼ�涨��ӳ�䴦��
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pixel = m_Image.m_pBits[0][j][i];

			m_Image.m_pBits[0][j][i] = (BYTE)(nMap[0][pixel]);//ע����ʹ��m_pBits
			m_Image.m_pBits[1][j][i] = (BYTE)(nMap[0][pixel]);//��ʹ��CImage��Getbits
			m_Image.m_pBits[2][j][i] = (BYTE)(nMap[0][pixel]);
		}
	}

	m_Imagecp.X = 100;               //������ͼλ��,�Աȴ����Ч��,�����޷���ʾ
	m_Imagecp.Y = 100;
	m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
	m_Image.Y = m_Imagecp.Y;

	Invalidate(1);

}


void CImage_ProcessingView::OnMeanfilter()
{
	//��ֵ�˲�:m_Image���޸�,Ҳ�е��ʱ,��������ֵ�˲���
	// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();

	Dlg_GetFilterSize dlg;//�����Ի������

	if (IDOK == dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ��,�����׳���

		//�ж��Ƿ�������Ч������
		while (dlg.filterSize % 2 == 0 || dlg.filterSize<0 || dlg.filterSize>w || dlg.filterSize > h)
		{
			MessageBox(_T("����ģ��ߴ���Ч,������������ʵ�������ֵ"));
			if (IDOK == dlg.DoModal())
			{
				//UpdateData();
			}
			else
			{
				return;
			}
		}

		long B = 0, G = 0, R = 0;//�ۼӴ洢��ʹ��BYTE���ͻ�������,��ΪBYTE��unsigned char�����ֻ�ܵ���255

		//��������ά���飬�����ݴ���ͼ��û�г�ʼ����
		BYTE *** newImageArr;
		newImageArr = new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for (int i = 0; i < 3; i++)
		{
			newImageArr[i] = new  BYTE*[h];   //��H
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{
				newImageArr[i][j] = new BYTE[w];   //��W
			}
		}
		//int filter_size =13;  //���趨һ��Ĭ��ֵ,Ȼ���ٿ���ͨ���Ի�������ȡ
		int filter_size = (int)dlg.filterSize;

		//���ڴ����ٶȲ���,���Ǵ���һ��������
		CProgressCtrl myProCtrl;
		CRect rect, proRect;
		GetClientRect(&rect);
		proRect.left = rect.left + rect.Width() / 2 - 100;
		proRect.top = rect.top + rect.Height() / 2 - 20;
		proRect.right = rect.right - rect.Width() / 2 + 100;
		proRect.bottom = rect.bottom - rect.Height() / 2 + 20;
		//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
		myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //����λ�á���С

		//��ֵ�˲�
		//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)

		{
			for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
			{
				R = 0, G = 0, B = 0;//��ģ�����
				for (int k = -((filter_size - 1) / 2); k < (((filter_size - 1) / 2) + 1); k++)
				{
					for (int kk = -((filter_size - 1) / 2); kk < (((filter_size - 1) / 2) + 1); kk++)
					{
						B += m_Image.m_pBits[0][j + k][i + kk];//�ۼ����
						G += m_Image.m_pBits[1][j + k][i + kk];//�ۼ����
						R += m_Image.m_pBits[2][j + k][i + kk];//�ۼ����
					}
				}
				newImageArr[0][j][i] = B / (filter_size*filter_size);
				newImageArr[1][j][i] = G / (filter_size*filter_size);
				newImageArr[2][j][i] = R / (filter_size*filter_size);
			}
			double p;
			p = (double)j / (double)(h - ((filter_size - 1) / 2));
			int k = p * 100;

			myProCtrl.SetPos(k);  //���½���������

		}

		//����ͼ����Դͼ
		for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)//��ͼ��û�г�ʼ����!
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
				delete[] newImageArr[k][j];//�����ڴ�
			}
			delete[] newImageArr[k];
		}
		delete[] newImageArr;


		Invalidate(1);
	}

}


void CImage_ProcessingView::OnMeadianfilter()
{
	//��ֵ�˲�:��m_Image���޸�ԭͼ
	//ע��:��ֵ�˲��ܺ�ʱ
	// TODO: �ڴ���������������

	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	Dlg_GetFilterSize dlg; //���ڻ�ȡ�˲�ģ���С�Ի���

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();

	if (IDOK == dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while (dlg.filterSize % 2 == 0 || dlg.filterSize<0 || dlg.filterSize>w || dlg.filterSize > h)
		{
			MessageBox(_T("����ģ��ߴ���Ч\n������������ʵ�������ֵ"));
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

	//��������Դ��ͼ�����Ͽؼ�,ֱ������һ��������
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	GetClientRect(&rect);
	proRect.left = rect.left + rect.Width() / 2 - 100;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
	//myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //����λ�á���С
	myProCtrl.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTHREVERSE, proRect, this, 99); //����λ�á���С

	//��ά�������ͼ��
	BYTE *** newImageArr = nullptr;
	newImageArr = new  BYTE **[3];//3��ά�ȣ������ڴ�  
	for (int i = 0; i < 3; i++)
	{
		newImageArr[i] = new  BYTE*[h];   //��H
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			newImageArr[i][j] = new BYTE[w];   //��W
		}
	}

	//�ݴ����飬��ȡ��ֵ
	int *B, *G, *R;
	B = new int[filter_size*filter_size];
	G = new int[filter_size*filter_size];
	R = new int[filter_size*filter_size];

	int sz;//�����±�

	for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
	{
		for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
		{
			sz = 0;
			for (int k = -((filter_size - 1) / 2); k < (((filter_size - 1) / 2) + 1); k++)//ģ����ѭ��
			{
				for (int kk = -((filter_size - 1) / 2); kk < (((filter_size - 1) / 2) + 1); kk++)
				{
					B[sz] = m_Image.m_pBits[0][j + k][i + kk];
					G[sz] = m_Image.m_pBits[1][j + k][i + kk];
					R[sz] = m_Image.m_pBits[2][j + k][i + kk];
					sz++;
				}
			}

			std::sort(B, B + filter_size * filter_size);//sort����,��Ҫ #include <algorithm>
			std::sort(G, G + filter_size * filter_size);//��Ϊ��Ҫ����������,����ٶȺ���
			std::sort(R, R + filter_size * filter_size);
			newImageArr[0][j][i] = B[(filter_size*filter_size - 1) / 2 + 1];//ȡ��ֵ
			newImageArr[1][j][i] = G[(filter_size*filter_size - 1) / 2 + 1];
			newImageArr[2][j][i] = R[(filter_size*filter_size - 1) / 2 + 1];
		}

		double p;
		p = (double)j / (double)(h - ((filter_size - 1) / 2));
		int k = p * 100;

		myProCtrl.SetPos(k);//��Ϊ�����ٶȺ���,�����ý�������ʾ���ȣ���

	}

	//����ͼ����Դͼ
	for (int j = ((filter_size - 1) / 2); j < h - ((filter_size - 1) / 2); j++)//��ͼ��û�г�ʼ����!
	{
		for (int i = ((filter_size - 1) / 2); i < w - ((filter_size - 1) / 2); i++)
		{
			m_Image.m_pBits[0][j][i] = newImageArr[0][j][i];
			m_Image.m_pBits[1][j][i] = newImageArr[1][j][i];
			m_Image.m_pBits[2][j][i] = newImageArr[2][j][i];
		}
	}

	//����ָ��

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] newImageArr[i][j];//�����ڴ�
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
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();


	long i, j;					//i:��ѭ������ ,j:��ѭ������
	double dTmp;				//��ʱ����
	//w��h��
	long width = 1, height = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int width_power = 0, height_power = 0;		//wid hei :2���ݴ���

	ComplexNum *pTd = new ComplexNum[sizeof(ComplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	ComplexNum *pFd = new ComplexNum[sizeof(ComplexNum)*w*h];//Ϊָ��Ƶ���ָ������ڴ�


////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���,ͬʱ���Ա�֤�߳�ȫ��Ϊ2���ݴη�//////
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

	/////////��ʼ��pTd//////////////
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pTd[i*width + j].re = 0;
			pTd[i*width + j].im = 0;
		}
	}

	/////////ͼ����pTdָ��////////////////////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			pTd[j*width + i].re = pow((double)-1, (double)(i + j))*m_Image.m_pBits[0][j][i];//��-1)^(i+j)�ƶ��任����
		}
	}
	++FftTime;

	if (FTResult)  //���FTResult������ʼ���Ļ�,�����������쳣
	{
		delete[]FTResult;								//����任���ָ����Ч��ɾ���ڴ�
	}

	FTResult = new ComplexNum[sizeof(ComplexNum)*w*h];	//Ϊ�任������·����ڴ�


//////////���ø���Ҷ�仯����Fourier////////////////////
	fourierTransform(pTd, w, h, pFd, this);

	/////////////������/////////////

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			FTResult[width *i + j] = pTd[width *i + j];
		}


	////////////�����任����ʾ���/////////////////////////
	int **Ftmp;			//�ݴ��ά����wid*hei -> ��i����j��
						//��ά����  ��hei*wid -> ��j����i��

	//////////////�����ڴ�/////////////////////
	Ftmp = new int *[width];
	double maxF(1);//�任������ϵ��
	int s(1);	//�����任ϵ��
	for (i = 0; i < width; i++)
	{
		Ftmp[i] = new int[height];
	}

	//////////////�����ݴ��ά����///////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			dTmp = pTd[j*width + i].re*pTd[j*width + i].re + pTd[j*width + i].im*pTd[j*width + i].im;
			dTmp = sqrt(dTmp) / 100;
			if (maxF < dTmp)
			{
				maxF = dTmp;//�������ֵ
			}
			Ftmp[i][j] = dTmp;
		}
	}
	double maxx = 0;
	double v = 2;//����
	///////////////���ж����任///////////////////
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
	double pq = 255 / maxx;//ռ����
   ///////////////////������Դͼ////////////////
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			double p = Ftmp[i][j];
			m_Image.m_pBits[2][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[0][j][i] = min(pq*Ftmp[i][j], 255);

		}
	}

	//////////////////�����ݴ�����ָ��////////////////
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
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	if (!FftTime) //�ж�ͼ���Ƿ�Ϊ��
	{
		MessageBox(_T("���ȸ���Ҷ�任��"));
		return;
	}

	m_Image.Flag = 0;	//�ָ�FLAG
	--FftTime;

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();


	double dTmp;				//��ʱ����
	long i, j;					//i:��ѭ������ ,j:��ѭ������
	//w��h��
	long wid = 1, hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor = 0, heipor = 0;		//wid hei :2���ݴ���

	ComplexNum *pTd = new ComplexNum[sizeof(ComplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	ComplexNum *pFd = new ComplexNum[sizeof(ComplexNum)*w*h];//Ϊָ��Ƶ���ָ������ڴ�

//////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
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

	/////////��ʼ��pTd//////////////
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = FTResult[i*wid + j].re;
			pTd[i*wid + j].im = -FTResult[i*wid + j].im;//����
		}
	}

	//////////���ø���Ҷ�仯����Fourier////////////////////
	fourierTransform(pTd, w, h, pFd, this);

	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			dTmp = pTd[i*wid + j].re;
			dTmp = pTd[i*wid + j].im;
			pTd[i*wid + j].re = pTd[i*wid + j].re / (double)(wid*hei);
			pTd[i*wid + j].im = -pTd[i*wid + j].im / (double)(wid*hei);//����
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

	///////////����ָ���ڴ�/////////////
	delete[]pTd;
	delete[]pFd;

	Invalidate(TRUE);

}


void CImage_ProcessingView::OnLowpassfilter()
{
	//������Ϊ��ͨ�˲���,���ǿ��Ա�Ϊ��ͨ

	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//MessageBox(_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("���Ƚ��и���Ҷ�任��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();
	//�����˲���ģ��
	double **lpfilter;
	lpfilter = new double*[w];
	for (int i = 0; i < w; i++)
	{
		lpfilter[i] = new double[h];
	}

	double D;     //����D0
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

	//Ƶ���˲�����H(u,v),ʹ��lpfilter��ʾ
	int high_end(1), low_end(0);
	if (TRUE == IsHighPass) {  //�ж��Ƿ���Ҫ��ת��Ϊ��ͨ�˲���
		high_end = 0;
		low_end = 1;
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if ((pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)) <= D * D)
			{
				lpfilter[i][j] = high_end;   //�����(��)ͨ�˲���,���С(��)�ڽ���Ƶ����ͨ��
			}
			else {

				lpfilter[i][j] = low_end;
			}

		}
	}

	//���������ͨ�˲�,H(u,v)�븵��Ҷ�任���FTResult���
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = lpfilter[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = lpfilter[j][i] * FTResult[w *i + j].re;
		}


	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]lpfilter[i];
	}
	delete[]lpfilter;

	//����IFFT���з��任,�õ��ռ���Ľ��
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnButterworthfilter()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("���Ƚ��и���Ҷ�任��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();
	//����ģ��
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


	if (!isHighPass) { //��ͨ

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				btw_filter[i][j] = 1.0 / (pow((pow((pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)), 0.5) / D), (double)2 * n) + 1);

			}
		}
	}
	else { //��ͨ

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				btw_filter[i][j] = 1.0 / (pow((pow(D / (pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)), 0.5)), (double)2 * n) + 1);

			}
		}

	}
	//ButterWorth�˲�
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = btw_filter[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = btw_filter[j][i] * FTResult[w *i + j].re;
		}



	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]btw_filter[i];
	}
	delete[]btw_filter;

	//����IFFT,���з��任
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnGaussianFilter()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("���Ƚ��и���Ҷ�任��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();
	//����ģ��
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

		UpdateData(); //ò��û�����,Ҳ����???
		D = dlg_Gauss.D0;
		isHighPass = dlg_Gauss.is_HighPass;
	}
	else {
		return;
	}
	//�ж��Ƿ�Ϊ��ͨ�˲���
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
	//Gaussian�˲�
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = gaussian_filter[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = gaussian_filter[j][i] * FTResult[w *i + j].re;
		}

	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]gaussian_filter[i];
	}
	delete[]gaussian_filter;

	//����IFFT
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnFrequencyDomainShift()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(_T("���Ƚ��и���Ҷ�任��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h = m_Image.GetHeight();

	ComplexNum **pCS;

	pCS = new ComplexNum *[sizeof(ComplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	for (int i = 0; i < w; i++)
	{
		pCS[i] = new ComplexNum[h];
	}

	int u0(10), v0(10);

	//////Ƶ��ƽ��,Ϊʲô����ֺܶ�����????
	//for (int i = 0; i < h; i++)
	//	for (int j = 0; j < w; j++)
	//	{
	//		FTResult[w *i + j].im = FTResult[w *((i + u0) % h) + (j + v0) % w].im;
	//		FTResult[w *i + j].re = FTResult[w *((i + u0) % h) + (j + v0) % w].re;
	//	}

	/////Ƶ����ת,Ϊɶ��Ӱ��ԭͼ????
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

	//�޸ĸ���Ҷ�任��� 
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			/*	FTResult[w *i + j].im = FSMul(pCS[i][j], FTResult[w *i + j]).im;
				FTResult[w *i + j].re = FSMul(pCS[i][j], FTResult[w *i + j]).re;*/
			FTResult[w *i + j].im = pCS[i][j].im*FTResult[w *i + j].im;
			FTResult[w *i + j].re = pCS[i][j].re* FTResult[w *i + j].re;
		}


	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]pCS[i];
	}
	delete[]pCS;

	//����IFFT
	CImage_ProcessingView::OnIfft();

}


void CImage_ProcessingView::OnGeometricmeanfilter()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//���弸�ξ�ֵ�˲�����Ҫ�Ĳ���,�˲�ģ�峤��m,n,������

	int m = 5, n = 9;  //����Ϊ������,��������˲���ʱ������

	//TODO:�����Ի���,���жϲ����Ϸ���
	Dlg_GetFilterSize size_dlg;

	if (IDOK == size_dlg.DoModal()) {

		//TODO:�ж�m,n�Ƿ�Ϊ������
		//�ж��Ƿ�������Ч������
		while (size_dlg.filterSize % 2 == 0 || size_dlg.filterSize<0 || size_dlg.filterSize>w || size_dlg.filterSize > h)
		{
			MessageBox(_T("����ģ��ߴ���Ч\n������������ʵ�������ֵ"));
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
		return;//��������ֵ��return���ֻ�����ڷ�������Ϊvoid�ĺ�����return�����Ϊ����������ǿ�ƽ����������÷�������ѭ���ṹ�е�break�������á�
	}

	//����һЩ��������
	long  double R = 1, G = 1, B = 1;  //�������double,�������Ϊȫ�ڵ�,��Ϊ������R,G,B�������С��,���Ϊ0��

	BYTE*** newImagePtr = new BYTE**[3]; //��ά��������ڴ�,�ͷ��ڴ�ʱ˳��Ҫ�෴  
	for (int i = 0; i < 3; i++)
	{
		newImagePtr[i] = new  BYTE*[h];   //��H

		for (int j = 0; j < h; j++)
		{
			newImagePtr[i][j] = new BYTE[w];   //��W
		}
	}

	//TODO:���ξ�ֵ�˲�
	for (int i = int((m - 1) / 2); i < (h - (m - 1) / 2); i++)
	{
		for (int j = int((n - 1) / 2); j < (w - (n - 1) / 2); j++) {
			R = 1.0;
			G = 1.0;
			B = 1.0;
			for (int p = -(m - 1) / 2; p < ((m - 1) / 2 + 1); p++) {

				for (int q = -(n - 1) / 2; q < ((n - 1) / 2 + 1); q++)
				{
					//����ȳ�����,����ٿ���,ֵ�����,�Ͼ������Դﵽ255^(m*n);���ÿ���ȿ����Ǹ�,����ٳ�����
					B = (double)B * pow((double)m_Image.m_pBits[0][i + p][j + q], (double)1.0 / (double)(m*n));//R,G,B���Ϊlong, ����һ��С����Ϊ0��
					G = (double)G * pow((double)m_Image.m_pBits[1][i + p][j + q], (double)1.0 / (double)(m*n));
					R = (double)R * pow((double)m_Image.m_pBits[2][i + p][j + q], (double)1.0 / (double)(m*n));

				}
			}
			//R =(int)pow((double)R, (double)(1.0 / (m*n))); //���Ҫ��ô��,ǰ�����Ҫֱ�ӻҶ�ֵ�۳�,��ֵ����,��ò�Ҫ��ô��
			//G =(int)pow((double)G, (double)(1.0 / (m*n)));
			//B =(int)pow((double)B, (double)(1.0 / (m*n)));

			newImagePtr[0][i][j] = B;
			newImagePtr[1][i][j] = G;
			newImagePtr[2][i][j] = R;

		}
	}

	for (int i = int((m - 1) / 2); i < (h - (m - 1) / 2); i++)  //�޸�Դͼ
	{
		for (int j = int((n - 1) / 2); j < (w - (n - 1) / 2); j++) {


			m_Image.m_pBits[0][i][j] = newImagePtr[0][i][j];
			m_Image.m_pBits[1][i][j] = newImagePtr[1][i][j];
			m_Image.m_pBits[2][i][j] = newImagePtr[2][i][j];

		}
	}

	////����ָ��,��ά������ڴ��ͷ�,delete

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] newImagePtr[i][j];//�����ڴ�
		}
		delete[] newImagePtr[i];

	}
	delete[] newImagePtr;

	Invalidate(1);

}


void CImage_ProcessingView::OnHarmonicmeanfilter()
{
	// TODO: �ڴ��������������룬г����ֵ�˲�
	if (m_Image.IsNull()) {

		OnFileOpen();
		//return;//���Բ�return,��ͼƬ��ֱ���˲���
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	int m = 5, n = 3; //������

	Dlg_HarmonicFilter har_dlg;

	if (IDOK == har_dlg.DoModal()) {

		while (har_dlg.m % 2 == 0 || har_dlg.m<0 || har_dlg.m>w || har_dlg.m > h || har_dlg.n % 2 == 0 || har_dlg.n<0 || har_dlg.n>w || har_dlg.n > h)
		{
			MessageBox(_T("������˲�������Ч,������������ʵ�������ֵ"));
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

	//���������ڴ�

	BYTE *** newImageArray = new BYTE**[3];

	for (int i = 0; i < 3; i++) {

		newImageArray[i] = new BYTE*[h];
		for (int j = 0; j < h; j++) {

			newImageArray[i][j] = new BYTE[w];
		}

	}

	//��ʼ��Ϊһ��ȫ�ڵ�ͼ��
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
					B += (double)1 / m_Image.m_pBits[0][i + p][j + q]; //�������
					G += (double)1 / m_Image.m_pBits[1][i + p][j + q];
					R += (double)1 / m_Image.m_pBits[2][i + p][j + q];
				}
			}
			newImageArray[0][i][j] = (BYTE)m*n / B;//г����ֵ�˲�

			newImageArray[1][i][j] = (BYTE)m*n / G;
			newImageArray[2][i][j] = (BYTE)m*n / R;

		}
	}

	//���˲��������ԭͼ
	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
	{
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
		{
			m_Image.m_pBits[0][i][j] = newImageArray[0][i][j];
			m_Image.m_pBits[1][i][j] = newImageArray[1][i][j];
			m_Image.m_pBits[2][i][j] = newImageArray[2][i][j];

		}
	}

	//TODO:�ͷ�newImageArray�����ڴ�,��new��˳��պ��෴
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

	// TODO: �ڴ��������������룺��г����ֵ�˲���
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;//���Բ�return,��ͼƬ��ֱ���˲���
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	int m = 5, n = 5; //������
	double Q = 1.5;

	Dlg_ContraHarmonicMeanFilter contra_dlg;

	if (IDOK == contra_dlg.DoModal()) {

		while (contra_dlg.m % 2 == 0 || contra_dlg.m<0 || contra_dlg.m>w || contra_dlg.m > h || contra_dlg.n % 2 == 0 || contra_dlg.n<0 || contra_dlg.n>w || contra_dlg.n > h)
		{
			MessageBox(_T("������˲�����m,n��Ч,������������ʵ�������ֵ"));
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

	//ÿ���ۼӵķ��Ӻͷ�ĸ,up��low
	long double Bu = 0, Gu = 0, Ru = 0;
	long double Bl = 0, Gl = 0, Rl = 0;

	//���������ڴ�

	BYTE *** newImageArray = new BYTE**[3];

	for (int i = 0; i < 3; i++) {

		newImageArray[i] = new BYTE*[h];
		for (int j = 0; j < h; j++) {

			newImageArray[i][j] = new BYTE[w];
		}

	}

	//��ʼ��Ϊһ��ȫ�ڵ�ͼ��
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int k = 0; k < 3; k++) {

				newImageArray[k][i][j] = 1;
			}
		}

	}

	//��������Դ��ͼ�����Ͽؼ�,ֱ������һ��������
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	GetClientRect(&rect);
	proRect.left = rect.left + rect.Width() / 2 - 80;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
	myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //����λ�á���С
	//myProCtrl.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTHREVERSE, proRect, this, 99); //����λ�á���С


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
					Bu += (double)pow(m_Image.m_pBits[0][i + p][j + q], Q + 1); //�ݴ������
					Gu += (double)pow(m_Image.m_pBits[1][i + p][j + q], Q + 1);
					Ru += (double)pow(m_Image.m_pBits[2][i + p][j + q], Q + 1);

					Bl += (double)pow(m_Image.m_pBits[0][i + p][j + q], Q); //�ݴ������
					Gl += (double)pow(m_Image.m_pBits[1][i + p][j + q], Q);
					Rl += (double)pow(m_Image.m_pBits[2][i + p][j + q], Q);
				}
			}

			newImageArray[0][i][j] = (BYTE)(Bu / Bl);//��г����ֵ�˲�
			newImageArray[1][i][j] = (BYTE)(Gu / Gl);
			newImageArray[2][i][j] = (BYTE)(Ru / Rl);

		}

		//��Ϊ�����ٶȺ���,�����ý�������ʾ���ȣ���
		double p = (double)i / (double)((m + n - 2) / 2); //������������޸�,ֻҪ�������ٶ���ʵ�ʴ����ٶȲ�����
		myProCtrl.SetPos(p);//���ֱ��SetPos(i)�ᵼ��,�������Ѿ�������,���ǻ�û�д�����

	}

	//���˲��������ԭͼ
	for (int i = (m - 1) / 2; i < h - (m - 1) / 2; i++)
	{
		for (int j = (n - 1) / 2; j < w - (n - 1) / 2; j++)
		{
			m_Image.m_pBits[0][i][j] = newImageArray[0][i][j];
			m_Image.m_pBits[1][i][j] = newImageArray[1][i][j];
			m_Image.m_pBits[2][i][j] = newImageArray[2][i][j];

		}
	}

	//TODO:�ͷ�newImageArray�����ڴ�,��new��˳��պ��෴
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
	// TODO: �ڴ���������������
	if (true == m_Image.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	double p_salt(0.4), p_pepper(0.4);
	int n = 10000;

	//TODO:�����Ի���,���ж�p_salt��p_pepper,�Լ�n�ĺϷ���
	Dlg_SaltPepperNoise sp_dlg;
	if (IDOK == sp_dlg.DoModal()) {

		while (sp_dlg.Pa < 0 || sp_dlg.Pb < 0 || sp_dlg.Pn < 0 || sp_dlg.Pa >1 || sp_dlg.Pb >1 || sp_dlg.Pn >1 || (sp_dlg.Pa + sp_dlg.Pb) > 1)
		{
			if (sp_dlg.Pa < 0 || sp_dlg.Pb < 0 || sp_dlg.Pn < 0 || sp_dlg.Pa >1 || sp_dlg.Pb >1 || sp_dlg.Pn >1)
			{
				MessageBox(L"����������Ⱦ�̶Ⱦ�������0~1֮��,����������!");
				//sp_dlg.DoModal();  //DoModal()���Զ�����UpdateData(),����дUpdateData()
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
				MessageBox(L"Pa��Pb֮�ͱ���С��1,����������!");
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
		return;  //û�����Ļ�,��"ȡ��"���޷�ȡ��
	}

	//ֱ�Ӷ�������Ҫ��ʹ�ó���,�����ⲿ����,���ʹ��vector��Ϊ�˶�̬����,���Կ��ƽ����������Գ��ֵĸ���,�Լ����������̶�
	std::vector<int> idxSalt_x, idxSalt_y;
	std::vector<int> idxPepper_x, idxPepper_y;//����ʹ�ö�̬�������Ҳ����,new,delete,����

	for (int k = 0; k < n; k++) {
		int ran = rand() % n;  //rand()����0~???֮�������
		if (ran < (int)(n*p_salt)) {
			idxSalt_x.push_back(rand() % w); //����һ��������������
			idxSalt_y.push_back(rand() % h);
		}
		else if (ran > (int)(n*p_salt) && ran < (int)(n*(p_pepper + p_salt)))
		{
			idxPepper_x.push_back(rand() % w); //����һ�����������������
			idxPepper_y.push_back(rand() % h);
		}
		else {
			//do nothing
		}

	}

	//ʹ��vector�±������Ȼ��,����ʹ�õ�����Ч�ʸ���,����Ҫע��,iter1,iter2����ͬ������,���д��һ��forѭ������������

	for (std::vector<int>::iterator
		iter1 = idxSalt_x.begin(), iter2 = idxSalt_y.begin();
		iter1 != idxSalt_x.end(), iter2 != idxSalt_y.end();  //ʹ�ö�̬����,����ͻ�򵥺ܶడ!!!!!!!!��ʱ����
		iter1++, iter2++)
	{
		for (int i = 0; i < 3; i++) {
			m_Image.m_pBits[i][*iter2][*iter1] = 255; //������

		}
	}
	//�����������forѭ���ֿ�д,��Ϊ������Pa !=Pbʱ,vector����size��һ��

	for (std::vector<int>::iterator iter3 = idxPepper_x.begin(), iter4 = idxPepper_y.begin();
		iter3 != idxPepper_x.end(), iter4 != idxPepper_y.end(); iter3++, iter4++)
	{
		for (int i = 0; i < 3; i++)
		{
			m_Image.m_pBits[i][*iter4][*iter3] = 1;  //��������
		}

	}

	Invalidate(1);
}


void CImage_ProcessingView::OnGaussiannoise()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

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
			MessageBox(L"������Ϸ�����������!");
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
			//������˹�������
			//������Marsaglia��Bray��1964�����,C++�汾: mu�Ǿ�ֵ,sigma�Ƿ���,X����N(0,1)�ֲ�
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


			//����ͨ��,���Դ���
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 5;

	Invalidate(1);
}


void CImage_ProcessingView::OnShowprocessedimage()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 0;

	Invalidate(1);
}


void CImage_ProcessingView::OnProcessimagebackup()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
		// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull() || m_Imagecp.IsNull()) {

		OnFileOpen();
		return;
	}
	m_Image.Flag = 1;

	m_Imagecp.X = 100;               //������ͼλ��,�Աȴ����Ч��
	m_Imagecp.Y = 100;
	m_Image.X = m_Imagecp.X + 10 + m_Imagecp.GetWidth();
	m_Image.Y = m_Imagecp.Y;

	Invalidate(1);
}


void CImage_ProcessingView::OnMaxMinvaluefilter()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}

	Dlg_MaxMinValueFilter dlg;
	BOOL maxcheck, mincheck, midcheck;
	int m(5), n(5);  //�˲�ģ��߳�

	if (IDOK == dlg.DoModal()) {

		maxcheck = dlg.maxcheck;
		mincheck = dlg.mincheck;
		midcheck = dlg.midcheck;

		while (dlg.m % 2 == 0 || dlg.n % 2 == 0 || dlg.m < 0 || dlg.n < 0 || dlg.m > h || dlg.n > w)
		{

			MessageBox(L"������Ϸ����˲�ģ��߳�!����Ϊ������!");

			if (IDOK == dlg.DoModal()) {

				//UpdateData();
			}
			else {
				return;
			}

		}

		//TODO:ͨ���Ի�������ȡ�˲�ģ���ֵ
		m = dlg.m;
		n = dlg.n;

	}
	else {
		return;
	}

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//�½���ά����,������ͼ
	BYTE *** newImageArr = new BYTE **[3];

	for (int k = 0; k < 3; k++) {

		newImageArr[k] = new BYTE *[h];

	}
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < h; i++) {

			newImageArr[k][i] = new BYTE[w];

		}
	}

	//�½�һ������,����ÿ���˲���ģ�����ĵĽ��,�Ա���ʹ�÷����㷨�����������ֵ
	BYTE**	rgbArr = new BYTE*[3];
	for (int k = 0; k < 3; k++) {
		rgbArr[k] = new BYTE[m*n];
	}

	if (TRUE == maxcheck && FALSE == mincheck && FALSE == midcheck) {

		//MessageBox(L"ѡ�������ֵ�˲���");

		//���ֵ�˲�
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
							rgbArr[k][kk] = m_Image.m_pBits[k][i + p][j + q];  //��ģ���ڵ�ֵȫ��������������
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
		//MessageBox(L"ѡ������Сֵ�˲���");
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
							rgbArr[k][kk] = m_Image.m_pBits[k][i + p][j + q];  //��ģ���ڵ�ֵȫ��������������
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
							rgbArr[k][kk] = m_Image.m_pBits[k][i + p][j + q];  //��ģ���ڵ�ֵȫ��������������
						}
						kk++;
					}
				}
				for (int k = 0; k < 3; k++)
				{
					//�е��˲�
					newImageArr[k][i][j] = (BYTE)((*std::min_element(rgbArr[k], rgbArr[k] + m * n) + *std::max_element(rgbArr[k], rgbArr[k] + m * n)) / 2);

				}

			}
		}

		midcheck = FALSE;

	}


	//�޸�ԭͼ
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

	//�ͷ��ڴ�
	for (int k = 0; k < 3; k++) {
		delete[]rgbArr[k];
	}
	delete[]rgbArr;

	//��new��˳����ǡ���෴��
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
	// TODO: ����Ӧ��ֵ�˲�~~~~~~

	if (m_Image.IsNull())
	{

		OnFileOpen();
		return;

	}

	m_Image.Flag = 0;
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	int m(3), n(3);//�˲���ģ��
	int m_max(9);//���Ƶ�����ģ��
	int n_max(9);
	int n_start(3), m_start(3); //ģ��߳���ʼֵ

	Dlg_AdaptiveMedianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		while (dlg.n_max % 2 == 0 || dlg.m_max % 2 == 0 || dlg.n_max < 0 || dlg.m_max < 0 ||
			dlg.n_start % 2 == 0 || dlg.m_start % 2 == 0 || dlg.n_start < 0 || dlg.m_start < 0
			)
		{
			MessageBox(L"������Ϸ��Ĳ���!!!");

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

	//����һ����ά����,������ͼ
	BYTE*** newImageArr = new BYTE **[3];
	for (int k = 0; k < 3; k++)
	{
		newImageArr[k] = new BYTE *[h];
		for (int i = 0; i < h; i++)
		{
			newImageArr[k][i] = new BYTE[w];
		}

	}

	//������
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	GetClientRect(&rect);
	proRect.left = rect.left + rect.Width() / 2 - 100;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE
	//myProCtrl.Create(WS_VISIBLE, proRect, this, 99); //����λ�á���С
	myProCtrl.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTHREVERSE, proRect, this, 99); //����λ�á���С


	BYTE* z_max = new BYTE[3];//ʵ������unsigned char
	BYTE* z_min = new BYTE[3];
	BYTE* z_med = new BYTE[3];

	int hk = 0;
	for (int i = m_max; i < h - m_max; i++)
	{
		for (int j = n_max; j < w - n_max; j++)
		{
			for (int k = 0; k < 3; k++)  //����ͨ��,���Ե��� ����
			{
				for (m = m_start, n = n_start; m < m_max + 1, n < n_max + 1; m++, n++)  //m,n��5��ʼ����,�ȴ�3��ʼ����,Ч����һ��
				{
					//��̬����һ����ά���鱣��ģ���ڵ�ͼ��Ҷ�
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

					std::sort(rgbArr[k], rgbArr[k] + m * n);  //������������

					z_max[k] = rgbArr[k][m*n - 1];   //���ֵ
					z_min[k] = rgbArr[k][0];           //��Сֵ
					z_med[k] = rgbArr[k][(int)(m*n - 1) / 2]; //��ֵ

					hk = 0;

					//�ͷ��ڴ�
					for (int k = 0; k < 3; k++)
					{
						delete[]rgbArr[k];
					}
					delete[]rgbArr;

					newImageArr[k][i][j] = z_med[k];

					//�ж���ֵ�Ƿ������
					if (z_max[k] != z_med[k] && z_min[k] != z_med[k])//B���̿�ʼ
					{
						//std::sort(rgbArr[k], rgbArr[k] + m * n);
						if (z_max[k] != m_Image.m_pBits[k][i][j] && z_min[k] != m_Image.m_pBits[k][i][j]) //ԭ���ص㲻�����,�򲻱�
						{

							newImageArr[k][i][j] = m_Image.m_pBits[k][i][j];

						}
						else
						{
							newImageArr[k][i][j] = z_med[k]; //ԭ���ص������,������ֵ���
						}

						break;  //����break,�ٶȿ�,���ӵĻ�,�ٶ�����,��Ч������,��Ϊ��ʱ�൱��ÿ�ζ���������ģ������˲�
					}

				}

			}

		}

		double p;
		p = (double)i / (double)(h - ((m*n - 1) / 2));
		int kl = p * 100;

		myProCtrl.SetPos(kl);//���ý�������ʾ����
	}

	//�޸�ԭͼ
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

	//�ͷ��ڴ�
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
	// TODO: �ڴ���������������

	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//�����������������Ƚ�ͼ��ȫ������
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int x = rand() % h;
			int y = rand() % w;
			if ((rand() % 3000) > 1)    //����,�����һ��������
			{
				for (int k = 0; k < 3; k++)
				{

					m_Image.m_pBits[k][i][j] = 0;

				}

			}
			else  //��һ�����ʼ���һЩ����,�������ʽ�Ϊ1/3000
			{
				for (int k = 0; k < 3; k++)
				{

					m_Image.m_pBits[k][i][j] = 255;

				}

			}
		}
	}
	////��������������ֱ��
	for (int k = 0; k < 3; k++) {
		for (int p = 10; p < int(h / 10); p += 3) {

			m_Image.m_pBits[k][1 * p][2 * p] = 255;

			m_Image.m_pBits[k][4 * p][2 * p] = 255;

			m_Image.m_pBits[k][7 * p][w - p - 10] = 255;//ע���Խ��

			m_Image.m_pBits[k][5 * p][w - 2 * p] = 255;//����һ��ע�Ⱑ,w-2*p��p��0��ʼ����ʱ,w-2*p =w,���Խ����

		}
	}
	Invalidate(TRUE);


	MessageBox(L"��ʼֱ�߼�⣡");

	////TODO���ȼ�������ͼ��Ϊ0��255��2ֵͼ��0Ϊ������255Ϊ�����㣬��������Ҳ��ʱֻ���Ǽ��һ�����ֱ��
	////����ֻ�Ǵ���һЩɢ�㣬�����ٿ��Ǽ����ݶȼ�⣬ȥ�룬��ֵ����

	const double PI = 3.141592;
	const int min_theta = 0;
	const int max_theta = 180;

	int max_thro = (int)sqrt(w*w + h * h);    //thro�����ֵ����ʵ����ͼ��ĶԽ��߾���

	//��̬��������
	int **countArr = new int*[sizeof(int) * max_theta];
	for (int i = 0; i < max_theta; i++)
	{
		countArr[i] = new int[sizeof(int) * max_thro];
		memset(countArr[i], 0, sizeof(int)*max_thro); //��ʼ��
	}

	//ͳ��ÿ�����������е�theta��thro��������count������
	for (int p_theta = 0; p_theta < max_theta; p_theta++)
	{
		//cos_theta��sin_theta
		double cos_theta, sin_theta;
		cos_theta = cos(double(PI * p_theta / 180));
		sin_theta = sin(double(PI * p_theta / 180));

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (m_Image.m_pBits[0][i][j] == 255)  //�Ѿ�תΪ�Ҷ�ͼ�����ֻ����Bͨ��
				{
					int thro = int(i * cos_theta + j * sin_theta);
					if (0 < thro && thro < max_thro)
					{
						countArr[p_theta][thro]++;  //ͳ��ֱ�ߵĲ���
					}
				}
			}
		}
	}

	//Ѱ��theta_thro�Ե����������Ҳ����Ѱ��count���ֵ����Ӧ��theta_thro

	std::vector<int> v_theta(0);  //�洢�ҵ���ֱ������Ӧ�Ĳ���
	std::vector<int> v_thro(0);

	for (int i = min_theta; i < max_theta; i++)
	{
		for (int j = 0; j < max_thro; j++)
		{
			if (countArr[i][j] > 6)  //����6��������һ������Ϊ��һ��ֱ��
			{
				v_theta.push_back(i);
				v_thro.push_back(j);
			}
		}

	}

	//����x��yƽ�棬�õ�����ֱ�ߵı��ʽ, ������ͼ����ÿ���㣬�ж��Ƿ��ڸ�ֱ���ϣ�������ֱ��
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
					m_Image.m_pBits[0][i][j] = b;  //��ɫ
					m_Image.m_pBits[1][i][j] = g;
					m_Image.m_pBits[2][i][j] = r;

				}
			}
		}
	}

	//�ͷŶ�̬����countArr
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
	// TODO: �ڴ���������������

	if (m_Image.IsNull())
	{
		OnFileOpen();
		return;
	}
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();
	MessageBox(_T("����ȡ�Ҷ�ͼ!"));
	OnTogrey();
	//MessageBox(_T("�������ƽ������~!"));
	//��ֵƽ��
	//OnMeanfilter();

	//��Ե���,Ϊ�˼�,�ȿ���prewitt����
	//���������ڴ�
	MessageBox(_T("�����Ե���!"));
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
	//����ͼ����Դͼ
	for (int j = 1; j < h - 1; j++)//��ͼ��û�г�ʼ����!
	{
		for (int i = 1; i < w - 1; i++)
		{
			m_Image.m_pBits[0][j][i] = newImageArr[0][j][i];
			m_Image.m_pBits[1][j][i] = newImageArr[1][j][i];
			m_Image.m_pBits[2][j][i] = newImageArr[2][j][i];
		}
	}
	Invalidate(TRUE);

	//��ֵ��
	MessageBox(_T("����0~255��ֵ��!"));
	for (int j = 0; j < h; j++)//��ͼ��û�г�ʼ����!
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {

		OnFileOpen();
		return;
	}

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

	//�ָ���ԭͼ,�Է�ֹ�û���ε��ô˺�������ɻҶ�ֵȫ��Ϊ0�����
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
	// TODO: �ڴ���������������
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


	//�ָ���ԭͼ,�Է�ֹ�û���ε��ô˺�������ɻҶ�ֵȫ��Ϊ0�����
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
		//����ͼ����Դͼ
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

	

	//����ָ��

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] newImageArr[i][j];//�����ڴ�
		}
	}
	for (int i = 0; i < 3; i++)
	{
		delete[] newImageArr[i];
	}
	delete[] newImageArr;

	Invalidate(1);

}
