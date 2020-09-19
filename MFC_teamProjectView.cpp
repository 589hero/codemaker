
// MFC_teamProjectView.cpp: CMFCteamProjectView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_teamProject.h"
#endif
#include "MainFrm.h"
#include "MFC_teamProjectDoc.h"
#include "MFC_teamProjectView.h"
#include "CSourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCteamProjectView

IMPLEMENT_DYNCREATE(CMFCteamProjectView, CFormView)

BEGIN_MESSAGE_MAP(CMFCteamProjectView, CFormView)
	ON_COMMAND(ID_IF, &CMFCteamProjectView::OnIf)
	ON_COMMAND(ID_FOR, &CMFCteamProjectView::OnFor)
	ON_COMMAND(ID_WHILE, &CMFCteamProjectView::OnWhile)
	ON_COMMAND(ID_VAR, &CMFCteamProjectView::OnVar)
	ON_COMMAND(ID_NORMAL, &CMFCteamProjectView::OnNormal)
	ON_COMMAND(ID_END, &CMFCteamProjectView::OnEnd)
	//ON_COMMAND(ID_IF_TRUE, &CMFCteamProjectView::OnIfTrue)
	//ON_COMMAND(ID_IF_FALSE, &CMFCteamProjectView::OnIfFalse)
	ON_COMMAND(ID_ONLYIF, &CMFCteamProjectView::OnOnlyif)
	ON_COMMAND(ID_IFELSE, &CMFCteamProjectView::OnIfelse)
	ON_WM_PAINT()
	ON_COMMAND(ID_DELETE, &CMFCteamProjectView::OnDelete)
	ON_COMMAND(ID_CLEAR, &CMFCteamProjectView::OnClear)
	ON_COMMAND(ID_SOURCE, &CMFCteamProjectView::OnSource)
	ON_COMMAND(ID_SELECTCPP, &CMFCteamProjectView::OnSelectcpp)
	ON_COMMAND(ID_SELECTJAVA, &CMFCteamProjectView::OnSelectjava)
	ON_UPDATE_COMMAND_UI(ID_SELECTCPP, &CMFCteamProjectView::OnUpdateSelectcpp)
	ON_UPDATE_COMMAND_UI(ID_SELECTJAVA, &CMFCteamProjectView::OnUpdateSelectjava)
	ON_WM_VSCROLL()
//	ON_WM_MOUSEHWHEEL()
//	ON_WM_MOUSELEAVE()
//ON_WM_MOUSEWHEEL()
//ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CMFCteamProjectView 생성/소멸

CMFCteamProjectView::CMFCteamProjectView() noexcept
	: CFormView(IDD_MFC_TEAMPROJECT_FORM), chart_node(nullptr), nSourceLanguage(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	
	// 순서도의 시작부분 생성
	flowChart.root = new CNode(flowChart.root);
	flowChart.root->key = new FlowChart(10, 10, START);
	flowChart.root->key->code.SetString(_T("START"));
	
	flowChart.root->left = new CNode(flowChart.root);
	flowChart.root->left->key = new FlowChart(10, 10, NONE);
	
	sourceDlg = nullptr;
}

CMFCteamProjectView::~CMFCteamProjectView()
{
}

void CMFCteamProjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMFCteamProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMFCteamProjectView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	show(flowChart.root);
}


// CMFCteamProjectView 진단

