#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

// 계산기 모형 : 17*25

// ASCII value
#define A 65 // 10진수 2진수 변환
#define a 97 
#define S 83 // 10진수 2진수 사칙연산
#define s 115
#define C 67 // reset
#define c 99
#define q 113 // quit
#define Q 81

void gotoxy(int x, int y) //모니터상의 x,y 좌표로 이동시키는 함수
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show) // 커서숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int x = 3, y = 2;  // 계산기 시작 좌표
int key;  // 키보드로 입력받은 키값을 저장
double n_s;  // 입력할 수
long n1, n2;
char sign; // 계산기호
int bit_n; // 비트 수 설정(추후 정의)
void title();   // 시작 화면
void menu_1();  // 메뉴 상단
void menu_2();  // 메뉴 하단
void manu_3();  // 종료, 리셋 알림
void number_enter(long* n1, char sign, long* n2, int* bit_n);  // 계산식 입력
void main_set();   // 계산기 처음 셋팅
void check_key();   // 키입력
void bin_add();  // 덧셈
void sub();  // 뺄셈
void multi();  // 곱셈
void divide();  // 나눗셈
void conv1(double n_s);  // 양의 실수 이진화
void conv2();   // 음의 정수 이진화
void one_num(double n_s, long* n1);  // 10진수 1개 입력
void var_reset(double* n_s, long* n1, long* n2, int* bit_n);  // 변수 초기화
int binaryproduct(int binary1, int binary2);  // 2진수 곱셈

void main()
{
    CursorView(0);   // 0이면 커서 숨겨짐
    title();

    while (1)  // q안누르면 반복할 수 있음
    {
        system("cls");
        menu_1();
        menu_2();
        manu_3();
        check_key();
    }
}

void title()
{
    gotoxy(x, y);
    printf("■■■     ■    ■    ■        ■        ■■■     ■    ■ \n");
    gotoxy(x, y + 1);
    printf("■   ■    ■    ■■  ■       ■■       ■   ■     ■  ■\n");
    gotoxy(x, y + 2);
    printf("■■■     ■    ■ ■ ■      ■  ■      ■■■        ■\n");
    gotoxy(x, y + 3);
    printf("■   ■    ■    ■  ■■     ■■■■     ■   ■       ■\n");
    gotoxy(x, y + 4);
    printf("■■■     ■    ■    ■    ■      ■    ■   ■       ■\n");
    gotoxy(x, y + 5);
    printf("                                                    \n");
    gotoxy(x, y + 6);
    printf(" ■■■        ■        ■          ■■■    ■    ■    ■             ■      ■■■■      ■■      ■■■   \n");
    gotoxy(x, y + 7);
    printf("■            ■■       ■         ■         ■    ■    ■            ■■        ■       ■    ■    ■   ■\n");
    gotoxy(x, y + 8);
    printf("■           ■  ■      ■         ■         ■    ■    ■           ■  ■       ■       ■    ■    ■■■\n");
    gotoxy(x, y + 9);
    printf("■          ■■■■     ■         ■         ■    ■    ■          ■■■■      ■       ■    ■    ■   ■\n");
    gotoxy(x, y + 10);
    printf(" ■■■    ■      ■    ■■■      ■■■      ■■      ■■■     ■      ■     ■         ■■      ■    ■\n");
    while (1)
    {
        gotoxy(x + 42, y + 17);
        printf("START(Just press any key...)");
        Sleep(500);
        gotoxy(x + 42, y + 17);
        printf("                             ");
        Sleep(500);

        if (_kbhit())
            break;
    }while (_kbhit()) _getch(); //키버퍼를 비움 
}

void menu_1()
{
    gotoxy(x + 33, y);
    printf("■      ■      ■■       ■■■       ■■■ \n");
    gotoxy(x + 33, y + 1);
    printf("■■  ■■    ■    ■     ■   ■      ■     \n");
    gotoxy(x + 33, y + 2);
    printf("■  ■  ■    ■    ■     ■    ■     ■■■   \n");
    gotoxy(x + 33, y + 3);
    printf("■      ■    ■    ■     ■   ■      ■     \n");
    gotoxy(x + 33, y + 4);
    printf("■      ■      ■■       ■■■       ■■■    \n");
}

