#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "food.h"

/*�޴��� �����ϴ� ������ �����ϴ� ���̺�(�迭)*/
food _all[NUM_OF_FOODS] =
{
	{10, "ġ����ż�Ʈ", 3000},
	{11, "�������ż�Ʈ", 4500},
	{12, "ġŲ��Ʈ", 10000},

	{20, "ġ�����", 1600},
	{21, "��������", 2900},
	{22, "�ܹ���", 1200},

	{30, "���̽�ũ��", 1200},
	{31, "��������", 1800},
	{32, "����", 2000},

	{40, "�ݶ�", 1000},
	{41, "Ŀ��", 1100},
	{42, "��ũ����ũ", 1500}
};

/*���� ���õ� ������ �����ϴ� �迭*/
selected_food _selected[NUM_OF_FOODS];

/*top of _selected*/
unsigned int tos; /*���Ī ���*/

/*function prototype declaration*/
extern void print_all(const unsigned int*);
extern void print_selected(const unsigned int*);
extern void print_option(void);

extern void add_handler(unsigned int*);
extern void cancel_handler(unsigned int*);
extern void quit_handler(unsigned int*);

extern void get_option(unsigned int*);

/*array of pointer to function(unsigned int*) returning void*/
void (*call_handler[3])(unsigned int*) = { add_handler, cancel_handler, quit_handler };

int main(void)
{
	/*������ �ɼ� ��ȣ*/
	unsigned int opt = 0;
	/*������ �Ѿ�*/
	unsigned int sum = 0;

	while (1)
	{
		print_all(&sum);
		print_option();
		get_option(&opt);
		call_handler[opt - 1](&sum);
	}

	return 0;
}