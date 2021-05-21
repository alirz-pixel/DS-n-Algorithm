#include <stdio.h>
#include <stdlib.h>

#define MAXVERTEX 10

typedef struct node {

    int vertex; // 연결되어있는 Vertex의 번호를 나타낸다
    struct node* next;

} Node;

// DFS를 했을 떄, Stack에 들어오게 되는 최대 Vertex의 수는 MAXVERTEX이다.
// 따라서 stack의 사이즈를 MAXVERTEX로 선언한다.
Node* stack[MAXVERTEX];
int top = -1;

void push(Node* insertNode);
void pop();


// BFS를 했을 때, queue에 들어오게 되는 최대 VERTEX의 수는 MAXVERTEX이다.
// 따라서 queue의 사이즈를 MAXVERTEX로 선언한다.
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
    printf("[----- [최문형] [2020039004] -----]\n");

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
                printf("DFS를 시작할 노드(0~%d): ", MAXVERTEX - 1);
                scanf("%d", &key1);
                DFS(headNode, key1);
                break;

            case 'b': case 'B':
                printf("BFS를 시작할 노드(0~%d): ", MAXVERTEX - 1);
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
    initialize 하기 위한 함수
    */

    if (*h != NULL)
        freeGS(*h);

    /* crete a head node */
    // headnode의 배열을 NULL로 초기화 해야 되기 때문에 calloc으로 동적할당
    (*h) = (Node*)calloc(MAXVERTEX, sizeof(Node)); 
    if ((*h) == NULL)
    {
        printf("Error! : 동적할당이 제대로 수행되지 않았습니다.\n");
        return -1;
    }
 
    // headNode의 vertex값이 0이면 아직 추가되지 않은 vertex로 취급하며
    // headNode의 vertex값이 1이면 추가된 vertex로 취급한다.
    for (int i = 0; i < MAXVERTEX; i++)
    {
        (*h)[i].vertex = 0;  // 현재의 vertex가 그래프에 아직 추가되지 않았으므로 0으로 초기화해준다.
        (*h)[i].next = NULL; // 현재의 vertex에 연결된 vertex가 없기 때문에 next를 NULL로 초기화해준다.
    }

    return 1;
}

int insertVertex(Node* h, int key)
{
    /*
      그래프에 vertex를 추가하기 위한 함수
    */

    if (h == NULL)
    {
        printf("\n Error! : initializeGS가 제대로 수행되었는지 확인해 주세요!\n");
        return -1;
    }


    if (!(0 <= key && key < MAXVERTEX))
    {
        printf("\n Error! : 0 ~ %d사이의 값만 입력해주세요.\n", MAXVERTEX - 1);
        return -1;
    }

    if (h[key].vertex == 1)
    {
        printf("\n Error! : 이미 추가되어있는 Vertex입니다.\n");
        return -1;
    }

    printf("\n Vertex[%d] 가 추가되었습니다.\n", key);
    h[key].vertex = 1; // vertex를 추가했으므로 headNode의 vertex값을 1로 만들어준다.
    return 1;
}

