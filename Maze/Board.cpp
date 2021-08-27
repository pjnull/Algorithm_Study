#include "Board.h"
#include "ConsoleHelper.h"
#include <iostream>
#include "Player.h"
using namespace std;

const char* Tile = "бс";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(__int32 size, Player* player)
{
	_size = size;
	_player = player;
	GenerateMap();
}


void Board::Render()
{

	ConsoleHelper::ShowConsoleCursor(false);
	ConsoleHelper::SetCursorPosition(0, 0);

	
	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{
			ConsoleColor color = GetTileColor(Pos{ y,x });
			ConsoleHelper::SetCursorColor(color);
			cout << Tile;
		}
		cout << endl;
	}
}

void Board::GenerateMap()
{
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x%2==0 || y %2==0)
				_tile[y][x] = TileType::Wall;
			else
				_tile[y][x] = TileType::Empty;
			

		}

		cout << endl;
	}
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (y == _size - 2 && x == _size - 2)continue;
			if (x % 2 == 0 || y % 2 == 0)continue;
			if (y == _size - 2)
			{
				_tile[y][x + 1] = TileType::Empty;
				continue;
			}
			if (x == _size - 2)
			{
				_tile[y+1][x] = TileType::Empty;
				continue;
			}
			const int32 randval=::rand() % 2;
			if (randval % 2 == 0)_tile[y][x + 1] = TileType::Empty;
			else _tile[y+1][x] = TileType::Empty;
		}
	}
}

TileType Board::GetTileType(Pos pos)
{
	if(pos.x<0||pos.x>=_size)
		return TileType::None;
	if (pos.y < 0 || pos.y >=_size)
		return TileType::None;
	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (_player != nullptr && _player->GetPos() == pos)return ConsoleColor::YELLOW;
	if (GetExitPos() == pos)return ConsoleColor::BLUE;
	TileType tiletype = GetTileType(pos);
	switch(tiletype)
	{
		case TileType::Empty:
			return ConsoleColor::GREEN;
		case TileType::Wall:
			return ConsoleColor::RED;
	}
	return ConsoleColor::WHITE;
}
