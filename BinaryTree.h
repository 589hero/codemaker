#pragma once
#include"CNode.h"


/*
이 Binary Tree는 기본적으로 left-child에 노드가 추가되는 구조이다.
right-child에 노드가 추가되는 조건은 if구문의 조건의 false가 될 때만 해당한다.
또한 이 Binary Tree의 탐색은 깊이우선탐색을 기본으로 한다.
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

	// View에서 간단하게 사용하기 위한 Wrapping 함수
	void makeCppSourceCode();
	void makeJavaSourceCode();

	/*void show(CNode* node, CMFCteamProjectView* view);*/
	void clear(CNode* node);
};

