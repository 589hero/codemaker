#pragma once
#include"FlowChart.h"

class CNode
{
public:
	FlowChart *key;			// value
	CNode* left;				// left child node
	CNode* right;				// right child node
	CNode* parent;			// parent node
public:
	CNode();
	CNode(CNode* parent);
	CNode(CNode* left, CNode* right);
	~CNode();
	
	void setLeft(CNode* left);
	void setRight(CNode* right);
	
	CNode* getLeft();
	CNode* getRight();
};