int insertEdge(Node* h, int fir_Vertex, int sec_Vertex)
{
    /*
      두 vertex를 연결하기 연결하기 위한 함수입니다.

      1. 우선 main함수에서 연결하고 싶은 두 개의 vertex를 입력받습니다.
      2. 그 후, 다양한 전처리를 통해 에러 문구를 출력시킵니다.
         (2-1. initializeGS를 제대로 하지 않은 경우)
         (2-2. 0 ~ [MAXVERTEX - 1] 사이의 값을 입력하지 않은 경우)
         (2-3. 자기간선을 만드려 하는 경우)
         (2-4. 추가되어 있지 않은 vertex를 연결하려는 경우)
         (2-5. 다중 간선을 만드려 하는 경우)

      3. 처음으로 입력받은 fir_Vertex를 sec_Vertex와 연결합니다.
      4. 두 번째로 입력받은 sec_Vertex를 fir_Vertex와 연결합니다.
    */
    

//----------------------다양한 전처리----------------------

    if (h == NULL) // initializeGS가 제대로 수행되지 않은 경우
    {
        printf("\n Error! : initializeGS가 제대로 수행되었는지 확인해 주세요!\n");
        return -1;
    }
    
    if (!(0 <= fir_Vertex && fir_Vertex < MAXVERTEX) || !(0 <= sec_Vertex && sec_Vertex < MAXVERTEX))
    {
        printf("\n Error! : 0 ~ %d사이의 값만 입력해주세요.\n", MAXVERTEX - 1);
        return -1;
    }

    if (fir_Vertex == sec_Vertex) // 자기간선을 만드려 하는경우
    {
        printf("\n Error! : 이 프로그램은 자기간선을 허용하지 않습니다.\n");
        return -1;
    }
    
    if (h[fir_Vertex].vertex == 0 || h[sec_Vertex].vertex == 0) // vertex가 추가되어 있지 않은 경우
    {
        if (h[fir_Vertex].vertex == 0)
            printf("\n Error! : 그래프에 [vertex %d]이(가) 추가되어 있지 않습니다.\n", fir_Vertex);
        else
                printf("\n Error! : 그래프에 [vertex %d]이(가) 추가되어 있지 않습니다.\n", sec_Vertex);
        return -1;
    }

    // 다중간선을 만드려 하는지 확인하는 코드
    Node* searchNode = h[fir_Vertex].next;
    while (searchNode != NULL) // h[fir_Vertex]의 리스트 노드들을 하나씩 검색하도록 반복문 설정
    {
        // fir_Vertex와 sec_Vertex가 이미 연결되어 있는 경우
        if (searchNode->vertex == sec_Vertex)
        {
            printf("\n Error! : 이 프로그램은 다중간선을 허용하지 않습니다.\n");
            return -1;
        }

        searchNode = searchNode->next;
    }

//--------------------------------------------------------


//--------------두 Vertex를 연결하기 위한 코드--------------

    // 우선 fir_Vertex에서 sec_Vertex를 연결
    Node* firstNode = (Node*)malloc(sizeof(Node));
    if (firstNode == NULL) // 동적할당이 제대로 되지 않은 경우
    {
        printf("\n Error! : 동적할당이 제대로 수행되지 않았습니다.\n");
        return -1;
    }
    firstNode->vertex = sec_Vertex; // fir_Vertex에서 sec_Vertex를 연결
    firstNode->next = NULL;

    // fir_Vertex에서 sec_Vertex를 연결하기 위해 h[fir_Vertex]에 firstNode 삽입
    nodeInsert(&h[fir_Vertex], firstNode);


    // 그 후, sec_Vertex에서 fir_Vertex를 연결
    Node* secondNode = (Node*)malloc(sizeof(Node));
    if (secondNode == NULL) // 동적할당이 제대로 되지 않은 경우
    {
        printf("\n Error! : 동적할당이 제대로 수행되지 않았습니다.\n");
        return -1;
    }
    secondNode->vertex = fir_Vertex; // sec_Vertex에서 fir_Vertex를 연결
    secondNode->next = NULL;
    
    // sec_Vertex에서 fir_Vertex를 연결하기 위해 h[sec_Vertex]에 secondNode 삽입
    nodeInsert(&h[sec_Vertex], secondNode);

//--------------------------------------------------------

    return 1;
}

void nodeInsert(Node* headIndex, Node* insertNode)
{
    /*
      헤드노드에 리스트 노드를 담기위한 함수입니다.
    */
    Node* previous = headIndex;
    Node* searchNode = headIndex->next;

    while (searchNode != NULL) // searchNode가 NULL일 때까지 반복
    {
        // 오름차순으로 노드를 넣기 위해 if문을 사용함
        if(insertNode->vertex < searchNode->vertex)
            break;

        previous = searchNode;
        searchNode = searchNode->next;
    }

    // insertNode를 삽입하는 코드
    insertNode->next = searchNode;
    previous->next = insertNode;
}

