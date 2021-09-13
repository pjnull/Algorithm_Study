#include "Player.h"
#include "Player.h"
#include "Board.h"
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	//RightHand();
	//BFS();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())return;
	_sumTick += deltaTick;
	if (_sumTick >= 100)
	{
		_sumTick = 0;
		_pos = _path[_pathIndex];
		_pathIndex++;
	}

}

void Player::RightHand()
{
	Pos pos = _pos;
	_path.clear();//초기화
	_path.push_back(pos);//시작지점
	Pos dest = _board->GetExitPos();
	Pos front[4] =
	{
		Pos{-1,0},//up
		Pos{0,-1},//left
		Pos{1,0},//down
		Pos{0,1}//right
	};
	while (pos != dest)
	{
		int32 newDir = (_dir - 1 + DIR_Count) % DIR_Count;
		//현재 바라보는 방향에서 오른쪽으로 갈수있는지 확인
		if (CanGo(pos + front[newDir]))
		{
			_dir = newDir;
			pos += front[_dir];
			_path.push_back(pos);
		}
		//현재	바라보는 방향에서 전진할수 있는지
		else if (CanGo(pos + front[_dir]))
		{
			pos += front[_dir];
			_path.push_back(pos);
		}
		//왼쪽으로 회전
		else
		{
			_dir = (_dir + 1) % DIR_Count;
		}
	}
	stack<Pos>s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])s.pop();
		else  s.push(_path[i]);
	}
	if (_path.empty() == false)s.push(_path.back());

	vector<Pos>path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}
	reverse(path.begin(), path.end());
	_path = path;
}

void Player::BFS()
{
	Pos pos = _pos;
	_path.clear();//초기화
	_path.push_back(pos);//시작지점
	Pos dest = _board->GetExitPos();
	Pos front[4] =
	{
		Pos{-1,0},//up
		Pos{0,-1},//left
		Pos{1,0},//down
		Pos{0,1}//right
	};
	const int32 size=_board->GetSize();
	vector<vector<bool>>discover(size,vector<bool>(size,false));
	map<Pos, Pos>parent;
	
	parent[pos] = pos;

	queue<Pos>q;
	q.push(pos);
	discover[pos.y][pos.x] = true;
	
	while (q.empty()==false)
	{
		pos = q.front();
		q.pop();
		if (pos == dest)break;
		for (int32 i = 0; i < 4; i++)
		{
			Pos nextpos = pos + front[i];
			if (CanGo(nextpos) == false)continue;
			if (discover[nextpos.y][nextpos.x])continue;
			q.push(nextpos);
			discover[nextpos.y][nextpos.x] = true;
			parent[nextpos] = pos;
		}
	}
	_path.clear();
	pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos])break;
		pos = parent[pos];
	}
	std::reverse(_path.begin(),_path.end());
	//_path.push_back(pos);
}

struct  PQ
{
	bool operator<(const PQ& other)const { return f < other.f; }
	bool operator>(const PQ& other)const { return f > other.f; }
	int32 f;
	int32 g;
	Pos pos;
};

void Player::AStar()
{
	//	F=G+H ==> 적을수록 좋음
	//F(최종점수)
	//G(시작점에서 해당 좌표까지 이동하는데 드는 비용)
	//H(목적지에서 얼마나 가까운지 )
	
	Pos start = _pos;
	Pos dest = _board->GetExitPos();
	Pos front[] =
	{
		Pos{-1,0},//up
		Pos{0,-1},//left
		Pos{1,0},//down
		Pos{0,1},//right
		Pos{-1,-1},//U_L
		Pos{1,-1},//D_L
		Pos{-1,1},//U_R
		Pos{1,1},//D_R
	};

	int32 cost[] =
	{
		10,//up
		10,//left
		10,//down
		10,//right
		14,
		14,
		14,
		14
	};
	const int32 size = _board->GetSize();

	vector<vector<bool>>closed(size, vector<bool>(size, false));
	//closeList
	vector<vector<int32>>best(size, vector<int32>(size, INT32_MAX));
	map<Pos, Pos>parent;
	priority_queue<PQ, vector<PQ>, greater<PQ>>pq;//openList

	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQ{ g + h,g,start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}
	while(pq.empty() == false)
	{
		PQ node = pq.top();
		pq.pop();
		if (closed[node.pos.y][node.pos.x])continue;
		
		closed[node.pos.y][node.pos.x] = true;

		if (node.pos == dest)break;
		
		for (int32 dir = 0; dir < DIR_Count; dir++)
		{
			Pos nextPos = node.pos + front[dir];

			if (CanGo(nextPos) == false)continue;//갈 수 있는 지역인지
			
			if (closed[nextPos.y][nextPos.x])continue;//이미 방문한 지역인지
			
			//비용계산 
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			
			if (best[nextPos.y][nextPos.x] <= g + h)continue;//더 빠른 길을 발견할경우 

			//예약
			pq.push(PQ{ g + h,g,nextPos });
			best[nextPos.y][nextPos.x] = g + h;
			parent[nextPos]=node.pos;
		}
	}
	_path.clear();
	_pathIndex = 0;
	Pos pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos])break;
		pos = parent[pos];
	}
	std::reverse(_path.begin(), _path.end());
}

bool Player::CanGo(Pos pos)
{
	TileType tiletype = _board->GetTileType(pos);
	return tiletype==TileType::Empty;
}
