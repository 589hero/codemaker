// CSourceDialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_teamProject.h"
#include "CSourceDialog.h"
#include "afxdialogex.h"
#include "MFC_teamProjectView.h"
#include "CSourceEdit.h"


// CSourceDialog 대화 상자

IMPLEMENT_DYNAMIC(CSourceDialog, CDialog)

CSourceDialog::CSourceDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CSourceDialog::~CSourceDialog()
{
}

void CSourceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_sourceEdit1);
}


BEGIN_MESSAGE_MAP(CSourceDialog, CDialog)
	ON_BN_CLICKED(IDC_SAVECPP, &CSourceDialog::OnBnClickedSavecpp)
	ON_BN_CLICKED(IDC_COMPILECPP, &CSourceDialog::OnBnClickedCompilecpp)
	ON_BN_CLICKED(IDC_EXECPP, &CSourceDialog::OnBnClickedExecpp)
	ON_BN_CLICKED(IDC_SAVEJAVA, &CSourceDialog::OnBnClickedSavejava)
	ON_BN_CLICKED(IDC_COMPILEJAVA, &CSourceDialog::OnBnClickedCompilejava)
	ON_BN_CLICKED(IDC_EXEJAVA, &CSourceDialog::OnBnClickedExejava)
END_MESSAGE_MAP()


// CSourceDialog 메시지 처리기


void CSourceDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_parent->sourceDlg = nullptr;
	this->DestroyWindow(); // 모달리스 창을 없앰.
	// CDialog::OnCancel();
}


void CSourceDialog::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialog::PostNcDestroy();
}


BOOL CSourceDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	m_sourceEdit1.SetWindowTextW(m_sourceEdit1.m_sourceCode);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSourceDialog::OnBnClickedSavecpp()
{
	CStdioFile file;
	CFileDialog dlg(FALSE, _T("cpp file(*.cpp)"), _T("*.cpp"), NULL, _T("cpp file(*.cpp)|*.cpp|"));
	CString path;

	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		if (path.Right(4) != ".cpp")
		{
			path += ".cpp";
		}
		file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		CString str;
		m_sourceEdit1.GetWindowTextW(str);
		str.Replace(_T("\r\n"), _T("\n"));
		file.WriteString(str);
		file.Close();
	}
}


void CSourceDialog::OnBnClickedCompilecpp()
{
	CFileDialog dlg(TRUE, _T("cpp file(*.cpp)"), _T("*.cpp"), NULL, _T("cpp file(*.cpp)|*.cpp|"));
	CString path, f_name, remove_f_name;
	CString ko = _T("\"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvars64\"");
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		f_name = dlg.GetFileName();
		path.Replace(_T("\\"), _T("/"));
		remove_f_name = _T("/") + f_name;
		path.Replace(remove_f_name, _T(""));
		ko += _T("&&cd ") + path + _T("&&cl ") + f_name + _T("&pause");

		char *s2 = new char[ko.GetLength() + 1];
		strcpy_s(s2, ko.GetLength() + 1, CT2A(ko));
		system(s2);
		delete s2;
	}
}


void CSourceDialog::OnBnClickedExecpp()
{
	CFileDialog dlg(TRUE, _T("exe file(*.exe)"), _T("*.exe"), NULL, _T("exe file(*.exe)|*.exe|"));
	CString path, f_name, remove_f_name;
	CString ko;
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		f_name = dlg.GetFileName();
		path.Replace(_T("\\"), _T("/"));
		remove_f_name = _T("/") + f_name;
		path.Replace(remove_f_name, _T(""));
		ko += _T("\"cd ") + path + _T("\"&&") + f_name + _T("&pause");

		char *s2 = new char[ko.GetLength() + 1];
		strcpy_s(s2, ko.GetLength() + 1, CT2A(ko));
		system(s2);
		delete s2;
	}
}


void CSourceDialog::OnBnClickedSavejava()
{
	CStdioFile file;
	CFileDialog dlg(FALSE, _T("java file(*.java)"), _T("*.java"), NULL, _T("java file(*.java)|*.java|"));
	CString path, f_name, remove_f_name;

	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		f_name = dlg.GetFileName();
		path.Replace(_T("\\"), _T("/"));
		f_name.Replace(_T(".java"), _T(""));
		if (path.Right(5) != ".java")
		{
			path += ".java";
		}
		file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		CString str;
		m_sourceEdit1.GetWindowTextW(str);
		str.Replace(_T("\r\n"), _T("\n"));
		str.Replace(_T("JavaSourceCode"), f_name);
		file.WriteString(str);
		file.Close();
	}
}


void CSourceDialog::OnBnClickedCompilejava()
{
	CFileDialog dlg(TRUE, _T("java file(*.java)"), _T("*.java"), NULL, _T("java file(*.java)|*.java|"));
	CString path, f_name, remove_f_name;
	CString ko;
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		f_name = dlg.GetFileName();
		path.Replace(_T("\\"), _T("/"));
		remove_f_name = _T("/") + f_name;
		path.Replace(remove_f_name, _T(""));
		ko += _T("\"cd ") + path + _T("\"&&")+_T("javac ") + f_name + _T("&pause");

		char *s2 = new char[ko.GetLength() + 1];
		strcpy_s(s2, ko.GetLength() + 1, CT2A(ko));
		system(s2);
		delete s2;
	}
}


void CSourceDialog::OnBnClickedExejava()
{
	CFileDialog dlg(TRUE, _T("class file(*.class)"), _T("*.class"), NULL, _T("class file(*.class)|*.class|"));
	CString path, f_name, remove_f_name;
	CString ko;
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		f_name = dlg.GetFileName();
		path.Replace(_T("\\"), _T("/"));
		remove_f_name = _T("/") + f_name;
		f_name.Replace(_T(".class"), _T(""));
		path.Replace(remove_f_name, _T(""));
		ko += _T("\"cd ") + path + _T("\"&&") + _T("java ") + f_name + _T("&pause");

		char *s2 = new char[ko.GetLength() + 1];
		strcpy_s(s2, ko.GetLength() + 1, CT2A(ko));
		system(s2);
		delete s2;
	}
}
