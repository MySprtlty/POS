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

/*지정한 음식의 인덱스를 찾는 함수*/
int search_index(const unsigned int seq, enum mode m)
{
	if (m == ALL) /* _all에서 탐색 */
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
	else if (m == SELECTED) /* _selected에서 탐색*/
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
	else /*유효하지 않은 모드*/
	{
		fprintf(stderr, "Error: invalid mode\n");
	}
	return -1;
}

/*사용자에게 선택을 입력받는 함수*/
void get_option(unsigned int* opt)
{
	do
	{
		printf("번호 선택후 Enter: ");
		scanf("%u", opt);
	} while (*opt < 1 || *opt > 3); /*1 미만이거나 3 초과면 반복한다.*/

	return;
}

/*추가를 처리하는 함수*/
void add_handler(unsigned int* sum)
{
	unsigned int seq = 0, selected_num = 0;
	int i_all = -1, i_selected = -1; /*_all 배열의 index와 _selected 배열의 index*/
	do
	{
		printf("메뉴번호 입력 후 Enter: ");
		scanf("%u", &seq);
	} while (search_index(seq, ALL) == -1); /*메뉴에 존재하지 않는 번호를 입력하면, 재입력 받는다.*/
	printf("수량 입력 후 Enter: ");
	scanf("%u", &selected_num);
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
	system("cls");
	print_selected(&tos);
	do
	{
		printf("취소할 메뉴 버튼을 입력 후 Enter(0을 입력하면 종료): ");
		scanf("%u", &seq);
	} while (search_index(seq, SELECTED) == -1); /*유효하지 않은 번호를 입력할 시, 재입력 받는다.*/

	if (is_exist(seq))
	{
		selected_food* target = &(_selected[search_index(seq, SELECTED)]);
		*sum -= target->data->price * target->selected_num;
		target->selected_num = 0;
	}
	return;
}

/*종료 옵션을 처리하는 함수*/
void quit_handler(unsigned int* sum) // compatible type: const 사용여부 확인
{
	unsigned int pay = 0;
	printf("고객이 지불할 총액은 %u원 입니다.\n", *sum);
	printf("고객으로부터 받은 금액을 입력 후 Enter: ");
	scanf("%u", &pay);

	system("cls");

	printf("<명세표>\n");
	print_selected(&tos);
	printf("금액: %u\n", *sum);
	printf("잔돈: %d\n", pay - (*sum));
	exit(0);
}