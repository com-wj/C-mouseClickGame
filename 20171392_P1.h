
// 20171392_P1.h : 20171392_P1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy20171392_P1App:
// �� Ŭ������ ������ ���ؼ��� 20171392_P1.cpp�� �����Ͻʽÿ�.
//

class CMy20171392_P1App : public CWinAppEx
{
public:
	CMy20171392_P1App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy20171392_P1App theApp;