int DFS(Node* h, int startVertex)
{
    /*
      깊이 우선 탐색을 위한 함수입니다.

      1. 우선 main함수에서 DFS를 시작할 vertex를 입력받습니다.
      2. 그 후, 다양한 전처리를 통해 에러 문구를 출력시킵니다.
         (2-1. initializeGS를 제대로 하지 않은 경우)
         (2-2. 0 ~ [MAXVERTEX - 1] 사이의 값을 입력하지 않은 경우)
         (2-3. 추가되어 있지 않은 vertex를 시작 vertex로 지정한 경우)

      3. DFS 시작 문구를 화면에 출력합니다.
      4. 그 후, DFS를 진행합니다.
    */



//----------------------다양한 전처리----------------------

    if (h == NULL) // initializeGS가 제대로 수행되지 않은 경우
    {
        printf("\n Error! : initializeGS가 제대로 수행되었는지 확인해 주세요!\n");
        return -1;
    }

    // 0 ~ [MAXVERTEX - 1] 사이의 값을 입력하지 않은 경우
    if (!(0 <= startVertex && startVertex < MAXVERTEX)) 
    {
        printf("\n Error! : 0 ~ %d사이의 값만 입력해주세요.\n", MAXVERTEX - 1);
        return -1;
    }

    if (h[startVertex].vertex == 0) // 추가되어 있지 않은 vertex를 DFS 탐색의 시작 vertex로 지정한 경우 
    {
        printf("\n Error! : 그래프에 [vertex %d]이(가) 추가되어 있지 않습니다.\n", startVertex);
        return -1;
    }

//--------------------------------------------------------


//----------------------DFS 관련 코드----------------------

    // DFS탐색 시작 문구를 화면에 출력
    printf("\n DFS(%d)을 시작합니다.\n\n", startVertex);

    // DFS하려는 Vertex와 연결된 vertex가 없는 경우, 하나만 출력하고 함수 종료
    if (h[startVertex].next == NULL)
    {
        printf(" [%d]", startVertex);
        return 1;
    }


    // 방문 처리를 위한 동적 배열 선언
    short int* visited = (short int*)calloc(MAXVERTEX, sizeof(short int));
    if (visited == NULL) // 동적할당이 제대로 되지 않은 경우
    {
        printf("\n Error! : 동적할당이 제대로 수행되지 않았습니다.\n");
        return -1;
    }
    
    // stack 초기화
    top = -1; 

    // DFS 시작
    Node* w = NULL;

    push(h[startVertex].next);        // 사용자가 정한 Vertex를 stack에 넣는다.
    visited[startVertex] = 1;         // 이 vertex를 방문처리와
    printf(" [%d] -> ", startVertex); // 화면에 출력해준다.

    while (top != -1) // stack is empty일 때까지 반복
    {
        // stack[top]->vertex를 아직 방문하지 않은 경우, 이와 연결된 vertex 하나를 방문하고 push함
        while (!visited[stack[top]->vertex])
        {
            if (!visited[stack[top]->vertex])
            {
                visited[stack[top]->vertex] = 1;
                printf(" [%d] -> ", stack[top]->vertex);
                push(h[stack[top]->vertex].next);
            }
        }
        
        // stack[top]이 NULL일 때까지 반복
        while (stack[top])
        {
            // 만약, stack[top]->vertex를 아직 방문하지 않았다면 반복문 종료 후, 
            // 이 vertex에 대해 다시 DFS을 하러 감
            if (!visited[stack[top]->vertex])
                break;

            stack[top] = stack[top]->next;
        }

        // 이 vertex와 연결된 vertex가 없거나 모든 vertex들을 방문한 경우, pop한다.
        if (stack[top] == NULL)
            pop();
    }


    free(visited); // DFS가 끝났으므로 방문 처리를 위해 사용된 메모리 해제

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
      너비 우선 탐색을 위한 함수입니다.

      1. 우선 main함수에서 BFS를 시작할 vertex를 입력받습니다.
      2. 그 후, 다양한 전처리를 통해 에러 문구를 출력시킵니다.
         (2-1. initializeGS를 제대로 하지 않은 경우)
         (2-2. 0 ~ [MAXVERTEX - 1] 사이의 값을 입력하지 않은 경우)
         (2-3. 추가되어 있지 않은 vertex를 탐색 시작 vertex로 지정한 경우)

      3. BFS 시작 문구를 화면에 출력합니다.
      4. 그 후, BFS를 진행합니다.
    */



//----------------------다양한 전처리----------------------

    if (h == NULL) // initializeGS가 제대로 수행되지 않은 경우
    {
        printf("\n Error! : initializeGS가 제대로 수행되었는지 확인해 주세요!\n");
        return -1;
    }

    // 0 ~ [MAXVERTEX - 1] 사이의 값을 입력하지 않은 경우
    if (!(0 <= startVertex && startVertex < MAXVERTEX)) 
    {
        printf("\n Error! : 0 ~ %d사이의 값만 입력해주세요.\n", MAXVERTEX - 1);
        return -1;
    }

    if (h[startVertex].vertex == 0) // 추가되어 있지 않은 vertex를 BFS 탐색의 시작 vertex로 지정한 경우 
    {
        printf("\n Error! : 그래프에 [vertex %d]이(가) 추가되어 있지 않습니다.\n", startVertex);
        return -1;
    }

//--------------------------------------------------------


//----------------------BFS 관련 코드----------------------

    // BFS탐색 시작 문구를 화면에 출력
    printf("\n BFS(%d)을 시작합니다.\n\n", startVertex);

    // 방문 처리를 위한 동적 배열 선언
    short int* visited = (short int*)calloc(MAXVERTEX, sizeof(short int));
    if (visited == NULL) // 동적할당이 제대로 되지 않은 경우
    {
        printf("\n Error! : 동적할당이 제대로 수행되지 않았습니다.\n");
        return -1;
    }

    // BFS 탐색을 위해 queue 초기화
    front = -1;
    rear = -1;

    // BFS 시작
    Node* w = NULL;

    enQueue(h[startVertex].next);                // BFS 탐색의 시작 vertex를 queue에 삽입
    visited[startVertex] = 1;                    // 시작 vertex를 방문처리를 해준다.
    printf(" [%d] -> ", startVertex);            // 시작 vetex를 화면에 출력한다.

    while(front != rear)                         // queue가 비어있다면 반복문 종료
        for (w = deQueue(); w; w = w->next)      // 
            if (!visited[w->vertex])
            {
                printf(" [%d] -> ", w->vertex);  // 현재의 vertex를 화면에 출력
                visited[w->vertex] = 1;          // 현재의 vertex를 방문처리
                enQueue(h[w->vertex].next);      // 현재의 vertex를 queue에 삽입한다.
            }


    free(visited); // BFS가 끝났으므로 방문 처리를 위해 사용된 메모리 해제

//--------------------------------------------------------

    return 1;
}

