#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "food.h"

extern food _all[NUM_OF_FOODS];
extern selected_food _selected[NUM_OF_FOODS];
extern unsigned int tos;
enum mode { ALL, SELECTED };

/*prototype function declaration*/
extern void print_selected(const unsigned int*);
static enum bool is_exist(const unsigned int);
static int search_index(const unsigned int seq, enum mode m);

/*���� ���õ� ������ �����ϴ� �迭�� ���ڷ� �ѱ� ������ �����ϴ� Ȯ���ϴ� �Լ�*/
enum bool is_exist(const unsigned int seq)
{
	for (int i = 0; i < tos; i++)
	{
		/*�̹� ���õ� �����̸�*/
		if (_selected[i].data->seq == seq)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/*������ ������ �ε����� ã�� �Լ�*/
int search_index(const unsigned int seq, enum mode m)
{
	if (m == ALL) /* _all���� Ž�� */
	{
		for (int i = 0; i < NUM_OF_FOODS; i++)
		{
			if (_all[i].seq == seq)
			{
				return i; /*return index*/
			}
		}
		fprintf(stderr, "Error: can't search index (mode: ALL)\n");
	}
	else if (m == SELECTED) /* _selected���� Ž��*/
	{
		for (int i = 0; i < tos; i++)
		{
			if (_selected[i].data->seq == seq)
			{
				return i;
			}
		}
		fprintf(stderr, "Error: can't search index (mode: SELECTED)\n");
	}
	else /*��ȿ���� ���� ���*/
	{
		fprintf(stderr, "Error: invalid mode\n");
	}
	return -1;
}

/*����ڿ��� ������ �Է¹޴� �Լ�*/
void get_option(unsigned int* opt)
{
	do
	{
		printf("��ȣ ������ Enter: ");
		scanf("%u", opt);
	} while (*opt < 1 || *opt > 3); /*1 �̸��̰ų� 3 �ʰ��� �ݺ��Ѵ�.*/

	return;
}

/*�߰��� ó���ϴ� �Լ�*/
void add_handler(unsigned int* sum)
{
	unsigned int seq = 0, selected_num = 0;
	int i_all = -1, i_selected = -1; /*_all �迭�� index�� _selected �迭�� index*/
	do
	{
		printf("�޴���ȣ �Է� �� Enter: ");
		scanf("%u", &seq);
	} while (search_index(seq, ALL) == -1); /*�޴��� �������� �ʴ� ��ȣ�� �Է��ϸ�, ���Է� �޴´�.*/
	printf("���� �Է� �� Enter: ");
	scanf("%u", &selected_num);
	/*get _all's index*/
	i_all = search_index(seq, ALL);

	if (!is_exist(seq)) /*���� ���õ����� ���� �����̸�*/
	{
		/*push new data*/
		_selected[tos].data = &(_all[i_all]);
		_selected[tos].selected_num = selected_num;
		tos++;
	}
	else /*�̹� ���õ� ���� �ִ� �����̶��*/
	{
		/*get _selected's index*/
		i_selected = search_index(seq, SELECTED);
		/*�߰��� ��ŭ ���õ� ���� ����*/
		_selected[i_selected].selected_num += selected_num;
	}
	/*������ �Ѿ׿� �߰�*/

	*sum += ((_all[i_all].price) * selected_num);
	system("cls");
	return;
}

/*��Ҹ� ó���ϴ� �Լ�*/
void cancel_handler(unsigned int* sum)
{
	unsigned int seq = 0;
	system("cls");
	print_selected(&tos);
	do
	{
		printf("����� �޴� ��ư�� �Է� �� Enter(0�� �Է��ϸ� ����): ");
		scanf("%u", &seq);
	} while (search_index(seq, SELECTED) == -1); /*��ȿ���� ���� ��ȣ�� �Է��� ��, ���Է� �޴´�.*/

	if (is_exist(seq))
	{
		selected_food* target = &(_selected[search_index(seq, SELECTED)]);
		*sum -= target->data->price * target->selected_num;
		target->selected_num = 0;
	}
	return;
}

/*���� �ɼ��� ó���ϴ� �Լ�*/
void quit_handler(unsigned int* sum) // compatible type: const ��뿩�� Ȯ��
{
	unsigned int pay = 0;
	printf("���� ������ �Ѿ��� %u�� �Դϴ�.\n", *sum);
	printf("�����κ��� ���� �ݾ��� �Է� �� Enter: ");
	scanf("%u", &pay);

	system("cls");

	printf("<��ǥ>\n");
	print_selected(&tos);
	printf("�ݾ�: %u\n", *sum);
	printf("�ܵ�: %d\n", pay - (*sum));
	exit(0);
}