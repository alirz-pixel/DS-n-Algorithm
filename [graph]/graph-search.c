/*
 * graph-search.c
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTEX 10

typedef struct node {

    int vertex; // ����Ǿ��ִ� Vertex�� ��ȣ�� ��Ÿ����
    struct node* next;

} Node;

// DFS�� ���� ��, Stack�� ������ �Ǵ� �ִ� Vertex�� ���� MAXVERTEX�̴�.
// ���� stack�� ����� MAXVERTEX�� �����Ѵ�.
Node* stack[MAXVERTEX];
int top = -1;

void push(Node* insertNode);
void pop();


// BFS�� ���� ��, queue�� ������ �Ǵ� �ִ� VERTEX�� ���� MAXVERTEX�̴�.
// ���� queue�� ����� MAXVERTEX�� �����Ѵ�.
Node* queue[MAXVERTEX];
int front = -1;
int rear = -1;

void enQueue(Node* insertNode);
Node* deQueue();


/* List of user-defined functions */
int initializeGS(Node** h);
int insertVertex(Node* h, int key);
int insertEdge(Node* h, int fir_Vertex, int sec_Vertex);
void nodeInsert(Node* headIndex, Node* insertNode);
int DFS(Node* h, int startVertex);
int BFS(Node* h, int startVertex);
void printG(Node* h); // headIndex
int freeGS(Node* h);


int main(void)
{
    printf("[----- [�ֹ���] [2020039004] -----]\n");

    Node* headNode = NULL;

	char command;
	int key1, key2;

    do{
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                     Graph Searches\n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph     = z                                       \n");
        printf(" Insert Vertex        = v          Insert Edge           = e    \n");
        printf(" Depth First Search   = d          Breath First Search   = b    \n");
        printf(" Print Graph          = p          Quit                  = q    \n");
        printf("----------------------------------------------------------------\n");
        
        printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
            case 'z': case 'Z':
                initializeGS(&headNode);
                break;

            case 'v': case 'V':
                printf("Your Key(0~%d) = ", MAXVERTEX - 1);
                scanf("%d", &key1);
                insertVertex(headNode, key1);
                break;
                
            case 'e': case 'E':
                printf("input Vertex 1(0~%d) : ", MAXVERTEX - 1);
                scanf("%d", &key1);
                printf("input Vertex 2(0~%d) : ", MAXVERTEX - 1);
                scanf("%d", &key2);
                insertEdge(headNode, key1, key2);
                break;

            case 'd': case 'D':
                printf("DFS�� ������ ���(0~%d): ", MAXVERTEX - 1);
                scanf("%d", &key1);
                DFS(headNode, key1);
                break;

            case 'b': case 'B':
                printf("BFS�� ������ ���(0~%d): ", MAXVERTEX - 1);
                scanf("%d", &key1);
                BFS(headNode, key1);
                break;

            case 'p': case 'P':
                printG(headNode);
                break;

            case 'q': case 'Q':
                freeGS(headNode);
                break;

            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    }while(command != 'q' && command != 'Q');
}


int initializeGS(Node** h)
{
    /*
    initialize �ϱ� ���� �Լ�
    */

    if (*h != NULL)
        freeGS(*h);

    /* crete a head node */
    // headnode�� �迭�� NULL�� �ʱ�ȭ �ؾ� �Ǳ� ������ calloc���� �����Ҵ�
    (*h) = (Node*)calloc(MAXVERTEX, sizeof(Node)); 
    if ((*h) == NULL)
    {
        printf("Error! : �����Ҵ��� ����� ������� �ʾҽ��ϴ�.\n");
        return -1;
    }
 
    // headNode�� vertex���� 0�̸� ���� �߰����� ���� vertex�� ����ϸ�
    // headNode�� vertex���� 1�̸� �߰��� vertex�� ����Ѵ�.
    for (int i = 0; i < MAXVERTEX; i++)
    {
        (*h)[i].vertex = 0;  // ������ vertex�� �׷����� ���� �߰����� �ʾ����Ƿ� 0���� �ʱ�ȭ���ش�.
        (*h)[i].next = NULL; // ������ vertex�� ����� vertex�� ���� ������ next�� NULL�� �ʱ�ȭ���ش�.
    }

    return 1;
}

