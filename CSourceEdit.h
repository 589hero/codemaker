#pragma once


// CSourceEdit

class CSourceEdit : public CEdit
{
	DECLARE_DYNAMIC(CSourceEdit)

public:
	CSourceEdit();
	virtual ~CSourceEdit();
	CString m_sourceCode;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


