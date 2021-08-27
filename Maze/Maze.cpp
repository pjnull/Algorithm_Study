// Maze.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"
#include <time.h>
#include "Player.h"
Player player;
Board board;
int main()
{
	::srand (static_cast<unsigned int>(time(nullptr)));
	board.Init(25,&player);
	player.Init(&board);
	uint64 lasttick = 0;
	while (true)
	{
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lasttick;
		lasttick = currentTick;


		player.Update(deltaTick);

		board.Render();
	}
}