int insertVertex(Node* h, int key)
{
    /*
      �׷����� vertex�� �߰��ϱ� ���� �Լ��Դϴ�.

      1. main�Լ��κ��� headNode�� �߰��ϰ� ���� vertex�� �Է¹޽��ϴ�.
      2. �� ��, �پ��� ��ó���� ���� ���� ������ ��½�ŵ�ϴ�.
         (2-1. initializeGS�� ����� ���� ���� ���)
         (2-2. 0 ~ [MAXVERTEX - 1] ������ ���� �Է����� ���� ���)
         (2-3. �̹� �߰��� vertex�� �� �߰��Ϸ��� ���)

      3. headNode[key].vertex ���� 1�� ����� vertex�� �߰��մϴ�.
    */

//----------------------�پ��� ��ó��----------------------

    if (h == NULL)
    {
        printf("\n Error! : initializeGS�� ����� ����Ǿ����� Ȯ���� �ּ���!\n");
        return -1;
    }


    if (!(0 <= key && key < MAXVERTEX))
    {
        printf("\n Error! : 0 ~ %d������ ���� �Է����ּ���.\n", MAXVERTEX - 1);
        return -1;
    }

    if (h[key].vertex == 1)
    {
        printf("\n Error! : �̹� �߰��Ǿ��ִ� Vertex�Դϴ�.\n");
        return -1;
    }

//--------------------------------------------------------

    printf("\n Vertex[%d] �� �߰��Ǿ����ϴ�.\n", key);
    h[key].vertex = 1; // vertex�� �߰������Ƿ� headNode�� vertex���� 1�� ������ش�.
    return 1;
}

int insertEdge(Node* h, int fir_Vertex, int sec_Vertex)
{
    /*
      �� vertex�� �����ϱ� �����ϱ� ���� �Լ��Դϴ�.

      1. �켱 main�Լ����� �����ϰ� ���� �� ���� vertex�� �Է¹޽��ϴ�.
      2. �� ��, �پ��� ��ó���� ���� ���� ������ ��½�ŵ�ϴ�.
         (2-1. initializeGS�� ����� ���� ���� ���)
         (2-2. 0 ~ [MAXVERTEX - 1] ������ ���� �Է����� ���� ���)
         (2-3. �ڱⰣ���� ����� �ϴ� ���)
         (2-4. �߰��Ǿ� ���� ���� vertex�� �����Ϸ��� ���)
         (2-5. ���� ������ ����� �ϴ� ���)

      3. ó������ �Է¹��� fir_Vertex�� sec_Vertex�� �����մϴ�.
      4. �� ��°�� �Է¹��� sec_Vertex�� fir_Vertex�� �����մϴ�.
    */
    

//----------------------�پ��� ��ó��----------------------

    if (h == NULL) // initializeGS�� ����� ������� ���� ���
    {
        printf("\n Error! : initializeGS�� ����� ����Ǿ����� Ȯ���� �ּ���!\n");
        return -1;
    }
    
    if (!(0 <= fir_Vertex && fir_Vertex < MAXVERTEX) || !(0 <= sec_Vertex && sec_Vertex < MAXVERTEX))
    {
        printf("\n Error! : 0 ~ %d������ ���� �Է����ּ���.\n", MAXVERTEX - 1);
        return -1;
    }

    if (fir_Vertex == sec_Vertex) // �ڱⰣ���� ����� �ϴ°��
    {
        printf("\n Error! : �� ���α׷��� �ڱⰣ���� ������� �ʽ��ϴ�.\n");
        return -1;
    }
    
    if (h[fir_Vertex].vertex == 0 || h[sec_Vertex].vertex == 0) // vertex�� �߰��Ǿ� ���� ���� ���
    {
        if (h[fir_Vertex].vertex == 0)
            printf("\n Error! : �׷����� [vertex %d]��(��) �߰��Ǿ� ���� �ʽ��ϴ�.\n", fir_Vertex);
        else
                printf("\n Error! : �׷����� [vertex %d]��(��) �߰��Ǿ� ���� �ʽ��ϴ�.\n", sec_Vertex);
        return -1;
    }

    // ���߰����� ����� �ϴ��� Ȯ���ϴ� �ڵ�
    Node* searchNode = h[fir_Vertex].next;
    while (searchNode != NULL) // h[fir_Vertex]�� ����Ʈ ������ �ϳ��� �˻��ϵ��� �ݺ��� ����
    {
        // fir_Vertex�� sec_Vertex�� �̹� ����Ǿ� �ִ� ���
        if (searchNode->vertex == sec_Vertex)
        {
            printf("\n Error! : �� ���α׷��� ���߰����� ������� �ʽ��ϴ�.\n");
            return -1;
        }

        searchNode = searchNode->next;
    }

//--------------------------------------------------------


//--------------�� Vertex�� �����ϱ� ���� �ڵ�--------------

    // vertex ������ ���� Node ����
    Node* firstNode = (Node*)malloc(sizeof(Node));
    Node* secondNode = (Node*)malloc(sizeof(Node));
    if (firstNode == NULL || secondNode == NULL) // �����Ҵ��� ����� ���� ���� ���
    {
        printf("\n Error! : �����Ҵ��� ����� ������� �ʾҽ��ϴ�.\n");
        return -1;
    }

    // �� vertex�� �����ϱ� ���� ������ ���� �����Ѵ�.
    secondNode->vertex = fir_Vertex; // sec_Vertex���� fir_Vertex�� ����
    firstNode->vertex = sec_Vertex; // fir_Vertex���� sec_Vertex�� ����
    firstNode->next = secondNode->next = NULL;
    

    // fir_Vertex���� sec_Vertex�� �����ϱ� ���� h[fir_Vertex]�� firstNode ����
    nodeInsert(&h[fir_Vertex], firstNode);

    // sec_Vertex���� fir_Vertex�� �����ϱ� ���� h[sec_Vertex]�� secondNode ����
    nodeInsert(&h[sec_Vertex], secondNode);

//--------------------------------------------------------

    return 1;
}

