#include <stdio.h>
#include <stdlib.h>

typedef struct node {

    int vertex; // 연결되어있는 Vertex의 번호를 나타낸다
    struct node* next;

} Node;

#define MAXVERTEX 10

/* List of user-defined functions */
int initializeGS(Node** h);


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
                break;
                
            case 'e': case 'E':
                break;

            case 'd': case 'D':
                break;

            case 'b': case 'B':
                break;

            case 'p': case 'P':
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
 
    // headNode의 vertex값이 -2이면 아직 추가되지 않은 vertex로 취급하며
    // headNode의 vertex값이 -1이면 추가된 vertex로 취급한다.
    for (int i = 0; i < MAXVERTEX; i++)
    {
        (*h)[i].vertex = -2; // 아직 추가되지 않은 vertex로 초기화 해준다.
        (*h)[i].next = NULL;
    }

    return 1;
}