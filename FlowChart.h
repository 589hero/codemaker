#pragma once
#include"CMyEdit.h"

/*
NONE : Ÿ���� ���� ���� ����
START : �������� ���� �κ� -> ���� �� ���� �����ؾ� ��
END : �������� ���� �κ� -> ������ ���� ����
VAR : ��������
NORMAL : �Ϲ����� ������
IF : ���ǹ�
IF_TRUE : ���ǹ��� ���� ��� ������ ����
IF_FLASE : ���ǹ��� ������ ��� ������ ����
FOR : for �ݺ���
WHILE : while �ݺ���
*/
enum flowchartType{
	NONE = 0, START, END, VAR, NORMAL, IF, IF_TRUE, IF_FALSE, 
	FOR_CONDITION, FOR_DO, WHILE_CONDITION, WHILE_DO
};

class FlowChart
{
public:
	int x, y;		// ���� ��� �𼭸��� x, y ��ǥ ��
	int type;		// � ������ ������
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