void enQueue(Node* insertNode)
{
	queue[++rear] = insertNode;	
}

Node* deQueue()
{
    if(front == rear) // queue가 비어있다면, NULL값 반환
        return NULL;

    return queue[++front];
}

void printG(Node* h)
{
    /*
      insert 되어있는 vertex와
      그 vertex에 연결되어 있는 vertex를 화면에 출력하는 함수
    */
    printf ("\n---PRINT\n");

    if (h == NULL)
    {
        printf("인쇄할 항목이 없습니다.\n");
        return;
    }


    Node* p = NULL; // 연결된 vertex를 찾기위한 변수
    int cnt = 0;    // vertex의 개수를 알기 위한 변수

    for (int i = 0; i < MAXVERTEX; i++)
    {
        if (h[i].vertex == 1) // vertex가 추가되어 있다면 
        {
            p = h[i].next;    // 연결된 vertex를 찾기위해 p에 h[i].next를 대입한다.

            printf(" ( Vertex %d :", i);
            while(p != NULL)  // [vertex i]에 연결된 vertex가 없을 때까지 반복
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
    // h가 NULL인 경우, freeG 함수를 수행할 필요가 없으므로 -1을 리턴한다.
    if (h == NULL) return -1;

    Node* deleteNode = NULL;
    Node* nextNode = NULL;
    for (int i = 0; i < MAXVERTEX; i++) // MAXVERTEX 수만큼 반복
        if (h[i].vertex == 1) // vertex가 생성되어 있다면
        {
            printf("\n 헤드 노드 : [%d]\n", i);
            printf("  삭제된 노드 : ");
            deleteNode = NULL;
            nextNode = h[i].next;

            while(nextNode) // nextNode가 NULL일 때까지 반복
            {
                // 헤드노드인 h[i]에 리스트 노드가 있을 경우,
                // 메모리의 해제는 singly-linked-list와 알고리즘이 같다
                // 따라서 리스트 노드를 하나씩 방문하며 이전 노드의 메모리를 해제하는 방식으로 하면 된다.
                deleteNode = nextNode; 
                nextNode = nextNode->next;

                printf("[%d]  ", deleteNode->vertex); // freeG가 잘 수행되는지 확인하는 코드.
                free(deleteNode);
            }

            printf("\n");
        }

    free(h);
    return 1;
}