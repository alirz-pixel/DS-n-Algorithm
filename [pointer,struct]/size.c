#include<stdio.h>
#include<stdlib.h>

int main()
{
    printf("\n----- [�ֹ���]  [2020039004] -----\n");

    int **x;

    printf("sizeof(x) = %lu\n", sizeof(x));     //���� ������ ���� x�� �޸� ũ�⸦ ����Ѵ�.
    printf("sizeof(*x) = %lu\n", sizeof(*x));   //x�� �� �� ������ �߱� ������ int�� ������ ������ �޸� ũ�⸦ ����Ѵ�.
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //x�� �� �� ������ �߱� ������ int�� ������ �޸� ũ�⸦ ����Ѵ�.
}