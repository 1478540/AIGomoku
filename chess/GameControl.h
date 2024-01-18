#pragma once
#include"AI.h"
#include"Chess.h"
#include"Man.h"

class GameControl
{
public:
	GameControl(Man* man, Chess* chess, AI* ai);
	void play();
	
private:
	Man* man;
	Chess* chess;
	AI* ai;

private:
	CHESS_KIND gameStart();
	
};

