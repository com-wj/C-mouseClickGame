
// 20171392_P1View.h : CMy20171392_P1View Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CMy20171392_P1View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy20171392_P1View();
	DECLARE_DYNCREATE(CMy20171392_P1View)

// Ư���Դϴ�.
public:
	CMy20171392_P1Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMy20171392_P1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	GLfloat m_fPosX1st[4];	// �������� 1 �簢�� X��ǥ 4��
	GLfloat m_fPosY1st[4];	// �������� 1 �簢�� Y��ǥ 4��
	GLsizei m_nSizeRect1st[4];	// �������� 1 �簢�� ũ�� 4��
	int StageNum;	// �������� ��ȣ 1~11
	CPoint m_ptMouseDown;	// ���콺 ��ǥ ������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void MouseClick();
	GLfloat convertXpos;	// ��ǥ�� ��ȯ
	GLfloat convertYpos;
	GLdouble aspect_ratio;
	int m_Life;	// ���� ���( Ŭ�� ���� �� ���� )
	GLfloat m_fPosX2st[4];	// �������� 2 �簢�� X��ǥ 4��
	GLfloat m_fPosY2st[4];	// �������� 2 �簢�� Y��ǥ 4��
	GLsizei m_nSizeRect2st;	// �������� 2 �簢�� ũ��
	GLfloat m_fLifeBoxPosX;	// ������ �ڽ� X��ǥ
	GLfloat m_fLifeBoxPosY;	// ������ �ڽ� Y��ǥ
	GLsizei m_nSizeRectLifeBox;	// ������ �ڽ� ������
	GLfloat m_fStepXLifeBox;	// ������ �ڽ� �̵��Ÿ�
	GLfloat m_fStepYLifeBox;
	bool m_bLifeBox;	// ������ �ڽ� ǥ�� ����
	GLfloat m_fPosX3st[3];	// �������� 2 �簢�� X��ǥ 4��
	GLfloat m_fPosY3st[3];	// �������� 2 �簢�� Y��ǥ 4��
	GLsizei m_nSizeRect3st[3];	// �������� 2 �簢�� ũ��
};

#ifndef _DEBUG  // 20171392_P1View.cpp�� ����� ����
inline CMy20171392_P1Doc* CMy20171392_P1View::GetDocument() const
   { return reinterpret_cast<CMy20171392_P1Doc*>(m_pDocument); }
#endif

