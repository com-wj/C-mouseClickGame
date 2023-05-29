
// 20171392_P1View.cpp : CMy20171392_P1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20171392_P1.h"
#endif

#include "20171392_P1Doc.h"
#include "20171392_P1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20171392_P1View

IMPLEMENT_DYNCREATE(CMy20171392_P1View, CView)

BEGIN_MESSAGE_MAP(CMy20171392_P1View, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMy20171392_P1View 생성/소멸

CMy20171392_P1View::CMy20171392_P1View()
	: m_pDC(NULL)
	, m_fWinHeight(0)
	, m_fWinWidth(0)
	, m_fStepX(0)
	, m_fStepY(0)
	, StageNum(0)
	, m_ptMouseDown(0)
	, convertXpos(0)
	, convertYpos(0)
	, aspect_ratio(0)
	, m_Life(0)
	, m_fLifeBoxPosX(0)
	, m_fLifeBoxPosY(0)
	, m_fStepXLifeBox(0)
	, m_fStepYLifeBox(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_fStepX = 2.0f;
	m_fStepY = 2.0f;
	convertXpos = convertYpos = 0.0f;	// 마우스 좌표를 뷰포트 좌표로 변환
	// 변수에 대한 주석은 헤더파일에 기록
	m_Life = 5;	
	StageNum = 0;
	m_fPosX1st[0] = 250.0f;	m_fPosY1st[0] = 70.0f;
	m_fPosX1st[1] = 80.0f;	m_fPosY1st[1] = 170.0f;
	m_fPosX1st[2] = 360.0f;	m_fPosY1st[2] = 10.0f;
	m_fPosX1st[3] = 300.0f;	m_fPosY1st[3] = 200.0f;
	m_nSizeRect1st[0] = 60;	m_nSizeRect1st[1] = 30;
	m_nSizeRect1st[2] = 20; m_nSizeRect1st[3] = 7;

	m_fPosX2st[0] = 220.0f;	m_fPosY2st[0] = 70.0f;
	m_fPosX2st[1] = 160.0f;	m_fPosY2st[1] = 170.0f;
	m_fPosX2st[2] = 80.0f;	m_fPosY2st[2] = 10.0f;
	m_fPosX2st[3] = 40.0f;	m_fPosY2st[3] = 190.0f;
	m_nSizeRect2st = 35;
	
	m_bLifeBox = FALSE;
	m_fLifeBoxPosX = 290.0f;	m_fLifeBoxPosY = 8.0f;
	m_nSizeRectLifeBox = 10;
	m_fStepXLifeBox = m_fStepYLifeBox = 3.0f;

	m_fPosX3st[0] = 265.0f;	m_fPosY3st[0] = 15.0f;
	m_fPosX3st[1] = 80.0f;	m_fPosY3st[1] = 200.0f;
	m_fPosX3st[2] = 360.0f;	m_fPosY3st[2] = 95.0f;
	m_nSizeRect3st[0] = 40;	m_nSizeRect3st[1] = 25;
	m_nSizeRect3st[2] = 15;
}

CMy20171392_P1View::~CMy20171392_P1View()
{
}

BOOL CMy20171392_P1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMy20171392_P1View 그리기

void CMy20171392_P1View::OnDraw(CDC* pDC)
{
	CMy20171392_P1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderScene();
	::glFinish();

	::SwapBuffers(m_pDC->GetSafeHdc());
}


// CMy20171392_P1View 진단

#ifdef _DEBUG
void CMy20171392_P1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20171392_P1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20171392_P1Doc* CMy20171392_P1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20171392_P1Doc)));
	return (CMy20171392_P1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20171392_P1View 메시지 처리기


int CMy20171392_P1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	InitializeOpenGL();
	return 0;
}


bool CMy20171392_P1View::InitializeOpenGL()
{
	m_pDC = new CClientDC(this);

	if (m_pDC == NULL)
	{
		MessageBox(_T("Error Obtaining DC"));
		return FALSE;
	}
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	if (m_hRC == 0)
	{
		MessageBox(_T("Error Creating RC"));
		return FALSE;
	}
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		MessageBox(_T("Error making RC Current"));
		return FALSE;
	}
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	::glClearDepth(1.0f);
	::glEnable(GL_DEPTH_TEST);

	return TRUE;
}


