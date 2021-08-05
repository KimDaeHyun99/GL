#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

// ���� ���� : 17*25

// ASCII value
#define A 65 // 10���� 2���� ��ȯ
#define a 97 
#define S 83 // 10���� 2���� ��Ģ����
#define s 115
#define C 67 // reset
#define c 99
#define q 113 // quit
#define Q 81

void gotoxy(int x, int y) //����ͻ��� x,y ��ǥ�� �̵���Ű�� �Լ�
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show) // Ŀ�������
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int x = 3, y = 2;  // ���� ���� ��ǥ
int key;  // Ű����� �Է¹��� Ű���� ����
double n_s;  // �Է��� ��
long n1, n2;
char sign; // ����ȣ
int bit_n; // ��Ʈ �� ����(���� ����)
void title();   // ���� ȭ��
void menu_1();  // �޴� ���
void menu_2();  // �޴� �ϴ�
void manu_3();  // ����, ���� �˸�
void number_enter(long* n1, char sign, long* n2, int* bit_n);  // ���� �Է�
void main_set();   // ���� ó�� ����
void check_key();   // Ű�Է�
void bin_add();  // ����
void sub();  // ����
void multi();  // ����
void divide();  // ������
void conv1(double n_s);  // ���� �Ǽ� ����ȭ
void conv2();   // ���� ���� ����ȭ
void one_num(double n_s, long* n1);  // 10���� 1�� �Է�
void var_reset(double* n_s, long* n1, long* n2, int* bit_n);  // ���� �ʱ�ȭ
int binaryproduct(int binary1, int binary2);  // 2���� ����

void main()
{
    CursorView(0);   // 0�̸� Ŀ�� ������
    title();

    while (1)  // q�ȴ����� �ݺ��� �� ����
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
    printf("����     ��    ��    ��        ��        ����     ��    �� \n");
    gotoxy(x, y + 1);
    printf("��   ��    ��    ���  ��       ���       ��   ��     ��  ��\n");
    gotoxy(x, y + 2);
    printf("����     ��    �� �� ��      ��  ��      ����        ��\n");
    gotoxy(x, y + 3);
    printf("��   ��    ��    ��  ���     �����     ��   ��       ��\n");
    gotoxy(x, y + 4);
    printf("����     ��    ��    ��    ��      ��    ��   ��       ��\n");
    gotoxy(x, y + 5);
    printf("                                                    \n");
    gotoxy(x, y + 6);
    printf(" ����        ��        ��          ����    ��    ��    ��             ��      �����      ���      ����   \n");
    gotoxy(x, y + 7);
    printf("��            ���       ��         ��         ��    ��    ��            ���        ��       ��    ��    ��   ��\n");
    gotoxy(x, y + 8);
    printf("��           ��  ��      ��         ��         ��    ��    ��           ��  ��       ��       ��    ��    ����\n");
    gotoxy(x, y + 9);
    printf("��          �����     ��         ��         ��    ��    ��          �����      ��       ��    ��    ��   ��\n");
    gotoxy(x, y + 10);
    printf(" ����    ��      ��    ����      ����      ���      ����     ��      ��     ��         ���      ��    ��\n");
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
    }while (_kbhit()) _getch(); //Ű���۸� ��� 
}

void menu_1()
{
    gotoxy(x + 33, y);
    printf("��      ��      ���       ����       ���� \n");
    gotoxy(x + 33, y + 1);
    printf("���  ���    ��    ��     ��   ��      ��     \n");
    gotoxy(x + 33, y + 2);
    printf("��  ��  ��    ��    ��     ��    ��     ����   \n");
    gotoxy(x + 33, y + 3);
    printf("��      ��    ��    ��     ��   ��      ��     \n");
    gotoxy(x + 33, y + 4);
    printf("��      ��      ���       ����       ����    \n");
}