#ifdef _DEBUG
void CMFCteamProjectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCteamProjectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCteamProjectDoc* CMFCteamProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCteamProjectDoc)));
	return (CMFCteamProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCteamProjectView 메시지 처리기



/*
추가 구현 함수들
*/

void CMFCteamProjectView::check(CNode * node, CPoint pt, CNode** chart)
{
	if (node == nullptr || *chart != nullptr)
		return;

	// first recur on left subtree
	check(node->left, pt, chart);

	// then recur on right subtree
	check(node->right, pt, chart);

	// now deal with the node
	ScreenToClient(&pt);
	CRgn rgn;
	rgn.CreateRectRgnIndirect(node->key->rect);
	if (pt.x >= node->key->x && pt.x <= node->key->x + 100 &&
		pt.y >= node->key->y && pt.y <= node->key->y + 50)
	{
		*chart =node;
	}
}

void CMFCteamProjectView::_delete(CNode * node)
{
	if (node == nullptr)
		return;

	// first recur on left subtree
	_delete(node->left);

	// then recur on right subtree
	_delete(node->right);

	// now deal with the node
	if (node->key->pEdit != nullptr)
	{
		node->key->pEdit->GetWindowTextW(node->key->code);
		delete node->key->pEdit;
	}
}


void CMFCteamProjectView::update(CNode * node)
{
	if (node == nullptr)
		return;

	// 생각 다시 해보자
}


void CMFCteamProjectView::show_line(CNode * node, CPaintDC& dc)
{
	if (node == nullptr)
		return;
	// first recur on left subtree
	show_line(node->left, dc);

	// then recur on right subtree
	show_line(node->right, dc);

	// now deal with the node
	if (node->key->type != START)
	{
		// 오른쪽에 출력되는 경우
		if (node->parent->key->x < node->key->x)
		{
			dc.SelectObject(CBrush(RGB(0, 0, 0)));
			dc.MoveTo(node->parent->key->x + 100, node->parent->key->y + 25);
			dc.LineTo(node->key->x, node->key->y + 25);
		}
		// 왼쪽에 출력되는 경우
		else
		{
			dc.SelectObject(CBrush(RGB(0, 0, 0)));
			dc.MoveTo(node->parent->key->x + 50, node->parent->key->y + 50);
			dc.LineTo(node->key->x + 50, node->key->y);
		}
	}
}


void CMFCteamProjectView::clear(CNode * node)
{
	if (node == nullptr)
		return;

	// first recur on left subtree
	clear(node->left);

	// then recur on right subtree
	clear(node->right);

	// now deal with the node
	delete node;
}


void CMFCteamProjectView::OnIf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = IF;
	/*
	IF 구문에 대한 새로운 순서도 생성
	left-child : IF_TRUE	
	right-child : IF_FALSE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, IF_TRUE);
	chart_node->right = new CNode(chart_node);
	chart_node->right->key = new FlowChart(chart_node->key->x, chart_node->key->y, IF_FALSE);
	chart_node->right->left = new CNode(chart_node->right);
	chart_node->right->left->key = new FlowChart(chart_node->right->key->x, chart_node->right->key->y, NONE);

	
	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후, 
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnFor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = FOR_CONDITION;
	/*
	FOR 구문에 대한 새로운 순서도 생성
	left-child : FOR_DO
	left-child's left-child : NONE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, FOR_DO);
	chart_node->left->left = new CNode(chart_node->left);
	chart_node->left->left->key = new FlowChart(chart_node->left->key->x, chart_node->left->key->y, NONE);


	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnWhile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = WHILE_CONDITION;
	/*
	WHILE 구문에 대한 새로운 순서도 생성
	left-child : WHLE_DO
	left-child's left-child : NONE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, WHILE_DO);
	chart_node->left->left = new CNode(chart_node->left);
	chart_node->left->left->key = new FlowChart(chart_node->left->key->x, chart_node->left->key->y, NONE);

	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnVar()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = VAR;
	/*
	VAR 구문에 대한 새로운 순서도 생성
	left-child : NONE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, NONE);
	 
	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnNormal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = NORMAL;
	/*
	NORMAL 구문에 대한 새로운 순서도 생성
	left-child : NONE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, NONE);

	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnEnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = END;
	CString str;
	str.SetString(_T("END"));
	chart_node->key->pEdit->SetWindowTextW(str);

	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


//void CMFCteamProjectView::OnIfTrue()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	chart_node->key->type = IF_TRUE;
//}
//
//
//void CMFCteamProjectView::OnIfFalse()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	chart_node->key->type = IF_FALSE;
//}


void CMFCteamProjectView::OnOnlyif()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = IF;
	/*
	IF 구문에 대한 새로운 순서도 생성
	left-child : IF_TRUE
	right-child : IF_FALSE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, IF_TRUE);
	chart_node->right = new CNode(chart_node);
	chart_node->right->key = new FlowChart(chart_node->key->x, chart_node->key->y, IF_FALSE);
	chart_node->right->key->type = NONE;

	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnIfelse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	chart_node->key->type = IF;
	/*
	IF 구문에 대한 새로운 순서도 생성
	left-child : IF_TRUE
	right-child : IF_FALSE
	*/
	chart_node->left = new CNode(chart_node);
	chart_node->left->key = new FlowChart(chart_node->key->x, chart_node->key->y, IF_TRUE);
	chart_node->right = new CNode(chart_node);
	chart_node->right->key = new FlowChart(chart_node->key->x, chart_node->key->y, IF_FALSE);
	chart_node->right->left = new CNode(chart_node->right);
	chart_node->right->left->key = new FlowChart(chart_node->right->key->x, chart_node->right->key->y, NONE);


	chart_node = nullptr;
	/*
	현재 출력된 모든 Edit Control을 제거 후,
	업데이트 된 좌표에 새롭게 다시 출력하는 구문
	*/
	_delete(flowChart.root);
	Invalidate(false);
	show(flowChart.root);
}


