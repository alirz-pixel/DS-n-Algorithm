#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [최문형]  [2020039004] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix_create = (int**)malloc(row * sizeof(int*));

    /* check post conditions */
    if (matrix_create == NULL)
    {
        /* proper actions for unexpected conditions */
        printf("Insufficient memory!\n");
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        matrix_create[i] = (int*)malloc(col * sizeof(int));

        if (matrix_create[i] == NULL)
        {
            /* proper actions for unexpected conditions */
            printf("Insufficient memory!\n");
            return NULL;
        }
    }

    return matrix_create;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++)         // 0 ~ row 만큼 반복한다.          
    {
        for(int j = 0; j < col; j++)     // 0 ~ col 만큼 반복한다.
            printf("%-4d", matrix[i][j]);// 필드 폭을 4칸 확보하고, 왼쪽 정렬한다.

        printf("\n");
    }

    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++)   // 0 ~ row 만큼 반복한다.
        free(matrix[i]);            // 2차원 배열의 가로 공간 메모리 해제

    free(matrix);                   // 2차원 배열의 세로 공간 메모리 해제
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++)        // 0 ~ row 만큼 반복한다.
        for(int j = 0; j < col; j++)    // 0 ~ col 만큼 반복한다.
            matrix[i][j] = rand() % 20; // 행렬의 성분값을 0 ~ 19사이의 값을 랜덤으로 부여한다.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_add = create_matrix(row, col);

    if (matrix_add == NULL) //만약, 메모리가 부족한 경우
    {
        /* proper actions for unexpected conditions */
        printf("메모리 부족으로 addition_matrix 함수를 수행할 수 없습니다.\n");
        return -1;  //에러가 발생했으므로 -1을 반환한다.
    }

    for (int i = 0; i < row; i++)       // 0 ~ row 만큼 반복한다.
        for (int j = 0; j < col; j++)   // 0 ~ col 만큼 반복한다.
            matrix_add[i][j] = matrix_a[i][j] + matrix_b[i][j]; // 행렬의 합연산 실행하는 코드

    print_matrix(matrix_add, row, col); // 연산이 끝났으므로 결과값을 프린트한다.

    free_matrix(matrix_add, row, col);  // 연산이 종료되었으므로 할당했던 메모리를 해제한다.

    return 0;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); // A - B 연산 결과를 담을 변수 선언

    if (matrix_sub == NULL) //만약, 메모리가 부족한 경우
    {
        /* proper actions for unexpected conditions */
        printf("메모리 부족으로 subtraction_matrix 함수를 수행할 수 없습니다.\n");
        return -1;  //에러가 발생했으므로 -1을 반환한다.
    }

    for (int i = 0; i < row; i++)       // 0 ~ row 만큼 반복한다.
        for (int j = 0; j < col; j++)   // 0 ~ col 만큼 반복한다.
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // 행렬의 뺄셈 연산 실행하는 코드

    print_matrix(matrix_sub, row, col); // 연산이 끝났으므로 결과값을 프린트한다.

    free_matrix(matrix_sub, row, col);  // 연산이 종료되었으므로 할당했던 메모리를 해제한다.
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{

}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{

}

