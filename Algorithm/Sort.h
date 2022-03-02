#pragma once


#include <vector>
using namespace std;

class Sort
{
public:

	void Bubble(vector<int>& v);
	void Selection(vector<int>& v);
	void Insert(vector<int>& v);
	
	void HeapSort(vector<int>&v);
	void MergeSort(vector<int>& v,int left,int right);
	void MergeResult(vector<int>&v,int left,int mid,int right);
};

