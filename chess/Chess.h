#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

struct chessPos {
	int x;
	int y;
	chessPos(int row=0,int col=0):x(row),y(col){}
};

typedef enum {
	CHESS_WHITE = -1,
	CHESS_EMPTY = 0,
	CHESS_BLACK = 1,
}CHESS_KIND;

class Chess
{
public:
	IMAGE chessBackImg;
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	void init();
	void chessDown(chessPos* pos, CHESS_KIND kind);
	int getGradeSize();
	bool checkOver();
	CHESS_KIND getChessKind(int x, int y);
	CHESS_KIND getChessKind(chessPos* pos);

	bool clickBoard(int x, int y, chessPos* pos);
	bool posInMap(int x, int y);
	CHESS_KIND humMan_kind;
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	
	IMAGE chessWinImg;
	IMAGE chessDefeatImg;

	int gradeSize;
	int margin_x;
	int margin_y;
	float chessSize;

	
	chessPos lastPos;
private:
	void updateMap(chessPos* pos);
	bool cheerWin();

public:
	vector<vector<int>> chessMap;//原本是private成员
	bool playerFlag;//原本是private成员
};

void putimagePNG(int x, int y, IMAGE* picture);