void CMFCteamProjectView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
	
	dc.SetViewportOrg(0 - GetScrollPos(SB_HORZ), 0-GetScrollPos(SB_VERT));
	show_line(flowChart.root, dc);
	//show_line(flowChart.root, dc);
}


void CMFCteamProjectView::OnDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	switch (chart_node->key->type)
	{
	case VAR:
	case NORMAL:
		chart_node->left->parent = chart_node->parent;
		if (chart_node->parent->key->type == IF)
			chart_node->parent->right = chart_node->left;
		else
			chart_node->parent->left = chart_node->left;

		if (chart_node->left->key->rect != nullptr)
		{
			delete chart_node->left->key->rect;
			chart_node->left->key->rect = new CRect(
				chart_node->key->rect->left,
				chart_node->key->rect->top,
				chart_node->key->rect->right,
				chart_node->key->rect->bottom
			);
			chart_node->left->key->set_coordinates();
		}

		if (chart_node != nullptr)
			delete chart_node;
		break;
	case FOR_DO:
		chart_node->left->parent = chart_node->parent->parent;
		if (chart_node->parent->parent->key->type == IF)
			chart_node->parent->parent->right = chart_node->left;
		else
			chart_node->parent->parent->left = chart_node->left;

		if (chart_node->left->key->rect != nullptr)
		{
			delete chart_node->left->key->rect;
			chart_node->left->key->rect = new CRect(
				chart_node->parent->key->rect->left,
				chart_node->parent->key->rect->top,
				chart_node->parent->key->rect->right,
				chart_node->parent->key->rect->bottom
			);
			chart_node->left->key->set_coordinates();
		}
		

		if (chart_node->parent != nullptr)
			delete chart_node->parent;
		if (chart_node != nullptr)
			delete chart_node;
		break;
	/*case WHILE_CONDITION:
		break;*/
	case WHILE_DO:
		chart_node->left->parent = chart_node->parent->parent;
		if (chart_node->parent->parent->key->type == IF)
			chart_node->parent->parent->right = chart_node->left;
		else
			chart_node->parent->parent->left = chart_node->left;

		if (chart_node->left->key->rect != nullptr)
		{
			delete chart_node->left->key->rect;
			chart_node->left->key->rect = new CRect(
				chart_node->parent->key->rect->left,
				chart_node->parent->key->rect->top,
				chart_node->parent->key->rect->right,
				chart_node->parent->key->rect->bottom
			);
			chart_node->left->key->set_coordinates();
		}

		if (chart_node->parent != nullptr)
			delete chart_node->parent;
		if (chart_node != nullptr)
			delete chart_node;
		break;
	case IF:
		chart_node->right->parent = chart_node->parent;
		if (chart_node->parent->key->type == IF)
			chart_node->parent->right = chart_node->right;
		else
			chart_node->parent->left = chart_node->right;

		if (chart_node->right->key->rect != nullptr)
		{
			delete chart_node->right->key->rect;
			chart_node->right->key->rect = new CRect(
				chart_node->key->rect->left,
				chart_node->key->rect->top,
				chart_node->key->rect->right,
				chart_node->key->rect->bottom
			);
			chart_node->right->key->set_coordinates();
		}

		if (chart_node->left != nullptr)
			delete chart_node->left;
		if (chart_node != nullptr)
			delete chart_node;
		break;
	case IF_FALSE:
		chart_node->left->parent = chart_node->parent->parent;
		if (chart_node->parent->parent->key->type == IF)
			chart_node->parent->parent->right = chart_node->left;
		else
			chart_node->parent->parent->left = chart_node->left;

		if (chart_node->left->key->rect != nullptr)
		{
			delete chart_node->left->key->rect;
			chart_node->left->key->rect = new CRect(
				chart_node->parent->key->rect->left,
				chart_node->parent->key->rect->top,
				chart_node->parent->key->rect->right,
				chart_node->parent->key->rect->bottom
			);
			chart_node->left->key->set_coordinates();
		}

		if (chart_node->parent->left != nullptr)
			delete chart_node->parent->left;
		if (chart_node->parent != nullptr)
			delete chart_node->parent;
		if (chart_node != nullptr)
			delete chart_node;
		break;
	case END:
		chart_node->key->code.Format(_T(""));
		chart_node->key->pEdit->SetWindowTextW(_T(""));
		chart_node->key->type = NONE;
		break;
	}

	chart_node = nullptr;
	_delete(flowChart.root);
	show(flowChart.root);
	Invalidate(true);
}


