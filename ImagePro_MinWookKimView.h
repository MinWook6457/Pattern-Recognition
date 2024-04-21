
// ImagePro_MinWookKimView.h: CImageProMinWookKimView 클래스의 인터페이스
//

#pragma once


class CImageProMinWookKimView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProMinWookKimView() noexcept;
	DECLARE_DYNCREATE(CImageProMinWookKimView)

// 특성입니다.
public:
	CImageProMinWookKimDoc* GetDocument() const;
	int viewMode;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProMinWookKimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnRegionSharpeing();
	afx_msg void OnRegionMeaning();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionMedian();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnOpening();
	afx_msg void OnClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutAvg();
	afx_msg void OnGeometryRotate();
	afx_msg void OnGeometryWarping();
	afx_msg void OnGeometryMorphing();
};

#ifndef _DEBUG  // ImagePro_MinWookKimView.cpp의 디버그 버전
inline CImageProMinWookKimDoc* CImageProMinWookKimView::GetDocument() const
   { return reinterpret_cast<CImageProMinWookKimDoc*>(m_pDocument); }
#endif

