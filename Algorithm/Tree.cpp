#include "Tree.h"

template<typename T, typename Container = vector<T>, typename Function = less<T> >
class Priority_Q
{
public:
	void push(const T&data)
	{
		_heap.push_back(data);
		int now = static_cast<int>(_heap.size()) - 1;
		while (now>0)
		{
			//if (_heap[(now - 1) / 2] > _heap[now])break;//아래와 동일
			if (func(_heap[now], _heap[(now - 1) / 2]))break;
			swap(_heap[(now - 1) / 2], _heap[now]);
				now = (now - 1) / 2;

			
		}
	}
	void pop()
	{
		_heap[0] = _heap[_heap.size() - 1];
		_heap.pop_back();
		int now = 0;
		while(true)
		{
			int right = (now + 1) * 2;
			int left = (now + 1) * 2 - 1;
			if (left >= _heap.size())break;
			int next = now;
			if (func(_heap[next], _heap[left]))next = left;
			if (right<_heap.size()&&func(_heap[next],_heap[right]))next=right;
			if(next==now) break;
			swap(_heap[now],_heap[next]);
			now=next;

			
		}
	}
	bool empty()
	{
		return _heap.empty();
	}
	T& top()
	{
		return _heap[0];
	}
private:
	Container _heap = {  };
	Function func = {  };
};

void Tree()
{
	Priority_Q<int,vector<int>,greater<int>>pq;
	pq.push(100);
	pq.push(200);
	pq.push(300);
	pq.push(400);
	pq.push(500);

	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();
		cout << value << endl;
	}
}