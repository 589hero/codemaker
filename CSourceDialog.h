#pragma once
#include "CSourceEdit.h"

// CSourceDialog 대화 상자

class CMFCteamProjectView;

class CSourceDialog : public CDialog
{
	DECLARE_DYNAMIC(CSourceDialog)

public:
	CSourceDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSourceDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSourceDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedSavecpp();
	afx_msg void OnBnClickedCompilecpp();
	afx_msg void OnBnClickedExecpp();
	afx_msg void OnBnClickedSavejava();
	afx_msg void OnBnClickedCompilejava();
	afx_msg void OnBnClickedExejava();

	CMFCteamProjectView* m_parent; // 부모 윈도우
	CSourceEdit m_sourceEdit1;

	
};
