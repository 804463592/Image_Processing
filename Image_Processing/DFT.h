#pragma once
#include "ComplexNum.h"
#include "Image_ProcessingView.h"
/************************************************************************/
/* 函数参数含义：
		   ComplexNum * pTd		指向时域数组指针
		   int wid				图像宽度
		   int hei				图像高度
		   ComplexNum * pFd		指向频域数组指针
	函数功能：调用FFT来计算DFT
	*/
	/************************************************************************/
void fourierTransform(ComplexNum *pTd, int wid, int hei, ComplexNum * pFd, CImage_ProcessingView* p);