void menu_2()
{
    gotoxy(x + 48, y + 14);
    printf("▷ TRANSLATION(A)");
    gotoxy(x + 48, y + 16);
    printf("▷ CALCULATION(S)");

    while (1)
    {
        if (_kbhit()) { //키입력이 있는 경우  
            key = _getch();
            if ((key == A) || (key == a))
            {
                system("cls");
                main_set();
                one_num(n_s, &n1);
                break;
            }
            else if ((key == s) || (key == S))
            {
                system("cls");
                main_set();
                number_enter(&n1, sign, &n2, &bit_n);
                break;
            }
            else
                continue;
        }
    }while (_kbhit()) _getch(); //키버퍼를 비움 
}

void one_num(double n_s, long* n1)
{
    gotoxy(x + 32, y + 6);
    scanf("%lf", &n_s);

    if (n_s < 0)
    {
        *n1 = (int)n_s;
        conv2();
    }
    else
    {
        conv1(n_s);
    }

}

void number_enter(long* n1, char sign, long* n2, int* bin_n)
{
    while (1)
    {
        gotoxy(x + 32, y + 6);
        scanf(" %d %c %d", n1, &sign, n2);

        if (sign == '+')
        {
            gotoxy(x + 32, y + 6);
            printf("비트 수를 입력하시오 : ");
            scanf(" %d", bin_n);
            bin_add(); // 덧셈 출력
            break;
        }
        else if (sign == '-')
        {
            gotoxy(x + 32, y + 6);
            printf("비트 수를 입력하시오 : ");
            scanf(" %d", bin_n);
            sub(); // 뺄셈 출력
            break;
        }
        else if (sign == '*')// 계산결과 1024넘어가면 오류
        {
            multi(); // 곱셈 출력
            break;
        }
        else if (sign == '/')
        {
            divide(); // 나눗셈 출력
            break;
        }
        else
        {
            gotoxy(x + 32, y + 6);
            printf("                  ");
            gotoxy(x + 65, y + 7);
            printf("             ");
            gotoxy(x + 65, y + 7);
            printf("ERROR");
            Sleep(500);
            gotoxy(x + 65, y + 7);
            printf("             ");
        }
    }
}

void main_set()
{
    //배경을 그림(x, y좌표로 위치 지정)
    gotoxy(x + 30, y + 5);
    printf("┌───────────────────────────┐");
    gotoxy(x + 30, y + 6);
    printf("│                           │");
    gotoxy(x + 30, y + 7);
    printf("│                           │");
    gotoxy(x + 30, y + 8);
    printf("│                           │");
    gotoxy(x + 30, y + 9);
    printf("│                           │");
    gotoxy(x + 30, y + 10);
    printf("├──────┬──────┬──────┬──────┤");
    gotoxy(x + 30, y + 11);
    printf("│   c  │   E  │   ÷ │  ×  │");
    gotoxy(x + 30, y + 12);
    printf("├──────┼──────┼──────┼──────┤");
    gotoxy(x + 30, y + 13);
    printf("│   7  │   8  │   9  │   -  │");
    gotoxy(x + 30, y + 14);
    printf("├──────┼──────┼──────┼──────┤");
    gotoxy(x + 30, y + 15);
    printf("│   4  │   5  │   6  │   +  │");
    gotoxy(x + 30, y + 16);
    printf("├──────┼──────┼──────┼──────┤");
    gotoxy(x + 30, y + 17);
    printf("│   1  │   2  │   3  │   =  │");
    gotoxy(x + 30, y + 18);
    printf("├──────┴──────┴──────┴──────┤");
    gotoxy(x + 30, y + 19);
    printf("│             0             │");
    gotoxy(x + 30, y + 20);
    printf("└───────────────────────────┘");
}

void manu_3()
{
    gotoxy(x + 65, y + 12);
    printf("C = 'RESET'");
    gotoxy(x + 65, y + 13);
    printf("Q = 'QUIT'");
}

void check_key()
{
    while (1)  // q안누르면 계속됨
    {
        if (_kbhit()) { //키입력이 있는 경우  
            gotoxy(x + 3, y + 7);
            key = _getch(); //키값을 받음

            if ((key == q) || (key == Q)) // q, Q 입력시 종료
            {
                system("cls"); //화면을 지우고 
                exit(0); //프로그램 종료
            }
            else if ((key == c) || (key == C)) // c, C 입력시 초기화
            {
                var_reset(&n_s, &n1, &n2, &sign, &bit_n);
                system("cls");  // 출력화면 정리
                break;
            }
            else  // 잘못 입력했을 때 메시지 출력
            {
                key = 0;
                gotoxy(x + 65, y + 7);
                printf("             ");
                gotoxy(x + 65, y + 7);
                printf("ERROR");
                Sleep(500);
                gotoxy(x + 65, y + 7);
                printf("             ");
            }
        }
        while (_kbhit()) _getch(); //키버퍼를 비움  
    }
}

