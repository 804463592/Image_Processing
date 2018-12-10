#pragma once
class MyImage_
{
public:
	MyImage_(void);
	~MyImage_(void);
	//inline HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName) throw();
	//inline BOOL  MyImage_::Draw(
	//	_In_ HDC hDestDC,
	//	_In_ int xDest,
	//	_In_ int yDest,
	//	_In_ int nDestWidth,
	//	_In_ int nDestHeight) const throw();
	//inline bool MyImage_::IsNull() const throw();
	//inline void MyImage_::Destroy() throw();
	//inline int MyImage_::GetWidth() const throw();
	//inline int MyImage_::GetHeight() const throw();


	HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName);//加载图像，参数pszFileName是文件路径及文件名
	BOOL  MyImage_::Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight) const;//显示图像，hDestDC是绘图设备上下文的句柄，xDest,yDest是绘图左上角起始点的坐标，nDestWidth是要绘的宽度，nDestHeight是要绘的高度

	BOOL  MyImage_::Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest) const;//显示图像，参数同上一个Draw函数;相当于上一个Draw后两个参数为图像的宽度和高度的情况

	HRESULT MyImage_::Save(
		_In_z_ LPCTSTR pszFileName,
		_In_ REFGUID guidFileType = GUID_NULL) const;//保存图像，pszFileName为路径名和文件名， guidFileType我没有了解过

	bool MyImage_::IsNull() const ;//判断图像是否为空，如是空返回0
	void MyImage_::Destroy() ;//销毁MyImage_类加载到内存中的图像
	int MyImage_::GetWidth()const;//返回图像的宽度
	int MyImage_::GetHeight() const;//返回图像的高度


	float probability[3][256];

	CImage m_CImage;

	BYTE*** m_pBits;//三维数组，用于保存图像的BGR像素值

	int Flag;

	//==============================
	//函数功能：统计直方图
	//无输入输出，直接通过probability保存
	//======================
	void  GetHistgram(void );

	// //显示的中心位置坐标x
	int X;
	// 显示的中心位置坐标Y
	int Y;


private:
	//CImage m_CImage;
	
};

