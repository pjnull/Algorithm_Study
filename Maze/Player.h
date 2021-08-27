#pragma once
#include "pch.h"
class Board;

class Player
{
public:
	void Init(Board* board);
	void Update(uint64 deltaTick);
	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos(){ return _pos; }
private:
	Pos _pos = {};
	int _dir = DIR_Up;
	Board* _board = nullptr;
	bool CanGo(Pos pos);
	vector<Pos> _path;
	uint64 _sumTick = 0;
	uint32 _pathIndex = 0;
};

