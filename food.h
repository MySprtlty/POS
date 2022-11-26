#pragma once /*��� �ѹ��� ������*/

/*���� ���� ������ �����ϴ� ����ü*/
typedef struct food {
	const unsigned int seq; /* ������ �ĺ��ϴ� ���� �ĺ��� (PK)*/
	char* const name; /*�̸�*/
	const unsigned int price; /*����*/
} food;

/*���õ� ������ ������ ������ �����ϴ� ����ü*/
typedef struct selected_food {
	food* data; /*����ü food�� ����Ű�� ������*/
	unsigned int selected_num; /*������ ���õ� ����*/
} selected_food;

/*Boolean ����*/
enum bool{ FALSE, TRUE };

/*search_index�Լ��� ��带 ������ �� ����ϴ� ���Ż�� ����*/
enum mode { ALL, SELECTED };

/*�޴��� �����ϴ� ������ �� ����*/
#define NUM_OF_FOODS 12
/*������ ī�װ� ����*/
#define NUM_OF_CATEGORIES 4
