#pragma once
#include "ComplexNum.h"

/************************************************************************/
/*函数名称： FastFourierTran
 *函数参数：
		 CplexNum * pTd		指向时域数组指针
		 CplexNum * pFd		指向频域数组指针
		 int power			2的幂次方，迭代次数
  *函数功能：一维快速傅立叶变换
*/
/************************************************************************/

void fastFourierTran(ComplexNum * pTd, ComplexNum * pFd, int power);