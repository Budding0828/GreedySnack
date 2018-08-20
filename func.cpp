
#include "stdafx.h"
#include "func.h"
#include <iostream>
#include <string>
using namespace std;

//��ӡ�߿�
void showDomain()
{
	//��ӡ�߿�
	cout << "+";	//���Ͻ�
	for (int i = 1; i <= WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+";	//���Ͻ�
	cout << endl;
	for (int i = 1; i <= HIGHT; i++)
	{
		cout << "!" << endl;
	}
	cout << "+";	//���½�
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

//��ʼ����
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

//�ƶ����
void gotoxy(const COORD pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//��ü�������ķ�λ�������ض�Ӧ��ֵ
//���Ƿ����������-1
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
				//cout << "��" << endl;
				return ch;
				break;
			case DOWN:
				//cout << "��" << endl;
				return ch;
				break;
			case LEFT:
				//cout << "��" << endl;
				return ch;
				break;
			case RIGHT:
				//cout << "��" << endl;
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

//�ƶ�����
void mymove(int dire, node* &head, node* &tail)
{
	//β���ȿհ�
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

//��ӡ��
//��������ƶ�����ͷλ��
void showSnake(node* &head)
{
	node* point = head->next;
	gotoxy(head->pos);
	cout << "#";	//��ӡ��ͷ
	while (point)
	{
		gotoxy(point->pos);
		cout << "*";
		point = point->next;
	}

	gotoxy(head->pos);
}

//�䳤
void becomeLonger(int dire, node* &tail)
{
	node* p = new node();
	p->next = NULL;
	tail->next = p;
	tail = p;
}

//�ж�λ��
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

//����ʳ��
void generateFood(COORD& food, node* &head)
{
	while (true)
	{
		srand((unsigned)time(NULL));
		int food_x = (rand() % (WIDTH)) + 2;
		int food_y = (rand() % (HIGHT)) + 2;
		//����������غ�
		node* point = head;
		while (point)
		{
			if ((point->pos.X == food_x) && (point->pos.Y == food_y))
				break;
			point = point->next;
		}
		if (point == NULL)
		{
			//�ұ������ߣ�û�з����غ�
			food.X = food_x;
			food.Y = food_y;
			gotoxy(food);
			cout << 'o';
			return;
		}
	}

}

//�ж��Ƿ�Ե�ʳ��
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

//�ж��Ƿ�ײ���߽�
bool outOfDomain(node* &head)
{
	if (head->pos.X == WIDTH || head->pos.X == 0)	return true;
	if (head->pos.Y == HIGHT + 2 || head->pos.Y == 0)	return true;
	return false;
}
