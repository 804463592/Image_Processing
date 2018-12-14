#include "StdAfx.h"
#include "MyImage_.h"


MyImage_::MyImage_(void):Flag(0), X(100), Y(100)
{
	m_pBits=NULL;
}


MyImage_::~MyImage_(void)
{

	if ( m_pBits!=NULL)
	{
		int h=m_CImage.GetHeight();
		for   (int   i=0;   i<3;   i++)     //这个框架这里,可能是出于防止多次delete???/,原来这里是i<2
		{          
			for   (int   j=0;   j<h;   j++)         
			{   

				delete[] m_pBits[i][j];   
				m_pBits[i][j]=NULL;
			}
		}
		for (int   i=0;   i<3;   i++)//这个框架这里,可能是出于防止多次delete???/,原来这里是i<2
		{
			delete[] m_pBits[i];  
			m_pBits[i]=NULL;
		}
		delete[]  m_pBits;
		m_pBits=NULL; 
	}
}

HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName) 
{
	m_CImage.Load(pszFileName);
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址

	CImage* mp = &m_CImage;

	if (abs(nrow)!=3*w)
	{
		////**************************************
		///*创建三维数组并将m_CImage复制进三维数组*/
		//m_pBits = new  BYTE **[3];//3个维度；分配内存

		//for (int i = 0; i < 3; i++)
		//{
		//	//m_pBits[i] = (BYTE**)new  BYTE*[h]; 
		//	m_pBits[i] = /*(BYTE**)*/new  BYTE*[h];

		//}
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < h; j++)
		//	{
		//		m_pBits[i][j] = new BYTE[w];
		//	}
		//}

		///*将m_CImage复制进三维数组*/

		//for (int j = 0; j < h; j++)
		//{
		//	for (int k = 0; k < w; k++)
		//	{
		//		m_pBits[0][j][k] = psrc[j*nrow + k];//B
		//		m_pBits[1][j][k] = psrc[j*nrow + k];//G
		//		m_pBits[2][j][k] = psrc[j*nrow + k];//R
		//		//COLORREF pixel;
		//		//byte r, g, b, avg;
		//		//pixel = mp->GetPixel(k,j);
		//		//r = GetRValue(pixel);
		//		//g = GetGValue(pixel);
		//		//b = GetBValue(pixel);
		//		//avg = (int)((r + g + b) / 3);
		//		////image - ＞SetPixelRGB(x, y, avg, avg, avg);
		//		//m_pBits[0][j][k] = avg;
		//		//m_pBits[1][j][k] = avg;
		//		//m_pBits[2][j][k] = avg;

		//	}
		//}

		///*创建三维数组并将m_CImage复制进三维数组*/
		//return(S_OK);//为了与CImge类的Load函数返回值相同

		//**********************************
		m_CImage.Destroy();
		return ( S_FALSE );//防止加载非24位的彩色图,在image_process_view中的OnFileOpen弹出错误信息
	}
	else {

		/*创建三维数组并将m_CImage复制进三维数组*/
		//m_pBits= (BYTE***)new   BYTE**[3];  //这个是助教给的 

		m_pBits = new  BYTE **[3];//3个维度；分配内存

		for (int i = 0; i < 3; i++)
		{
			//m_pBits[i] = (BYTE**)new  BYTE*[h]; 
			m_pBits[i] = /*(BYTE**)*/new  BYTE*[h];

		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{

				m_pBits[i][j] = new BYTE[w];
			}
		}

		/*将m_CImage复制进三维数组*/

		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				m_pBits[0][j][k] = psrc[j*nrow + k * 3];//B
				m_pBits[1][j][k] = psrc[j*nrow + k * 3 + 1];//G
				m_pBits[2][j][k] = psrc[j*nrow + k * 3 + 2];//R

			}
		}

		/*创建三维数组并将m_CImage复制进三维数组*/
		return(S_OK);//为了与CImge类的Load函数返回值相同
	}

}
// HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName) 
//{
//	m_CImage.Load(pszFileName);
//
//}

BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest,
	_In_ int nDestWidth,
	_In_ int nDestHeight) const 
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址
	/*将三维数组复制进m_CImage*/
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	/*将三维数组复制进m_CImage*/

	return m_CImage.Draw(hDestDC,xDest, yDest,nDestWidth, nDestHeight);//调用CImage的Draw;
}
bool MyImage_::IsNull() const 
{
	return m_CImage.IsNull();
}

void MyImage_::Destroy() 
{
	m_CImage.Destroy();
}

int MyImage_::GetWidth() const 
{
	return m_CImage.GetWidth();
}
int MyImage_::GetHeight() const
{
	return m_CImage.GetHeight();
}


BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest) const
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址
	/*将三维数组复制进m_CImage*/

	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	/*将三维数组复制进m_CImage*/
	return m_CImage.Draw(hDestDC,xDest,yDest);
}

HRESULT MyImage_::Save(
	_In_z_ LPCTSTR pszFileName,
	_In_ REFGUID guidFileType) const
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址
	for (int j=0;j<h;j++)
	{
	
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	return m_CImage.Save(pszFileName,guidFileType);

}


//==============================
//函数功能：统计直方图
//无输入输出，直接通过probability保存
//======================
void MyImage_::GetHistgram() {

	BYTE *lpSrc;	//指向源图的指针
	long i, j;		//循环计数
	int w = GetWidth();
	int h = GetHeight();
	int gray[3][256];	//灰度计数
	int nrow = m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	//float probability[256];
	BYTE pixel0, pixel1,pixel2;		//像素值
	//BYTE *lpDIBBits=(BYTE *)m_CImage.GetBits();//获得源图像起始位置
	memset(gray, 0, sizeof(gray));//初始化

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				pixel0 = m_pBits[0][j][i];
				pixel1 = m_pBits[1][j][i];
				pixel2 = m_pBits[2][j][i];

				gray[0][pixel0]++;
				gray[1][pixel1]++;
				gray[2][pixel2]++;

			}

			for (i = 0; i < 256; i++) {

				probability[0][i] = gray[0][i] / (w*h*1.0f);
				probability[1][i] = gray[1][i] / (w*h*1.0f);
				probability[2][i] = gray[2][i] / (w*h*1.0f);

			}

	}
}
