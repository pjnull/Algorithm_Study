#pragma once

enum class Color
{
	Red=0,
	Black=1,
};

struct Node2
{
	Node2*	parent=nullptr;
	Node2*	left=nullptr;
	Node2*	right=nullptr;
	int		key = {};
	Color	color = Color::Black;
};


class BinarySearch
{
public:
	BinarySearch();
	~BinarySearch();

	void	Insert(int key);
	void	InsertFixup(Node2* node);
	//void	Print_Inorder(Node2* node);
	//void	Print_Inorder() { Print_Inorder(_root); }
	void	Print(Node2* node, int x, int y);
	void	Print() { Print(_root,10,0); }
	void	print();
	void	Delete(int key);
	void	Delete(Node2* node);
	void	DeleteFixup(Node2* node);
	void	Replace(Node2* node1,Node2* node2);

	void	LeftRotate(Node2* x);
	void	RightRotate(Node2* y);

	Node2*	Search_key(Node2* node,int key);

	Node2*	Max(Node2* node);
	Node2*	Min(Node2* node);
	Node2*	Next(Node2* node);
private:
	Node2*	_root=nullptr;
	Node2*	_nil = nullptr;
};

