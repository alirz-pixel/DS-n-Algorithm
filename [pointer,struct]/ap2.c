#include <stdio.h>
#include <stdlib.h>

int main ()
{
    printf("\n----- [최문형]  [2020039004] -----\n");
    
    int list[5];
    int *plist[5];

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int));           
    //힙 영영에 int형 크기만큼의 공간을 할당하고, 할당된 주소를 plist[0]에 넣어준다.

    printf("list[0] \t= %d\n", list[0]);            //list[0]에 들어있는 값을 출력한다.
    printf("address of list \t= %p\n", list);       //list[0]의 주솟값을 출력한다.
    printf("address of list[0] \t= %p\n", &list[0]);//list[0]의 주솟값을 출력한다.
    printf("address of list + 0 \t= %p\n", list+0); //list+0 = &list[0] + 0 * sizeof(int)의 값을 출력한다.
    printf("address of list + 1 \t= %p\n", list+1); //list+1 = &list[0] + 1 * sizeof(int)의 값을 출력한다.
    printf("address of list + 2 \t= %p\n", list+2); //list+2 = &list[0] + 2 * sizeof(int)의 값을 출력한다.
    printf("address of list + 3 \t= %p\n", list+3); //list+3 = &list[0] + 3 * sizeof(int)의 값을 출력한다.
    printf("address of list + 4 \t= %p\n", list+4); //list+4 = &list[0] + 4 * sizeof(int)의 값을 출력한다.
    printf("address of list[4] \t= %p\n", &list[4]);//list[4]의 주솟값을 출력한다.
    
    free(plist[0]); //plist[0]이 가리키고 있는 힙 영역에 할당된 공간을 해제시켜준다. 
}