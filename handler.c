/*
* handler.c
* 옵션들을 처리하는 Handler 정의되어 있다.
*/
#define _CRT_SECURE_NO_WARNINGS

/*입력 버퍼를 비우는 매크로*/
#define FFLUSH_STDIN while(getchar() != '\n'){} 

/*입력 버퍼 사이즈*/
#define INPUT_BUFFER_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "food.h"
#include <Windows.h>

extern food _all[NUM_OF_FOODS];
extern selected_food _selected[NUM_OF_FOODS];
extern unsigned int tos;

/*prototype declaration*/
extern void print_selected(const unsigned int*);
extern unsigned int ctoi(const char);
extern enum bool is_digit_string(const char*);
extern enum bool is_exist(const unsigned int);
extern int search_index(const unsigned int seq, enum mode m);

void get_option(unsigned int*);
void add_handler(unsigned int*);
void cancel_handler(unsigned int*);
void quit_handler(const unsigned int*);

/*사용자에게 옵션을 입력받는 함수*/
void get_option(unsigned int* opt)
{
	
	char tmp[INPUT_BUFFER_SIZE];

	while(1)
	{
		printf("번호 선택후 Enter: ");
		scanf("%s", tmp); 

		/* 
		* 숫자거나; 1 미만이거나 3 초과면 반복한다.
		* short circuit을 이용한 에러 처리
		* 숫자일때만 atoi(tmp)가 평가된다.
		*/
		if (is_digit_string(tmp) && (atoi(tmp) >= 1 && atoi(tmp) <= 3)) 
			break;

		FFLUSH_STDIN
	} 

	*opt = atoi(tmp);

	return;
}

/*추가를 처리하는 함수*/
void add_handler(unsigned int* sum)
{
	unsigned int seq = 0, selected_num = 0;
	int i_all = -1, i_selected = -1; /*_all 배열의 index와 _selected 배열의 index*/

	char tmp[INPUT_BUFFER_SIZE];

	/*메뉴 번호를 입력받는다.*/
	while (1)
	{
		printf("메뉴번호 입력 후 Enter: ");
		scanf("%s", tmp);

		/*숫자거나, _ALL배열에 존재할 경우에만 허용*/
		if (is_digit_string(tmp) && search_index(atoi(tmp), ALL) != -1)
			break;

		FFLUSH_STDIN
	}
	seq = atoi(tmp);
	FFLUSH_STDIN

	/*수량을 입력받는다.*/
	while (1)
	{
		printf("수량 입력 후 Enter: ");
		scanf("%s", tmp);

		/*숫자일 경우만 허용*/
		if (is_digit_string(tmp))
			break;

		FFLUSH_STDIN
	}
	selected_num = atoi(tmp);

	/*get _all's index*/
	i_all = search_index(seq, ALL);

	if (!is_exist(seq)) /*아직 선택된적이 없는 음식이면*/
	{
		/*push new data*/
		_selected[tos].data = &(_all[i_all]);
		_selected[tos].selected_num = selected_num;
		tos++;
	}
	else /*이미 선택된 적이 있는 음식이라면*/
	{
		/*get _selected's index*/
		i_selected = search_index(seq, SELECTED);
		/*추가한 만큼 선택된 수량 갱신*/
		_selected[i_selected].selected_num += selected_num;
	}
	/*지불할 총액에 추가*/

	*sum += ((_all[i_all].price) * selected_num);
	system("cls");
	return;
}

/*취소를 처리하는 함수*/
void cancel_handler(unsigned int* sum)
{
	unsigned int seq = 0;
	char tmp[INPUT_BUFFER_SIZE];

	system("cls");

	print_selected(&tos);

	while (1)
	{
		printf("취소할 메뉴 버튼을 입력 후 Enter(0을 입력하면 종료): ");
		scanf("%s", tmp);

		/*숫자일 경우*/
		if (is_digit_string(tmp))
		{
			seq = atoi(tmp);

			/*값이 0인 경우*/
			if (seq == 0) 
			{
				return;
			}

			/*_selected 배열에 존재하는 경우*/
			if (is_exist(seq))
			{
				break;
			}
		}
		
		FFLUSH_STDIN
	}

	FFLUSH_STDIN

	/*음식의 수량을 0으로 갱신한다.*/
	if (is_exist(seq))
	{
		selected_food* target = &(_selected[search_index(seq, SELECTED)]);
		*sum -= target->data->price * target->selected_num;
		target->selected_num = 0;
	}
	return;
}

/*종료를 처리하는 함수*/
void quit_handler(const unsigned int* sum)
{
	unsigned int pay = 0;
	char tmp[INPUT_BUFFER_SIZE];

	system("cls");

	printf("고객이 지불할 총액은 %u원 입니다.\n", *sum);

	while (1) 
	{
		printf("고객으로부터 받은 금액을 입력 후 Enter: ");
		scanf("%s", &tmp);

		/*숫자이고, 음수가 아닐 경우에만 허용*/
		if (is_digit_string(tmp) && ((pay = atoi(tmp)) >= 0))
			break;
		FFLUSH_STDIN
	}

	system("cls");

	printf("<명세표>\n");
	print_selected(&tos);
	printf("금액: %u\n", *sum);
	printf("잔돈: %d\n", pay - (*sum));
	
	Sleep(1000);
	exit(0);
}