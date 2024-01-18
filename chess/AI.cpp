#include "AI.h"


void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}

	for (int i = 0; i < size; i++) {
		vector<int> row2;
		for (int j = 0; j < size; j++) {
			row2.push_back(0);
		}
		second_scoreMap.push_back(row2);
	}
}

void AI::go()
{
	chessPos pos = think();
	chess->chessDown(&pos,flag);
}

void AI::setFlag(CHESS_KIND kind)
{
	flag = kind;
}

void AI::changeChessValue()
{
	chessValue[0][0] = 5;
	chessValue[0][1] = chessValue[0][2] = chessValue[0][3] = 50;
	chessValue[0][4] = chessValue[0][5] = chessValue[0][6] = 500;
	chessValue[0][7] = chessValue[0][8] = chessValue[0][9] = chessValue[0][10] = chessValue[0][11] = chessValue[0][13] = 5000;
	chessValue[0][12] = 100000;

	chessValue[1][0] = 0;
	chessValue[1][1] = chessValue[1][2] = chessValue[1][3] = 20;
	chessValue[1][4] = chessValue[1][5] = chessValue[1][6] = 50;
	chessValue[1][7] = chessValue[1][8] = chessValue[1][9] = chessValue[1][10] = chessValue[1][11] = chessValue[1][13] = 2500;
	chessValue[1][12] = 50000;
}

CHESS_KIND AI::getFlag()
{
	return flag;
}



void AI::calculate()
{
	int size = chess->getGradeSize();
	int personNum = 0;
	int aiNum = 0;
	int emptyNum = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			scoreMap[i][j] = 0;
		}
	}

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessKind(row, col)) continue;
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {
					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					if (x == 0 && y == 0) continue;
					if (x != 1 && y == 0)continue;

					//黑棋下在这里会形成的棋形
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_BLACK) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					//黑棋反方向计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_BLACK) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (personNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if(emptyNum == 2) {
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum >= 4) {
						scoreMap[row][col] += 20000;
					}

					emptyNum = 0;
					//白棋下在这里会形成的棋形
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_WHITE) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					//白棋反方向计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_WHITE) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (aiNum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}



void AI::calculate_plus()
{
	int size = chess->getGradeSize();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			scoreMap[i][j] = 0;
		}
	}

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessKind(row, col)) continue;
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {
					if (x == 0 && y == 0) continue;
					if (x != 1 && y == 0)continue;

					calculate_direction(x, y, row, col);
				}
			}
		}
	}
}

void AI::calculate_direction(int x, int y, int row, int col)
{
	int personNum = 0;
	int aiNum = 0;
	int emptyNum = 0;
	int jumpNum = 0;
	int jumpFlag = 0;

	//正方向计算本方棋子的价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row + i * y;
		int curCol = col + i * x;
		if (chess->posInMap(curRow, curCol) && 
			chess->getChessKind(curRow, curCol) == getFlag()) {
			aiNum++;
		}
		else if (chess->posInMap(curRow, curCol) && 
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			 }
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出地图或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//反方向计算本方棋子价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row - i * y;
		int curCol = col - i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == getFlag()) {
			aiNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出棋盘或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//传值计算分数
	scoreMap[row][col] += calculate_score(personNum, emptyNum, aiNum, jumpNum, 0);

	personNum = 0;
	aiNum = 0;
	emptyNum = 0;
	jumpNum = 0;
	jumpFlag = 0;
	CHESS_KIND K = CHESS_KIND(-int(getFlag()));//人类棋手的棋子类型
	
	//正方向计算敌方棋子的价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row + i * y;
		int curCol = col + i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == K) {
			personNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出棋盘或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//反方向计算敌方棋子价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row - i * y;
		int curCol = col - i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == K) {
			personNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出棋盘或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//传值计算敌方分数
	scoreMap[row][col] += calculate_score(personNum, emptyNum, aiNum, jumpNum, 1);
}

int AI::calculate_score(int personNum, int emptyNum, int aiNum, int jumpNum,int i)
{
	int num = (personNum == 0 ? aiNum : personNum);
	if (num == 0 && emptyNum != 0)//单子
		return AI::chessValue[value_x + i][0];
	else if (num == 1 && emptyNum == 2 && jumpNum == 0)//连二
		return AI::chessValue[value_x + i][1];
	else if (num == 1 && emptyNum == 2 && jumpNum == 1)//跳二
		return AI::chessValue[value_x + i][2];
	else if (num == 1 && emptyNum == 1 && jumpNum == 1)//死二
		return AI::chessValue[value_x + i][3];

	else if (num == 2 && emptyNum == 2 && jumpNum == 0)//活三
		return AI::chessValue[value_x + i][4];
	else if (num == 2 && emptyNum == 2 && jumpNum == 1)//跳三
		return AI::chessValue[value_x + i][5];
	else if (num == 2 && emptyNum == 1)//死三
		return AI::chessValue[value_x + i][6];


	else if (num == 3 && emptyNum == 2 && jumpNum == 0)//活四
		return AI::chessValue[value_x + i][7];
	else if (num == 3 && emptyNum == 2 && jumpNum == 1)//跳四
		return AI::chessValue[value_x + i][8];
	else if (num == 3 && emptyNum == 1 && jumpNum == 0)//死四
		return AI::chessValue[value_x + i][9];
	else if (num == 3 && emptyNum == 1 && jumpNum == 1)//死跳四
		return AI::chessValue[value_x + i][10];
	else if (num == 3 && emptyNum == 0 && jumpNum == 1)//双死跳四
		return AI::chessValue[value_x + i][11];


	else if (num >= 4 && jumpNum == 0)//连五
		return AI::chessValue[value_x + i][12];
	else if (num >= 4 && jumpNum == 1)//跳五
		return AI::chessValue[value_x + i][13];

	return 0;
}

