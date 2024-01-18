#include<iostream>
#include"GameControl.h"
using namespace std;

int main() {
	Man man;
	Chess chess(13, 31, 31, 48.07);//È«²¿³ıÓÚ1.4±¶
	AI ai;
	/*ai.changeChessValue();*/

	AI ai2;
	ai2.init(&chess);
	ai.ai_teacher = &ai2;

	GameControl game(&man, &chess, &ai);
	game.play();
	return 0;
}