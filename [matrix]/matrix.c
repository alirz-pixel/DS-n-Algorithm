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
    printf("[----- [�ֹ���]  [2020039004] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL || matrix_a_t == NULL) {return -1;} // �޸� �Ҵ��� ���� ������ ��, ������ ����

    do{
        // �޴� â ����
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        // command �Է� �ޱ�
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

    }while(command != 'q' && command != 'Q'); // Q�� �ԷµǸ� ���α׷��� �����Ѵ�.

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) // i x j ��Ŀ��� i�� j �� �ϳ��� �������� ���� ���.
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix_create = (int**)malloc(row * sizeof(int*));

    /* check post conditions */
    if (matrix_create == NULL) // �����Ҵ翡�� ������ �߻��� ���
    {
        /* proper actions for unexpected conditions */
        printf("Insufficient memory!\n");
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        matrix_create[i] = (int*)malloc(col * sizeof(int));

        if (matrix_create[i] == NULL) // �����Ҵ翡�� ������ �߻��� ���
        {
            /* proper actions for unexpected conditions */
            printf("Insufficient memory!\n");
 
            // �޸𸮸� �Ҵ��ϴ� ���� ������ ����� ������
            // ������ ����� ������ �Ҵ��� �޸𸮸� ���� �ؾ���.
            free_matrix(matrix_create, i, col);
            return NULL;
        }
    }

    return matrix_create;   // �����Ҵ� �� �ּҰ��� �����Ѵ�.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++)         // 0 ~ row ��ŭ �ݺ��Ѵ�.          
    {
        for(int j = 0; j < col; j++)     // 0 ~ col ��ŭ �ݺ��Ѵ�.
            printf("%-4d", matrix[i][j]);// �ʵ� ���� 4ĭ Ȯ���ϰ�, ���� �����Ѵ�.

        printf("\n");
    }

    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++)   // 0 ~ row ��ŭ �ݺ��Ѵ�.
        free(matrix[i]);            // 2���� �迭�� ���� ���� �޸� ����

    free(matrix);                   // 2���� �迭�� ���� ���� �޸� ����
    matrix = NULL;  // �ٸ� �Լ����� ��ó�� �˻縦 �ϱ� ���� NULL�� ����

    return 1; // �Լ� ���� ���� �ڵ�
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++)        // 0 ~ row ��ŭ �ݺ��Ѵ�.
        for(int j = 0; j < col; j++)    // 0 ~ col ��ŭ �ݺ��Ѵ�.
        {
            matrix[i][j] = rand() % (MAX + 1); // ����� ���а��� 0 ~ 19������ ���� �������� �ο��Ѵ�.
            
            if (matrix[i][j] > MAX || matrix[i][j] < 0)  // ����� ���� ���� ����� �ο����� �ʾҴٸ�
            {
                printf("����� ���� ���� ����� �ο����� �ʾҽ��ϴ�.\n");
                return -1; // �Լ��� ������ ���Ḧ �ǹ���.
            } 
        }
    
    return 1; // �Լ� ���� ���� �ڵ�
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_add = create_matrix(row, col); // A + B ���� ����� ���� ���� ����

    if (matrix_add == NULL) //����, �޸𸮸� �Ҵ���� ���� ���
    {
        /* proper actions for unexpected conditions */
        printf("�޸� �Ҹ� ������ addition_matrix �Լ��� ������ �� �����ϴ�.\n");
        return -1;  //������ �߻������Ƿ� -1�� ��ȯ�Ѵ�.
    }

    for (int i = 0; i < row; i++)       // 0 ~ row ��ŭ �ݺ��Ѵ�.
        for (int j = 0; j < col; j++)   // 0 ~ col ��ŭ �ݺ��Ѵ�.
        {
            matrix_add[i][j] = matrix_a[i][j] + matrix_b[i][j]; // ����� �տ��� �����ϴ� �ڵ�

            if (matrix_add[i][j] > (MAX + MAX) || matrix_add < 0) // matrix_add�� 38( 19 + 19 )�� ���� ������, 0���� ���� �� �����Ƿ�
            {
                printf("addition_matrix �Լ����� ������ �����ϴ� ���� ������ �߻��Ͽ����ϴ�.\n");
                return -1; // �Լ��� ������ ���Ḧ �ǹ���.
            }
        }

    print_matrix(matrix_add, row, col); // ������ �������Ƿ� ������� ����Ʈ�Ѵ�.

    // ������ ����Ǿ����Ƿ� �Ҵ��ߴ� �޸𸮸� �����Ѵ�. 
    // ����, free_matrix �Լ��� ����� ������� �ʾҴٸ�, �޸� ������ ���� ������ �߻��� ���̹Ƿ� -1�� �������ش�.
    if (free_matrix(matrix_add, row, col) != 1) 
    {
        printf("addition_matrix �Լ����� [matrix_add]�� �޸� ������ ���� ������ �߻��Ͽ����ϴ�.\n");
        return -1; // �Լ��� ������ ���Ḧ �ǹ���.
    }

    return 1;  // �Լ� ���� ���� �ڵ�
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); // A - B ���� ����� ���� ���� ����

    if (matrix_sub == NULL) //����, �޸𸮸� �Ҵ���� ���� ���
    {
        /* proper actions for unexpected conditions */
        printf("�޸� �Ҵ� ������ subtraction_matrix �Լ��� ������ �� �����ϴ�.\n");
        return -1;  //������ �߻������Ƿ� -1�� ��ȯ�Ѵ�.
    }

    for (int i = 0; i < row; i++)       // 0 ~ row ��ŭ �ݺ��Ѵ�.
        for (int j = 0; j < col; j++)   // 0 ~ col ��ŭ �ݺ��Ѵ�.
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // ����� ���� ���� �����ϴ� �ڵ�

            if (matrix_sub[i][j] < ((-1) * MAX) || matrix_sub[i][j] > MAX) // ���� ���� ���� �ּڰ�(0 - 19)�� �ִ�(19 - 0)�� ����� �ڵ�
            {
                printf("subtraction_matrix �Լ����� ������ �����ϴ� ���� ������ �߻��Ͽ����ϴ�.\n");
                return -1; // �Լ��� ������ ���Ḧ �ǹ���.
            }
        }

    print_matrix(matrix_sub, row, col); // ������ �������Ƿ� ������� ����Ʈ�Ѵ�.

    // ������ ����Ǿ����Ƿ� �Ҵ��ߴ� �޸𸮸� �����Ѵ�. 
    // ����, free_matrix �Լ��� ����� ������� �ʾҴٸ�, �޸� ������ ���� ������ �߻��� ���̹Ƿ� -1�� �������ش�.
    if (free_matrix(matrix_sub, row, col) != 1) 
    {
        printf("subtraction_matrix �Լ����� [matrix_sub]�� �޸� ������ ���� ������ �߻��Ͽ����ϴ�.\n");
        return -1; // �Լ��� ������ ���Ḧ �ǹ���.
    }

    return 1;  // �Լ� ���� ���� �ڵ�
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    for (int i = 0; i < row; i++)           // 0 ~ row(������ : col) ��ŭ �ݺ��Ѵ�.
        for (int j = 0; j < col; j++)       // 0 ~ col(������ : row) ��ŭ �ݺ��Ѵ�.
        {
            matrix_t[i][j] = matrix[j][i];  // ��� A�� ��� ���� �ٲ� �����ϸ鼭 ��ġ��� T�� ���Ѵ�.

            if (matrix_t[i][j] > MAX || matrix_t < 0)
            {
                printf("transpose_matrix �Լ����� ����� ���� ���� �ִ� �Ǵ� �ּڰ��� ����� ������ �߻��Ͽ����ϴ�.\n");
                return -1; // �Լ��� ������ ���Ḧ �ǹ���.
            } 
        }

    return 1; // �Լ� ���� ���� �ڵ�
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int result; // matrix_mutl�� �� ����� ��� �� ���� ����� �ֱ� ���� �ӽ� ���� ����
    int** matrix_multi = create_matrix(row, row); 
    // ixj ��� * jxi ����� ���� ����� ixi ����� ���°� �����Ƿ� ixi ��ķ� matrix_multi�� �����.

    if (matrix_multi == NULL) // ����, �޸𸮸� �Ҵ���� ���� ���
    {
        /* proper actions for unexpected conditions */
        printf("�޸� �Ҵ� ������ multiply_matrix �Լ��� ������ �� �����ϴ�.\n");
        return -1;  //������ �߻������Ƿ� -1�� ��ȯ�Ѵ�.
    }

    for (int i_row = 0; i_row < row; i_row++)
    {
        for (int j_col = 0; j_col < row; j_col++)
        {
            result = 0;
            
            for (int i = 0; i < col; i++)
                result += (matrix_a[i_row][i] * matrix_t[i][j_col]); // A * T �� �����ϴ� �ڵ�

            matrix_multi[i_row][j_col] = result; //�������� matrix_multi�� �����ϴ� �ڵ�

            // �࿬���� ���� ���� ���� ������ ���� �� ���� ���� �ִ��� �Ѵ� ��츦 ����� ���� �ڵ�
            if (matrix_multi[i_row][j_col] > (MAX * MAX * col) || matrix_multi[i_row][j_col] < 0) 
            {
                printf("multiply_matrix �Լ����� A * T �� �����ϴ� ���� ������ �߻��Ͽ����ϴ�.\n");
                return -1; // �Լ��� ������ ���Ḧ �ǹ���.
            }
        }
    }

    print_matrix(matrix_multi, row, row);

    // ������ ����Ǿ����Ƿ� �Ҵ��ߴ� �޸𸮸� �����Ѵ�. 
    // ����, free_matrix �Լ��� ����� ������� �ʾҴٸ�, �޸� ������ ���� ������ �߻��� ���̹Ƿ� -1�� �������ش�.
    if (free_matrix(matrix_multi, row, row) != 1) 
    {
        printf("multiply_matrix �Լ����� [matrix_multi]�� �޸� ������ ���� ������ �߻��Ͽ����ϴ�.\n");
        return -1; // �Լ��� ������ ���Ḧ �ǹ���.
    }

    return 1; // �Լ� ���� ���� �ڵ�
}

