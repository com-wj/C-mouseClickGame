
// 20171392_P1View.cpp : CMy20171392_P1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CMy20171392_P1View ����/�Ҹ�

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
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_fStepX = 2.0f;
	m_fStepY = 2.0f;
	convertXpos = convertYpos = 0.0f;	// ���콺 ��ǥ�� ����Ʈ ��ǥ�� ��ȯ
	// ������ ���� �ּ��� ������Ͽ� ���
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMy20171392_P1View �׸���

void CMy20171392_P1View::OnDraw(CDC* pDC)
{
	CMy20171392_P1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderScene();
	::glFinish();

	::SwapBuffers(m_pDC->GetSafeHdc());
}


// CMy20171392_P1View ����

#ifdef _DEBUG
void CMy20171392_P1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20171392_P1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20171392_P1Doc* CMy20171392_P1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20171392_P1Doc)));
	return (CMy20171392_P1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20171392_P1View �޽��� ó����


int CMy20171392_P1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

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
	glColor3f(255.0f, 0.0f, 0.0f);	// ���� ��ư �÷�
	glRectf(m_fWinWidth, 240, m_fWinWidth - 10, 250);	//���� ��ư ��ġ

	switch (m_Life)
	{
	case 1:
		glColor3f(255.0f, 255.0f, 255.0f);	// ü�� �÷�
		glRectf(10, 242, 18, 250);	// ü�� ������ ��ġ
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
		MessageBox(_T("�»�� : ���� ��� ��, ���� : ���� ��ư\n\n����� ������ ��� �׸� Ŭ���� ���켼��"), _T("�ȳ�"), MB_ICONINFORMATION);
		StageNum++;
		break;
	case 1:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX1st[0], m_fPosY1st[0],
		m_fPosX1st[0] + m_nSizeRect1st[0], m_fPosY1st[0] + m_nSizeRect1st[0]);
		//�� �簢�� ��ǥ ����
		break;
	case 2:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX1st[1], m_fPosY1st[1],
			m_fPosX1st[1] + m_nSizeRect1st[1], m_fPosY1st[1] + m_nSizeRect1st[1]);
		//�� �簢�� ��ǥ ����
		break;
	case 3:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX1st[2], m_fPosY1st[2],
			m_fPosX1st[2] + m_nSizeRect1st[2], m_fPosY1st[2] + m_nSizeRect1st[2]);
		//�� �簢�� ��ǥ ����
		break;
	case 4:
		glColor3f(0.0f, 5.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX1st[3], m_fPosY1st[3],
			m_fPosX1st[3] + m_nSizeRect1st[3], m_fPosY1st[3] + m_nSizeRect1st[3]);
		//�� �簢�� ��ǥ ����
		break;
	case 5:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX2st[0], m_fPosY2st[0],
			m_fPosX2st[0] + m_nSizeRect2st, m_fPosY2st[0] + m_nSizeRect2st);
		//�� �簢�� ��ǥ ����
		break;
	case 6:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX2st[1], m_fPosY2st[1],
			m_fPosX2st[1] + m_nSizeRect2st, m_fPosY2st[1] + m_nSizeRect2st);
		//�� �簢�� ��ǥ ����
		if (m_bLifeBox)
		{
			glColor3f(255.0f, 255.0f, 255.0f); // RGB ������ �簢�� �÷� ����
			glRectf(m_fLifeBoxPosX, m_fLifeBoxPosY,
				m_fLifeBoxPosX + m_nSizeRectLifeBox, m_fLifeBoxPosY + m_nSizeRectLifeBox);
		}
		break;
	case 7:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX2st[2], m_fPosY2st[2],
			m_fPosX2st[2] + m_nSizeRect2st, m_fPosY2st[2] + m_nSizeRect2st);
		//�� �簢�� ��ǥ ����
		break;
	case 8:
		glColor3f(0.0f, 0.0f, 128.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX2st[3], m_fPosY2st[3],
			m_fPosX2st[3] + m_nSizeRect2st, m_fPosY2st[3] + m_nSizeRect2st);
		//�� �簢�� ��ǥ ����
		break;
	case 9:
		glColor3f(246.0f, 217.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX3st[0], m_fPosY3st[0],
			m_fPosX3st[0] + m_nSizeRect3st[0], m_fPosY3st[0] + m_nSizeRect3st[0]);
		//�� �簢�� ��ǥ ����
		break;
	case 10:
		glColor3f(246.0f, 217.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX3st[1], m_fPosY3st[1],
			m_fPosX3st[1] + m_nSizeRect3st[1], m_fPosY3st[1] + m_nSizeRect3st[1]);
		//�� �簢�� ��ǥ ����
		break;
	case 11:
		glColor3f(246.0f, 217.0f, 0.0f); // RGB ������ �簢�� �÷� ����
		glRectf(m_fPosX3st[2], m_fPosY3st[2],
			m_fPosX3st[2] + m_nSizeRect3st[2], m_fPosY3st[2] + m_nSizeRect3st[2]);
		//�� �簢�� ��ǥ ����
		break;
	}

	if (StageNum < 5)
	{
		SetTimer(0, 33, NULL);	// ȭ�� ���� ����
	}
	else if (StageNum == 6)
	{
		SetTimer(0, 100, NULL);	// ȭ�� ���� ����
	}
	else if (StageNum == 11)
	{
		SetTimer(0, 500, NULL);	// ȭ�� ���� ����
	}
	else if (5 <= StageNum && StageNum < 9)
	{
		SetTimer(0, 10, NULL);	// ȭ�� ���� ����
	}
	else if (9 <= StageNum && StageNum < 11)
	{
		SetTimer(0, 5, NULL);	// ȭ�� ���� ����
	}
	
}


