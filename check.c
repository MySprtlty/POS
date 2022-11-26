/*
* check.c
* 변환이나 탐색을 맡는 함수가 정의되어 있다.
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

/*십진수 문자열인지 체크하는 함수*/
enum bool is_digit_string(const char* c)
{
	const size_t length = strlen(c);
	int i = 0;
	for (i; i < length; i++)
	{
		/*하나라도 숫자가 아니라면*/
		if (!isdigit(c[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*현재 선택된 음식을 저장하는 배열에 인자로 넘긴 음식이 존재하는 확인하는 함수*/
enum bool is_exist(const unsigned int seq)
{
	for (int i = 0; i < tos; i++)
	{
		/*이미 선택된 음식이면*/
		if (_selected[i].data->seq == seq)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/*
* 지정한 음식의 인덱스를 찾는 함수
* 모드를 ALL로 지정하면, _all배열에서 지정한 음식을 탐색한다.
* 모드를 SELECTED로 지정하면 _selected배열에서 지정한 음식을 탐색한다.
*/
int search_index(const unsigned int seq, enum mode m)
{
	int i = 0;
	if (m == ALL) /* _all에서 탐색 */
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
	else if (m == SELECTED) /* _selected에서 탐색*/
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
	else /*유효하지 않은 모드*/
	{
		fprintf(stderr, "Error: Invalid mode\n");
	}
	return -1;
}