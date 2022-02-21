#include "BinarySearch.h"
#include <iostream>
#include <windows.h>
using namespace std;


void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x),static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}
void BinarySearch::Insert(int key)
{
	Node2* newnode = new Node2();
	newnode->key = key;

	if (_root == nullptr)
	{
		_root = newnode;
		return;
	}
	Node2* node = _root;
	Node2* parent = nullptr;

	while (node)
	{
		parent = node;
		if (node->key < key)
		{
			node = node->right;
		}
		else if (node->key > key)
		{
			node = node->left;
		}
	}
	newnode->parent = parent;

	if (key < parent->key)parent->left=newnode;
	else parent->right=newnode;
}

void BinarySearch::Print_Inorder(Node2* node)
{
	if (node == nullptr)return;
	//전위 순회
	cout << node->key << endl;

	Print_Inorder(node->left);
	Print_Inorder(node->right);
	
	
}

void BinarySearch::Print(Node2* node, int x, int y)
{
	if (node == nullptr)return;

	SetCursorPosition(x, y);
	cout << node->key;
	Print(node->left, x-5/(y+1), y+1);
	Print(node->right, x+5/(y+1), y+1);
}

void BinarySearch::Delete(int key)
{
	Node2* deleteNode = Search_key(_root, key);
	Delete(deleteNode);

}

void BinarySearch::Delete(Node2* node)
{
	if (node == nullptr)return;

	if (node->left == nullptr)Replace(node, node->right);
	else if (node->right == nullptr)Replace(node, node->left);
	else
	{
		Node2* next=Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearch::Replace(Node2* node1, Node2* node2)
{
	if (node1->parent == nullptr)_root = node2;
	else if (node1 == node1->parent->left) node1->parent->left = node2;
	else node1->parent->right = node2;
	
	if (node2)node2->parent = node1->parent;

	delete node1;
}

Node2* BinarySearch::Search_key(Node2* node, int key)
{
	if (node == nullptr || key == node->key)
	{
		return node;
	}

	if (key < node->key)return Search_key(node->left,key);
	else return Search_key(node->right,key);

}

Node2* BinarySearch::Max(Node2* node)
{
	while (node->right)
	{
		node=node->right;
	}
	return node;
}

Node2* BinarySearch::Min(Node2* node)
{
	while (node->left)
	{
		node= node->left;
	}
	return node;
}

Node2* BinarySearch::Next(Node2* node)
{
	if (node->right)return Min(node->right);
	
	Node2* parent = node->parent;

	while (parent&& node==parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}


