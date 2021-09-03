// Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <list>
#include "Gragh.h"
#include "Dijkstra.h"

using namespace std;

template<typename T>
class Vector
{
public:
	Vector()
	{

	}
	~Vector()
	{
		if (_data)delete _data;
	}
	void push_back(const T& value)
	{
		if (_size == _capacity)
		{
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)newCapacity++;
			reserve(newCapacity);
		}
		_data[_size] = value;
		_size++;
	}
	void reserve(int capacity)
	{
		_capacity = capacity;
		T* newData = new T[_capacity];
		for (int i = 0; i < _size; i++)
		{
			newData[i] = _data[i];
		}
		if (_data)delete _data;
		_data = newData;
	}
	T& operator[](const int pos) { return _data[pos]; }
	int size() { return _size; }
	int capacity() { return _capacity; }
	void clear() 
	{
		if (_data)
		{
			delete _data;
			_data = new T[_capacity];
		}
		_size = 0; 
	}
private:
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;

};

template<typename T>
class Node
{
public:
	Node() :_prev(nullptr), _next(nullptr), _data(T())
	{

	}
	Node(const T& value) :_prev(nullptr), _next(nullptr), _data(value)
	{

	}
	
private:
	T _data;
	Node* _prev;
	Node* _next;
};



template<typename T>
class Iterator
{
public:
	Iterator():_node(nullptr) 
	{

	}
	Iterator(Node<T>*node) :_node(node)
	{

	}
	//++it
	Iterator operator ++()
	{
		_node = _node->_next;
		return *this;
	}
	//--it
	Iterator operator --()
	{
		_node = _node->_prev;
		return *this;
	}
	//it++
	Iterator& operator ++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}
	//it--
	Iterator& operator --(int)
	{
		Iterator<T>temp = *this;
		_node = _node->_prev;
		return temp;
	}
	T& operator *()
	{
		return _node->_data;
	}
	bool operator ==(const Iterator& other)
	{
		return _node == other._node;
	}
	bool operator !=(const Iterator& other)
	{
		return _node != other._node;
	}


public:
	Node<T>* _node;
};

template<typename T>
class List
{
public:
	List() :_size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->next = _tail;
		_tail->prev = _head;
	}
	~List()
	{
		while (size > 0)
		{
			PopBack();
		}
		delete _head;
		delete _tail;

	}
	void PushBack(const T& value)
	{
		AddNode(_tail, value);
	}
	void PopBack()
	{
		Remove(_tail->_prev);
	}



private:
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = newNode;

		newNode->_next = before;
		before->_prev = newNode;
		return newNode;
	}

	Node<T>* Remove(Node<T>* node)
	{
		Node<T>* nextnode = node->_next;
		Node<T>* prevnode = node->_prev;

		nextnode->_prev = prevnode;
		prevnode->_next = nextnode;
		delete node;
		_size--;
		return nextnode;
	}
	int size() { return _size; }

public:
	using iterator = Iterator<T>;
	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }
	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}
	iterator erase(iterator it)
	{
		Node<T>* node = Remove(it._node);
			return iterator(node);
	}

public:
	Node<T>* _head;
	Node<T>* _tail;
	int _size;

};



int main()
{
	list<int>li;

	Vector<int>v;
	v.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		li.push_back(i);
		//cout<<v[i] <<" "<< v.size() << " " << v.capacity() << endl;
		cout<<v[i] <<" "<< v.size() << " " << v.capacity() << endl;
	}
	v.clear();
	cout << v.size() << " " << v.capacity() << endl;
	cout << "=======================" << endl;
	cout << "==========Grapgh=============" << endl;
	
	CreateGraph_1();
	CreateGraph_2();
	CreateGraph_3();
	Dijkstra(0);
	

}

