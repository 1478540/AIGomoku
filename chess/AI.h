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
	{5,17,10,6,170,60,40,10000,200,200,195,195,30000,600},//����
	{0,15,10,6,150,55,35,1000,195,195,190,190,20000,600},//�˰�
	{5,15,10,6,150,55,35,10000,195,195,190,190,30000,600},//����
	{0,17,10,6,170,60,40,1000,200,200,195,195,20000,600}//�˺�
	};//����0 ����1 ����2 ����3 ����4 ����5 ����6 ����7 ����8 ����9 ������10 ˫������11 ����12 ����13

	AI* ai_teacher;
private:
	int calculate_super();
	void calculate_direction_super(int x, int y, int row, int col);
	void two_step();
	
};

