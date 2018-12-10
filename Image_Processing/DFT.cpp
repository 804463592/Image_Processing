#include "StdAfx.h"
#include "DFT.h"
#include "FFT.h"


void fourierTransform(ComplexNum *pTd, int wi, int he, ComplexNum * pFd, CImage_ProcessingView *pv)
{
	int i, j;					//循环控制变量
	int wid = 1, hei = 1;		//进行傅立叶变换的宽度和高度
	int width_power = 0, height_power = 0;		//wid hei :2的幂次数

//////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
	while (wid * 2 <= wi)
	{
		wid *= 2;
		width_power++;
	}
	while (hei * 2 <= he)
	{
		hei *= 2;
		height_power++;
	}

	/////////////X方向FFT////////////////
	for (i = 0; i < hei; i++)
	{
		fastFourierTran(&pTd[wid*i], &pFd[wid*i], width_power);

		double p;
		p = (double)i / (double)(hei);
		int k = p * 50;

	}

	///////////////矩阵转置///////////
	for (i = 0; i < hei; i++)
		for (j = 0; j < wid; j++)
			pTd[hei * j + i] = pFd[wid *i + j];

	/////////////Y方向一维FFT////////////////
	for (j = 0; j < wid; j++)
	{
		fastFourierTran(&pTd[j*hei], &pFd[hei*j], height_power);

		double p;
		p = (double)j / (double)(wid);
		int k = p * 50;
	}

	////////////pFd存储为傅立叶变换的结果，但需要转置回来存在pTd/////////
	for (i = 0; i < hei; i++)
		for (j = 0; j < wid; j++)
			pTd[wid *i + j] = pFd[hei *j + i];

}