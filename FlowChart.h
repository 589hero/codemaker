#pragma once
#include"CMyEdit.h"

/*
NONE : 타입을 선택 하지 않음
START : 순서도의 시작 부분 -> 오직 한 개만 존재해야 함
END : 순서도의 종료 부분 -> 여러개 존재 가능
VAR : 변수선언
NORMAL : 일반적인 구문들
IF : 조건문
IF_TRUE : 조건문이 참인 경우 실행할 구문
IF_FLASE : 조건문이 거짓인 경우 실행할 구문
FOR : for 반복문
WHILE : while 반복문
*/
enum flowchartType{
	NONE = 0, START, END, VAR, NORMAL, IF, IF_TRUE, IF_FALSE, 
	FOR_CONDITION, FOR_DO, WHILE_CONDITION, WHILE_DO
};

class FlowChart
{
public:
	int x, y;		// 왼쪽 상단 모서리의 x, y 좌표 값
	int type;		// 어떤 구문이 들어가는지
	int width_num;
	int height_num;

	CString code;
	CMyEdit* pEdit;
	CRect* rect;
public:
	FlowChart();
	FlowChart(int x, int y, int type);
	~FlowChart();

	void set_coordinates();

	void addContent(CString str);
	void addConditionOfIf(CString str);
	void addTrueOfIf(CString str);
	void addFalseOfIf(CString str);
	void addConditionOfWhile(CString str);
	void addContentOfWhile(CString str);
	void addConditionOfFor(CString str);
	void addContentOfFor(CString str);
};
