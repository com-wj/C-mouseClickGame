
// 20171392_P1View.h : CMy20171392_P1View 클래스의 인터페이스
//

#pragma once
#include "atltypes.h"


class CMy20171392_P1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20171392_P1View();
	DECLARE_DYNCREATE(CMy20171392_P1View)

// 특성입니다.
public:
	CMy20171392_P1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy20171392_P1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	HGLRC m_hRC;
	CDC* m_pDC;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	bool InitializeOpenGL();
	bool SetupPixelFormat();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void RenderScene();
	afx_msg void OnDestroy();
	GLfloat m_fWinHeight;
	GLfloat m_fWinWidth;
	GLfloat m_fStepX;
	GLfloat m_fStepY;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	GLfloat m_fPosX1st[4];	// 스테이지 1 사각형 X좌표 4개
	GLfloat m_fPosY1st[4];	// 스테이지 1 사각형 Y좌표 4개
	GLsizei m_nSizeRect1st[4];	// 스테이지 1 사각형 크기 4개
	int StageNum;	// 스테이지 번호 1~11
	CPoint m_ptMouseDown;	// 마우스 좌표 포인터
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void MouseClick();
	GLfloat convertXpos;	// 좌표계 변환
	GLfloat convertYpos;
	GLdouble aspect_ratio;
	int m_Life;	// 게임 목숨( 클릭 실패 시 차감 )
	GLfloat m_fPosX2st[4];	// 스테이지 2 사각형 X좌표 4개
	GLfloat m_fPosY2st[4];	// 스테이지 2 사각형 Y좌표 4개
	GLsizei m_nSizeRect2st;	// 스테이지 2 사각형 크기
	GLfloat m_fLifeBoxPosX;	// 라이프 박스 X좌표
	GLfloat m_fLifeBoxPosY;	// 라이프 박스 Y좌표
	GLsizei m_nSizeRectLifeBox;	// 라이프 박스 사이즈
	GLfloat m_fStepXLifeBox;	// 라이프 박스 이동거리
	GLfloat m_fStepYLifeBox;
	bool m_bLifeBox;	// 라이프 박스 표시 여부
	GLfloat m_fPosX3st[3];	// 스테이지 2 사각형 X좌표 4개
	GLfloat m_fPosY3st[3];	// 스테이지 2 사각형 Y좌표 4개
	GLsizei m_nSizeRect3st[3];	// 스테이지 2 사각형 크기
};

#ifndef _DEBUG  // 20171392_P1View.cpp의 디버그 버전
inline CMy20171392_P1Doc* CMy20171392_P1View::GetDocument() const
   { return reinterpret_cast<CMy20171392_P1Doc*>(m_pDocument); }
#endif

