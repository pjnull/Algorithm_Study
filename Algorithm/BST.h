#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
};

class BST
{
public:

	void insert(int key);
	void Print(Node* node,int x,int y);
	void Print();
	void Print_Tree(Node* node);
	void Print_Tree() { Print_Tree(_root); }
private:
	Node* _root=nullptr;
};