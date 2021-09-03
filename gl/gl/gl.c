#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define UP 0 //Ű���尪�� 
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define Choose 4

#define COL GetStdHandle(STD_OUTPUT_HANDLE) // �ܼ�â�� �ڵ����� �ޱ�
#define MAX 10240
#define print printf

void init(); void gotoxy(int, int);
void setcursortype(CURSOR_TYPE);
void box();
void titleDraw();
void selectmenu();
void teaminfo();
void thankyou();
void Line(); void Line2(); void Line3();
int menuDraw();
int keyControl();
void Korean_food();
void Western_food();
void Japanese_food();
void Chinese_food();
void etc();



void init() {
	system("mode con cols=70 lines=35 | title ����� ������ å������! GL"); //���α���, ���α���, ����
}

void gotoxy(int x, int y) { //gotoxy�Լ� 
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) { //Ŀ�� �Ⱥ��̰� �ϴ� �Լ� 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
		CurInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void titleDraw() {
	SetConsoleTextAttribute(COL, 0x0006);
	gotoxy(13, 8);  print("             �ââ�      ��          ");
	gotoxy(13, 9);  print("           ��            ��          ");
	gotoxy(13, 10); print("           ��   �â�     ��          ");
	gotoxy(13, 11); print("           ��     ��     ��          ");
	gotoxy(13, 12); print("            �ââ�   ��  �âââ�  \n");
	SetConsoleTextAttribute(COL, 0x000B);
	gotoxy(17, 27); print("    �����      ��Ÿ��      ���ؿ�");
}

int keyControl() {
	int temp = getch();
	int nSelect = 0;
	if (kbhit()) {
		nSelect = getch();
		if (nSelect == 224) {
			nSelect = getch();
		}
	}
	if (temp == 119 || temp == 87 || nSelect == 72) { // 'w' or 'W' or '��'
		return UP;
	}
	else if (temp == 115 || temp == 83 || nSelect == 80) { // 's' or 'S' or '��' 
		return DOWN;
	}
	else if (temp == 97 || temp == 65 || nSelect == 75) { // 'a' or 'A' or '��'
		return LEFT;
	}
	else if (temp == 100 || temp == 68 || nSelect == 77) { // 'd' or 'D' or '��'
		return RIGHT;
	}
	else if (temp == 32 || temp == 13) { // Enter �Ǵ� Spacebar
		return Choose;
	}
}

void box() {
	system("color 06"); // �ݻ� �׵θ� ������ֱ� ���� ���
	gotoxy(24, 15); print("��---------------------��");
	gotoxy(24, 16); print("��                     ��");
	gotoxy(24, 17); print("��                     ��");
	gotoxy(24, 18); print("��                     ��");
	gotoxy(24, 19); print("��                     ��");
	gotoxy(24, 20); print("��                     ��");
	gotoxy(24, 21); print("��                     ��");
	gotoxy(24, 22); print("��                     ��");
	gotoxy(24, 23); print("��                     ��");
	gotoxy(24, 24); print("��                     ��");
	gotoxy(24, 25); print("��---------------------��");
}

int menuDraw() { // �޴� ����â
	SetConsoleTextAttribute(COL, 0x000f); // ���� ��� ����
	int x = 29;
	int y = 17;
	gotoxy(x - 3, y);
	print("��   �ѽ�");
	gotoxy(x, y + 1);
	print("  ���");
	gotoxy(x, y + 2);
	print("  �߽�");
	gotoxy(x, y + 3);
	print("  �Ͻ�");
	gotoxy(x, y + 4);
	print("  ��Ÿ");
	gotoxy(x, y + 5);
	print("  �� ����");
	gotoxy(x, y + 6);
	print("  �ý��� ����");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 17) {
				gotoxy(x - 3, y);
				print("   ");
				gotoxy(x - 3, --y);
				print("��");
			}
			break;
		}
		case DOWN: {
			if (y < 23) {
				gotoxy(x - 3, y);
				print("   ");
				gotoxy(x - 3, ++y);
				print("��");
			}
			break;
		}
		case Choose: {
			return y - 17;
		}
		}
	}
}

