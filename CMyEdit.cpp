#include "stdafx.h"
#include "CMyEdit.h"
#include"resource.h"
#include"MFC_teamProjectView.h"
#include"CNode.h"


CMyEdit::CMyEdit()
	: color(NULL)
{
}

CMyEdit::CMyEdit(COLORREF color)
	: color(color)
{
	brush.CreateSolidBrush(color);
}


CMyEdit::~CMyEdit()
{
}
BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CONTEXTMENU()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



void CMyEdit::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CPoint pt = point;
	CMFCteamProjectView* pView = (CMFCteamProjectView*)GetParent();
	pt.y += pView->GetScrollPos(SB_VERT);
	pt.x += pView->GetScrollPos(SB_HORZ);
	pView->chart_node = nullptr;
	pView->check(pView->flowChart.root, pt, &(pView->chart_node));
	if (pView->chart_node != nullptr)
	{
		if (pView->chart_node->key->type != START && pView->chart_node->key->type != END)
		{
			if (pView->chart_node->left == nullptr && pView->chart_node->right == nullptr && pView->chart_node->key->type != IF_TRUE)
			{
				CMenu menu;
				menu.LoadMenuW(IDR_MENU1);
				CMenu* pMenu = menu.GetSubMenu(0);
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
			}
			else if (pView->chart_node->left != nullptr)
			{
				if (pView->chart_node->left->key->type == NONE)
				{
					CMenu menu;
					menu.LoadMenuW(IDR_MENU1);
					CMenu* pMenu = menu.GetSubMenu(1);
					pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
				}
				else if (pView->chart_node->right != nullptr)
				{
					if (pView->chart_node->right->key->type == NONE)
					{
						CMenu menu;
						menu.LoadMenuW(IDR_MENU1);
						CMenu* pMenu = menu.GetSubMenu(1);
						pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
					}
				}
			}
			else
				pView->chart_node = nullptr;
		}
		else if (pView->chart_node->key->type == END)
		{
			CMenu menu;
			menu.LoadMenuW(IDR_MENU1);
			CMenu* pMenu = menu.GetSubMenu(1);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
		}
		else
			pView->chart_node = nullptr;
	}
}


HBRUSH CMyEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  부모 처리기가 호출되지 않을 경우 Null이 아닌 브러시를 반환합니다.

	pDC->SetBkColor(color);
	return brush;
}