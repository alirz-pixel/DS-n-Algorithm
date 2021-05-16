#include <stdio.h>
#include <stdlib.h>

typedef struct node {

    int vertex; // 연결되어있는 Vertex의 번호를 나타낸다
    struct node* next;

} Node;

#define MAXVERTEX 10

/* List of user-defined functions */
int initializeGS(Node** h);
int insertVertex(Node* h, int key);
int insertEdge(Node* h, int fir_Vertex, int sec_Vertex);
void nodeInsert(Node* headIndex, Node* insertNode);
void printG(Node* h); // headIndex


int main(void)
{
    printf("[----- [최문형] [2020039004] -----]\n");

    Node* headNode = NULL;

	char command;
	int key, sec_Key;

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
                printf("Your Key(0~%d) = ", MAXVERTEX);
                scanf("%d", &key);
                insertVertex(headNode, key);
                break;
                
            case 'e': case 'E':
                printf("input Vertex 1(0~%d) : ", MAXVERTEX);
                scanf("%d", &key);
                printf("input Vertex 2(0~%d) : ", MAXVERTEX);
                scanf("%d", &sec_Key);
                insertEdge(headNode, key, sec_Key);
                break;

            case 'd': case 'D':
                break;

            case 'b': case 'B':
                break;

            case 'p': case 'P':
                printG(headNode);
                break;

            case 'q': case 'Q':
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

    /*
    freeGS가 구현되면 추가될 공간입니다.
    if (*h != NULL)
        freeGS(*h);
    */

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
        printf("\n Error! : 0 ~ 9사이의 값만 입력해주세요.\n");
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
         (2-2. 0~9사이의 값을 입력하지 않은 경우)
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
        printf("\n Error! : 0 ~ %d사이의 값만 입력해주세요.\n", MAXVERTEX);
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
        return 1;
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