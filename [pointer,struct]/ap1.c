#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("\n----- [�ֹ���]  [2020039004] -----\n");

    int list[5];
    int *plist[5] = {NULL,};


    plist[0] = (int *)malloc(sizeof(int)); 
    //�� ������ int�� ũ�⸸ŭ �Ҵ��ϰ�, �Ҵ�� �ּҸ� plist[0]�� �ִ´�.

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;

    printf("value of list[0] = %d\n", list[0]);         //list[0]�� ����ִ� ���� ����Ѵ�.
    printf("address of list[0]      = %p\n", &list[0]); //list[0]�� �ּڰ��� ����Ѵ�.
    printf("value of list           = %p\n", list);     //&list[0] = list �̹Ƿ� list[0]�� �ּڰ��� ����Ѵ�.
    printf("address of list (&list) = %p\n", &list);    //&list[0] = &list �̹Ƿ� list[0]�� �ּڰ��� ����Ѵ�.

    printf("---------------------------------------\n\n");

    printf("value of list[1]   = %d\n", list[1]);     //list[1]�� ����ִ� ���� ����Ѵ�.
    printf("address of list[1] = %p\n", &list[1]);    //list[1]�� �ּڰ��� ����Ѵ�.
    printf("value of *(list+1) = %d\n", *(list + 1)); //list + 1 = &list[0] + 1 * sizeof(int) �̹Ƿ� list[1]�� ����ִ� ���� ����Ѵ�.
    printf("address of list+1  = %p\n", list+1);      //list+1 = &list[0] + 1 * sizeof(int)�̹Ƿ� list[1]�� �ּڰ��� ����Ѵ�.

    printf("---------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]); //plist[0]�� 200�� �־����Ƿ� 200�� ����Ѵ�.
    printf("&plist[0]          = %p\n", &plist[0]); //plist[0]�� �ּڰ��� ����Ѵ�.
    printf("&plist             = %p\n", &plist);    //&plist[0] = &plist�̹Ƿ� plist[0]�� �ּڰ��� ����Ѵ�.
    printf("plist              = %p\n", plist);     //&plist[0] = plist�̹Ƿ� plist[0]�� �ּڰ��� ����Ѵ�.
    printf("plist[0]           = %p\n", plist[0]);  //plist[0]�� ����ִ� �ּڰ��� ����Ѵ�.
    printf("plist[1]           = %p\n", plist[1]);  //plist[0]���� �ּҸ� �Ҵ������Ƿ� NULL���� ��µȴ�.
    printf("plist[2]           = %p\n", plist[2]);  //plist[0]���� �ּҸ� �Ҵ������Ƿ� NULL���� ��µȴ�.
    printf("plist[3]           = %p\n", plist[3]);  //plist[0]���� �ּҸ� �Ҵ������Ƿ� NULL���� ��µȴ�.
    printf("plist[4]           = %p\n", plist[4]);  //plist[0]���� �ּҸ� �Ҵ������Ƿ� NULL���� ��µȴ�.


    free(plist[0]); //plist[0]�� ����Ű�� �ִ� �� ������ �Ҵ�� ������ ���������ش�. 
}