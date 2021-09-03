#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define UP 0 //키보드값들 
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define Choose 4

#define COL GetStdHandle(STD_OUTPUT_HANDLE) // 콘솔창의 핸들정보 받기
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
	system("mode con cols=70 lines=35 | title 당신의 점심을 책임진다! GL"); //가로길이, 세로길이, 제목
}

void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) { //커서 안보이게 하는 함수 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
		CurInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
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
	gotoxy(13, 8);  print("             ▣▣▣      ▣          ");
	gotoxy(13, 9);  print("           ▣            ▣          ");
	gotoxy(13, 10); print("           ▣   ▣▣     ▣          ");
	gotoxy(13, 11); print("           ▣     ▣     ▣          ");
	gotoxy(13, 12); print("            ▣▣▣   ■  ▣▣▣▣  \n");
	SetConsoleTextAttribute(COL, 0x000B);
	gotoxy(17, 27); print("    김대현      강타우      박준원");
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
	if (temp == 119 || temp == 87 || nSelect == 72) { // 'w' or 'W' or '↑'
		return UP;
	}
	else if (temp == 115 || temp == 83 || nSelect == 80) { // 's' or 'S' or '↓' 
		return DOWN;
	}
	else if (temp == 97 || temp == 65 || nSelect == 75) { // 'a' or 'A' or '←'
		return LEFT;
	}
	else if (temp == 100 || temp == 68 || nSelect == 77) { // 'd' or 'D' or '→'
		return RIGHT;
	}
	else if (temp == 32 || temp == 13) { // Enter 또는 Spacebar
		return Choose;
	}
}

void box() {
	system("color 06"); // 금색 테두리 만들어주기 위해 사용
	gotoxy(24, 15); print("┌---------------------┐");
	gotoxy(24, 16); print("│                     │");
	gotoxy(24, 17); print("│                     │");
	gotoxy(24, 18); print("│                     │");
	gotoxy(24, 19); print("│                     │");
	gotoxy(24, 20); print("│                     │");
	gotoxy(24, 21); print("│                     │");
	gotoxy(24, 22); print("│                     │");
	gotoxy(24, 23); print("│                     │");
	gotoxy(24, 24); print("│                     │");
	gotoxy(24, 25); print("└---------------------┘");
}

int menuDraw() { // 메뉴 선택창
	SetConsoleTextAttribute(COL, 0x000f); // 글자 흰색 유지
	int x = 29;
	int y = 17;
	gotoxy(x - 3, y);
	print("▷   한식");
	gotoxy(x, y + 1);
	print("  양식");
	gotoxy(x, y + 2);
	print("  중식");
	gotoxy(x, y + 3);
	print("  일식");
	gotoxy(x, y + 4);
	print("  기타");
	gotoxy(x, y + 5);
	print("  팀 정보");
	gotoxy(x, y + 6);
	print("  시스템 종료");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 17) {
				gotoxy(x - 3, y);
				print("   ");
				gotoxy(x - 3, --y);
				print("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 23) {
				gotoxy(x - 3, y);
				print("   ");
				gotoxy(x - 3, ++y);
				print("▶");
			}
			break;
		}
		case Choose: {
			return y - 17;
		}
		}
	}
}

void teaminfo() { // 팀 정보 출력
	system("cls");
	system("color 0E");
	gotoxy(9, 15); print("┌--------------<  TEAM INFORMATION  >--------------┐");
	gotoxy(9, 16); print("│     MEMBER 1         MEMBER 2        MEMBER 3    │");
	gotoxy(9, 17); print("│      김대현           강타우          박준원     │");
	gotoxy(9, 18); print("└--------------------------------------------------┘");
	gotoxy(2, 19); print(" \t  === 이전 화면으로 돌아가려면 아무키나 누르세요. === \n\n");
	if (getch()) system("cls"); // 아무키나 누르면 메뉴화면으로 돌아가게끔 만듦.
}

void selectmenu() {
	while (1) {
		switch (menuDraw()) {
		case 0://한식
			system("cls");
			Korean_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 1://양식
			system("cls");
			Western_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 2://중식
			system("cls");
			Chinese_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 3://일식
			system("cls");
			Japanese_food();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 4://기타
			system("cls");
			etc();
			Sleep(600);
			if (getch()) system("cls");
			system("cls");
			box();
			titleDraw();
			break;
		case 5://팀 정보
			teaminfo();
			system("cls");
			box();
			titleDraw();
			break;
		default://시스템 종료
			system("cls");
			thankyou();
			if (getch());
			SetConsoleTextAttribute(COL, 0); //검정색: 최종 종료 시 계속하려면 아무키나 누르십시오를 보이지 않게하기 위함
			exit(0);
		}
	}
}

void thankyou() {
	int x = 16;
	int y = 13;
	system("color 0E"); // 글자 밝은 노랑
	gotoxy(x, y);     print("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	gotoxy(x, y + 1); print("▤                                    ▤");
	gotoxy(x, y + 2); print("▤  +-----------------------------+   ▤");
	gotoxy(x, y + 3); print("▤  |당신의 점심을 책임지겠습니다!|   ▤");
	gotoxy(x, y + 4); print("▤  +-----------------------------+   ▤");
	gotoxy(x, y + 5); print("▤                                    ▤");
	gotoxy(x, y + 6); print("▤                                    ▤");
	gotoxy(x, y + 7); print("▤           맛있게 드세요!           ▤");
	gotoxy(x, y + 8); print("▤                                    ▤");
	gotoxy(x, y + 9); print("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
}


void Line() { // 레이아웃
	print("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
}

void Line2() { // 레이아웃
	print("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
}

void Line3() { // 레이아웃
	print("\n〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
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
		fprintf(stderr, "파일을 찾을 수 없습니다!\n");
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
	gotoxy(21, 15); printf("추천해드릴 음식은!\n");
	gotoxy(21, 16); printf("%s", k[random_number]);
	gotoxy(21, 17); printf("입니다.");
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
		fprintf(stderr, "파일을 찾을 수 없습니다!\n");
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
	gotoxy(21, 15); printf("추천해드릴 음식은!\n");
	gotoxy(21, 16); printf("%s", w[random_number]);
	gotoxy(21, 17); printf("입니다.");
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
		fprintf(stderr, "파일을 찾을 수 없습니다!\n");
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
	gotoxy(21, 15); printf("추천해드릴 음식은!\n");
	gotoxy(21, 16); printf("%s", c[random_number]);
	gotoxy(21, 17); printf("입니다.");
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
		fprintf(stderr, "파일을 찾을 수 없습니다!\n");
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
	gotoxy(21, 15); printf("추천해드릴 음식은!\n");
	gotoxy(21, 16); printf("%s", j[random_number]);
	gotoxy(21, 17); printf("입니다.");
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
		fprintf(stderr, "파일을 찾을 수 없습니다!\n");
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
	gotoxy(21, 15); printf("추천해드릴 음식은!\n");
	gotoxy(21, 16); printf("%s", e[random_number]);
	gotoxy(21, 17); printf("입니다.");
	gotoxy(0, 18); Line3();
	printf("\n\n");

	for (int i = 0; i < 16; i++)
		free(e[i]);

	fclose(fp);
}

int main() {
	setcursortype(NOCURSOR); //커서 없앰
	init();
	box();
	titleDraw();
	selectmenu();
	return 0;
}
