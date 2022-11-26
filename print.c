/*
* print.c
* 출력과 관련된 함수가 정의되어 있다.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "food.h"

/*prototype declaration*/
extern food _all[NUM_OF_FOODS];
extern selected_food _selected[NUM_OF_FOODS];

void print_option(void);
void print_all(const unsigned int*);
void print_selected(const unsigned int*);

/*카테고리 이름을 저장하는 배열*/
static char* categories[NUM_OF_CATEGORIES] =
{
	"세트메뉴",
	"버거메뉴",
	"디저트메뉴",
	"음료메뉴"
};

/*선택지를 출력하는 함수*/
void print_option(void)
{
	printf("1. 추가 \t2. 취소 \t3. 입력종료\n");

	return;
}

/*메뉴에 존재하는 모든 음식을 출력하는 함수*/
void print_all(const unsigned int* sum)
{
	int i = 0;
	system("cls");

	/*_all 배열을 순환하며 요소를 출력한다.*/
	for (i; i < NUM_OF_FOODS; i++)
	{
		/*특정 카테고리의 첫 음식이라면*/
		if (_all[i].seq % 10 == 0)
		{
			/*카테고리 명을 출력한다.*/
			printf("------------------------\n");
			printf("%s\n", categories[(_all[i].seq / 10) - 1]);;
		}

		/*음식 정보를 출력한다.*/
		printf("%2u %15s %u\n", _all[i].seq, _all[i].name, _all[i].price);
	}
	printf("------------------------\n");
	printf("지불할 총액:\t%u\n", *sum);

	return;
}

/*현재까지 선택된 음식들을 출력하는 함수*/
void print_selected(const unsigned int* tos)
{
	int i = 0;
	printf("------------------------\n");
	printf("선택한 메뉴\n");

	for (i; i < *tos; i++)
	{
		if (_selected[i].selected_num == 0) /*이미 삭제된 데이터일 경우 출력하지 않는다.*/
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