void teaminfo() { // �� ���� ���
	system("cls");
	system("color 0E");
	gotoxy(9, 15); print("��--------------<  TEAM INFORMATION  >--------------��");
	gotoxy(9, 16); print("��     MEMBER 1         MEMBER 2        MEMBER 3    ��");
	gotoxy(9, 17); print("��      �����           ��Ÿ��          ���ؿ�     ��");
	gotoxy(9, 18); print("��--------------------------------------------------��");
	gotoxy(2, 19); print(" \t  === ���� ȭ������ ���ư����� �ƹ�Ű�� ��������. === \n\n");
	if (getch()) system("cls"); // �ƹ�Ű�� ������ �޴�ȭ������ ���ư��Բ� ����.
}

void selectmenu() {
	while (1) {
		switch (menuDraw()) {
		case 0://�ѽ�
			system("cls");
			Korean_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 1://���
			system("cls");
			Western_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 2://�߽�
			system("cls");
			Chinese_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 3://�Ͻ�
			system("cls");
			Japanese_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 4://��Ÿ
			system("cls");
			etc();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 5://�� ����
			teaminfo();
			system("cls");
			box();
			titleDraw();
			break;
		default://�ý��� ����
			system("cls");
			thankyou();
			if (getch());
			SetConsoleTextAttribute(COL, 0); //������: ���� ���� �� ����Ϸ��� �ƹ�Ű�� �����ʽÿ��� ������ �ʰ��ϱ� ����
			exit(0);
		}
	}
}

