#include <stdio.h>

#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;
int main(void)
{
    printf("\n----- [최문형]  [2020039004] -----\n");

    for(i=0; i < MAX_SIZE; i++)
        input[i] = i;

    /* for checking call by reference */
    printf("address of input = %p\n", input);   //input = &input[0]이므로 input[0]의 주솟값을 출력한다.

    answer = sum(input, MAX_SIZE);     
    printf("The sum is: %f\n", answer);         //0부터 99까지 더한 값을 출력한다.
}

float sum(float list[], int n)
{
    printf("value of list = %p\n", list);       //input의 배열을 list가 받았기 때문에 input[0]의 주솟값이 출력된다.
    printf("address of list = %p\n\n", &list);  //&list = &list[0]이므로 list[0]의 주솟값을 출력한다.

    int i;
    float tempsum = 0;
    for(i = 0; i < n; i++)  //n = MAX_SIZE이므로 반복문은 0~99 까지 반복하게 된다.
        tempsum += list[i]; 

    return tempsum; 
}