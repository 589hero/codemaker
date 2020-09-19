#pragma once
#include <afxwin.h>

class CNode;

class CMyEdit :
	public CEdit
{
public:
	CBrush brush;
	int red;
	int green;
	int blue;
	COLORREF color;
public:
	CMyEdit();
	CMyEdit(COLORREF color);
	~CMyEdit();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/);

};

