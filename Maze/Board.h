#pragma once
#include "pch.h"
#include "ConsoleHelper.h"
class Player;
enum
{
	Board_Max_Size = 100,

};

enum class TileType
{
	None=0,
	Empty,
	Wall,
};
class Board
{
public:

	Board();
	~Board();
	void Init(__int32 size,Player* player);
	void Render();
	void GenerateMap();
	TileType GetTileType(Pos pos);
	ConsoleColor GetTileColor(Pos pos);
	Pos GetEnterPos() { return Pos{ 1,1 }; };
	Pos GetExitPos() { return Pos{ _size - 2,_size - 2 }; };
private:
	
	TileType	 _tile[Board_Max_Size][Board_Max_Size];
	int32		 _size= 0;
	Player*		_player=nullptr;
};

