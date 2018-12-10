#include "StdAfx.h"
#include "DFT.h"
#include "FFT.h"


void fourierTransform(ComplexNum *pTd, int wi, int he, ComplexNum * pFd, CImage_ProcessingView *pv)
{
	int i, j;					//ѭ�����Ʊ���
	int wid = 1, hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int width_power = 0, height_power = 0;		//wid hei :2���ݴ���

//////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
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

	/////////////X����FFT////////////////
	for (i = 0; i < hei; i++)
	{
		fastFourierTran(&pTd[wid*i], &pFd[wid*i], width_power);

		double p;
		p = (double)i / (double)(hei);
		int k = p * 50;

	}

	///////////////����ת��///////////
	for (i = 0; i < hei; i++)
		for (j = 0; j < wid; j++)
			pTd[hei * j + i] = pFd[wid *i + j];

	/////////////Y����һάFFT////////////////
	for (j = 0; j < wid; j++)
	{
		fastFourierTran(&pTd[j*hei], &pFd[hei*j], height_power);

		double p;
		p = (double)j / (double)(wid);
		int k = p * 50;
	}

	////////////pFd�洢Ϊ����Ҷ�任�Ľ��������Ҫת�û�������pTd/////////
	for (i = 0; i < hei; i++)
		for (j = 0; j < wid; j++)
			pTd[wid *i + j] = pFd[hei *j + i];

}