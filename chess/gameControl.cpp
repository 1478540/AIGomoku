#include "GameControl.h"
#include"Chess.h"

GameControl::GameControl(Man* man, Chess* chess, AI* ai)
{
	this->ai = ai;
	this->chess = chess;
	this->man = man;

	man->init(chess);
	ai->init(chess);
}

void GameControl::play()
{
	chess->init();
	CHESS_KIND kind;
	kind = gameStart();
	chess->humMan_kind = kind;
	man->setFlag(kind);
	ai->setFlag(CHESS_KIND(-int(kind)));
	ai->ai_teacher->setFlag(kind);

	if (ai->getFlag() == CHESS_BLACK) {
		ai->value_x = 0;
		ai->ai_teacher->value_x = 2;
	}
	else {
		ai->value_x = 2;
		ai->ai_teacher->value_x = 0;
	}
		

	int flag = 1;
	while (1) {
		if (flag == 1 && ai->getFlag()==CHESS_BLACK ){
			chessPos pos(6, 6);
			chess->chessDown(&pos, CHESS_BLACK);
		}
		if (flag == 1) flag = 0;

		man->go();
		if (chess->checkOver()) {
			break;
		}

		ai->go();
		if (chess->checkOver()) {
			break;
		}
	}
}

CHESS_KIND GameControl::gameStart()
{
	IMAGE choose_black;
	IMAGE choose_white;
	loadimage(&choose_black, "res/black2.png", 250, 250, true);
	loadimage(&choose_white, "res/white2.png", 250, 250, true);
	putimagePNG(50, 200, &choose_black);
	putimagePNG(350, 200, &choose_white);
	MOUSEMSG msg;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x > 50 && msg.x < 300 && msg.y>200 && msg.y < 450) {
				putimage(0, 0, &chess->chessBackImg);
				return CHESS_BLACK;
			}
			if (msg.x > 350 && msg.x < 600 && msg.y>200 && msg.y < 450) {
				putimage(0, 0, &chess->chessBackImg);
				return CHESS_WHITE;
			}
		}
	}
}
