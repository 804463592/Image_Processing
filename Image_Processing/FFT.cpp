#include "StdAfx.h"
#include "FFT.h"
#include <math.h>
#include "Calculate.h"
#define PI 3.1415926
void fastFourierTran(ComplexNum * pTd, ComplexNum * pFd, int power)
{
	long i, j;//i:��ѭ��������j:��ѭ������
	long dotCount;//����Ҷ�任�ĵ���
	int k;//ѭ������
	int bfsize, p;//�м����
	double angle;//�Ƕ�
	ComplexNum * pWn, *temReg1, *temReg2, *temReg;

	dotCount = 1 << power;//���㸵��Ҷ�任����

	///////////�������������ڴ�//////////////////////////
	pWn = new ComplexNum[sizeof(ComplexNum)*dotCount / 2];
	temReg1 = new ComplexNum[sizeof(ComplexNum)*dotCount];
	temReg2 = new ComplexNum[sizeof(ComplexNum)*dotCount];
	////////////�����Ȩϵ��/////////////////////
	for (i = 0; i < dotCount / 2; i++)
	{
		angle = -i * PI * 2 / dotCount;
		pWn[i].re = cos(angle);
		pWn[i].im = sin(angle);
	}

	/////////////��ʱ��д��temReg1//////////////
	memcpy(temReg1, pTd, sizeof(ComplexNum)*dotCount);

	/////////////��������///////////////////////////////
	for (k = 0; k < power; k++)					//k �ǵ�������ĵ�������
	{
		for (j = 0; j < 1 << k; j++)				//j ��ÿ�ε�������Ⱥ����
		{
			bfsize = 1 << (power - k);			//bfsize���ڼ�����Ⱥ��С����Խ�߶�
			for (i = 0; i < bfsize / 2; i++)		//i �ǵ�����ÿ����Ⱥ�ڵ��θ���
			{
				p = j * bfsize;
				temReg2[i + p] = FSAdd(temReg1[i + p], temReg1[i + p + bfsize / 2]);
				temReg2[i + p + bfsize / 2] = FSMul(FSSub(temReg1[i + p], temReg1[i + p + bfsize / 2]), pWn[i*(1 << k)]);
			}
		}
		temReg = temReg1;//����temReg1,2
		temReg1 = temReg2;
		temReg2 = temReg;
	}

	/////////////////////���ñ��ط�ת��������������˳��/////////////////
	for (j = 0; j < dotCount; j++)
	{
		p = 0;
		for (i = 0; i < power; i++)
		{
			if (j&(1 << i))
			{
				p += 1 << (power - i - 1);
			}
		}
		pFd[j] = temReg1[p];
	}

	/////////////////////��������ָ��/////////////////////////////
	delete[]pWn;
	delete[]temReg1;
	delete[]temReg2;

}