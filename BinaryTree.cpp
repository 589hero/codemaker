#include "stdafx.h"
#include "BinaryTree.h"


BinaryTree::BinaryTree()
{
}

BinaryTree::BinaryTree(CNode * root)
	: root(root)
{
}


BinaryTree::~BinaryTree()
{
}

void BinaryTree::setRoot(CNode * root)
{
	this->root = root;
}

CNode * BinaryTree::getRoot()
{
	return root;
}

void BinaryTree::preOrderToMakeCppCode(CNode * curNode)
{
	if (curNode == nullptr) {
		return;
	}

	if (curNode != nullptr && curNode->key->type != START) {
		CString str;
		curNode->key->pEdit->GetWindowTextW(str);

		switch (curNode->key->type) {
		case VAR:
		case NORMAL:
			curNode->key->addContent(str);
			break;
		case IF:
			curNode->key->addConditionOfIf(str);
			break;
		case IF_TRUE:
			curNode->key->addTrueOfIf(str);
			break;
		case IF_FALSE:
			curNode->key->addFalseOfIf(str);
			break;
		case WHILE_CONDITION:
			curNode->key->addConditionOfWhile(str);
			break;
		case WHILE_DO:
			curNode->key->addContentOfWhile(str);
			break;
		case FOR_CONDITION:
			curNode->key->addConditionOfFor(str);
			break;
		case FOR_DO:
			curNode->key->addContentOfFor(str);
			break;
		default:
			break;
		}
		tempCode += curNode->key->code;
	}

	preOrderToMakeCppCode(curNode->left);
	preOrderToMakeCppCode(curNode->right);
}

void BinaryTree::preOrderToMakeJavaCode(CNode * curNode)
{
	if (curNode == nullptr) {
		return;
	}

	if (curNode != nullptr && curNode->key->type != START) {
		CString str;
		curNode->key->pEdit->GetWindowTextW(str);

		switch (curNode->key->type) {
		case VAR:
		case NORMAL:
			curNode->key->addContent(str);
			break;
		case IF:
			curNode->key->addConditionOfIf(str);
			break;
		case IF_TRUE:
			curNode->key->addTrueOfIf(str);
			break;
		case IF_FALSE:
			curNode->key->addFalseOfIf(str);
			break;
		case WHILE_CONDITION:
			curNode->key->addConditionOfWhile(str);
			break;
		case WHILE_DO:
			curNode->key->addContentOfWhile(str);
			break;
		case FOR_CONDITION:
			curNode->key->addConditionOfFor(str);
			break;
		case FOR_DO:
			curNode->key->addContentOfFor(str);
			break;
		default:
			break;
		}
		tempCode += curNode->key->code;
	}

	preOrderToMakeJavaCode(curNode->left);
	preOrderToMakeJavaCode(curNode->right);
}

void BinaryTree::clearCode(CNode * curNode)
{
	if (curNode == nullptr) {
		return;
	}

	if (curNode != nullptr && curNode->key->type != START) {
		curNode->key->code = "";
	}

	clearCode(curNode->left);
	clearCode(curNode->right);
}

void BinaryTree::makeCppSourceCode()
{
	tempCode = "";
	clearCode(this->root);
	preOrderToMakeCppCode(this->root);
}

void BinaryTree::makeJavaSourceCode()
{
	tempCode = "";
	clearCode(this->root);
	preOrderToMakeJavaCode(this->root);
}

//void BinaryTree::show(CNode * node, CMFCteamProjectView* view)
//{
//	if (node == nullptr)
//		return;
//	
//	// first recur on left subtree
//	show(node->left, view);
//
//	// then recur on right subtree
//	show(node->right, view);
//
//	// now deal with the node
//	node->key->pEdit = new CEdit;
//	int len = node->key->pEdit->GetWindowTextLengthW();
//	node->key->pEdit->SetSel(0, len);
//	node->key->pEdit->ReplaceSel(node->key->code);
//	node->key->pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN,
//		*(node->key->rect), view, 1);
//}

void BinaryTree::clear(CNode * node)
{
	if (node == nullptr)
		return;

	// first recur on left subtree
	clear(node->left);

	// then recur on right subtree
	clear(node->right);

	// now deal with the node
	node->key->pEdit->GetWindowTextW(node->key->code);
	if (node->key->pEdit != nullptr)
		delete node->key->pEdit;
	if (node->key->rect != nullptr)
		delete node->key->rect;
}