void nodeInsert(Node* headIndex, Node* insertNode)
{
    /*
      ����忡 ����Ʈ ��带 ������� �Լ��Դϴ�.
    */
    Node* previous = headIndex;
    Node* searchNode = headIndex->next;

    while (searchNode != NULL) // searchNode�� NULL�� ������ �ݺ�
    {
        // ������������ ��带 �ֱ� ���� if���� �����
        if(insertNode->vertex < searchNode->vertex)
            break;

        previous = searchNode;
        searchNode = searchNode->next;
    }

    // insertNode�� �����ϴ� �ڵ�
    insertNode->next = searchNode;
    previous->next = insertNode;
}

int DFS(Node* h, int startVertex)
{
    /*
      ���� �켱 Ž���� ���� �Լ��Դϴ�.

      1. �켱 main�Լ����� DFS�� ������ vertex�� �Է¹޽��ϴ�.
      2. �� ��, �پ��� ��ó���� ���� ���� ������ ��½�ŵ�ϴ�.
         (2-1. initializeGS�� ����� ���� ���� ���)
         (2-2. 0 ~ [MAXVERTEX - 1] ������ ���� �Է����� ���� ���)
         (2-3. �߰��Ǿ� ���� ���� vertex�� ���� vertex�� ������ ���)

      3. DFS ���� ������ ȭ�鿡 ����մϴ�.
      4. �� ��, DFS�� �����մϴ�.
    */



//----------------------�پ��� ��ó��----------------------

    if (h == NULL) // initializeGS�� ����� ������� ���� ���
    {
        printf("\n Error! : initializeGS�� ����� ����Ǿ����� Ȯ���� �ּ���!\n");
        return -1;
    }

    // 0 ~ [MAXVERTEX - 1] ������ ���� �Է����� ���� ���
    if (!(0 <= startVertex && startVertex < MAXVERTEX)) 
    {
        printf("\n Error! : 0 ~ %d������ ���� �Է����ּ���.\n", MAXVERTEX - 1);
        return -1;
    }

    if (h[startVertex].vertex == 0) // �߰��Ǿ� ���� ���� vertex�� DFS Ž���� ���� vertex�� ������ ��� 
    {
        printf("\n Error! : �׷����� [vertex %d]��(��) �߰��Ǿ� ���� �ʽ��ϴ�.\n", startVertex);
        return -1;
    }

//--------------------------------------------------------


//----------------------DFS ���� �ڵ�----------------------

    // DFSŽ�� ���� ������ ȭ�鿡 ���
    printf("\n DFS(%d)�� �����մϴ�.\n\n", startVertex);

    // DFS�Ϸ��� Vertex�� ����� vertex�� ���� ���, �ϳ��� ����ϰ� �Լ� ����
    if (h[startVertex].next == NULL)
    {
        printf(" [%d]", startVertex);
        return 1;
    }


    // �湮 ó���� ���� ���� �迭 ����
    short int* visited = (short int*)calloc(MAXVERTEX, sizeof(short int));
    if (visited == NULL) // �����Ҵ��� ����� ���� ���� ���
    {
        printf("\n Error! : �����Ҵ��� ����� ������� �ʾҽ��ϴ�.\n");
        return -1;
    }
    
    // stack �ʱ�ȭ
    top = -1; 

    // DFS ����
    Node* w = NULL;

    push(h[startVertex].next);        // ����ڰ� ���� Vertex�� stack�� �ִ´�.
    visited[startVertex] = 1;         // �� vertex�� �湮ó����
    printf(" [%d] -> ", startVertex); // ȭ�鿡 ������ش�.

    while (top != -1) // stack is empty�� ������ �ݺ�
    {
        // stack[top]->vertex�� ���� �湮���� ���� ���, �̿� ����� vertex �ϳ��� �湮�ϰ� push��
        while (!visited[stack[top]->vertex])
        {
            if (!visited[stack[top]->vertex])
            {
                visited[stack[top]->vertex] = 1;
                printf(" [%d] -> ", stack[top]->vertex);
                push(h[stack[top]->vertex].next);
            }
        }
        
        // stack[top]�� NULL�� ������ �ݺ�
        while (stack[top])
        {
            // ����, stack[top]->vertex�� ���� �湮���� �ʾҴٸ� �ݺ��� ���� ��, 
            // �� vertex�� ���� �ٽ� DFS�� �Ϸ� ��
            if (!visited[stack[top]->vertex])
                break;

            stack[top] = stack[top]->next;
        }

        // �� vertex�� ����� vertex�� ���ų� ��� vertex���� �湮�� ���, pop�Ѵ�.
        if (stack[top] == NULL)
            pop();
    }


    free(visited); // DFS�� �������Ƿ� �湮 ó���� ���� ���� �޸� ����

//--------------------------------------------------------


    return 1;
}

