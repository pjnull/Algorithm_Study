#include "BST.h"

void BST::insert(int key)
{
	Node* newnode = new Node();
	newnode->key = key;

	if (_root == nullptr)
	{
		_root = newnode;
		return;
	}
	Node* node = _root;
	Node* parent = nullptr;
	while (node)
	{
		parent = node;
		if (key < node->key)node = node->left;
		if (key > node->key)node = node->right;
		
	}
	newnode->parent = parent;
	if (key < parent->key)parent->left = newnode;
	if (key > parent->key)parent->right = newnode;

}

void BST::Print(Node* node, int x, int y)
{
}

void BST::Print_Tree(Node* node)
{
}
