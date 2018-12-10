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


	HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName);//����ͼ�񣬲���pszFileName���ļ�·�����ļ���
	BOOL  MyImage_::Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight) const;//��ʾͼ��hDestDC�ǻ�ͼ�豸�����ĵľ����xDest,yDest�ǻ�ͼ���Ͻ���ʼ������꣬nDestWidth��Ҫ��Ŀ�ȣ�nDestHeight��Ҫ��ĸ߶�

	BOOL  MyImage_::Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest) const;//��ʾͼ�񣬲���ͬ��һ��Draw����;�൱����һ��Draw����������Ϊͼ��Ŀ�Ⱥ͸߶ȵ����

	HRESULT MyImage_::Save(
		_In_z_ LPCTSTR pszFileName,
		_In_ REFGUID guidFileType = GUID_NULL) const;//����ͼ��pszFileNameΪ·�������ļ����� guidFileType��û���˽��

	bool MyImage_::IsNull() const ;//�ж�ͼ���Ƿ�Ϊ�գ����ǿշ���0
	void MyImage_::Destroy() ;//����MyImage_����ص��ڴ��е�ͼ��
	int MyImage_::GetWidth()const;//����ͼ��Ŀ��
	int MyImage_::GetHeight() const;//����ͼ��ĸ߶�


	float probability[3][256];

	CImage m_CImage;

	BYTE*** m_pBits;//��ά���飬���ڱ���ͼ���BGR����ֵ

	int Flag;

	//==============================
	//�������ܣ�ͳ��ֱ��ͼ
	//�����������ֱ��ͨ��probability����
	//======================
	void  GetHistgram(void );

	// //��ʾ������λ������x
	int X;
	// ��ʾ������λ������Y
	int Y;


private:
	//CImage m_CImage;
	
};