void CMy20171392_P1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_ptMouseDown = point;

	convertXpos = (GLfloat(m_ptMouseDown.x) * m_fWinWidth) / 1179;	// ���콺(��ũ��) ��ǥ�� OpenGL(����) ��ǥ�� ��ȯ
	convertYpos = 250 - ((GLfloat(m_ptMouseDown.y) * m_fWinHeight) / 692);
	
	// Ŭ���� ������ ���� ��ư�ΰ�?
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
		MouseClick();	// Ŭ�� �õ� �� �ش� �̺�Ʈ�� �̵�
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CMy20171392_P1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_ptMouseDown = CPoint(0, 0);

	CView::OnLButtonUp(nFlags, point);
}


void CMy20171392_P1View::MouseClick()
{
	switch (StageNum)
	{
	case 1:
		// Ŭ�� ��ġ�� �簢���� ������ ��
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
			MessageBox(_T("�������� 2 ����"), _T("�˸�"), MB_ICONINFORMATION);
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
			m_bLifeBox = FALSE;	// ����ڽ� Ŭ�� �� �ڽ� ����
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
			MessageBox(_T("�������� 3 ���� / Bonus Life + 1"), _T("�˸�"), MB_ICONINFORMATION);
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
				MessageBox(_T("���� ��Ʈ���̽ó׿�!"), _T("��� ����� �³���?"), MB_ICONINFORMATION);
			}
			MessageBox(_T("�����մϴ�! ��� ���������� Ŭ���� �߽��ϴ�!"), _T("���Ͽ�"), MB_ICONINFORMATION);
			StageNum++;
		}
		else m_Life--;
		break;
	}
	
	if (m_Life == 0)
	{
		MessageBox(_T("������ ��� �����Ͽ� ���� �����˴ϴ�."), _T("���� ����!!"), MB_ICONWARNING);
		StageNum = 1;
		m_Life = 5;
		m_fStepX = 2.0f;
		m_fStepY = 2.0f;
		m_bLifeBox = FALSE;
	}
}
