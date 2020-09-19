#pragma once
#include"CNode.h"


/*
�� Binary Tree�� �⺻������ left-child�� ��尡 �߰��Ǵ� �����̴�.
right-child�� ��尡 �߰��Ǵ� ������ if������ ������ false�� �� ���� �ش��Ѵ�.
���� �� Binary Tree�� Ž���� ���̿켱Ž���� �⺻���� �Ѵ�.
*/

class BinaryTree
{
public:
	CNode* root;
	CString tempCode;
public:
	BinaryTree();
	BinaryTree(CNode* root);
	~BinaryTree();

	void setRoot(CNode* root);
	CNode* getRoot();
	void preOrderToMakeCppCode(CNode* curNode);
	void preOrderToMakeJavaCode(CNode* curNode);
	void clearCode(CNode* curNode);

	// View���� �����ϰ� ����ϱ� ���� Wrapping �Լ�
	void makeCppSourceCode();
	void makeJavaSourceCode();

	/*void show(CNode* node, CMFCteamProjectView* view);*/
	void clear(CNode* node);
};

