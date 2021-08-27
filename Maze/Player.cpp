#include "Player.h"
#include "Player.h"
#include "Board.h"
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	Pos pos = _pos;
	_path.clear();//�ʱ�ȭ
	_path.push_back(pos);//��������
	Pos dest = board->GetExitPos();
	Pos front[4] =
	{
		Pos{-1,0},//up
		Pos{0,-1},//left
		Pos{1,0},//down
		Pos{0,1}//right
	};
	while (pos!=dest)
	{
		int32 newDir= (_dir - 1 + DIR_Count) % DIR_Count;
		//���� �ٶ󺸴� ���⿡�� ���������� �����ִ��� Ȯ��
		if (CanGo(pos+front[newDir]))
		{	
			_dir = newDir;
			pos += front[_dir];
			_path.push_back(pos);
		}
		//����	�ٶ󺸴� ���⿡�� �����Ҽ� �ִ���
		else if(CanGo(pos+front[_dir]))
		{
			pos += front[_dir];
			_path.push_back(pos);
		}
		//�������� ȸ��
		else
		{
			_dir = (_dir + 1) % DIR_Count;
		}
	}
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

bool Player::CanGo(Pos pos)
{
	TileType tiletype = _board->GetTileType(pos);
	return tiletype==TileType::Empty;
}
