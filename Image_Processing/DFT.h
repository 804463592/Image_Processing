#pragma once
#include "ComplexNum.h"
#include "Image_ProcessingView.h"
/************************************************************************/
/* �����������壺
		   ComplexNum * pTd		ָ��ʱ������ָ��
		   int wid				ͼ����
		   int hei				ͼ��߶�
		   ComplexNum * pFd		ָ��Ƶ������ָ��
	�������ܣ�����FFT������DFT
	*/
	/************************************************************************/
void fourierTransform(ComplexNum *pTd, int wid, int hei, ComplexNum * pFd, CImage_ProcessingView* p);