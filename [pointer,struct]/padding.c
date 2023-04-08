#include <stdio.h>

struct student {
    char lastName[13];  /* 13 bytes */
    int studentId;      /* 4 bytes */
    short grade;        /* 2 bytes */
};

int main()
{
    printf("\n----- [최문형]  [2020039004] -----\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student));  //struct student의 메모리 크기를 출력한다.
    printf("size of int = %ld\n", sizeof(int));                 //int형 변수의 메모리 크기를 출력한다.
    printf("size of short = %ld\n", sizeof(short));             //short형 변수의 메모리 크기를 출력한다.

    //gcc 컴파일러는 padding을 하고 있기 때문에
    //배열 변수 lastName이 차지하는 실제 메모리는 13 bytes 이지만 padding값 때문에 16 bytes를 차지하게 된다.
    //위와 마찬가지로 short형 변수 grade가 차지하는 실제 메모리는 2 bytes 이지만 padding 값 때문에 4 bytes를 차지하게 된다.
    //따라서 sizeof(struct student)를 출력하게 되면 16+4+4 = 24 bytes가 출력된다.

    return 0;
}