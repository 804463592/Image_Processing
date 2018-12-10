#pragma once
#include "ComplexNum.h"

/************************************************************************/
/*�������ƣ� FastFourierTran
 *����������
		 CplexNum * pTd		ָ��ʱ������ָ��
		 CplexNum * pFd		ָ��Ƶ������ָ��
		 int power			2���ݴη�����������
  *�������ܣ�һά���ٸ���Ҷ�任
*/
/************************************************************************/

void fastFourierTran(ComplexNum * pTd, ComplexNum * pFd, int power);