#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "food.h"

extern food _all[NUM_OF_FOODS];
extern selected_food _selected[NUM_OF_FOODS];

static char* categories[NUM_OF_CATEGORIES] =
{
	"��Ʈ�޴�",
	"���Ÿ޴�",
	"����Ʈ�޴�",
	"����޴�"
};

/*�ɼǵ��� ����ϴ� �Լ�*/
void print_option(void)
{
	printf("1. �߰�\t2. ���\t3. �Է�����\n");
	return;
}

/*�޴��� �����ϴ� ��� ������ ����ϴ� �Լ�*/
void print_all(const unsigned int* sum)
{
	int i = 0;
	system("cls");
	for (i; i < NUM_OF_FOODS; i++)
	{
		/*Ư�� ī�װ����� ù �����̶��*/
		if (_all[i].seq % 10 == 0)
		{
			/*ī�װ��� ���� ����Ѵ�.*/
			printf("------------------------\n");
			printf("%s\n", categories[(_all[i].seq / 10) - 1]);;
		}

		/*���� ������ ����Ѵ�.*/
		printf("%2u %15s %u\n", _all[i].seq, _all[i].name, _all[i].price);
	}
	printf("------------------------\n");
	printf("������ �Ѿ�:\t%u\n", *sum);

	return;
}

/*������� ���õ� ���ĵ��� ����ϴ� �Լ�*/
void print_selected(const unsigned int* tos)
{
	int i = 0;
	printf("------------------------\n");
	printf("������ �޴�\n");

	for (i; i < *tos; i++)
	{
		if (_selected[i].selected_num == 0) /*�̹� ������ �������� ��� ������� �ʴ´�.*/
		{
			continue;
		}

		printf("%u %15s * %2u = %u\n",
			_selected[i].data->seq,
			_selected[i].data->name,
			_selected[i].selected_num,
			_selected[i].data->price * _selected[i].selected_num);
	}

	printf("------------------------\n");
	return;
}