void menu_2()
{
    gotoxy(x + 48, y + 14);
    printf("�� TRANSLATION(A)");
    gotoxy(x + 48, y + 16);
    printf("�� CALCULATION(S)");

    while (1)
    {
        if (_kbhit()) { //Ű�Է��� �ִ� ���  
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
    }while (_kbhit()) _getch(); //Ű���۸� ��� 
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
            printf("��Ʈ ���� �Է��Ͻÿ� : ");
            scanf(" %d", bin_n);
            bin_add(); // ���� ���
            break;
        }
        else if (sign == '-')
        {
            gotoxy(x + 32, y + 6);
            printf("��Ʈ ���� �Է��Ͻÿ� : ");
            scanf(" %d", bin_n);
            sub(); // ���� ���
            break;
        }
        else if (sign == '*')// ����� 1024�Ѿ�� ����
        {
            multi(); // ���� ���
            break;
        }
        else if (sign == '/')
        {
            divide(); // ������ ���
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
    //����� �׸�(x, y��ǥ�� ��ġ ����)
    gotoxy(x + 30, y + 5);
    printf("����������������������������������������������������������");
    gotoxy(x + 30, y + 6);
    printf("��                           ��");
    gotoxy(x + 30, y + 7);
    printf("��                           ��");
    gotoxy(x + 30, y + 8);
    printf("��                           ��");
    gotoxy(x + 30, y + 9);
    printf("��                           ��");
    gotoxy(x + 30, y + 10);
    printf("����������������������������������������������������������");
    gotoxy(x + 30, y + 11);
    printf("��   c  ��   E  ��   �� ��  ��  ��");
    gotoxy(x + 30, y + 12);
    printf("����������������������������������������������������������");
    gotoxy(x + 30, y + 13);
    printf("��   7  ��   8  ��   9  ��   -  ��");
    gotoxy(x + 30, y + 14);
    printf("����������������������������������������������������������");
    gotoxy(x + 30, y + 15);
    printf("��   4  ��   5  ��   6  ��   +  ��");
    gotoxy(x + 30, y + 16);
    printf("����������������������������������������������������������");
    gotoxy(x + 30, y + 17);
    printf("��   1  ��   2  ��   3  ��   =  ��");
    gotoxy(x + 30, y + 18);
    printf("����������������������������������������������������������");
    gotoxy(x + 30, y + 19);
    printf("��             0             ��");
    gotoxy(x + 30, y + 20);
    printf("����������������������������������������������������������");
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
    while (1)  // q�ȴ����� ��ӵ�
    {
        if (_kbhit()) { //Ű�Է��� �ִ� ���  
            gotoxy(x + 3, y + 7);
            key = _getch(); //Ű���� ����

            if ((key == q) || (key == Q)) // q, Q �Է½� ����
            {
                system("cls"); //ȭ���� ����� 
                exit(0); //���α׷� ����
            }
            else if ((key == c) || (key == C)) // c, C �Է½� �ʱ�ȭ
            {
                var_reset(&n_s, &n1, &n2, &sign, &bit_n);
                system("cls");  // ���ȭ�� ����
                break;
            }
            else  // �߸� �Է����� �� �޽��� ���
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
        while (_kbhit()) _getch(); //Ű���۸� ���  
    }
}

void bin_add()
{
    int x, i;
    int* bin1 = malloc(bit_n * sizeof(int) * 4);//��Ʈ���� ���� ����ũ�� ����
    int* bin2 = malloc(bit_n * sizeof(int) * 4);
    int* bin3 = malloc(bit_n * sizeof(int) * 4);

    i = 0;
    while (n1 > 0)//�Է¹��� ���� 0�� �Ǳ� ������ 2�� ������ �������� �迭�� ������ �迭�� 2���� ����
    {
        bin1[i] = n1 % 2;
        n1 = n1 / 2;
        i = i + 1;
    }
    for (i = bit_n; i >= 0; i--)//������ ����� 2������ �ش� ��Ʈ �� ��ŭ�� ���̸� �������� 
    {
        if (bin1[i] == 1)  // �ش� ��Ʈ ������ 2������ ���̰� �� ª�� �� ���ڸ��� 0���� ä��
            bin1[i] = 1;
        else bin1[i] = 0;
    }
    i = 0;
    while (n2 > 0) {//�ι�° ���� �����ϰ� ����
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
    for (i = 0; i <= bit_n; i++)//�迭�� ����� �� ���� ���ϰ� x�� �����Ͽ� �������� bin3�� �����ϴ� ������� 2���� ���� ����
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
        printf(" (OVERFLOW)");//�迭1,2�� ��ȣ�� ������ ����� ��ȣ�� �ٸ��� �����÷ο�, �迭1,2�� ��Ʈ���� �Ѿ�� �����÷ο�
    free(bin1);
    free(bin2);
    free(bin3);
}

void sub()//������ ���� ��������� n2�� ����ȭ �Ͽ� ����� ���� ����
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

void multi() {//1024�Ѿ�� long long�� ������ �Ѿ�Ƿ� �����÷ο� �߻�

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
    for (i = 99; i >= 0; i--)//�Է¹��� ������ 2���� �迭�� ��ȯ
    {
        if (bin1[i] == 1)
            bin1[i] = 1;
        else bin1[i] = 0;
    }
    for (i = 0; i < 99; i++)//2���� �迭�� ���������� ����

    {
        h = pow(10, i);
        k += (bin1[i] * h);

    }
    gotoxy(x + 35, y + 7);
    printf("NUM1: ");
    printf("%d", k);
    i = 0;
    while (n2 > 0) {//�Է¹��� ������ 2���� �迭�� ��ȯ
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
    for (i = 0; i < 99; i++)//2���� �迭�� ���������� ����
    {
        m = pow(10, i);
        l += (bin2[i] * m);
    }
    gotoxy(x + 35, y + 8);
    printf("NUM2: ");
    printf("%d", l);
    while (l != 0)
    {
        digit = l % 10;//n2�� ���������� ��ȯ�� ��(l)�� 2�� ���� �������� digit�� ����
        if (digit == 1)//digit�� 1�̸� n1�� ���������� ��ȯ�� ��(k)�� factor�� ���ϰ� binaryproduct�Լ��� ���� ���� ����
        {
            k = k * factor;
            multiply = binaryproduct(k, multiply);
        }
        else//digit�� 0�̸� n1�� ���������� ��ȯ�� ��(k)�� factor�� ���ϰ� k�� ��ȯ�� l�� 10���� ���� �ڸ��� ����, factor���� 10���� ��ȯ�� �ڸ�������
            k = k * factor;
        l = l / 10;
        factor = 10;
    }
    gotoxy(x + 35, y + 9);
    printf("RES: ");
    printf("%d", multiply);
    if (l > 1111111111 || k > 1111111111 || multiply < 0) printf("(OVERFLOW)");
    //�Է°��̳� ������� 1024�� �Ѿ�� ������ ������� �Ѿ�Ƿ� overflow�߻�
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

    while (n1 > 0)//�Է¹��� ������ 2���� �迭�� ��ȯ
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
    for (i = 0; i < bit_n; i++)//2���� �迭�� ���������� k�� ����

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
    for (i = bit_n; i >= 0; i--)//�Է¹��� ������ 2���� �迭�� ��ȯ
    {
        if (bin2[i] == 1)
            bin2[i] = 1;
        else bin2[i] = 0;
    }
    for (i = 0; i < bit_n; i++)//2���� �迭�� ���������� �ӿ� ����
    {
        m = pow(10, i);
        l += (bin2[i] * m);
    }
    gotoxy(x + 35, y + 8);
    printf("NUM2: ");
    printf("%d", l);
    k1 = k;
    if (k > 1111111111) {//1024 �Ѿ�� �����÷ο�
        gotoxy(x + 34, y + 9);
        printf("RES: ");
        printf("(OVERFLOW)");
    }
    else {
        for (mask = l, i = 1; mask <= k1; mask <<= 1, i <<= 1);
        // �������� ���� �� �ִ� ���� ū ������ 2^n�� ã�� ���� 
        while (l <= k1) { // �������� �������� ������ �׸���

            if (k1 >= mask) {
                k1 -= mask;        // �������� ���� �ٽ� �������� ��� 
                cnt += i;        // ������ ���� ���� 
            }
            mask >>= 1;//��Ʈ�� 1��ŭ �̵�
            i >>= 1;//��Ʈ 1��ŭ �̵�
        }
        gotoxy(x + 35, y + 9);
        printf("RES: ");
        printf("%d", cnt);
    }
}

int binaryproduct(int binary1, int binary2)
{
    int i = 0, remainder = 0, sum[60];//������ �������� ��
    unsigned long long binaryprod = 0;

    while (binary1 != 0 || binary2 != 0)
    {
        sum[i++] = (binary1 % 10 + binary2 % 10 + remainder) % 2;//2(10)�� ���� �������� sum�� ����
        remainder = (binary1 % 10 + binary2 % 10 + remainder) / 2;//2�� ���� ���� remainder�� ��ȯ
        binary1 = binary1 / 10;//2�� ����(�ڸ��� ��ȯ)
        binary2 = binary2 / 10;//2�� ����(�ڸ��� ��ȯ)
    }
    if (remainder != 0)//�������� 0�� �ƴ϶�� sum�� �ٽ� ������ ����
        sum[i++] = remainder;
    --i;
    while (i >= 0)
        binaryprod = binaryprod * 10 + sum[i--];//2������ ��ȯ�Ͽ� ǥ��
    return binaryprod;
}

void var_reset(double* n_s, long* n1, long* n2, int* bit_n)
{
    *n_s = 0; *n1 = 0, * n2 = 0, bit_n = 0;
}

void conv1(double n_s)  // ���� �Ǽ� ������ȭ
{
    int i = 66, j, temp;
    char box[66] = { 0 };

    temp = (long)n_s; // temp�� �����κ��� �ִ´�.
    n_s = n_s - (double)temp; //n_s�� �Ҽ��κ��� �ִ´�.

    while (temp) box[--i] = '0' + temp % 2, temp /= 2; // �����κ��� ������ȭ�Ѵ�.

    temp = i;

    for (i = 0; i + temp < 66; i++)
        box[i] = box[i + temp];// �迭�� ó������ �̵���Ų��.

    temp = 65 - temp; // �Ҽ��� ��ġ�� temp�� �����Ѵ�.
    i = temp + 1; // �Ҽ������ϸ� ������ȭ �Ѵ�.

    gotoxy(x + 32, y + 8);
    while (n_s&& i < 66) n_s *= 2, box[i++] = '0' + (int)n_s, n_s -= (int)n_s;
    printf("B.N.: ");
    for (j = 0; i > j; j++)
        printf(temp == j ? "%c." : "%c", box[j]); //�迭 ���
}

void conv2()  // ���� ���� ������ȭ
{
    int binary1, binary2, count1, count2, i = 0, comp2, j = 0;
    int bin1[100], bin2[100];

    comp2 = n1 + 1;//2�� ���� ǥ������ �Է� �������� +1
    n1 = -n1;
    comp2 = -comp2;

    while (n1 > 0)//�Է¹��� ���� 0�� �Ǳ� ������ 2�� ������ �������� �迭�� ������ �迭�� 2���� ����
    {
        binary1 = n1 % 2;
        bin1[i] = binary1;
        n1 = n1 / 2;
        i += 1;
    }

    count1 = i - 1;
    gotoxy(x + 32, y + 7);
    printf("1's C : ");//��ȯ�� �迭�� 1�� 0���� 0�� 1�� �ٲ㼭 1�� ���� ǥ��
    for (i = count1; i >= 0; i--) {
        if (bin1[i] == 1) bin1[i] = 0;
        else bin1[i] = 1;
        printf("%d", bin1[i]);
    }
    while (comp2 > 0)//�Է¹�����+1�� 2������ ��ȯ
    {
        binary2 = comp2 % 2;
        bin2[j] = binary2;
        comp2 = comp2 / 2;
        j += 1;
    }
    count2 = j - 1;

    gotoxy(x + 32, y + 8);
    printf("2's C : ");//��ȯ�� �迭�� 1�� 0���� 0�� 1�� �ٲ㼭 2�� ���� ǥ��
    for (j = count2; j >= 0; j--) {
        if (bin2[j] == 1) bin2[j] = 0;
        else bin2[j] = 1;
        printf("%d", bin2[j]);
    }

}