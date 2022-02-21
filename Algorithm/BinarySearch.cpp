#include "BinarySearch.h"
#include <iostream>
#include <windows.h>
using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));

}


void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x),static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}


BinarySearch::BinarySearch()
{
	_nil = new Node2();
	_root = _nil;
}
BinarySearch::~BinarySearch()
{
	delete _nil;
}
void BinarySearch::Insert(int key)
{
	Node2* newnode = new Node2();
	newnode->key = key;

	/*if (_root == _nil)
	{
		_root = newnode;
		return;
	}*/
	Node2* node = _root;
	Node2* parent = _nil;

	while (node!= _nil)
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

	if (parent == _nil)_root = newnode;
	else if (key < parent->key)parent->left=newnode;
	else parent->right=newnode;

	newnode->left = _nil;
	newnode->right = _nil;
	newnode->color = Color::Red;

	InsertFixup(newnode);

}

void BinarySearch::InsertFixup(Node2* node)
{
	while (node->parent->color == Color::Red)
	{
		if (node->parent == node->parent->parent->left)
		{
			Node2* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				uncle->color = Color::Black;
				node = node->parent->parent;
			}
			else
			{
				if (node = node->parent->right)
				{
					node=node->parent;
					LeftRotate(node);
				}
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			Node2* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				uncle->color = Color::Black;
				node = node->parent->parent;
			}
			else
			{
				if (node = node->parent->left)
				{
					node = node->parent;
					RightRotate(node);
				}
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
			
		}
	}
	_root->color = Color::Black;
}

//void BinarySearch::Print_Inorder(Node2* node)
//{
//	if (node == nullptr)return;
//	//전위 순회
//	cout << node->key << endl;
//
//	Print_Inorder(node->left);
//	Print_Inorder(node->right);
//	
//	
//}

void BinarySearch::Print(Node2* node, int x, int y)
{
	if (node == _nil)return;

	SetCursorPosition(x, y);

	if (node->color == Color::Black)SetCursorColor(ConsoleColor::BLUE);
	else SetCursorColor(ConsoleColor::RED);

	cout << node->key;
	Print(node->left, x-5/(y+1), y+1);
	Print(node->right, x+5/(y+1), y+1);
	
	SetCursorColor(ConsoleColor::WHITE);

}

void BinarySearch::Delete(int key)
{
	Node2* deleteNode = Search_key(_root, key);
	Delete(deleteNode);

}

void BinarySearch::Delete(Node2* node)
{
	if (node == _nil)return;

	if (node->left == _nil)Replace(node, node->right);
	else if (node->right == _nil)Replace(node, node->left);
	else
	{
		Node2* next=Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearch::Replace(Node2* node1, Node2* node2)
{
	if (node1->parent == _nil)_root = node2;
	else if (node1 == node1->parent->left) node1->parent->left = node2;
	else node1->parent->right = node2;
	
	if (node2!= _nil)node2->parent = node1->parent;

	delete node1;
}

void BinarySearch::LeftRotate(Node2* x)
{
	Node2* y = x->right;

	x->right = y->left;

	if (y->left != _nil)y->left->parent = x;
	
	y->parent = x->parent;
	
	if (x->parent == _nil)_root = y;
	else if (x == x->parent->left)x->parent->left = y;
	else x->parent->right = y;
	
	y->left = x;
	x->parent = y;
}

void BinarySearch::RightRotate(Node2* y)
{
	Node2* x = y->left;

	y->left = x->right;

	if (y->right != _nil)x->right->parent = y;
	
	x->parent = y->parent;
	
	if (y->parent == _nil)_root = x;
	else if (y == y->parent->left)y->parent->left = x;
	else y->parent->right = x;
	
	x->right = y;
	y->parent = x;
}

Node2* BinarySearch::Search_key(Node2* node, int key)
{
	if (node == _nil || key == node->key)
	{
		return node;
	}

	if (key < node->key)return Search_key(node->left,key);
	else return Search_key(node->right,key);

}

Node2* BinarySearch::Max(Node2* node)
{
	while (node->right!=_nil)
	{
		node=node->right;
	}
	return node;
}

Node2* BinarySearch::Min(Node2* node)
{
	while (node->left!=_nil)
	{
		node= node->left;
	}
	return node;
}

Node2* BinarySearch::Next(Node2* node)
{
	if (node->right!= _nil)return Min(node->right);
	
	Node2* parent = node->parent;

	while (parent!= _nil && node==parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}