chessPos AI::think()
{
	/*calculate();*/
	calculate_plus();


	//two_step();//新加的


	int maxScore = INT_MIN;
	vector<chessPos> maxGroup;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessKind(row, col) == CHESS_EMPTY) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxGroup.clear();
					maxGroup.push_back(chessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxGroup.push_back(chessPos(row, col));
				}
			}
		}
	}

	int index = rand() % maxGroup.size();
	return maxGroup[index];
}


int AI::calculate_super()
{
	int size = chess->getGradeSize();
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			second_scoreMap[i][j] = 0;
		}
	}

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessKind(row, col)) continue;
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {
					if (x == 0 && y == 0) continue;
					if (x != 1 && y == 0)continue;

					calculate_direction_super(x, y, row, col);
				}
			}
		}
	}

	int maxScore = 0;
	for (int row2 = 0; row2 < size; row2++) {
		for (int col2 = 0; col2 < size; col2++) {
			if (chess->getChessKind(row2, col2) == CHESS_EMPTY) {
				if (second_scoreMap[row2][col2] > maxScore) {
					maxScore = second_scoreMap[row2][col2];
				}
			}
		}
	}

	return maxScore;
}

void AI::calculate_direction_super(int x, int y, int row, int col)
{
	int personNum = 0;
	int aiNum = 0;
	int emptyNum = 0;
	int jumpNum = 0;
	int jumpFlag = 0;

	//正方向计算本方棋子的价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row + i * y;
		int curCol = col + i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == getFlag()) {
			aiNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出地图或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//反方向计算本方棋子价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row - i * y;
		int curCol = col - i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == getFlag()) {
			aiNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出棋盘或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//传值计算分数
	second_scoreMap[row][col] += calculate_score(personNum, emptyNum, aiNum, jumpNum, 0);

	personNum = 0;
	aiNum = 0;
	emptyNum = 0;
	jumpNum = 0;
	jumpFlag = 0;
	CHESS_KIND K = CHESS_KIND(-int(getFlag()));//人类棋手的棋子类型

	//正方向计算敌方棋子的价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row + i * y;
		int curCol = col + i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == K) {
			personNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出棋盘或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//反方向计算敌方棋子价值
	for (int i = 1; i <= 5; i++) {
		int curRow = row - i * y;
		int curCol = col - i * x;
		if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == K) {
			personNum++;
		}
		else if (chess->posInMap(curRow, curCol) &&
			chess->getChessKind(curRow, curCol) == CHESS_EMPTY) {
			if (jumpNum == 0) {
				if (i == 5) {
					emptyNum++;
					break;
				}
				jumpNum++;
				jumpFlag = 1;
				continue;
			}
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
			}
			emptyNum++;
			break;
		}
		else {//跳出棋盘或遇到对手棋
			if (jumpFlag == 1) {
				jumpNum--;
				jumpFlag = 0;
				emptyNum++;
			}
			break;
		}
		jumpFlag = 0;
	}
	//传值计算敌方分数
	second_scoreMap[row][col] += calculate_score(personNum, emptyNum, aiNum, jumpNum, 1);
}

void AI::two_step()
{
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessKind(row, col) == CHESS_EMPTY) {
				chess->chessMap[row][col]= chess->playerFlag ? CHESS_BLACK : CHESS_WHITE;
				//................................................................
				ai_teacher->calculate_plus();//需要修改
				int maxScore = 0;
				chessPos maxPos;
				int size2 = chess->getGradeSize();
				for (int row2 = 0; row2 < size2; row2++) {
					for (int col2 = 0; col2 < size2; col2++) {
						if (chess->getChessKind(row2, col2) == CHESS_EMPTY) {
							if (ai_teacher->scoreMap[row2][col2] > maxScore) {
								maxScore = ai_teacher->scoreMap[row2][col2];
								maxPos = chessPos(row2, col2);
							}
						}
					}
				}

				chess->chessMap[maxPos.x][maxPos.y] = chess->playerFlag ? CHESS_WHITE : CHESS_BLACK;

				if (maxScore > 30000)
					scoreMap[row][col] -= 300000;
				else if (maxScore > 10000)
					scoreMap[row][col] -= 50000;
				else if (maxScore > 180)
					scoreMap[row][col] -= 2500;
				//..................................................................

				scoreMap[row][col] += calculate_super();

				//..................................................................
				chess->chessMap[maxPos.x][maxPos.y] = 0;

				//....................................................................
				chess->chessMap[row][col] = 0;
			}
		}
	}
}


