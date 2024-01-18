#include "Man.h"
#include<iostream>
using namespace std;

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	chessPos pos;
	
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x,msg.y,&pos)) {
			break;
		}
	}
	chess->chessDown(&pos, flag);
}

void Man::setFlag(CHESS_KIND kind)
{
	flag = kind;
}
