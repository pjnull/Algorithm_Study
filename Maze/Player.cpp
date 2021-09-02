#include "Player.h"
#include "Player.h"
#include "Board.h"
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	//RightHand();
	BFS();

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

bool Player::CanGo(Pos pos)
{
	TileType tiletype = _board->GetTileType(pos);
	return tiletype==TileType::Empty;
}
