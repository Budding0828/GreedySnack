#pragma once
#ifndef FUNC_H_
#define FUNC_H_

#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>

#define WIDTH 100	//设置界面范围
#define HIGHT 30
#define UP 72	//上下左右键
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//蛇身结点 
struct node 							
{
	COORD pos;
	node *next;
};

//打印边框
void showDomain();

//初始化蛇
void initSnake(node* &head, node* &tail);

//移动光标
void gotoxy(const COORD pos);


//获得键盘输入的方位键，返回对应的值
//若非方向键，返回-1
int getInput();

//移动函数
void mymove(int dire, node* &head, node* &tail);

//打印蛇
//并将光标移动到蛇头位置
void showSnake(node* &head);

//变长
void becomeLonger(int dire, node* &tail);

//判断位置
void getDire(int& dire, int input);

//产生食物
void generateFood(COORD& food, node* &head);

//判断是否吃到食物
bool findFood(const COORD& food, node* &head, int& score, int& speed);

//判断是否撞到边界
bool outOfDomain(node* &head);


#endif // !FUNC_H_
