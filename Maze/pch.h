#pragma once

#include<Windows.h>
#include<iostream>
#include<vector>
#include <stack>
#include"Type.h"
#include <map>
#include <queue>
using namespace std;

struct Pos
{
	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}
	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}
	bool operator<(const Pos& other)const
	{
		if (y != other.y)return y < other.y;
		if (x!= other.x)return x < other.x;

	}
	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}
	Pos operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}
	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_Up=0,
	DIR_Left=1,
	DIR_Down=2,
	DIR_Right=3,

	DIR_Count=4,
};