void bin_add()
{
    int x, i;
    int* bin1 = malloc(bit_n * sizeof(int) * 4);//비트수에 따라 배율크기 저장
    int* bin2 = malloc(bit_n * sizeof(int) * 4);
    int* bin3 = malloc(bit_n * sizeof(int) * 4);

    i = 0;
    while (n1 > 0)//입력받은 수가 0이 되기 전까지 2로 나누고 나머지를 배열에 저장해 배열에 2진수 저장
    {
        bin1[i] = n1 % 2;
        n1 = n1 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)//위에서 계산한 2진수가 해당 비트 수 만큼의 길이를 갖도록함 
    {
        if (bin1[i] == 1)  // 해당 비트 수보다 2진수의 길이가 더 짧을 때 빈자리를 0으로 채움
            bin1[i] = 1;
        else bin1[i] = 0;
    }
    i = 0;
    while (n2 > 0) {//두번째 수도 동일하게 저장
        bin2[i] = n2 % 2;
        n2 = n2 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)
    {
        if (bin2[i] == 1)
            bin2[i] = 1;
        else bin2[i] = 0;
    }
    x = 0;
    for (i = 0; i <= bit_n; i++)//배열에 저장된 각 수를 더하고 x에 저장하여 나머지를 bin3에 저장하는 방식으로 2진수 덧셈 실행
    {
        x = x + bin1[i] + bin2[i];
        bin3[i] = x % 2;
        x = x / 2;
    }

    gotoxy(x + 35, y + 7);
    printf("NUM1: ");
    for (i = 0; i < bit_n; ++i)
        printf("%d", bin1[bit_n - 1 - i]);
    gotoxy(x + 35, y + 8);
    printf("NUM2: ");
    for (i = 0; i < bit_n; ++i)
        printf("%d", bin2[bit_n - 1 - i]);
    gotoxy(x + 35, y + 9);
    printf("RES: ");
    for (i = 0; i < bit_n; ++i)
        printf("%d", bin3[bit_n - 1 - i]);
    //printf("\n");
    if (bin1[bit_n] > 0 || bin2[bit_n] > 0 || bin3[bit_n] > 0 || bin1[bit_n - 1] == bin2[bit_n - 1] && bin1[bit_n - 1] != bin3[bit_n - 1])
        printf(" (OVERFLOW)");//배열1,2의 부호가 같은데 결과의 부호가 다르면 오버플로우, 배열1,2가 비트수를 넘어가면 오버플로우
    free(bin1);
    free(bin2);
    free(bin3);
}

void sub()//덧셈과 같은 방식이지만 n2를 보수화 하여 계산해 뺄셈 구현
{
    int x, i;
    int* bin1 = malloc(bit_n * sizeof(int) * 4);
    int* bin2 = malloc(bit_n * sizeof(int) * 4);
    int* bin3 = malloc(bit_n * sizeof(int) * 4);

    i = 0;
    while (n1 > 0)
    {
        bin1[i] = n1 % 2;
        n1 = n1 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)
    {
        if (bin1[i] == 1) bin1[i] = 1;
        else bin1[i] = 0;
    }
    i = 0;
    while (n2 > 0) {
        bin2[i] = n2 % 2;
        n2 = n2 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)
    {
        if (bin2[i] == 1) bin2[i] = 0;
        else bin2[i] = 1;
    }
    for (i = 0; i <= bit_n; i++)
    {
        if (bin2[i] == 1) bin2[i] = 0;
        else {
            bin2[i] = 1;
            break;
        }
    }
    x = 0;
    for (i = 0; i <= bit_n; i++)
    {
        x = x + bin1[i] + bin2[i];
        bin3[i] = x % 2;
        x = x / 2;
    }
    gotoxy(x + 34, y + 7);
    printf("NUM1: ");
    for (i = 0; i < bit_n; ++i)
        printf("%d", bin1[bit_n - 1 - i]);
    gotoxy(x + 34, y + 8);
    printf("NUM2: ");
    for (i = 0; i < bit_n; ++i)
        printf("%d", bin2[bit_n - 1 - i]);
    gotoxy(x + 34, y + 9);
    printf("RES: ");
    for (i = 0; i < bit_n; ++i)
        printf("%d", bin3[bit_n - 1 - i]);
    //printf("\n");
    if (bin1[bit_n] > 0 || bin1[bit_n - 1] == bin2[bit_n - 1] && bin1[bit_n - 1] != bin3[bit_n - 1])
        printf(" (OVERFLOW)");
    free(bin1);
    free(bin2);
    free(bin3);
}

