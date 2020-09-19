// CSourceEdit.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_teamProject.h"
#include "CSourceEdit.h"


// CSourceEdit

IMPLEMENT_DYNAMIC(CSourceEdit, CEdit)

CSourceEdit::CSourceEdit()
{

}

CSourceEdit::~CSourceEdit()
{
}


BEGIN_MESSAGE_MAP(CSourceEdit, CEdit)
END_MESSAGE_MAP()



// CSourceEdit 메시지 처리기




BOOL CSourceEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	/*if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB &&
		pMsg->hwnd == this->m_hWnd) {

		ReplaceSel((CString)"\t");
		return true;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN &&
		pMsg->hwnd == this->m_hWnd) {

		ReplaceSel((CString)"\r\n");
		return true;
	}
	else {
		return CEdit::PreTranslateMessage(pMsg);
	}*/

	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == this->m_hWnd) {
		if (pMsg->wParam == VK_TAB) {
			ReplaceSel((CString)"\t");
			return true;
		}
		else if (pMsg->wParam == VK_RETURN) {
			ReplaceSel((CString)"\r\n");
			return true;
		}
		else {
			return CEdit::PreTranslateMessage(pMsg);
		}
	}
	else {
		return CEdit::PreTranslateMessage(pMsg);
	}	

	//return CEdit::PreTranslateMessage(pMsg);	
}