void push(Node* insertNode)
{
    stack[++top] = insertNode;
}

void pop()
{
    top--;
}

int BFS(Node* h, int startVertex)
{
    /*
      �ʺ� �켱 Ž���� ���� �Լ��Դϴ�.

      1. �켱 main�Լ����� BFS�� ������ vertex�� �Է¹޽��ϴ�.
      2. �� ��, �پ��� ��ó���� ���� ���� ������ ��½�ŵ�ϴ�.
         (2-1. initializeGS�� ����� ���� ���� ���)
         (2-2. 0 ~ [MAXVERTEX - 1] ������ ���� �Է����� ���� ���)
         (2-3. �߰��Ǿ� ���� ���� vertex�� Ž�� ���� vertex�� ������ ���)

      3. BFS ���� ������ ȭ�鿡 ����մϴ�.
      4. �� ��, BFS�� �����մϴ�.
    */



//----------------------�پ��� ��ó��----------------------

    if (h == NULL) // initializeGS�� ����� ������� ���� ���
    {
        printf("\n Error! : initializeGS�� ����� ����Ǿ����� Ȯ���� �ּ���!\n");
        return -1;
    }

    // 0 ~ [MAXVERTEX - 1] ������ ���� �Է����� ���� ���
    if (!(0 <= startVertex && startVertex < MAXVERTEX)) 
    {
        printf("\n Error! : 0 ~ %d������ ���� �Է����ּ���.\n", MAXVERTEX - 1);
        return -1;
    }

    if (h[startVertex].vertex == 0) // �߰��Ǿ� ���� ���� vertex�� BFS Ž���� ���� vertex�� ������ ��� 
    {
        printf("\n Error! : �׷����� [vertex %d]��(��) �߰��Ǿ� ���� �ʽ��ϴ�.\n", startVertex);
        return -1;
    }

//--------------------------------------------------------


//----------------------BFS ���� �ڵ�----------------------

    // BFSŽ�� ���� ������ ȭ�鿡 ���
    printf("\n BFS(%d)�� �����մϴ�.\n\n", startVertex);

    // �湮 ó���� ���� ���� �迭 ����
    short int* visited = (short int*)calloc(MAXVERTEX, sizeof(short int));
    if (visited == NULL) // �����Ҵ��� ����� ���� ���� ���
    {
        printf("\n Error! : �����Ҵ��� ����� ������� �ʾҽ��ϴ�.\n");
        return -1;
    }

    // BFS Ž���� ���� queue �ʱ�ȭ
    front = -1;
    rear = -1;

    // BFS ����
    Node* w = NULL;

    enQueue(h[startVertex].next);                // BFS Ž���� ���� vertex�� queue�� ����
    visited[startVertex] = 1;                    // ���� vertex�� �湮ó���� ���ش�.
    printf(" [%d] -> ", startVertex);            // ���� vetex�� ȭ�鿡 ����Ѵ�.

    while(front != rear)                         // queue�� ����ִٸ� �ݺ��� ����
        for (w = deQueue(); w; w = w->next)      // 
            if (!visited[w->vertex])
            {
                printf(" [%d] -> ", w->vertex);  // ������ vertex�� ȭ�鿡 ���
                visited[w->vertex] = 1;          // ������ vertex�� �湮ó��
                enQueue(h[w->vertex].next);      // ������ vertex�� queue�� �����Ѵ�.
            }


    free(visited); // BFS�� �������Ƿ� �湮 ó���� ���� ���� �޸� ����

//--------------------------------------------------------

    return 1;
}

