// GreedySnake.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "func.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

node *head = NULL, *tail;
COORD showScore;
COORD food;
int score = 0;
int speed = 100;	//游戏速度

int main()
{
	cout << " score: " << score << endl;
	showScore.X = 8;
	showScore.Y = 0;

	int dire = LEFT;	//前行方向
	
	showDomain();
	generateFood(food, head);
	initSnake(head,tail);
	showSnake(head);
	
	while (true)
	{
		Sleep(speed);
		while (!_kbhit())
		{//没有输入，继续按原方向继续前行
			Sleep(speed);
			mymove(dire,head,tail);
			if (outOfDomain(head))
			{
				system("cls");					//清除屏幕 
				cout << "end" << endl;
				return 0;
			}
			if (findFood(food,head,score,speed))
			{//吃到食物
				becomeLonger(dire,tail);
				//更新分数显示
				gotoxy(showScore);
				cout << score;
				generateFood(food,head);
			}
			showSnake(head);
		}
		int input = getInput();
		getDire(dire, input);

	}
	
	getchar();
	return 0;
}