void CMFCteamProjectView::OnClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	clear(flowChart.root);

	// 순서도의 시작부분 생성
	flowChart.root = new CNode(flowChart.root);
	flowChart.root->key = new FlowChart(10, 10, START);
	flowChart.root->key->code.SetString(_T("START"));

	flowChart.root->left = new CNode(flowChart.root);
	flowChart.root->left->key = new FlowChart(10, 10, NONE);

	show(flowChart.root);
	Invalidate(true);
}


// 소스코드 추가하는 작업 수행 
// Dialog 띄우고 거기에 sourceCode 출력 및 다양한 기능
void CMFCteamProjectView::OnSource()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if (nSourceLanguage == 0) { // c++소스
		sourceCode = "";
		sourceCode += "#include <iostream>\r\nusing namespace std;\r\n\r\nint main(void){\r\n";
		flowChart.makeCppSourceCode();
		sourceCode += flowChart.tempCode + (CString)"\r\n    return 0;\r\n}";
	}
	else if (nSourceLanguage == 1) { // Java 소스
		sourceCode = "";
		sourceCode += "import java.util.Scanner;\r\n\r\npublic class JavaSourceCode{\r\n\r\npublic static void main (String[] args){\r\n";
		flowChart.makeJavaSourceCode();
		sourceCode += flowChart.tempCode + (CString)"\r\n   }\r\n}";
	}

	if (sourceDlg == nullptr) {
		sourceDlg = new CSourceDialog();
		sourceDlg->m_parent = this;
		sourceDlg->m_sourceEdit1.m_sourceCode = this->sourceCode;
		sourceDlg->Create(IDD_DIALOG1, this);
		sourceDlg->ShowWindow(SW_SHOW);
	}
	else {

		sourceDlg->SetFocus();
	}
}


void CMFCteamProjectView::OnSelectcpp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	nSourceLanguage = 0;
}


void CMFCteamProjectView::OnSelectjava()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	nSourceLanguage = 1;
}


void CMFCteamProjectView::OnUpdateSelectcpp(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(nSourceLanguage == 0);
}


void CMFCteamProjectView::OnUpdateSelectjava(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(nSourceLanguage == 1);
}



void CMFCteamProjectView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}