void enQueue(Node* insertNode)
{
	queue[++rear] = insertNode;	
}

Node* deQueue()
{
    if(front == rear) // queue�� ����ִٸ�, NULL�� ��ȯ
        return NULL;

    return queue[++front];
}

void printG(Node* h)
{
    /*
      insert �Ǿ��ִ� vertex��
      �� vertex�� ����Ǿ� �ִ� vertex�� ȭ�鿡 ����ϴ� �Լ�
    */
    printf ("\n---PRINT\n");

    if (h == NULL)
    {
        printf("�μ��� �׸��� �����ϴ�.\n");
        return;
    }


    Node* p = NULL; // ����� vertex�� ã������ ����
    int cnt = 0;    // vertex�� ������ �˱� ���� ����

    for (int i = 0; i < MAXVERTEX; i++)
    {
        if (h[i].vertex == 1) // vertex�� �߰��Ǿ� �ִٸ� 
        {
            p = h[i].next;    // ����� vertex�� ã������ p�� h[i].next�� �����Ѵ�.

            printf(" ( Vertex %d :", i);
            while(p != NULL)  // [vertex i]�� ����� vertex�� ���� ������ �ݺ�
            {
                printf(" [%d] ->", p->vertex);
                p = p->next;
            }
            printf(" ) \n");

            cnt++;
        }
    }
    printf("\n  items = %d\n", cnt);
}

int freeGS(Node* h)
{
    // h�� NULL�� ���, freeG �Լ��� ������ �ʿ䰡 �����Ƿ� -1�� �����Ѵ�.
    if (h == NULL) return -1;

    Node* deleteNode = NULL;
    Node* nextNode = NULL;
    for (int i = 0; i < MAXVERTEX; i++) // MAXVERTEX ����ŭ �ݺ�
        if (h[i].vertex == 1) // vertex�� �����Ǿ� �ִٸ�
        {
            printf("\n ��� ��� : [%d]\n", i);
            printf("  ������ ��� : ");
            deleteNode = NULL;
            nextNode = h[i].next;

            while(nextNode) // nextNode�� NULL�� ������ �ݺ�
            {
                // ������� h[i]�� ����Ʈ ��尡 ���� ���,
                // �޸��� ������ singly-linked-list�� �˰����� ����
                // ���� ����Ʈ ��带 �ϳ��� �湮�ϸ� ���� ����� �޸𸮸� �����ϴ� ������� �ϸ� �ȴ�.
                deleteNode = nextNode; 
                nextNode = nextNode->next;

                printf("[%d]  ", deleteNode->vertex); // freeG�� �� ����Ǵ��� Ȯ���ϴ� �ڵ�.
                free(deleteNode);
            }

            printf("\n");
        }

    free(h);
    return 1;
}