void thankyou() {
	int x = 16;
	int y = 13;
	system("color 0E"); // ���� ���� ���
	gotoxy(x, y);     print("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	gotoxy(x, y + 1); print("��                                    ��");
	gotoxy(x, y + 2); print("��  +-----------------------------+   ��");
	gotoxy(x, y + 3); print("��  |����� ������ å�����ڽ��ϴ�!|   ��");
	gotoxy(x, y + 4); print("��  +-----------------------------+   ��");
	gotoxy(x, y + 5); print("��                                    ��");
	gotoxy(x, y + 6); print("��                                    ��");
	gotoxy(x, y + 7); print("��           ���ְ� �弼��!           ��");
	gotoxy(x, y + 8); print("��                                    ��");
	gotoxy(x, y + 9); print("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
}


void Line() { // ���̾ƿ�
	print("������������������������������������");
}

void Line2() { // ���̾ƿ�
	print("������������������������������������\n");
}

void Line3() { // ���̾ƿ�
	print("\n������������������������������������\n");
}

void Korean_food() {
	srand(time(NULL));
	int random_number = rand() % 120;
	char* k[120];
	char* name;
	FILE* fp = NULL;

	fp = fopen("Korean_food.txt", "r");
	if (fp == NULL)
	{
		Line2();
		fprintf(stderr, "������ ã�� �� �����ϴ�!\n");
		Line();
		if (getch());
		system("cls");
		init();
		box();
		titleDraw();
		selectmenu();
	}

	for (int i = 0; i < 120; i++)
	{
		name = (char*)malloc(sizeof(char) * MAX);
		fgets(name, MAX, fp);
		k[i] = name;
	}

	system("cls");
	gotoxy(0, 13); Line();
	gotoxy(21, 15); printf("��õ�ص帱 ������!\n");
	gotoxy(21, 16); printf("%s", k[random_number]);
	gotoxy(21, 17); printf("�Դϴ�.");
	gotoxy(0, 18); Line3();
	printf("\n\n");

	for (int i = 0; i < 120; i++)
		free(k[i]);

	fclose(fp);
}

void Western_food() {
	srand(time(NULL));
	int random_number = rand() % 33;
	char* w[33];
	char* name;
	FILE* fp = NULL;

	fp = fopen("Western_food.txt", "r");
	if (fp == NULL)
	{
		Line2();
		fprintf(stderr, "������ ã�� �� �����ϴ�!\n");
		Line();
		if (getch());
		system("cls");
		init();
		box();
		titleDraw();
		selectmenu();
	}

	for (int i = 0; i < 33; i++)
	{
		name = (char*)malloc(sizeof(char) * MAX);
		fgets(name, MAX, fp);
		w[i] = name;
	}

	system("cls");
	gotoxy(0, 13); Line();
	gotoxy(21, 15); printf("��õ�ص帱 ������!\n");
	gotoxy(21, 16); printf("%s", w[random_number]);
	gotoxy(21, 17); printf("�Դϴ�.");
	gotoxy(0, 18); Line3();
	printf("\n\n");

	for (int i = 0; i < 33; i++)
		free(w[i]);

	fclose(fp);
}

void Chinese_food() {
	srand(time(NULL));
	int random_number = rand() % 29;
	char* c[29];
	char* name;
	FILE* fp = NULL;

	fp = fopen("Chinese_food.txt", "r");
	if (fp == NULL)
	{
		Line2();
		fprintf(stderr, "������ ã�� �� �����ϴ�!\n");
		Line();
		if (getch());
		system("cls");
		init();
		box();
		titleDraw();
		selectmenu();
	}

	for (int i = 0; i < 29; i++)
	{
		name = (char*)malloc(sizeof(char) * MAX);
		fgets(name, MAX, fp);
		c[i] = name;
	}

	system("cls");
	gotoxy(0, 13); Line();
	gotoxy(21, 15); printf("��õ�ص帱 ������!\n");
	gotoxy(21, 16); printf("%s", c[random_number]);
	gotoxy(21, 17); printf("�Դϴ�.");
	gotoxy(0, 18); Line3();
	printf("\n\n");

	for (int i = 0; i < 29; i++)
		free(c[i]);

	fclose(fp);
}

void Japanese_food() {
	srand(time(NULL));
	int random_number = rand() % 39;

	char* j[39];
	char* name;
	FILE* fp = NULL;

	fp = fopen("Japanese_food.txt", "r");
	if (fp == NULL)
	{
		Line2();
		fprintf(stderr, "������ ã�� �� �����ϴ�!\n");
		Line();
		if (getch());
		system("cls");
		init();
		box();
		titleDraw();
		selectmenu();
	}

	for (int i = 0; i < 39; i++)
	{
		name = (char*)malloc(sizeof(char) * MAX);
		fgets(name, MAX, fp);
		j[i] = name;
	}

	system("cls");
	gotoxy(0, 13); Line();
	gotoxy(21, 15); printf("��õ�ص帱 ������!\n");
	gotoxy(21, 16); printf("%s", j[random_number]);
	gotoxy(21, 17); printf("�Դϴ�.");
	gotoxy(0, 18); Line3();
	printf("\n\n");

	for (int i = 0; i < 39; i++)
		free(j[i]);

	fclose(fp);
}

void etc() {
	srand(time(NULL));
	int random_number = rand() % 16;

	char* e[16];
	char* name;
	FILE* fp = NULL;

	fp = fopen("etc.txt", "r");
	if (fp == NULL)
	{
		Line2();
		fprintf(stderr, "������ ã�� �� �����ϴ�!\n");
		Line();
		if (getch());
		system("cls");
		init();
		box();
		titleDraw();
		selectmenu();
	}

	for (int i = 0; i < 16; i++)
	{
		name = (char*)malloc(sizeof(char) * MAX);
		fgets(name, MAX, fp);
		e[i] = name;
	}

	system("cls");
	gotoxy(0, 13); Line();
	gotoxy(21, 15); printf("��õ�ص帱 ������!\n");
	gotoxy(21, 16); printf("%s", e[random_number]);
	gotoxy(21, 17); printf("�Դϴ�.");
	gotoxy(0, 18); Line3();
	printf("\n\n");

	for (int i = 0; i < 16; i++)
		free(e[i]);

	fclose(fp);
}

int main() {
	setcursortype(NOCURSOR); //Ŀ�� ����
	init();
	box();
	titleDraw();
	selectmenu();
	return 0;
}
