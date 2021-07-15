#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("\n----- [최문형]  [2020039004] -----\n");

    int list[5];
    int *plist[5] = {NULL,};


    plist[0] = (int *)malloc(sizeof(int)); 
    //힙 영역에 int형 크기만큼 할당하고, 할당된 주소를 plist[0]에 넣는다.

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;

    printf("value of list[0] = %d\n", list[0]);         //list[0]에 들어있는 값을 출력한다.
    printf("address of list[0]      = %p\n", &list[0]); //list[0]의 주솟값을 출력한다.
    printf("value of list           = %p\n", list);     //&list[0] = list 이므로 list[0]의 주솟값을 출력한다.
    printf("address of list (&list) = %p\n", &list);    //&list[0] = &list 이므로 list[0]의 주솟값을 출력한다.

    printf("---------------------------------------\n\n");

    printf("value of list[1]   = %d\n", list[1]);     //list[1]에 들어있는 값을 출력한다.
    printf("address of list[1] = %p\n", &list[1]);    //list[1]의 주솟값을 출력한다.
    printf("value of *(list+1) = %d\n", *(list + 1)); //list + 1 = &list[0] + 1 * sizeof(int) 이므로 list[1]에 들어있는 값을 출력한다.
    printf("address of list+1  = %p\n", list+1);      //list+1 = &list[0] + 1 * sizeof(int)이므로 list[1]의 주솟값을 출력한다.

    printf("---------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]); //plist[0]에 200을 넣었으므로 200을 출력한다.
    printf("&plist[0]          = %p\n", &plist[0]); //plist[0]의 주솟값을 출력한다.
    printf("&plist             = %p\n", &plist);    //&plist[0] = &plist이므로 plist[0]의 주솟값을 출력한다.
    printf("plist              = %p\n", plist);     //&plist[0] = plist이므로 plist[0]의 주솟값을 출력한다.
    printf("plist[0]           = %p\n", plist[0]);  //plist[0]에 들어있는 주솟값을 출력한다.
    printf("plist[1]           = %p\n", plist[1]);  //plist[0]에만 주소를 할당했으므로 NULL값이 출력된다.
    printf("plist[2]           = %p\n", plist[2]);  //plist[0]에만 주소를 할당했으므로 NULL값이 출력된다.
    printf("plist[3]           = %p\n", plist[3]);  //plist[0]에만 주소를 할당했으므로 NULL값이 출력된다.
    printf("plist[4]           = %p\n", plist[4]);  //plist[0]에만 주소를 할당했으므로 NULL값이 출력된다.


    free(plist[0]); //plist[0]이 가리키고 있는 힙 영역에 할당된 공간을 해제시켜준다. 
}