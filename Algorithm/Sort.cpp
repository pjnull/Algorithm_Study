#include "Sort.h"

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
