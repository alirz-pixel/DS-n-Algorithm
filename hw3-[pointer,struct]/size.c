#include<stdio.h>
#include<stdlib.h>

int main()
{
    printf("\n----- [최문형]  [2020039004] -----\n");

    int **x;

    printf("sizeof(x) = %lu\n", sizeof(x));     //이중 포인터 변수 x의 메모리 크기를 출력한다.
    printf("sizeof(*x) = %lu\n", sizeof(*x));   //x를 한 번 역참조 했기 때문에 int형 포인터 변수의 메모리 크기를 출력한다.
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //x를 두 번 역참조 했기 때문에 int형 변수의 메모리 크기를 출력한다.
}