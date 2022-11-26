#pragma once /*��� �ߺ��� �����ִ� ��ó���� ���ù�*/

/*���� ���� ������ �����ϴ� ����ü*/
typedef struct food {
	const unsigned int seq; /* ������ �ĺ��ϴ� ���� �ĺ��� */
	char* const name; /*�̸�*/
	const unsigned int price; /*����*/
} food;

/*���õ� ������ ������ ������ �����ϴ� ����ü*/
typedef struct selected_food {
	food* data; /*food�� ����Ű�� ������*/
	unsigned int selected_num; /*������ ���õ� ����*/
} selected_food;

enum bool{ FALSE, TRUE }; /*boolean ����*/

/*�޴��� �����ϴ� ������ �� ����*/
#define NUM_OF_FOODS 12

/*������ ī�װ� ����*/
#define NUM_OF_CATEGORIES 4