bool CMy20171392_P1View::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


void CMy20171392_P1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	::glViewport(0, 0, cx, cy);

	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	if (cx <= cy)
	{
		m_fWinHeight = 250.0f / aspect_ratio;
		m_fWinWidth = 250.0f;
	}
	else
	{
		m_fWinHeight = 250.0f;
		m_fWinWidth = 250.0f*aspect_ratio;
	}
	gluOrtho2D(0.0f, m_fWinWidth, 0.0f, m_fWinHeight);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


void CMy20171392_P1View::RenderScene()
{
	glColor3f(255.0f, 0.0f, 0.0f);	// 리셋 버튼 컬러
	glRectf(m_fWinWidth, 240, m_fWinWidth - 10, 250);	//리셋 버튼 위치

	switch (m_Life)
	{
	case 1:
		glColor3f(255.0f, 255.0f, 255.0f);	// 체력 컬러
		glRectf(10, 242, 18, 250);	// 체력 아이콘 위치
		break;
	case 2:
		glColor3f(255.0f, 255.0f, 255.0f);
		glRectf(10, 242, 18, 250);
		glRectf(23, 242, 31, 250);
		break;
	case 3:
		glColor3f(255.0f, 255.0f, 255.0f);
		glRectf(10, 242, 18, 250);
		glRectf(23, 242, 31, 250);
		glRectf(36, 242, 44, 250);
		break;
	case 4:
		glColor3f(255.0f, 255.0f, 255.0f);
		glRectf(10, 242, 18, 250);
		glRectf(23, 242, 31, 250);
		glRectf(36, 242, 44, 250);
		glRectf(49, 242, 57, 250);
		break;
	case 5:
		glColor3f(255.0f, 255.0f, 255.0f);
		glRectf(10, 242, 18, 250);
		glRectf(23, 242, 31, 250);
		glRectf(36, 242, 44, 250);
		glRectf(49, 242, 57, 250);
		glRectf(62, 242, 70, 250);
		break;
	case 6:
		glColor3f(255.0f, 255.0f, 255.0f);
		glRectf(10, 242, 18, 250);
		glRectf(23, 242, 31, 250);
		glRectf(36, 242, 44, 250);
		glRectf(49, 242, 57, 250);
		glRectf(62, 242, 70, 250);
		glRectf(75, 242, 83, 250);
		break;
	case 7:
		glColor3f(255.0f, 255.0f, 255.0f);
		glRectf(10, 242, 18, 250);
		glRectf(23, 242, 31, 250);
		glRectf(36, 242, 44, 250);
		glRectf(49, 242, 57, 250);
		glRectf(62, 242, 70, 250);
		glRectf(75, 242, 83, 250);
		glRectf(88, 242, 96, 250);
		break;
	}

	switch (StageNum)
	{
	case 0:
		MessageBox(_T("좌상단 : 남은 목숨 수, 우상단 : 리셋 버튼\n\n상단을 제외한 모든 네모를 클릭해 지우세요"), _T("안내"), MB_ICONINFORMATION);
		StageNum++;
		break;
	case 1:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX1st[0], m_fPosY1st[0],
		m_fPosX1st[0] + m_nSizeRect1st[0], m_fPosY1st[0] + m_nSizeRect1st[0]);
		//→ 사각형 좌표 설정
		break;
	case 2:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX1st[1], m_fPosY1st[1],
			m_fPosX1st[1] + m_nSizeRect1st[1], m_fPosY1st[1] + m_nSizeRect1st[1]);
		//→ 사각형 좌표 설정
		break;
	case 3:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX1st[2], m_fPosY1st[2],
			m_fPosX1st[2] + m_nSizeRect1st[2], m_fPosY1st[2] + m_nSizeRect1st[2]);
		//→ 사각형 좌표 설정
		break;
	case 4:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX1st[3], m_fPosY1st[3],
			m_fPosX1st[3] + m_nSizeRect1st[3], m_fPosY1st[3] + m_nSizeRect1st[3]);
		//→ 사각형 좌표 설정
		break;
	case 5:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX2st[0], m_fPosY2st[0],
			m_fPosX2st[0] + m_nSizeRect2st, m_fPosY2st[0] + m_nSizeRect2st);
		//→ 사각형 좌표 설정
		break;
	case 6:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX2st[1], m_fPosY2st[1],
			m_fPosX2st[1] + m_nSizeRect2st, m_fPosY2st[1] + m_nSizeRect2st);
		//→ 사각형 좌표 설정
		if (m_bLifeBox)
		{
			glColor3f(255.0f, 255.0f, 255.0f); // RGB 값으로 사각형 컬러 설정
			glRectf(m_fLifeBoxPosX, m_fLifeBoxPosY,
				m_fLifeBoxPosX + m_nSizeRectLifeBox, m_fLifeBoxPosY + m_nSizeRectLifeBox);
		}
		break;
	case 7:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX2st[2], m_fPosY2st[2],
			m_fPosX2st[2] + m_nSizeRect2st, m_fPosY2st[2] + m_nSizeRect2st);
		//→ 사각형 좌표 설정
		break;
	case 8:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX2st[3], m_fPosY2st[3],
			m_fPosX2st[3] + m_nSizeRect2st, m_fPosY2st[3] + m_nSizeRect2st);
		//→ 사각형 좌표 설정
		break;
	case 9:
		glColor3f(246.0f, 217.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX3st[0], m_fPosY3st[0],
			m_fPosX3st[0] + m_nSizeRect3st[0], m_fPosY3st[0] + m_nSizeRect3st[0]);
		//→ 사각형 좌표 설정
		break;
	case 10:
		glColor3f(246.0f, 217.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX3st[1], m_fPosY3st[1],
			m_fPosX3st[1] + m_nSizeRect3st[1], m_fPosY3st[1] + m_nSizeRect3st[1]);
		//→ 사각형 좌표 설정
		break;
	case 11:
		glColor3f(246.0f, 217.0f, 0.0f); // RGB 값으로 사각형 컬러 설정
		glRectf(m_fPosX3st[2], m_fPosY3st[2],
			m_fPosX3st[2] + m_nSizeRect3st[2], m_fPosY3st[2] + m_nSizeRect3st[2]);
		//→ 사각형 좌표 설정
		break;
	}

	if (StageNum < 5)
	{
		SetTimer(0, 33, NULL);	// 화면 갱신 역할
	}
	else if (StageNum == 6)
	{
		SetTimer(0, 100, NULL);	// 화면 갱신 역할
	}
	else if (StageNum == 11)
	{
		SetTimer(0, 500, NULL);	// 화면 갱신 역할
	}
	else if (5 <= StageNum && StageNum < 9)
	{
		SetTimer(0, 10, NULL);	// 화면 갱신 역할
	}
	else if (9 <= StageNum && StageNum < 11)
	{
		SetTimer(0, 5, NULL);	// 화면 갱신 역할
	}
	
}


