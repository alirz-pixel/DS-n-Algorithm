#include <stdio.h>

void print1 (int *ptr, int rows);

int main()
{
    printf("\n----- [최문형]  [2020039004] -----\n");

    int one[] = {0, 1, 2, 3, 4};

    printf("one     = %p\n", one);      //one = &one[0]이므로 one[0]의 주솟값을 출력한다.
    printf("&one    = %p\n", &one);     //&one = &one[0]이므로 one[0]의 주솟값을 출력한다.
    printf("&one[0] = %p\n", &one[0]);  //one[0]의 주솟값을 출력한다.
    printf("\n");

    print1(&one[0], 5);

    return 0;
}

void print1 (int *ptr, int rows)
{/* print out a one-dimensional array using a pointer */

    int i;
    printf ("Address \t Contents\n");
    for (i = 0; i < rows; i++)  //rows == 5 이므로 반복문은 0~4까지 반복하게 된다.
        printf("%p \t  %5d\n", ptr + i, *(ptr + i));    //포인터 ptr은 배열 one을 가리키고 있으므로 one[0] ~ one[4] 까지 출력하게 된다.
    printf("\n");
}