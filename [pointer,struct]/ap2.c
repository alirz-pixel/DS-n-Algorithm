#include <stdio.h>
#include <stdlib.h>

int main ()
{
    printf("\n----- [�ֹ���]  [2020039004] -----\n");
    
    int list[5];
    int *plist[5];

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int));           
    //�� ������ int�� ũ�⸸ŭ�� ������ �Ҵ��ϰ�, �Ҵ�� �ּҸ� plist[0]�� �־��ش�.

    printf("list[0] \t= %d\n", list[0]);            //list[0]�� ����ִ� ���� ����Ѵ�.
    printf("address of list \t= %p\n", list);       //list[0]�� �ּڰ��� ����Ѵ�.
    printf("address of list[0] \t= %p\n", &list[0]);//list[0]�� �ּڰ��� ����Ѵ�.
    printf("address of list + 0 \t= %p\n", list+0); //list+0 = &list[0] + 0 * sizeof(int)�� ���� ����Ѵ�.
    printf("address of list + 1 \t= %p\n", list+1); //list+1 = &list[0] + 1 * sizeof(int)�� ���� ����Ѵ�.
    printf("address of list + 2 \t= %p\n", list+2); //list+2 = &list[0] + 2 * sizeof(int)�� ���� ����Ѵ�.
    printf("address of list + 3 \t= %p\n", list+3); //list+3 = &list[0] + 3 * sizeof(int)�� ���� ����Ѵ�.
    printf("address of list + 4 \t= %p\n", list+4); //list+4 = &list[0] + 4 * sizeof(int)�� ���� ����Ѵ�.
    printf("address of list[4] \t= %p\n", &list[4]);//list[4]�� �ּڰ��� ����Ѵ�.
    
    free(plist[0]); //plist[0]�� ����Ű�� �ִ� �� ������ �Ҵ�� ������ ���������ش�. 
}