void CMy20171392_P1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (::wglMakeCurrent(0, 0) == FALSE)
	{
		MessageBox(_T("Could not make RC non-current"));
	}
	if (::wglDeleteContext(m_hRC) == FALSE)
	{
		MessageBox(_T("Could not delete RC"));
	}

	if (m_pDC)
	{
		delete m_pDC;
	}
	m_pDC = NULL;
}


void CMy20171392_P1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (StageNum)
	{
	case 5:
		if (m_fPosX2st[0] > m_fWinWidth - m_nSizeRect2st || m_fPosX2st[0] < 0)
			m_fStepX = -m_fStepX;
		if (m_fPosY2st[0] > m_fWinHeight - m_nSizeRect2st || m_fPosY2st[0] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosX2st[0] > m_fWinWidth - m_nSizeRect2st)
			m_fPosX2st[0] = m_fWinWidth - m_nSizeRect2st - 1;
		if (m_fPosY2st[0] > m_fWinHeight - m_nSizeRect2st)
			m_fPosY2st[0] = m_fWinHeight - m_nSizeRect2st - 1;

		m_fPosX2st[0] += m_fStepX;
		m_fPosY2st[0] += m_fStepY;
		break;
	case 6:
		if (m_fPosX2st[1] > m_fWinWidth - m_nSizeRect2st || m_fPosX2st[1] < 0)
			m_fStepX = -m_fStepX;
		if (m_fPosY2st[1] > m_fWinHeight - m_nSizeRect2st || m_fPosY2st[1] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosX2st[1] > m_fWinWidth - m_nSizeRect2st)
			m_fPosX2st[1] = m_fWinWidth - m_nSizeRect2st - 1;
		if (m_fPosY2st[1] > m_fWinHeight - m_nSizeRect2st)
			m_fPosY2st[1] = m_fWinHeight - m_nSizeRect2st - 1;

		m_fStepX = -m_fStepX;
		m_fPosX2st[1] += m_fStepX;
		m_fPosY2st[1] += m_fStepY;

		if (m_bLifeBox)
		{
			if (m_fLifeBoxPosX > m_fWinWidth - m_nSizeRectLifeBox || m_fLifeBoxPosX < 0)
				m_fStepXLifeBox = -m_fStepXLifeBox;
			if (m_fLifeBoxPosY > m_fWinHeight - m_nSizeRectLifeBox || m_fLifeBoxPosY < 0)
				m_fStepYLifeBox = -m_fStepYLifeBox;
			if (m_fLifeBoxPosX > m_fWinWidth - m_nSizeRectLifeBox)
				m_fLifeBoxPosX = m_fWinWidth - m_nSizeRectLifeBox - 1;
			if (m_fLifeBoxPosY > m_fWinHeight - m_nSizeRectLifeBox)
				m_fLifeBoxPosY = m_fWinHeight - m_nSizeRectLifeBox - 1;

			m_fLifeBoxPosX += m_fStepXLifeBox;
			m_fLifeBoxPosY += m_fStepYLifeBox;
		}
		break;
	case 7:
		if (m_fPosX2st[2] > m_fWinWidth - m_nSizeRect2st || m_fPosX2st[2] < 0)
			m_fStepX = -m_fStepX;
		if (m_fPosY2st[2] > m_fWinHeight - m_nSizeRect2st || m_fPosY2st[2] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosX2st[2] > m_fWinWidth - m_nSizeRect2st)
			m_fPosX2st[2] = m_fWinWidth - m_nSizeRect2st - 1;
		if (m_fPosY2st[2] > m_fWinHeight - m_nSizeRect2st)
			m_fPosY2st[2] = m_fWinHeight - m_nSizeRect2st - 1;

		m_fPosX2st[2] += m_fStepX;
		m_fPosY2st[2] += m_fStepY;
		break;
	case 8:
		if (m_fPosX2st[3] > m_fWinWidth - m_nSizeRect2st || m_fPosX2st[3] < 0)
			m_fStepX = -m_fStepX;
		if (m_fPosY2st[3] > m_fWinHeight - m_nSizeRect2st || m_fPosY2st[3] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosX2st[3] > m_fWinWidth - m_nSizeRect2st)
			m_fPosX2st[3] = m_fWinWidth - m_nSizeRect2st - 1;
		if (m_fPosY2st[3] > m_fWinHeight - m_nSizeRect2st)
			m_fPosY2st[3] = m_fWinHeight - m_nSizeRect2st - 1;

		m_fPosX2st[3] += m_fStepX;
		m_fPosY2st[3] += m_fStepY;
		break;
	case 9:
		if (m_fPosX3st[0] > m_fWinWidth - m_nSizeRect3st[0] + 40)
		{
			m_fPosX3st[0] = -40;
		}
		if (m_fPosY3st[0] > m_fWinHeight - m_nSizeRect3st[0] || m_fPosY3st[0] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosY3st[0] > m_fWinHeight - m_nSizeRect3st[0])
			m_fPosY3st[0] = m_fWinHeight - m_nSizeRect3st[0] - 1;

		m_fPosX3st[0] += m_fStepX;
		m_fPosY3st[0] += m_fStepY;
		break;
	case 10:
		if (m_fPosX3st[1] > m_fWinWidth - m_nSizeRect3st[1] || m_fPosX3st[1] < 0)
			m_fStepX = -m_fStepX;
		if (m_fPosY3st[1] > m_fWinHeight - m_nSizeRect3st[1] || m_fPosY3st[1] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosX3st[1] > m_fWinWidth - m_nSizeRect3st[1])
			m_fPosX3st[1] = m_fWinWidth - m_nSizeRect3st[1] - 1;
		if (m_fPosY3st[1] > m_fWinHeight - m_nSizeRect3st[1])
			m_fPosY3st[1] = m_fWinHeight - m_nSizeRect3st[1] - 1;

		m_fPosX3st[1] += m_fStepX;
		m_fPosY3st[1] += m_fStepY;
		break;
	case 11:
		if (m_fPosX3st[2] > m_fWinWidth - m_nSizeRect3st[2] || m_fPosX3st[2] < 0)
			m_fStepX = -m_fStepX;
		if (m_fPosY3st[2] > m_fWinHeight - m_nSizeRect3st[2] || m_fPosY3st[2] < 0)
			m_fStepY = -m_fStepY;
		if (m_fPosX3st[2] > m_fWinWidth - m_nSizeRect3st[2])
			m_fPosX3st[2] = m_fWinWidth - m_nSizeRect3st[2] - 1;
		if (m_fPosY3st[2] > m_fWinHeight - m_nSizeRect3st[2])
			m_fPosY3st[2] = m_fWinHeight - m_nSizeRect3st[2] - 1;

		m_fPosX3st[2] += m_fStepX;
		m_fPosY3st[2] += m_fStepY;
		break;
	}
	

	InvalidateRect(NULL, TRUE);
	
	CView::OnTimer(nIDEvent);
}


