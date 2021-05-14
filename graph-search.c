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
void printG(Node* h);


int main(void)
{
    printf("[----- [최문형] [2020039004] -----]\n");

    Node* headNode = NULL;

	char command;
	int key;

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
                printf("Your Key(0~9) = ");
                scanf("%d", &key);
                insertVertex(headNode, key);
                break;
                
            case 'e': case 'E':
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
        (*h)[i].vertex = 0; // 아직 추가되지 않은 vertex로 초기화 해준다.
        (*h)[i].next = NULL;
    }

    return 1;
}

int insertVertex(Node* h, int key)
{
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
    h[key].vertex = 1;
    return 1;
}

void printG(Node* h)
{
    printf ("\n---PRINT\n");

    if (h == NULL)
    {
        printf("인쇄할 항목이 없습니다.\n");
        return;
    }


    Node* p = NULL;
    int cnt = 0;

    for (int i = 0; i < MAXVERTEX; i++)
    {
        if (h[i].vertex == 1)
        {
            p = h[i].next;

            printf(" ( Vertex %d :", i);
            while(p != NULL)
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