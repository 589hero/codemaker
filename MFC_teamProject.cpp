
// MFC_teamProject.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFC_teamProject.h"
#include "MainFrm.h"

#include "MFC_teamProjectDoc.h"
#include "MFC_teamProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCteamProjectApp

BEGIN_MESSAGE_MAP(CMFCteamProjectApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMFCteamProjectApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CMFCteamProjectApp 생성

CMFCteamProjectApp::CMFCteamProjectApp() noexcept
{
	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCteamProject.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CMFCteamProjectApp 개체입니다.

CMFCteamProjectApp theApp;


// CMFCteamProjectApp 초기화

BOOL CMFCteamProjectApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCteamProjectDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CMFCteamProjectView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CMFCteamProjectApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_infoText1;
	CStatic m_infoText2;
	CStatic m_infoText3;
	CStatic m_infoText4;
	CStatic m_infoText5;
	CStatic m_infoText6;
	virtual BOOL OnInitDialog();
	CStatic m_infoText7;
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NONETEXT, m_infoText1);
	DDX_Control(pDX, IDC_NORMALTEXT, m_infoText2);
	DDX_Control(pDX, IDC_IFTEXT, m_infoText3);
	DDX_Control(pDX, IDC_FORTEXT, m_infoText4);
	DDX_Control(pDX, IDC_WHILETEXT, m_infoText5);
	DDX_Control(pDX, IDC_VARTEXT, m_infoText6);
	DDX_Control(pDX, IDC_FILETEXT, m_infoText7);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CMFCteamProjectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCteamProjectApp 메시지 처리기





BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CString tempText1 = (CString)"아무런 Type이 지정되지 않은 Edit Control입니다. " + 
		(CString)"오른쪽 버튼을 눌러서 생기는 메뉴에서 원하는 Type을 선택하세요! ";

	CString tempText2 = (CString)("일반 구문을 작성하는 Edit Control입니다. ");

	CString tempText3 = (CString)"if문을 작성하는 Edit Control입니다. " +
		(CString)"if문만 만들 것인지 else구문도 만들 것인지 선택한 후 " + 
		(CString)"맨 처음 Edit Control에는 if문의 조건을, " +
		(CString)"밑에 있는 Edit Control에는 조건이 true일 때 실행되는 구문을, " +
		(CString)"오른쪽에 있는 Edit Control에는 조건이 false일 때 실행되는 구문을 입력하세요!";

	CString tempText4 = (CString)"for문을 작성하는 Edit Control입니다. " +
		(CString)"맨 처음 Edit Control은 for문의 조건들을 " +
		(CString)"(변수명)=(초기값):(끝값):(증가량)형태로 입력합니다. " + 
		(CString)"두 번째 Edit Control은 반복될 구문을 입력하세요! ";

	CString tempText5 = (CString)"while문을 작성하는 Edit Control입니다. " + 
		(CString)"맨 처음 Edit Control은 while문의 반복 조건을, " + 
		(CString)"두 번째 Edit Control은 반복될 구문을 입력하세요! ";

	CString tempText6 = (CString)"변수 선언을 하는 Edit Control입니다. " +
		(CString)"변수를 선언할 때에는 int a=1;와 같이 각 언어의 맞는 자료형을 명시해줘야 합니다. ";

	CString tempText7 = (CString)"① 원하는 언어를 선택하고 순서도를 만든 후 " +
		(CString)"\"작업->소스코드 만들기\" 메뉴를 클릭하여 소스코드를 생성합니다.\r\n\r\n" +
		(CString)"② (파일 저장)C++의 경우 \".cpp로 저장\", Java의 경우 " +
		(CString)"\".java로 저장\" 버튼을 눌러서 원하는 경로에 파일을 저장합니다. " +
		(CString)"\r\n\r\n" +
		(CString)"③ 선택한 언어에 대한 컴파일 버튼을 누른 후 " +
		(CString)"②에서 저장한 파일을 선택하여 컴파일 해줍니다.\r\n\r\n" +
		(CString)"④ (파일 실행)선택한 언어에 대해 실행하기 버튼을 누른 후 " +
		(CString)"C++의 경우 컴파일 과정에서 만들어진 exe파일, Java의 경우 " +
		(CString)".java파일을 선택해서 실행해줍니다. ";
	
	m_infoText1.SetWindowTextW(tempText1);
	m_infoText2.SetWindowTextW(tempText2);
	m_infoText3.SetWindowTextW(tempText3);
	m_infoText4.SetWindowTextW(tempText4);
	m_infoText5.SetWindowTextW(tempText5);
	m_infoText6.SetWindowTextW(tempText6);
	m_infoText7.SetWindowTextW(tempText7);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

