/*
* main.c
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "food.h"

/*메뉴에 존재하는 음식을 저장하는 테이블(배열)*/
food _all[NUM_OF_FOODS] =
{
	{10, "치즈버거세트", 3000},
	{11, "더블버거세트", 4500},
	{12, "치킨세트", 10000},

	{20, "치즈버거", 1600},
	{21, "더블버거", 2900},
	{22, "햄버거", 1200},

	{30, "아이스크림", 1200},
	{31, "포테이토", 1800},
	{32, "빙수", 2000},

	{40, "콜라", 1000},
	{41, "커피", 1100},
	{42, "밀크쉐이크", 1500}
};

/*현재 선택된 음식을 저장하는 배열*/
selected_food _selected[NUM_OF_FOODS];

/*
* top of _selected
* 비대칭 경계
*/
unsigned int tos;

/*prototype declaration*/
extern void print_all(const unsigned int*);
extern void print_selected(const unsigned int*);
extern void print_option(void);

extern void add_handler(unsigned int*);
extern void cancel_handler(unsigned int*);
extern void quit_handler(const unsigned int*);

extern void get_option(unsigned int*);

/*array of 3 pointer to function(unsigned int*) returning void*/
void (*call_handler[3])(unsigned int*) = { add_handler, cancel_handler, quit_handler };

int main(void)
{
	/*선택한 옵션*/
	unsigned int opt;
	/*지불할 총액*/
	unsigned int sum = 0;

	while (1)
	{
		/*전체 음식(메뉴판)을 출력해주는 함수 호출*/
		print_all(&sum);

		/*선택지를 출력해주는 함수 호출*/
		print_option();

		/*옵션을 입력 받는 함수 호출*/
		get_option(&opt);

		/*옵션값을 인덱스로 각각의 handler 호출*/
		call_handler[opt - 1](&sum);
	}

	return 0;
}