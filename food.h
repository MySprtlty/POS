#pragma once /*헤더 한번만 컴파일*/

/*음식 관련 정보를 저장하는 구조체*/
typedef struct food {
	const unsigned int seq; /* 음식을 식별하는 고유 식별자 (PK)*/
	char* const name; /*이름*/
	const unsigned int price; /*가격*/
} food;

/*선택된 음식의 정보와 수량을 저장하는 구조체*/
typedef struct selected_food {
	food* data; /*구조체 food를 가리키는 포인터*/
	unsigned int selected_num; /*음식이 선택된 수량*/
} selected_food;

/*Boolean 정의*/
enum bool{ FALSE, TRUE };

/*search_index함수의 모드를 설정할 때 사용하는 열거상수 정의*/
enum mode { ALL, SELECTED };

/*메뉴에 존재하는 음식의 총 개수*/
#define NUM_OF_FOODS 12
/*음식의 카테고리 개수*/
#define NUM_OF_CATEGORIES 4
