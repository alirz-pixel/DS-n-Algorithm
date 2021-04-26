/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("[----- [최문형] [2020039004] -----]\n");

	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	if(*h == NULL) // 메모리를 할당받지 못했을 경우
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 freeList를 수행할 수 없습니다.\n");
		return -1;
	}

	if (h->rlink != h) // 리스트에 헤더노드 뿐일 때, 헤더노드가 2번 삭제 되는 것을 방지하는 코드
	{
		listNode *searchNode = h->rlink;
		listNode *freeNode;

		h->llink->rlink = NULL; // 반복문이 종료가 되는 시점을 만들어 주기 위해 마지막 노드의 rlink를 NULL 값으로 대입해 준다.

		while (searchNode != NULL) // searchNode가 NULL일 때까지 반복 
		{
			freeNode = searchNode;
			searchNode = searchNode->rlink;

			free(freeNode); // 헤더 노드부터 마지막 노드전까지 메모리를 해제시켜준다.
		}
	}
	
	free(h); // 헤더노드의 메모리를 해제시켜준다.

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 insertLast를 수행할 수 없습니다.\n");
		return -1;
	}

	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // 메모리를 할당받지 못했을 경우
	{
		printf("메모리를 할당받지 못하여 insertLast를 수행할 수 없습니다.\n");
		return -1;
	}

	newNode->llink = h->llink; // newNode가 마지막 노드가 될 예정이므로, 기존의 마지막 노드 (h->llink)를 newNode의 이전 노드로 설정한다.
	newNode->rlink = h;		   // newNode가 마지막 노드가 될 예정이므로, newNode의 다음 노드를 헤더 노드로 설정한다.
	newNode->key = key;		   

	
	h->llink->rlink = newNode; // 마지막 노드의 rlink를 newNode로 설정해준다.
	h->llink = newNode;        // 헤더 노드의 마지막 노드를 newNode로 설정해준다.

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 deleteLast를 수행할 수 없습니다.\n");
		return -1;
	}

	// list에 헤더 노드뿐 일 경우
	if (h->llink == h) 
	{
		printf("Error! : list에 헤더 노드만 있기 때문에 deleteLast를 수행할 수 없습니다.\n");
		return -1;
	}


	listNode* lastNode = h->llink;

	lastNode->llink->rlink = h; // '마지막 노드의 이전 노드'에서 rlink를 헤더노드로 설정한다.
	h->llink = lastNode->llink; // 헤더노드의 llink를 새로운 마지막 노드로 설정한다.

	free(lastNode);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 insertFirst를 수행할 수 없습니다.\n");
		return -1;
	}


	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // 메모리를 할당받지 못했을 경우
	{
		printf("메모리를 할당받지 못하여 insertFirst를 수행할 수 없습니다.\n");
		return -1;
	}

	newNode->key = key;
	newNode->llink = h;        // newNode가 첫 번째 노드가 될 예정이므로, noewNode의 llink를 헤더 노드로 설정한다.
	newNode->rlink = h->rlink; // newNode가 첫 번째 노드가 될 예정이므로, 기존의 첫번째 노드를 newNode의 rlink로 설정한다.

	h->rlink->llink = newNode; // 기존의 첫 번째 노드의 llink를 newNode로 설정하여 newNode를 첫 번째 노드로 만듦
	h->rlink = newNode;		   // 첫 번째 노드가 변경되었으므로 h->rlink를 newNode로 설정한다.

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 deleteFirst를 수행할 수 없습니다.\n");
		return -1;
	}

	// list에 헤더 노드뿐 일 경우
	if (h->llink == h) 
	{
		printf("Error! : list에 헤더 노드만 있기 때문에 deleteFirst를 수행할 수 없습니다.\n");
		return -1;
	}

	listNode *firstNode = h->rlink;
	firstNode->rlink->llink = h; // 두번째 노드의 llink를 헤더 노드로 설정한다. 
	h->rlink = firstNode->rlink; // 헤더 노드의 rlink를 두 번째 노드로 설정한다.
	// 위의 코드를 통해 기존의 두 번째 노드가 첫 번째 노드로 되게 된다. (단, list에 노드가 2개 이상을 경우)
	
	free(firstNode);

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}


