/*
* check.c
* ��ȯ�̳� Ž���� �ô� �Լ��� ���ǵǾ� �ִ�.
*/

#include "food.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

extern food _all[NUM_OF_FOODS];
extern selected_food _selected[NUM_OF_FOODS];
extern unsigned int tos;

/*prototype declaration*/
unsigned int ctoi(const char);
enum bool is_digit_string(const char*);
enum bool is_exist(const unsigned int);
int search_index(const unsigned int seq, enum mode m);

/*convert char to int*/ 
unsigned int ctoi(const char c)
{
	static const char* const table = "0123456789";

	unsigned int i = 0;
	for (i; i < 10; i++)
	{
		if (c == table[i])
		{
			break;
		}
	}
	return i;
}

/*������ ���ڿ����� üũ�ϴ� �Լ�*/
enum bool is_digit_string(const char* c)
{
	const size_t length = strlen(c);
	int i = 0;
	for (i; i < length; i++)
	{
		/*�ϳ��� ���ڰ� �ƴ϶��*/
		if (!isdigit(c[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

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

/*
* ������ ������ �ε����� ã�� �Լ�
* ��带 ALL�� �����ϸ�, _all�迭���� ������ ������ Ž���Ѵ�.
* ��带 SELECTED�� �����ϸ� _selected�迭���� ������ ������ Ž���Ѵ�.
*/
int search_index(const unsigned int seq, enum mode m)
{
	int i = 0;
	if (m == ALL) /* _all���� Ž�� */
	{
		for (i; i < NUM_OF_FOODS; i++)
		{
			if (_all[i].seq == seq)
			{
				return i; /*return index*/
			}
		}
		fprintf(stderr, "Error: Can't search index (mode:ALL)\n");
	}
	else if (m == SELECTED) /* _selected���� Ž��*/
	{
		for (i; i < tos; i++)
		{
			if (_selected[i].data->seq == seq)
			{
				return i;
			}
		}
		fprintf(stderr, "Error: Can't search index (mode:SELECTED)\n");
	}
	else /*��ȿ���� ���� ���*/
	{
		fprintf(stderr, "Error: Invalid mode\n");
	}
	return -1;
}