#include "stdafx.h"
#include "FlowChart.h"

class CMFCteamProjectView;
FlowChart::FlowChart()
{
}

FlowChart::FlowChart(int x, int y, int type)
	: type(type), width_num(0), height_num(0), pEdit(nullptr), code("")
{
	// 순서도가 왼쪽으로 이어지는 경우
	if (this->type == START)
	{
		this->x = x;
		this->y = y;
	}
	else if (this->type == IF_FALSE)
	{
		this->x = x + 100 + 50;
		this->y = y;
	}
	// 순서도가 아래로 이어지는 경우
	else
	{
		this->x = x;
		this->y = y + 50 + 30;
	}
	rect = new CRect(this->x + (this->width_num) * 150, this->y, 
		this->x + (this->width_num) * 150 + 100, this->y + 50);
}


FlowChart::~FlowChart()
{
	if (pEdit != nullptr)
		delete pEdit;

	if (rect != nullptr)
		delete rect;
}

void FlowChart::set_coordinates()
{
	this->x = this->rect->left;
	this->y = this->rect->top;
}

void FlowChart::addContent(CString str)
{
	if (type != START && type != END) {
		code += str + (CString)"\r\n";
	}
}

void FlowChart::addConditionOfIf(CString str)
{
	code += (CString)"if(" + str + (CString)")";
}

void FlowChart::addTrueOfIf(CString str)
{
	code += (CString)"{\r\n" + str + (CString)"\r\n}\r\n";
}

void FlowChart::addFalseOfIf(CString str)
{
	code += (CString)"else{\r\n" + str + (CString)"\r\n}\r\n";
}

void FlowChart::addConditionOfWhile(CString str)
{
	code += (CString)"while(" + str + (CString)")";
}

void FlowChart::addContentOfWhile(CString str)
{
	code += (CString)"{\r\n" + str + (CString)"\r\n}\r\n";
}

void FlowChart::addConditionOfFor(CString str)
{
	CString varInit;
	CString conditionOfLoop;
	CString diffOfVar;
	CString nameOfVar;

	AfxExtractSubString(varInit, str, 0, ':');
	AfxExtractSubString(conditionOfLoop, str, 1, ':');
	AfxExtractSubString(diffOfVar, str, 2, ':');
	AfxExtractSubString(nameOfVar, varInit, 0, '=');

	code += (CString)"for(int " + varInit + (CString)"; " + nameOfVar +
		(diffOfVar >= (CString)"0" ? (CString)" <= " : (CString)" >= ") +
		conditionOfLoop + (CString)"; " + nameOfVar + (CString)" = " +
		nameOfVar + (diffOfVar >= (CString)"0" ? (CString)" + " : (CString)"") +
		diffOfVar + (CString)")";
}

void FlowChart::addContentOfFor(CString str)
{
	code += (CString)"{\r\n" + str + (CString)"\r\n}\r\n";
}
