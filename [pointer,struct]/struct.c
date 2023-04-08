#include <stdio.h>

struct student1 {
    char lastName;
    int  studentId;
    char grade;
};

typedef struct {
    char lastName;
    int  studentId;
    char grade;
} student2;


int main() {
    printf("\n----- [최문형]  [2020039004] -----\n");

    struct student1 st1 = {'A', 100, 'A'};  //typedef로 선언하지 않았기 때문에 앞에 'struct'을 반드시 적어줘야 한다.

    printf("st1.lastName = %c\n", st1.lastName);    //구조체 변수 st1에 들어있는 lastName의 값을 출력한다.
    printf("st1.studentId = %d\n", st1.studentId);  //구조체 변수 st1에 들어있는 studentId의 값을 출력한다.
    printf("st1.grade = %c\n", st1.grade);          //구조체 변수 st1에 들어있는 grade의 값을 출력한다.


    student2 st2 = {'B', 200, 'B'}; //위와 달리 typedef로 구조체 데이터 타입을 생성했기 때문에 앞에 'struct'을 적지 않아도 된다.

    printf("\nst2.lastName = %c\n", st2.lastName);  //구조체 변수 st2에 들어있는 lastName의 값을 출력한다.
    printf("st2.studentId = %d\n", st2.studentId);  //구조체 변수 st2에 들어있는 studentId의 값을 출력한다.
    printf("st2.grade = %c\n", st2.grade);          //구조체 변수 st2에 들어있는 grade의 값을 출력한다.


    student2 st3;

    st3 = st2;  //st3의 값들을 st2의 값들로 바꿔준다. (구조치환)

    printf("\nst3.lastName = %c\n", st3.lastName);  //구조체 변수 st3에 들어있는 lastName의 값을 출력한다.
    printf("st3.studentId = %d\n", st3.studentId);  //구조체 변수 st3에 들어있는 studentId의 값을 출력한다.
    printf("st3.grade = %c\n", st3.grade);          //구조체 변수 st3에 들어있는 grade의 값을 출력한다.

    /* equality test */
    /*
    if (st3 == st2)     //컴파일러마다 다를 수도 있지만 gcc에선 직접 비교할 순 없음  
        printf("equal\n");
    else
        printf("not equal\n");
    */


   return 0;
}