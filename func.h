#pragma once
#ifndef FUNC_H_
#define FUNC_H_

#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>

#define WIDTH 100	//���ý��淶Χ
#define HIGHT 30
#define UP 72	//�������Ҽ�
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//������ 
struct node 							
{
	COORD pos;
	node *next;
};

//��ӡ�߿�
void showDomain();

//��ʼ����
void initSnake(node* &head, node* &tail);

//�ƶ����
void gotoxy(const COORD pos);


//��ü�������ķ�λ�������ض�Ӧ��ֵ
//���Ƿ����������-1
int getInput();

//�ƶ�����
void mymove(int dire, node* &head, node* &tail);

//��ӡ��
//��������ƶ�����ͷλ��
void showSnake(node* &head);

//�䳤
void becomeLonger(int dire, node* &tail);

//�ж�λ��
void getDire(int& dire, int input);

//����ʳ��
void generateFood(COORD& food, node* &head);

//�ж��Ƿ�Ե�ʳ��
bool findFood(const COORD& food, node* &head, int& score, int& speed);

//�ж��Ƿ�ײ���߽�
bool outOfDomain(node* &head);


#endif // !FUNC_H_