void multi() {//1024넘어가면 long long의 범위를 넘어가므로 오버플로우 발생

    long long x, i, h, m;
    long long k, l;
    long long bin1[100] = { 0, };
    long long bin2[100] = { 0, };

    x = 0;
    k = 0;
    l = 0;
    i = 0;
    long long digit, factor = 1;
    long long multiply = 0;

    while (n1 > 0)
    {
        bin1[i] = n1 % 2;
        n1 = n1 / 2;
        i = i + 1;
    }
    for (i = 99; i >= 0; i--)//입력받은 정수를 2진수 배열로 변환
    {
        if (bin1[i] == 1)
            bin1[i] = 1;
        else bin1[i] = 0;
    }
    for (i = 0; i < 99; i++)//2진수 배열을 정수형으로 저장

    {
        h = pow(10, i);
        k += (bin1[i] * h);

    }
    gotoxy(x + 35, y + 7);
    printf("NUM1: ");
    printf("%d", k);
    i = 0;
    while (n2 > 0) {//입력받은 정수를 2진수 배열로 변환
        bin2[i] = n2 % 2;
        n2 = n2 / 2;
        i = i + 1;
    }
    for (i = 99; i >= 0; i--)
    {
        if (bin2[i] == 1)
            bin2[i] = 1;
        else bin2[i] = 0;
    }
    for (i = 0; i < 99; i++)//2진수 배열을 정수형으로 저장
    {
        m = pow(10, i);
        l += (bin2[i] * m);
    }
    gotoxy(x + 35, y + 8);
    printf("NUM2: ");
    printf("%d", l);
    while (l != 0)
    {
        digit = l % 10;//n2를 정수형으로 변환한 수(l)를 2로 나눈 나머지를 digit에 저장
        if (digit == 1)//digit이 1이면 n1을 정수형으로 변환한 수(k)에 factor를 곱하고 binaryproduct함수를 통해 곱셈 수행
        {
            k = k * factor;
            multiply = binaryproduct(k, multiply);
        }
        else//digit이 0이면 n1을 정수형으로 변환한 수(k)에 factor를 곱하고 k를 변환후 l을 10으로 나눠 자릿수 변경, factor또한 10으로 변환해 자릿수변경
            k = k * factor;
        l = l / 10;
        factor = 10;
    }
    gotoxy(x + 35, y + 9);
    printf("RES: ");
    printf("%d", multiply);
    if (l > 1111111111 || k > 1111111111 || multiply < 0) printf("(OVERFLOW)");
    //입력값이나 결과값이 1024를 넘어가면 정수형 저장범위 넘어가므로 overflow발생
}

void divide() {
    long long x, i, h, m;
    long long k, l, k1;
    long long cnt = 0;
    unsigned mask;
    long long* bin1 = malloc(bit_n * sizeof(int) * 4);
    long long* bin2 = malloc(bit_n * sizeof(int) * 4);
    long long* bin3 = malloc(bit_n * sizeof(int) * 4);
    x = 0;
    k = 0;
    l = 0;
    i = 0;

    while (n1 > 0)//입력받은 정수를 2진수 배열로 변환
    {
        bin1[i] = n1 % 2;
        n1 = n1 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)
    {
        if (bin1[i] == 1)
            bin1[i] = 1;
        else bin1[i] = 0;
    }
    for (i = 0; i < bit_n; i++)//2진수 배열을 정수형으로 k에 저장

    {
        h = pow(10, i);
        k += (bin1[i] * h);

    }
    gotoxy(x + 35, y + 7);
    printf("NUM1: ");
    printf("%d", k);
    i = 0;
    while (n2 > 0) {
        bin2[i] = n2 % 2;
        n2 = n2 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)//입력받은 정수를 2진수 배열로 변환
    {
        if (bin2[i] == 1)
            bin2[i] = 1;
        else bin2[i] = 0;
    }
    for (i = 0; i < bit_n; i++)//2진수 배열을 정수형으로 ㅣ에 저장
    {
        m = pow(10, i);
        l += (bin2[i] * m);
    }
    gotoxy(x + 35, y + 8);
    printf("NUM2: ");
    printf("%d", l);
    k1 = k;
    if (k > 1111111111) {//1024 넘어가면 오버플로우
        gotoxy(x + 34, y + 9);
        printf("RES: ");
        printf("(OVERFLOW)");
    }
    else {
        for (mask = l, i = 1; mask <= k1; mask <<= 1, i <<= 1);
        // 피제수를 나눌 수 있는 가장 큰 제수의 2^n을 찾는 과정 
        while (l <= k1) { // 피제수가 제수보다 작으면 그만함

            if (k1 >= mask) {
                k1 -= mask;        // 나머지를 구해 다시 피제수로 사용 
                cnt += i;        // 구해진 몫을 더함 
            }
            mask >>= 1;//비트를 1만큼 이동
            i >>= 1;//비트 1만큼 이동
        }
        gotoxy(x + 35, y + 9);
        printf("RES: ");
        printf("%d", cnt);
    }
}

