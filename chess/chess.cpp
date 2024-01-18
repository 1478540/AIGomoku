#include "Chess.h"
#include<math.h>
#include<conio.h>

void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}


Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = margin_x;
	this->margin_y = margin_y;
	this->chessSize = chessSize;

	playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int i = 0; i < gradeSize; i++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	initgraph(641, 639);
	loadimage(&chessBackImg, "res/棋盘2.jpg", 641, 639, true);
	putimage(0, 0, &chessBackImg);

	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	loadimage(&chessDefeatImg, "res/失败.jpg", 641, 639, true);
	loadimage(&chessWinImg, "res/胜利.jpg", 641, 639, true);

	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}

}

void Chess::chessDown(chessPos* pos, CHESS_KIND kind)
{
	int x = pos->y * chessSize + margin_x - 0.5 * chessSize;
	int y = pos->x * chessSize + margin_y - 0.5 * chessSize;
	if (kind == CHESS_BLACK)
		putimagePNG(x, y, &chessBlackImg);
	if (kind == CHESS_WHITE)
		putimagePNG(x, y, &chessWhiteImg);
	updateMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
}

bool Chess::checkOver()
{
	if (cheerWin()) {
		Sleep(5000);
		if ((playerFlag == true&&humMan_kind==CHESS_WHITE)|| (playerFlag == false && humMan_kind == CHESS_BLACK))
			putimage(0, 0, &chessWinImg);
		else {
			putimage(0, 0, &chessDefeatImg);
			return false;
		}
		_getch();
		return true;
	}
	return false;
}

CHESS_KIND Chess::getChessKind(int x, int y)
{
	return CHESS_KIND(chessMap[x][y]);
}

CHESS_KIND Chess::getChessKind(chessPos* pos)
{
	return CHESS_KIND(chessMap[pos->x][pos->y]);
}


bool Chess::clickBoard(int x, int y, chessPos* pos)//可以优化
{
	bool ret = false;
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + col * chessSize;
	int leftTopPosY = margin_y + row * chessSize;
	int len;
	int offset = chessSize * 0.4;
	int x2, y2;
	do {
		len= sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->x = row;
			pos->y = col;
			if (chessMap[pos->x][pos->y] == 0) {
				ret = true;
			}
			break;
		}

		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->x = row;
			pos->y = col+1;
			if (chessMap[pos->x][pos->y] == 0) {
				ret = true;
			}
			break;
		}

		x2 = leftTopPosX ;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->x = row + 1;
			pos->y = col;
			if (chessMap[pos->x][pos->y] == 0) {
				ret = true;
			}
			break;
		}

		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->x = row + 1;
			pos->y = col + 1;
			if (chessMap[pos->x][pos->y] == 0) {
				ret = true;
			}
			break;
		}

	} while (0);

	return ret;
}

bool Chess::posInMap(int x, int y)
{
	if (x < 0 || x >= gradeSize || y < 0 || y >= gradeSize)
		return false;
	else
		return true;
}

void Chess::updateMap(chessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->x][pos->y] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;
}

bool Chess::cheerWin()
{
	int row;
	int col;
	int kind = chessMap[lastPos.x][lastPos.y];
	int num;

	for (int i = 0; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			if (i == 0 && j != 1)continue;
			row = lastPos.x;
			col = lastPos.y;
			num = 1;

			for (int k = 1; k <= 4; k++) {
				if (row + k * i < 0 || row + k * i >= gradeSize || col + k * j < 0 || col + k * j >= gradeSize) break;
				if (chessMap[row + k * i][col + k * j] == kind) {
					num++;
				}
				else {
					break;
				}
			}
			for (int k = 1; k <= 4; k++) {
				if (row - k * i < 0 || row - k * i >= gradeSize || col - k * j < 0 || col - k * j >= gradeSize) break;
				if (chessMap[row - k * i][col - k * j] == kind) {
					num++;
				}
				else {
					break;
				}
			}
			if (num >= 5)
				return true;
		}
	}
	return false;
}
