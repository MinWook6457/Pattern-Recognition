
// ImagePro_MinWookKimDoc.h: CImageProMinWookKimDoc 클래스의 인터페이스
//


#pragma once


class CImageProMinWookKimDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProMinWookKimDoc() noexcept;
	DECLARE_DYNCREATE(CImageProMinWookKimDoc)

// 특성입니다.

public:
	/*
	unsigned char inputImg[256][256];
	unsigned char inputImg2[256][256];
	unsigned char resultImg[256][256];
	*/
	unsigned char** inputImg; 
	unsigned char** inputImg2;
	unsigned char** resultImg;
	int imageWidth; // 가로
	int imageHeight; // 세로
	int depth; // 1 = 흑백, 3 = 컬러

	// 결과 영상의 크기가 변화되는 기하학적 처리를 위해 추가되는 코드
	int gImageWidth;// 크기가 변한 결과 영상의 가로크기
	int gImageHeight;// 크기가 변한 결과 영상의 세로크기
	unsigned char **gResultImg;// 크기가 변한 결과 영상에 대한 포인터변수

	unsigned char** morphedImg[10]; // 모핑 결과 저장

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProMinWookKimDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void PixelAdd();
	void OnPixelHistoEq();
	void PixelHistoEq();
	void PixelTwoImageAdd();
	void LoadTwoImages();
	void LoadImageFile();
	void LoadImageFile(CArchive &ar);
	void loadSecondImageFile();
	void loadSecondImageFile(CArchive& ar);
	void RegionSharpening();
	void Convolve();
	void Convolve(unsigned char** inputImg, unsigned char** resultImg, int cols, int rows, float mask[][3], int bias, int depth);
	void RegionMeaning();
	void RegionSobel();
	void RegionMedian();
	void Erosion();
	void Dilation();
	void Opening();
	void CopyResultToInput();
	void Closing();
	void GeometryZoominPixelCopy();
	void GeometryZoominInterpolation();
	void GeometryZoomoutSubsampling();
	void GeometryZoomoutAvg();
	void GeometryRotate();
	void GeometryWarping();
	void GeometryMorphing();
};
