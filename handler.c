#define _CRT_SECURE_NO_WARNINGS

/*�Է� ���۸� ����.*/
#define FFLUSH_STDIN while(getchar() != '\n'){} 
#define INPUT_BUFFER_SIZE 50

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "food.h"

extern food _all[NUM_OF_FOODS];
extern selected_food _selected[NUM_OF_FOODS];
extern unsigned int tos;

/*prototype function declaration*/
extern void print_selected(const unsigned int*);
extern unsigned int ctoi(const char);
extern enum bool is_digit_string(const char*);
extern enum bool is_exist(const unsigned int);
extern int search_index(const unsigned int seq, enum mode m);

/*����ڿ��� �ɼ��� �Է¹޴� �Լ�*/
void get_option(unsigned int* opt)
{
	
	char tmp[INPUT_BUFFER_SIZE];

	while(1)
	{
		printf("��ȣ ������ Enter: ");
		scanf("%s", tmp); 

		/* 
		* ���ڰų�; 1 �̸��̰ų� 3 �ʰ��� �ݺ��Ѵ�.
		* short circuit�� �̿��� ���� ó��
		* �����϶��� atoi(tmp)�� �򰡵ȴ�.
		*/
		if (is_digit_string(tmp) && (atoi(tmp) >= 1 && atoi(tmp) <= 3)) 
			break;

		FFLUSH_STDIN
	} 

	*opt = atoi(tmp);

	return;
}

/*�߰��� ó���ϴ� �Լ�*/
void add_handler(unsigned int* sum)
{
	unsigned int seq = 0, selected_num = 0;
	int i_all = -1, i_selected = -1; /*_all �迭�� index�� _selected �迭�� index*/

	char tmp[INPUT_BUFFER_SIZE];

	/*�޴� ��ȣ�� �Է¹޴´�.*/
	while (1)
	{
		printf("�޴���ȣ �Է� �� Enter: ");
		scanf("%s", tmp);

		/*���ڰų�, _ALL�迭�� ������ ��쿡�� ���*/
		if (is_digit_string(tmp) && search_index(atoi(tmp), ALL) != -1)
			break;

		FFLUSH_STDIN
	}
	seq = atoi(tmp);
	FFLUSH_STDIN

	/*������ �Է¹޴´�.*/
	while (1)
	{
		printf("���� �Է� �� Enter: ");
		scanf("%s", tmp);

		/*������ ��츸 ���*/
		if (is_digit_string(tmp))
			break;

		FFLUSH_STDIN
	}
	selected_num = atoi(tmp);

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
	char tmp[INPUT_BUFFER_SIZE];

	system("cls");

	print_selected(&tos);

	while (1)
	{
		printf("����� �޴� ��ư�� �Է� �� Enter(0�� �Է��ϸ� ����): ");
		scanf("%s", tmp);

		/*������ ���*/
		if (is_digit_string(tmp))
		{
			seq = atoi(tmp);

			/*���� 0�� ���*/
			if (seq == 0) 
			{
				return;
			}

			/*_selected �迭�� �����ϴ� ���*/
			if (is_exist(seq))
			{
				break;
			}
		}
		
		FFLUSH_STDIN
	}

	FFLUSH_STDIN

	/**/
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