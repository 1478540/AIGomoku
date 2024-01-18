#pragma once
#include"Chess.h"

class Man
{
public:
	void init(Chess* chess);
	void go();
	void setFlag(CHESS_KIND kind);
private:
	Chess* chess;
	CHESS_KIND flag;
};

