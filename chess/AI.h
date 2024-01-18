#pragma once
#include"Chess.h"
#include"vector"
using namespace std;

class AI
{
public:
	void init(Chess* chess);
	void go();
	void setFlag(CHESS_KIND kind);
	void changeChessValue();
	CHESS_KIND getFlag();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;
	vector<vector<int>> second_scoreMap;
	CHESS_KIND flag;
private:
	void calculate();
	void calculate_plus();
	void calculate_direction(int x, int y, int row, int col);
	int calculate_score(int personNum, int emptyNum, int aiNum, int jumpNum, int i);
	chessPos think();
	


public:
	int value_x;
	int chessValue[4][14] = {
	{5,17,10,6,170,60,40,10000,200,200,195,195,30000,600},//机黑
	{0,15,10,6,150,55,35,1000,195,195,190,190,20000,600},//人白
	{5,15,10,6,150,55,35,10000,195,195,190,190,30000,600},//机白
	{0,17,10,6,170,60,40,1000,200,200,195,195,20000,600}//人黑
	};//单子0 连二1 跳二2 死二3 活三4 跳三5 死三6 活四7 跳四8 死四9 死跳四10 双死跳四11 连五12 跳五13

	AI* ai_teacher;
private:
	int calculate_super();
	void calculate_direction_super(int x, int y, int row, int col);
	void two_step();
	
};

