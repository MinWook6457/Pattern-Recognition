
// ImagePro_MinWookKimView.cpp: CImageProMinWookKimView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_MinWookKim.h"
#endif

#include "ImagePro_MinWookKimDoc.h"
#include "ImagePro_MinWookKimView.h"

#define TWO_IMAGES 1
#define THREE_IMAGES 2
#define TWO_IMAGES_SCALED 4
#define MORPHING 8

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProMinWookKimView

IMPLEMENT_DYNCREATE(CImageProMinWookKimView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProMinWookKimView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProMinWookKimView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CImageProMinWookKimView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProMinWookKimView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProMinWookKimView::OnPixelTwoImageAdd)
	ON_COMMAND(ID_REGION_SHARPEING, &CImageProMinWookKimView::OnRegionSharpeing)
	ON_COMMAND(ID_REGION_MEANING, &CImageProMinWookKimView::OnRegionMeaning)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProMinWookKimView::OnRegionSobel)
	ON_COMMAND(ID_EROSION, &CImageProMinWookKimView::OnErosion)
	ON_COMMAND(ID_DILATION, &CImageProMinWookKimView::OnDilation)
	ON_COMMAND(ID_OPENING, &CImageProMinWookKimView::OnOpening)
	ON_COMMAND(ID_CLOSING, &CImageProMinWookKimView::OnClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProMinWookKimView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CImageProMinWookKimView::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProMinWookKimView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CImageProMinWookKimView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImageProMinWookKimView::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProMinWookKimView::OnGeometryWarping)
	ON_COMMAND(ID_GEOMETRY_MORPHING, &CImageProMinWookKimView::OnGeometryMorphing)
END_MESSAGE_MAP()

// CImageProMinWookKimView 생성/소멸

CImageProMinWookKimView::CImageProMinWookKimView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProMinWookKimView::~CImageProMinWookKimView()
{
}

BOOL CImageProMinWookKimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProMinWookKimView 그리기

void CImageProMinWookKimView::OnDraw(CDC* pDC)
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;

	if (pDoc->depth == 1) {
		for (int y = 0; y < pDoc->imageHeight; y++) {
			for (int x = 0; x < pDoc->imageWidth; x++) {
				pDC->SetPixel(x, y, RGB((pDoc->inputImg[y][x]), pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
			}
		}


		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++) {     // 두번째입력영상출력
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x]));
				}
			}

			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
				}
			}
		}
		else if (viewMode == TWO_IMAGES_SCALED) {
			for (int y = 0; y < pDoc->gImageHeight ; y++)// 크기가변한결과영상출력
				for(int x=0; x< pDoc->gImageWidth; x++) 
					pDC->SetPixel(x+pDoc->imageWidth+30, y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
		}
		else if (viewMode == MORPHING) {
			for (int y = 0; y < pDoc->imageHeight; y++)       // 두번째입력영상출력
				for(int x=0; x< pDoc->imageWidth; x++)
					pDC->SetPixel(x+pDoc->imageWidth+30, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x])); 
			
			for (int i= 0; i< 10; i++) 
				for(int y=0; y< pDoc->imageHeight; y++)       // 모핑결과출력
					for(int x=0; x< pDoc->imageWidth; x++) 
						pDC->SetPixel(x+pDoc->imageWidth*2+60,y, RGB(pDoc->morphedImg[i][y][x], pDoc->morphedImg[i][y][x], pDoc->morphedImg[i][y][x]));
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++) {    
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
				}
			}
		}
	}
	else if (pDoc->depth == 3) {
		for (int y = 0; y < pDoc->imageHeight; y++) {
			for (int x = 0; x < pDoc->imageWidth; x++) {
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3 * x], pDoc->inputImg[y][3 * x + 1], pDoc->inputImg[y][3 * x + 2]));
			}
		}
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->inputImg2[y][3 * x], pDoc->inputImg2[y][3 * x + 1], pDoc->inputImg2[y][3 * x + 2]));
				}
			}

			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x + 1], pDoc->resultImg[y][3 * x + 2]));
				}
			}
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x + 1], pDoc->resultImg[y][3 * x + 2]));
				}
			}
		}
	}
				
		


	
	/*
	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			pDC->SetPixel(x, y, RGB((pDoc->inputImg[y][x]), pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
		}
	}
	
	if (viewMode == THREE_IMAGES) {
		for (int y = 0; y < 256; y++)       // 두번째입력영상출력
			for(int x=0; x<256; x++) 
				pDC->SetPixel(x+300, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x]));

		for (int y = 0; y < 256; y++) {
			for (int x = 0; x < 256; x++) {
				pDC->SetPixel(x + 600, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
			}
		}
	}
	else {
		for (int y = 0; y < 256; y++)       // 결과영상출력
			for (int x = 0; x < 256; x++)
				pDC->SetPixel(x + 300, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
	}
	*/
}

void CImageProMinWookKimView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;

	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProMinWookKimView 인쇄


void CImageProMinWookKimView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProMinWookKimView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProMinWookKimView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProMinWookKimView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProMinWookKimView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProMinWookKimView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProMinWookKimView 진단

#ifdef _DEBUG
void CImageProMinWookKimView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProMinWookKimView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProMinWookKimDoc* CImageProMinWookKimView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProMinWookKimDoc)));
	return (CImageProMinWookKimDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProMinWookKimView 메시지 처리기


void CImageProMinWookKimView::OnPixelAdd()
{
	CImageProMinWookKimDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 

	if (pDoc->inputImg == NULL)
		return;

	pDoc->PixelAdd(); 
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
	
}


void CImageProMinWookKimView::OnPixelHistoEq()
{
		CImageProMinWookKimDoc* pDoc = GetDocument();

		ASSERT_VALID(pDoc);


		if (pDoc->inputImg == NULL) // 입력 영상이 있는지 검사
			return;

		pDoc->PixelHistoEq();

		viewMode = TWO_IMAGES;
		Invalidate(FALSE); // 화면 갱신
}


void CImageProMinWookKimView::OnPixelTwoImageAdd()
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelTwoImageAdd();

	viewMode = THREE_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnRegionSharpeing()
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->RegionSharpening();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnRegionMeaning()
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->RegionMeaning();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnRegionSobel()
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->RegionSobel();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}

void CImageProMinWookKimView::OnRegionMedian()
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->RegionMedian();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}

void CImageProMinWookKimView::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Erosion();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Dilation();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Opening();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Closing();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryZoominPixelCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 
	if (pDoc->inputImg == NULL) 
		return; 
	
	pDoc->GeometryZoominPixelCopy(); 
	viewMode = TWO_IMAGES_SCALED; 
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryZoominInterpolation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
	if (pDoc->inputImg == NULL) 
		return; 
	pDoc->GeometryZoominInterpolation(); 
	viewMode = TWO_IMAGES_SCALED; 
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryZoomoutSubsampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL)
		return;
	pDoc->GeometryZoomoutSubsampling();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryZoomoutAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL)
		return;
	pDoc->GeometryZoomoutAvg();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL)
		return;
	pDoc->GeometryRotate();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryWarping()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL)
		return;
	pDoc->GeometryWarping();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProMinWookKimView::OnGeometryMorphing()
{
	CImageProMinWookKimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
	pDoc->GeometryMorphing();     
	viewMode = MORPHING; 
	Invalidate(FALSE);
}