void CMy20171392_P1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseDown = point;

	convertXpos = (GLfloat(m_ptMouseDown.x) * m_fWinWidth) / 1179;	// 마우스(스크린) 좌표를 OpenGL(세계) 좌표로 변환
	convertYpos = 250 - ((GLfloat(m_ptMouseDown.y) * m_fWinHeight) / 692);
	
	// 클릭한 영역이 리셋 버튼인가?
	if (m_fWinWidth - 10 < convertXpos && convertXpos < m_fWinWidth
		&& 240.0f < convertYpos && convertYpos < 250.0f)
	{
		StageNum = 1;
		m_Life = 5;
		m_fStepX = 2.0f;
		m_fStepY = 2.0f;
		m_bLifeBox = FALSE;
		return;
	}
	else
	{
		MouseClick();	// 클릭 시도 시 해당 이벤트로 이동
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CMy20171392_P1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseDown = CPoint(0, 0);

	CView::OnLButtonUp(nFlags, point);
}


void CMy20171392_P1View::MouseClick()
{
	switch (StageNum)
	{
	case 1:
		// 클릭 위치가 사각형의 내부일 때
		if (m_fPosX1st[0] < convertXpos && convertXpos < m_fPosX1st[0] + m_nSizeRect1st[0]
				&& m_fPosY1st[0] < convertYpos && convertYpos < m_fPosY1st[0] + m_nSizeRect1st[0])
		{
				StageNum++;
		}
		else m_Life--;
		break;
	case 2:
		if (m_fPosX1st[1] < convertXpos && convertXpos < m_fPosX1st[1] + m_nSizeRect1st[1]
			&& m_fPosY1st[1] < convertYpos && convertYpos < m_fPosY1st[1] + m_nSizeRect1st[1])
		{
			StageNum++;
		}
		else m_Life--;
		break;
	case 3:
		if (m_fPosX1st[2] < convertXpos && convertXpos < m_fPosX1st[2] + m_nSizeRect1st[2]
			&& m_fPosY1st[2] < convertYpos && convertYpos < m_fPosY1st[2] + m_nSizeRect1st[2])
		{
			StageNum++;
		}
		else m_Life--;
		break;
	case 4:
		if (m_fPosX1st[3] < convertXpos && convertXpos < m_fPosX1st[3] + m_nSizeRect1st[3]
			&& m_fPosY1st[3] < convertYpos && convertYpos < m_fPosY1st[3] + m_nSizeRect1st[3])
		{
			StageNum++;
			MessageBox(_T("스테이지 2 시작"), _T("알림"), MB_ICONINFORMATION);
		}
		else m_Life--;
		break;
	case 5:
		if (m_fPosX2st[0] < convertXpos && convertXpos < m_fPosX2st[0] + m_nSizeRect2st
			&& m_fPosY2st[0] < convertYpos && convertYpos < m_fPosY2st[0] + m_nSizeRect2st)
		{
			m_fStepX = 50.0f;
			m_fStepY = 8.0f;
			m_bLifeBox = TRUE;
			StageNum++;
		}
		else m_Life--;
		break;
	case 6:
		if (m_fPosX2st[1] < convertXpos && convertXpos < m_fPosX2st[1] + m_nSizeRect2st
			&& m_fPosY2st[1] < convertYpos && convertYpos < m_fPosY2st[1] + m_nSizeRect2st)
		{
			m_fStepX = 7.0f;
			m_fStepY = 2.0f;
			m_fStepY = -m_fStepY;
			m_bLifeBox = FALSE;
			StageNum++;
		}
		else if (m_bLifeBox == TRUE
			&& m_fLifeBoxPosX < convertXpos && convertXpos < m_fLifeBoxPosX + m_nSizeRectLifeBox
			&& m_fLifeBoxPosY < convertYpos && convertYpos < m_fLifeBoxPosY + m_nSizeRectLifeBox)
		{
			m_bLifeBox = FALSE;	// 생명박스 클릭 시 박스 제거
			m_Life++;
		}
			else m_Life--;
		break;
	case 7:
		if (m_fPosX2st[2] < convertXpos && convertXpos < m_fPosX2st[2] + m_nSizeRect2st
			&& m_fPosY2st[2] < convertYpos && convertYpos < m_fPosY2st[2] + m_nSizeRect2st)
		{
			m_fStepX = 2.0f;
			m_fStepY = 8.0f;
			m_fStepY = -m_fStepY;
			StageNum++;
		}
		else m_Life--;
		break;
	case 8:
		if (m_fPosX2st[3] < convertXpos && convertXpos < m_fPosX2st[3] + m_nSizeRect2st
			&& m_fPosY2st[3] < convertYpos && convertYpos < m_fPosY2st[3] + m_nSizeRect2st)
		{
			m_fStepX = 7.0f;
			m_fStepY = 2.0f;
			StageNum++;
			m_Life++;
			MessageBox(_T("스테이지 3 시작 / Bonus Life + 1"), _T("알림"), MB_ICONINFORMATION);
		}
		else m_Life--;
		break;
	case 9:
		if (m_fPosX3st[0] < convertXpos && convertXpos < m_fPosX3st[0] + m_nSizeRect3st[0]
			&& m_fPosY3st[0] < convertYpos && convertYpos < m_fPosY3st[0] + m_nSizeRect3st[0])
		{
			m_fStepX = 7.0f;
			m_fStepY = 7.0f;
			m_fStepX = -m_fStepX;
			m_fStepY = -m_fStepY;
			StageNum++;
		}
		else m_Life--;
		break;
	case 10:
		if (m_fPosX3st[1] < convertXpos && convertXpos < m_fPosX3st[1] + m_nSizeRect3st[1]
			&& m_fPosY3st[1] < convertYpos && convertYpos < m_fPosY3st[1] + m_nSizeRect3st[1])
		{
			m_fStepX = 50.0f;
			m_fStepY = 50.0f;
			m_fStepX = -m_fStepX;
			m_fStepY = -m_fStepY;
			StageNum++;
		}
		else m_Life--;
		break;
	case 11:
		if (m_fPosX3st[2] < convertXpos && convertXpos < m_fPosX3st[2] + m_nSizeRect3st[2]
			&& m_fPosY3st[2] < convertYpos && convertYpos < m_fPosY3st[2] + m_nSizeRect3st[2])
		{
			if (m_Life == 7)
			{
				MessageBox(_T("신의 컨트롤이시네요!"), _T("당신 사람이 맞나요?"), MB_ICONINFORMATION);
			}
			MessageBox(_T("축하합니다! 모든 스테이지를 클리어 했습니다!"), _T("축하요"), MB_ICONINFORMATION);
			StageNum++;
		}
		else m_Life--;
		break;
	}
	
	if (m_Life == 0)
	{
		MessageBox(_T("생명을 모두 소진하여 게임 오버됩니다."), _T("게임 오버!!"), MB_ICONWARNING);
		StageNum = 1;
		m_Life = 5;
		m_fStepX = 2.0f;
		m_fStepY = 2.0f;
		m_bLifeBox = FALSE;
	}
}
