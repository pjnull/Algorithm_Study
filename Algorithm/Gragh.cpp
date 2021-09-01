#include "Gragh.h"


void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*>edges;
	};
	vector<Vertex>v;
	v.resize(6);
	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	bool connected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}
void CreateGraph_2()
{
	struct Vertex
	{
	};
	vector<Vertex>v;
	v.resize(6);
	vector<vector<bool>>adjacent(6, vector<bool>(6, false));

	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	bool connect = adjacent[0][4];
	cout << boolalpha << connect << endl;

	vector<vector<int>>adjacent2(6, vector<int>(6, -1));

	adjacent2[0][1] = 15;
	adjacent2[0][3] = 35;
	adjacent2[1][0] = 15;
	adjacent2[1][2] = 5;
	adjacent2[1][3] = 10;
	adjacent2[3][4] = 5;
	adjacent2[5][4] = 5;




}
vector<vector<int>>adj;
vector<bool>visited = vector < bool>(6, false);
vector<bool>discovered = vector < bool>(6, false);

void CreateGraph_3()
{
	struct Vertex
	{
	};
	vector<Vertex>v;

	v.resize(6);
	adj = vector<vector<int>>(6);
	adj[0].push_back(1);
	adj[0].push_back(3);
	adj[1].push_back(0);
	adj[1].push_back(2);
	adj[1].push_back(3);
	adj[3].push_back(4);
	adj[5].push_back(4);

	DFSAll();
	BFSAll();
}

void DFS(int start)
{
	visited[start] = true;
	cout << "Visted: " << start << endl;
	for (int i = 0; i < adj[start].size(); i++)
	{
		int there = adj[start][i];
		if (visited[there] == false)DFS(there);
	}
}

void DFSAll()
{
	for (int i=0;i<6;i++)
	{
		if (visited[i] == false)DFS(i);
	}
}

void BFS(int start)
{
	vector<int>parent(6, -1),distance(6,-1);
	queue<int>q;
	q.push(start);
	parent[start] = start;
	distance[start] = 0;
	discovered[start] = true;
	while (q.empty() == false)
	{
		start = q.front();
		q.pop();
		cout << "Discovered: " << start << endl;

		for (int discover : adj[start])
		{
			if (discovered[discover])continue;
			q.push(discover);
			discovered[discover] = true;
			parent[discover] = start;
			distance[discover] = distance[start] + 1;
		}
	}
}

void BFSAll()
{
	for (int i = 0; i < 6; i++)
	{
		if (discovered[i] == false)BFS(i);
	}
}
