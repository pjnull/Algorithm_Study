#include "Sort.h"
#include <queue>

void Sort::Bubble(vector<int>& v)
{
	for (int j = v.size(); j > 0; j--)
	{
		for (int i = 0; i < j; i++)
		{
			if (i + 1 != j)
			{
				if (v[i] > v[i + 1])::swap(v[i], v[i + 1]);
			}
		}
	}
}

void Sort::Selection(vector<int>& v)
{
	int best;
	for (int i = 0; i < v.size(); i++)
	{
		best = i;
		for (int j = i+1; j < v.size(); j++)
		{
			if (v[best] > v[j])best = j;
		}
		swap(v[i],v[best]);

	}
}

void Sort::Insert(vector<int>& v)
{
	for (int i = 1; i < v.size(); i++)
	{
		int insert = v[i];
		int count=0;
		for (int j = i-1; j >= 0; j--)
		{
			if (v[j] > insert)v[j + 1] = v[j];
			else
			{
				count = j;
				break;
			}
		}
		v[count + 1] = insert;
	}
}

void Sort::HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>>pq;

}

void Sort::MergeSort(vector<int>& v,int left,int right)
{
	if (left >= right)return;
	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid+1, right);
	MergeResult(v, left, mid, right);
}

void Sort::MergeResult(vector<int>& v, int left, int mid,int right)
{
	int leftindex = left;
	int rightindex = mid + 1;
	vector<int>temp;
	
	while (leftindex <= mid&&rightindex<=right)
	{
		if (v[leftindex] <= v[rightindex])
		{
			temp.push_back(v[leftindex]);
			leftindex++;
		}
		else
		{
			temp.push_back(v[rightindex]);
			rightindex++;
		}
	}
	if (leftindex > mid)
	{
		while (rightindex <= right)
		{
			temp.push_back(v[rightindex]);
			rightindex++;
		}
	}
	else
	{
		while (leftindex <= mid)
		{
			temp.push_back(v[leftindex]);
			leftindex++;
		}
	}
	for (int i=0;i<temp.size();i++)
	{
		v[left+i] = temp[i];
	}
}
