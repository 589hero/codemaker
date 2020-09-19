
// MFC_teamProjectView.h: CMFCteamProjectView 클래스의 인터페이스
//

#pragma once
#include"FlowChart.h"
#include"BinaryTree.h"

class CMFCteamProjectDoc;
class CSourceDialog;

class CMFCteamProjectView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMFCteamProjectView() noexcept;
	DECLARE_DYNCREATE(CMFCteamProjectView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFC_TEAMPROJECT_FORM };
#endif

// 특성입니다.
public:
	CMFCteamProjectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMFCteamProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 멤버변수 선언
	BinaryTree flowChart;
	/*FlowChart* chart;*/
	CNode* chart_node;



	/*
	show(), check(), _delete() : 매개변수 node는 Tree의 root를 의미한다.
											진행방향은 root에서 leaf로 postorder 방식을 사용한다.
	*/
	void show(CNode* node)
	{
		if (node == nullptr)
			return;
		ScrollToPosition(CPoint(0,0));
		// first recur on left subtree
		show(node->left);

		// then recur on right subtree
		show(node->right);

		// now deal with the node
		switch (node->key->type)
		{
		case NONE:
			node->key->pEdit = new CMyEdit(RGB(255, 255, 255));
			break;
		case START:
			node->key->pEdit = new CMyEdit(RGB(255, 225, 70));
			break;
		case END:
			node->key->pEdit = new CMyEdit(RGB(255, 225, 70));
			break;
		case VAR:
			node->key->pEdit = new CMyEdit(RGB(160, 175, 255));
			break;
		case NORMAL:
			node->key->pEdit = new CMyEdit(RGB(0, 175, 255));
			break;
		case IF:
		case IF_TRUE:
		case IF_FALSE:
			node->key->pEdit = new CMyEdit(RGB(255, 96, 127));
			break;
		case FOR_CONDITION:
		case FOR_DO:
			node->key->pEdit = new CMyEdit(RGB(115, 234, 168));
			break;
		case WHILE_CONDITION:
		case WHILE_DO:
			node->key->pEdit = new CMyEdit(RGB(60, 160, 60));
			break;
		}
		node->key->pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN,
			*(node->key->rect), this, 1);
		node->key->pEdit->SetWindowTextW(node->key->code);
	}
	void check(CNode* node, CPoint pt, CNode** chart);
	void _delete(CNode* node);

	CString sourceCode;
	CSourceDialog* sourceDlg;
	int nSourceLanguage; // 0 : c++, 1 : Java

	/*
	update() : 
	*/
	void update(CNode* node);

	void show_line(CNode* node, CPaintDC& dc);
	void clear(CNode* node);


	afx_msg void OnIf();
	afx_msg void OnFor();
	afx_msg void OnWhile();
	afx_msg void OnVar();
	afx_msg void OnNormal();
	afx_msg void OnEnd();
	//afx_msg void OnIfTrue();
	//afx_msg void OnIfFalse();
	afx_msg void OnOnlyif();
	afx_msg void OnIfelse();
	afx_msg void OnPaint();
	afx_msg void OnDelete();
	afx_msg void OnClear();
	afx_msg void OnSource();
	afx_msg void OnSelectcpp();
	afx_msg void OnSelectjava();
	afx_msg void OnUpdateSelectcpp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectjava(CCmdUI *pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	int scrolly;
//	afx_msg void OnMouseLeave();
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // MFC_teamProjectView.cpp의 디버그 버전
inline CMFCteamProjectDoc* CMFCteamProjectView::GetDocument() const
   { return reinterpret_cast<CMFCteamProjectDoc*>(m_pDocument); }
#endif

