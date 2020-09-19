#include "stdafx.h"
#include "CNode.h"



CNode::CNode()
	:key(nullptr), left(nullptr), right(nullptr), parent(nullptr)
{
}

CNode::CNode(CNode * parent)
	: parent(parent), key(nullptr), left(nullptr), right(nullptr)
{
}

CNode::CNode(CNode * left, CNode * right)
	: left(left), right(right), key(nullptr), parent(nullptr)
{
}


CNode::~CNode()
{
	if (key != nullptr)
		delete key;

	//if (parent != nullptr)
	//	delete parent;

	//if (right != nullptr)
	//	delete right;

	//if (left != nullptr)
	//	delete left;
}

void CNode::setLeft(CNode * left)
{
	this->left = left;
}

void CNode::setRight(CNode * right)
{
	this->right = right;
}

CNode * CNode::getLeft()
{
	return left;
}

CNode * CNode::getRight()
{
	return right;
}
