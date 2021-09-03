#include "Dijkstra.h"

void Dijkstra(int start)
{
	struct Vertex
	{
	};
	vector<Vertex>v;
	v.resize(6);
	vector<vector<int>>adjacent(6, vector<int>(6,-1));
	
	
	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;

	pair<int,int>vertex_cost;
	list<pair<int,int>>discorver;
	vector<int>best(6, INT32_MAX);
	vector<int>parent(6, -1);
	discorver.push_back(vertex_cost = {start,0});
	best[start] = 0;
	parent[start] = start;

	while (discorver.empty()==false)
	{
		list<pair<int, int>>::iterator bestit;
		int bestCost = INT32_MAX;
		for (auto it = discorver.begin(); it != discorver.end(); ++it)
		{
			const int cost = it->second;
			
			if (cost<bestCost)
			{
				bestCost = cost;
				bestit = it;
			}
		}
		int cost = bestit->second;
		start = bestit->first;
		discorver.erase(bestit);

		if (best[start] < cost)continue;
		

		for (int i=0;i<6;i++)
		{
			if (adjacent[start][i] == -1)continue;
			
			
			int nextCost = best[start] + adjacent[start][i];
			if (nextCost >= best[i])continue;

			best[i] = nextCost;
			parent[i] = start;
			discorver.push_back(vertex_cost = {i,nextCost});
		}
	}

}