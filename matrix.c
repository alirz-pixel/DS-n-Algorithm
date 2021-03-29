#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 19

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

    if (matrix_a == NULL || matrix_b == NULL || matrix_a_t == NULL) {return -1;} // 메모리 할당을 받지 못했을 시, 비정상 종료

    do{
        // 메뉴 창 생성
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        // command 입력 받기
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

    }while(command != 'q' && command != 'Q'); // Q가 입력되면 프로그램을 종료한다.

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) // i x j 행렬에서 i와 j 중 하나라도 음수값이 들어온 경우.
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix_create = (int**)malloc(row * sizeof(int*));

    /* check post conditions */
    if (matrix_create == NULL) // 동적할당에서 문제가 발생한 경우
    {
        /* proper actions for unexpected conditions */
        printf("Insufficient memory!\n");
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        matrix_create[i] = (int*)malloc(col * sizeof(int));

        if (matrix_create[i] == NULL) // 동적할당에서 문제가 발생한 경우
        {
            /* proper actions for unexpected conditions */
            printf("Insufficient memory!\n");
 
            // 메모리를 할당하던 도중 오류가 생겼기 때문에
            // 오류가 생기기 전까지 할당한 메모리를 해제 해야함.
            free_matrix(matrix_create, i, col);
            return NULL;
        }
    }

    return matrix_create;   // 동적할당 된 주소값을 리턴한다.
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
    matrix = NULL;  // 다른 함수에서 후처리 검사를 하기 위한 NULL값 대입

    return 1; // 함수 정상 종료 코드
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++)        // 0 ~ row 만큼 반복한다.
        for(int j = 0; j < col; j++)    // 0 ~ col 만큼 반복한다.
        {
            matrix[i][j] = rand() % (MAX + 1); // 행렬의 성분값을 0 ~ 19사이의 값을 랜덤으로 부여한다.
            
            if (matrix[i][j] > MAX || matrix[i][j] < 0)  // 행렬의 성분 값이 제대로 부여되지 않았다면
            {
                printf("행렬의 성분 값이 제대로 부여되지 않았습니다.\n");
                return -1; // 함수의 비정상 종료를 의미함.
            } 
        }
    
    return 1; // 함수 정상 종료 코드
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_add = create_matrix(row, col); // A + B 연산 결과를 담을 변수 선언

    if (matrix_add == NULL) //만약, 메모리를 할당받지 못한 경우
    {
        /* proper actions for unexpected conditions */
        printf("메모리 할만 문제로 addition_matrix 함수를 수행할 수 없습니다.\n");
        return -1;  //에러가 발생했으므로 -1을 반환한다.
    }

    for (int i = 0; i < row; i++)       // 0 ~ row 만큼 반복한다.
        for (int j = 0; j < col; j++)   // 0 ~ col 만큼 반복한다.
        {
            matrix_add[i][j] = matrix_a[i][j] + matrix_b[i][j]; // 행렬의 합연산 실행하는 코드

            if (matrix_add[i][j] > (MAX + MAX) || matrix_add < 0) // matrix_add는 38( 19 + 19 )을 넘지 않으며, 0보다 작을 순 없으므로
            {
                printf("addition_matrix 함수에서 덧셈을 수행하던 도중 오류가 발생하였습니다.\n");
                return -1; // 함수의 비정상 종료를 의미함.
            }
        }

    print_matrix(matrix_add, row, col); // 연산이 끝났으므로 결과값을 프린트한다.

    // 연산이 종료되었으므로 할당했던 메모리를 해제한다. 
    // 만약, free_matrix 함수가 제대로 시행되지 않았다면, 메모리 해제에 대한 문제가 발생한 것이므로 -1을 리턴해준다.
    if (free_matrix(matrix_add, row, col) != 1) 
    {
        printf("addition_matrix 함수에서 [matrix_add]의 메모리 해제에 대한 오류가 발생하였습니다.\n");
        return -1; // 함수의 비정상 종료를 의미함.
    }

    return 1;  // 함수 정상 종료 코드
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); // A - B 연산 결과를 담을 변수 선언

    if (matrix_sub == NULL) //만약, 메모리를 할당받지 못한 경우
    {
        /* proper actions for unexpected conditions */
        printf("메모리 할당 문제로 subtraction_matrix 함수를 수행할 수 없습니다.\n");
        return -1;  //에러가 발생했으므로 -1을 반환한다.
    }

    for (int i = 0; i < row; i++)       // 0 ~ row 만큼 반복한다.
        for (int j = 0; j < col; j++)   // 0 ~ col 만큼 반복한다.
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // 행렬의 뺄셈 연산 실행하는 코드

            if (matrix_sub[i][j] < ((-1) * MAX) || matrix_sub[i][j] > MAX) // 뺄셈 연산 후의 최솟값(0 - 19)과 최댓값(19 - 0)을 고려한 코드
            {
                printf("subtraction_matrix 함수에서 뺄셈을 수행하던 도중 오류가 발생하였습니다.\n");
                return -1; // 함수의 비정상 종료를 의미함.
            }
        }

    print_matrix(matrix_sub, row, col); // 연산이 끝났으므로 결과값을 프린트한다.

    // 연산이 종료되었으므로 할당했던 메모리를 해제한다. 
    // 만약, free_matrix 함수가 제대로 시행되지 않았다면, 메모리 해제에 대한 문제가 발생한 것이므로 -1을 리턴해준다.
    if (free_matrix(matrix_sub, row, col) != 1) 
    {
        printf("subtraction_matrix 함수에서 [matrix_sub]의 메모리 해제에 대한 오류가 발생하였습니다.\n");
        return -1; // 함수의 비정상 종료를 의미함.
    }

    return 1;  // 함수 정상 종료 코드
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    for (int i = 0; i < row; i++)           // 0 ~ row(실제값 : col) 만큼 반복한다.
        for (int j = 0; j < col; j++)       // 0 ~ col(실제값 : row) 만큼 반복한다.
        {
            matrix_t[i][j] = matrix[j][i];  // 행렬 A의 행과 열을 바꿔 대입하면서 전치행렬 T를 구한다.

            if (matrix_t[i][j] > MAX || matrix_t < 0)
            {
                printf("transpose_matrix 함수에서 행렬의 성분 값이 최댓값 또는 최솟값을 벗어나여 오류가 발생하였습니다.\n");
                return -1; // 함수의 비정상 종료를 의미함.
            } 
        }

    return 1; // 함수 정상 종료 코드
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int result; // matrix_mutl에 각 요소의 행렬 곱 연산 결과를 넣기 위한 임시 변수 선언
    int** matrix_multi = create_matrix(row, row); 
    // ixj 행렬 * jxi 행렬의 연산 결과는 ixi 행렬의 형태가 나오므로 ixi 행렬로 matrix_multi를 만든다.

    if (matrix_multi == NULL) // 만약, 메모리를 할당받지 못한 경우
    {
        /* proper actions for unexpected conditions */
        printf("메모리 할당 문제로 multiply_matrix 함수를 수행할 수 없습니다.\n");
        return -1;  //에러가 발생했으므로 -1을 반환한다.
    }

    for (int i_row = 0; i_row < row; i_row++)
    {
        for (int j_col = 0; j_col < row; j_col++)
        {
            result = 0;
            
            for (int i = 0; i < row; i++)
                result += (matrix_a[i_row][i] * matrix_t[i][j_col]); // A * T 를 수행하는 코드

            matrix_multi[i_row][j_col] = result; //연산결과를 matrix_multi에 대입하는 코드

            // 행연산을 통해 나온 값이 음수가 나올 수 없는 점과 최댓값을 넘는 경우를 고려한 예외 코드
            if (matrix_multi[i_row][j_col] > (MAX * MAX * col) || matrix_multi[i_row][j_col] < 0) 
            {
                printf("multiply_matrix 함수에서 A * T 를 수행하던 도중 오류가 발생하였습니다.\n");
                return -1; // 함수의 비정상 종료를 의미함.
            }
        }
    }

    print_matrix(matrix_multi, row, row);

    // 연산이 종료되었으므로 할당했던 메모리를 해제한다. 
    // 만약, free_matrix 함수가 제대로 시행되지 않았다면, 메모리 해제에 대한 문제가 발생한 것이므로 -1을 리턴해준다.
    if (free_matrix(matrix_multi, row, row) != 1) 
    {
        printf("multiply_matrix 함수에서 [matrix_multi]의 메모리 해제에 대한 오류가 발생하였습니다.\n");
        return -1; // 함수의 비정상 종료를 의미함.
    }

    return 1; // 함수 정상 종료 코드
}