int binaryproduct(int binary1, int binary2)
{
    int i = 0, remainder = 0, sum[60];//변수의 나머지와 몫
    unsigned long long binaryprod = 0;

    while (binary1 != 0 || binary2 != 0)
    {
        sum[i++] = (binary1 % 10 + binary2 % 10 + remainder) % 2;//2(10)로 나눈 나머지를 sum에 저장
        remainder = (binary1 % 10 + binary2 % 10 + remainder) / 2;//2로 나눈 몫을 remainder로 변환
        binary1 = binary1 / 10;//2로 나눔(자릿수 변환)
        binary2 = binary2 / 10;//2로 나눔(자릿수 변환)
    }
    if (remainder != 0)//나머지가 0이 아니라면 sum에 다시 나머지 저장
        sum[i++] = remainder;
    --i;
    while (i >= 0)
        binaryprod = binaryprod * 10 + sum[i--];//2진수로 변환하여 표현
    return binaryprod;
}

void var_reset(double* n_s, long* n1, long* n2, int* bit_n)
{
    *n_s = 0; *n1 = 0, * n2 = 0, bit_n = 0;
}

void conv1(double n_s)  // 양의 실수 이진수화
{
    int i = 66, j, temp;
    char box[66] = { 0 };

    temp = (long)n_s; // temp에 정수부분을 넣는다.
    n_s = n_s - (double)temp; //n_s에 소수부분을 넣는다.

    while (temp) box[--i] = '0' + temp % 2, temp /= 2; // 정수부분을 이진수화한다.

    temp = i;

    for (i = 0; i + temp < 66; i++)
        box[i] = box[i + temp];// 배열을 처음으로 이동시킨다.

    temp = 65 - temp; // 소수점 위치를 temp에 저장한다.
    i = temp + 1; // 소수점이하를 이진수화 한다.

    gotoxy(x + 32, y + 8);
    while (n_s&& i < 66) n_s *= 2, box[i++] = '0' + (int)n_s, n_s -= (int)n_s;
    printf("B.N.: ");
    for (j = 0; i > j; j++)
        printf(temp == j ? "%c." : "%c", box[j]); //배열 출력
}

void conv2()  // 음의 정수 이진수화
{
    int binary1, binary2, count1, count2, i = 0, comp2, j = 0;
    int bin1[100], bin2[100];

    comp2 = n1 + 1;//2의 보수 표현위해 입력 받은수에 +1
    n1 = -n1;
    comp2 = -comp2;

    while (n1 > 0)//입력받은 수가 0이 되기 전까지 2로 나누고 나머지를 배열에 저장해 배열에 2진수 저장
    {
        binary1 = n1 % 2;
        bin1[i] = binary1;
        n1 = n1 / 2;
        i += 1;
    }

    count1 = i - 1;
    gotoxy(x + 32, y + 7);
    printf("1's C : ");//변환한 배열의 1은 0으로 0은 1로 바꿔서 1의 보수 표현
    for (i = count1; i >= 0; i--) {
        if (bin1[i] == 1) bin1[i] = 0;
        else bin1[i] = 1;
        printf("%d", bin1[i]);
    }
    while (comp2 > 0)//입력받은수+1을 2진수로 변환
    {
        binary2 = comp2 % 2;
        bin2[j] = binary2;
        comp2 = comp2 / 2;
        j += 1;
    }
    count2 = j - 1;

    gotoxy(x + 32, y + 8);
    printf("2's C : ");//변환한 배열의 1은 0으로 0은 1로 바꿔서 2의 보수 표현
    for (j = count2; j >= 0; j--) {
        if (bin2[j] == 1) bin2[j] = 0;
        else bin2[j] = 1;
        printf("%d", bin2[j]);
    }

}