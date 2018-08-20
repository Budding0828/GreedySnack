
#include "stdafx.h"
#include "func.h"
#include <iostream>
#include <string>
using namespace std;

//打印边框
void showDomain()
{
	//打印边框
	cout << "+";	//左上角
	for (int i = 1; i <= WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+";	//右上角
	cout << endl;
	for (int i = 1; i <= HIGHT; i++)
	{
		cout << "!" << endl;
	}
	cout << "+";	//左下角
	for (int i = 1; i <= WIDTH; i++)
	{
		cout << "-";
	}

	COORD temp;
	temp.X = 101;
	temp.Y = 2;
	gotoxy(temp);

	for (int i = 1; i <= HIGHT; i++)
	{
		cout << "!" << endl;
		temp.Y++;
		gotoxy(temp);
	}
	cout << "+";
}

//初始化蛇
void initSnake(node* &head, node* &tail)
{
	node* p;
	int n = 3;
	head = new node;
	tail = head;
	head->pos.X = WIDTH / 2;
	head->pos.Y = HIGHT / 2;
	while (n--)
	{
		p = new node;
		tail->next = p;
		p->pos.X = tail->pos.X - 1;
		p->pos.Y = tail->pos.Y;
		tail = p;
	}
	tail->next = NULL;

}

//移动光标
void gotoxy(const COORD pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//获得键盘输入的方位键，返回对应的值
//若非方向键，返回-1
int getInput()
{
	char ch;
	while (true)
	{
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				//cout << "上" << endl;
				return ch;
				break;
			case DOWN:
				//cout << "下" << endl;
				return ch;
				break;
			case LEFT:
				//cout << "左" << endl;
				return ch;
				break;
			case RIGHT:
				//cout << "右" << endl;
				return ch;
				break;
			default:
				return -1;
				break;
			}
		}
		else return -1;
	}
}

//移动函数
void mymove(int dire, node* &head, node* &tail)
{
	//尾巴先空白
	gotoxy(tail->pos);
	cout << " ";
	COORD pre = head->pos;
	COORD cur;
	node* point = head->next;
	while (point)
	{
		cur = point->pos;
		point->pos = pre;
		pre = cur;
		point = point->next;
	}

	switch (dire)
	{
	case UP:
		head->pos.Y--;
		break;
	case DOWN:
		head->pos.Y++;
		break;
	case LEFT:
		head->pos.X--;
		break;
	case RIGHT:
		head->pos.X++;
		break;
	default:
		break;
	}

}

//打印蛇
//并将光标移动到蛇头位置
void showSnake(node* &head)
{
	node* point = head->next;
	gotoxy(head->pos);
	cout << "#";	//打印蛇头
	while (point)
	{
		gotoxy(point->pos);
		cout << "*";
		point = point->next;
	}

	gotoxy(head->pos);
}

//变长
void becomeLonger(int dire, node* &tail)
{
	node* p = new node();
	p->next = NULL;
	tail->next = p;
	tail = p;
}

//判断位置
void getDire(int& dire, int input)
{
	if (input == -1)	return;
	switch (dire)
	{
	case UP:
		if (input == LEFT)	dire = LEFT;
		else if (input == RIGHT)	dire = RIGHT;
		break;
	case DOWN:
		if (input == LEFT)	dire = LEFT;
		else if (input == RIGHT)	dire = RIGHT;
		break;
	case LEFT:
		if (input == UP)	dire = UP;
		else if (input == DOWN)	dire = DOWN;
		break;
	case RIGHT:
		if (input == UP)	dire = UP;
		else if (input == DOWN)	dire = DOWN;
		break;
	default:
		break;
	}

}

//产生食物
void generateFood(COORD& food, node* &head)
{
	while (true)
	{
		srand((unsigned)time(NULL));
		int food_x = (rand() % (WIDTH)) + 2;
		int food_y = (rand() % (HIGHT)) + 2;
		//避免和蛇身重合
		node* point = head;
		while (point)
		{
			if ((point->pos.X == food_x) && (point->pos.Y == food_y))
				break;
			point = point->next;
		}
		if (point == NULL)
		{
			//找遍整条蛇，没有发现重合
			food.X = food_x;
			food.Y = food_y;
			gotoxy(food);
			cout << 'o';
			return;
		}
	}

}

//判断是否吃到食物
bool findFood(const COORD& food, node* &head, int& score, int& speed)
{
	if ((head->pos.X == food.X) && (head->pos.Y == food.Y))
	{
		score++;
		if (score % 10 == 0)	speed -= 10;
		return true;
	}
	return false;
}

//判断是否撞到边界
bool outOfDomain(node* &head)
{
	if (head->pos.X == WIDTH || head->pos.X == 0)	return true;
	if (head->pos.Y == HIGHT + 2 || head->pos.Y == 0)	return true;
	return false;
}
