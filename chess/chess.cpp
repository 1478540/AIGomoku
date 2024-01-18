#include "Chess.h"
#include<math.h>
#include<conio.h>

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
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
	loadimage(&chessBackImg, "res/����2.jpg", 641, 639, true);
	putimage(0, 0, &chessBackImg);

	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	loadimage(&chessDefeatImg, "res/ʧ��.jpg", 641, 639, true);
	loadimage(&chessWinImg, "res/ʤ��.jpg", 641, 639, true);

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


bool Chess::clickBoard(int x, int y, chessPos* pos)//�����Ż�
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
