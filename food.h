#pragma once /*헤더 중복을 막아주는 전처리기 지시문*/

/*음식 관련 정보를 저장하는 구조체*/
typedef struct food {
	const unsigned int seq; /* 음식을 식별하는 고유 식별자 */
	char* const name; /*이름*/
	const unsigned int price; /*가격*/
} food;

/*선택된 음식의 정보와 수량을 저장하는 구조체*/
typedef struct selected_food {
	food* data; /*food를 가리키는 포인터*/
	unsigned int selected_num; /*음식이 선택된 수량*/
} selected_food;

enum bool{ FALSE, TRUE }; /*boolean 정의*/

/*메뉴에 존재하는 음식의 총 개수*/
#define NUM_OF_FOODS 12

/*음식의 카테고리 개수*/
#define NUM_OF_CATEGORIES 4
