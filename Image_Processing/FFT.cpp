#include "StdAfx.h"
#include "FFT.h"
#include <math.h>
#include "Calculate.h"
#define PI 3.1415926
void fastFourierTran(ComplexNum * pTd, ComplexNum * pFd, int power)
{
	long i, j;//i:行循环变量；j:列循环变量
	long dotCount;//傅立叶变换的点数
	int k;//循环变量
	int bfsize, p;//中间变量
	double angle;//角度
	ComplexNum * pWn, *temReg1, *temReg2, *temReg;

	dotCount = 1 << power;//计算傅立叶变换点数

	///////////分配运算所需内存//////////////////////////
	pWn = new ComplexNum[sizeof(ComplexNum)*dotCount / 2];
	temReg1 = new ComplexNum[sizeof(ComplexNum)*dotCount];
	temReg2 = new ComplexNum[sizeof(ComplexNum)*dotCount];
	////////////计算加权系数/////////////////////
	for (i = 0; i < dotCount / 2; i++)
	{
		angle = -i * PI * 2 / dotCount;
		pWn[i].re = cos(angle);
		pWn[i].im = sin(angle);
	}

	/////////////将时域写入temReg1//////////////
	memcpy(temReg1, pTd, sizeof(ComplexNum)*dotCount);

	/////////////蝶形运算///////////////////////////////
	for (k = 0; k < power; k++)					//k 是蝶形运算的迭代次数
	{
		for (j = 0; j < 1 << k; j++)				//j 是每次迭代的组群个数
		{
			bfsize = 1 << (power - k);			//bfsize用于计算组群大小及跨越尺度
			for (i = 0; i < bfsize / 2; i++)		//i 是迭代中每个组群内蝶形个数
			{
				p = j * bfsize;
				temReg2[i + p] = FSAdd(temReg1[i + p], temReg1[i + p + bfsize / 2]);
				temReg2[i + p + bfsize / 2] = FSMul(FSSub(temReg1[i + p], temReg1[i + p + bfsize / 2]), pWn[i*(1 << k)]);
			}
		}
		temReg = temReg1;//交换temReg1,2
		temReg1 = temReg2;
		temReg2 = temReg;
	}

	/////////////////////利用比特反转索引，重新排列顺序/////////////////
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

	/////////////////////回收数组指针/////////////////////////////
	delete[]pWn;
	delete[]temReg1;
	delete[]temReg2;

}