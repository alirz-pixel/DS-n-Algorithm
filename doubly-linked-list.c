/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[----- [최문형] [2020039004] -----]\n");

	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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


int initialize(headNode** h) {

	// singly-linked-list의 initialize 는 할당받은 메모리의 주소값을 반환하기 때문에 싱글포인터를 매개변수로 받지만
	// doubly-linked-list의 initialize 는 매개변수로 입력받은 곳에 할당받은 메모리의 주소값을 직접 넣어야 되기 때문에 이중포인터를 매개변수로 받는다.

	if (*h != NULL) // 이미 initialize를 한 경우, freeList를 한 후에 다시 메모리를 할당한다.
		freeList(*h); // h는 headnode의 주소값을 가리키고 있기 때문에 freeList를 호출할 때, 역참조를 한번 해줘야 된다.

	(*h) = (headNode*)malloc(sizeof(headNode)); // h에 할당받은 메모리의 주소값 대입해준다.
	if (*h == NULL) // 메모리를 할당받지 못한 경우 
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h){

	// initialize는 할당받은 주소값을 headnode에 대입해야하기 때문에 이중포인터를 매개변수로 받았지만
	// freeList는 할당받은 주소값에 접근하여 해제해주기만 하면 되기 때문에(=값을 수정할 필요가 없기 때문에) 싱글 포인터를 매개변수로 받는다.

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 freeList를 수행할 수 없습니다.\n");
		return -1;
	}
	
	// doubly-linked-list에 들어있는 값을 하나씩 방문하며 메모리를 해제한다.
	listNode *searchNode = h->first;
	listNode *freeNode;
	while (searchNode != NULL) // searchNode가 NULL값일 때 까지 반복
	{ 
		freeNode = searchNode;
		searchNode = searchNode->rlink;
		free(freeNode);
	}


	free(h); // 마지막으로 h를 해제해준다.

	return 0;
}


void printList(headNode* h) {
	int i = 0; // doubly-linked-list에 들어있는 item의 개수를 위한 int형 변수
	listNode* p;

	printf("\n---PRINT\n");

	// h에 메모리가 할당되어 있지 않은 경우
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // p가 NULL일 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 insertLast 수행할 수 없습니다.\n");
		return -1;
	}


	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // 메모리를 할당받지 못한 경우
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;


	if (h->first == NULL)   // empty인 상태라면
		h->first = newNode; // list의 첫 노드를 newNode로 한다.

	else // not empty 라면
	{
		listNode *searchNode = h->first; // 맨 마지막에 노드를 넣기 위한 변수

		while(searchNode->rlink != NULL)  // searchNode의 다음 노드가 NULL일 때까지 반복
			searchNode = searchNode->rlink;
		
		// list의 마지막 노드에 newNode를 추가하는 코드
		searchNode->rlink = newNode;
		newNode->llink = searchNode;
	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 deleteLast를 수행할 수 없습니다.\n");
		return -1;
	}

	// list에 노드가 하나도 없다면
	if (h->first == NULL)
	{
		printf("Error! : list에 노드가 없어 deleteLast를 수행할 수 없습니다.\n");
		return -1;
	}


	// list에 노드가 하나 뿐이라면
	if (h->first->rlink == NULL)
	{
		free(h->first);
		h->first = NULL;
	}

	else
	{
		listNode *searchNode = h->first;  // 마지막 노드를 삭제하기 위한 변수
		while (searchNode->rlink != NULL) // searchNode의 다음 노드가 NULL일 때까지 반복
			searchNode = searchNode->rlink;

		searchNode->llink->rlink = NULL;  // 마지막 노드를 free하기 전, 마지막의 이전 노드를 마지막 노드로 설정해주는 코드
		free(searchNode);
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 insertFirst를 수행할 수 없습니다.\n");
		return -1;
	}

	
	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // 메모리를 할당받지 못한 경우
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;


	if (h->first == NULL)   // empty인 상태라면
		h->first = newNode; // list의 첫 노드를 newNode로 한다.

	else // not empty 라면
	{
		newNode->rlink = h->first;
		h->first->llink = newNode;
		h->first = newNode;
	}

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 deleteFirst를 수행할 수 없습니다.\n");
		return -1;
	}

	// list에 노드가 하나도 없다면
	if (h->first == NULL)
	{
		printf("Error! : list에 노드가 없어 deleteFirst를 수행할 수 없습니다.\n");
		return -1;
	}


	// list에 노드가 하나뿐이라면
	if (h->first->rlink == NULL)
	{
		free(h->first);
		h->first = NULL;
	}

	else
	{
		listNode *freeNode = h->first;
		h->first = h->first->rlink;		// h->frist를 기존 h->frist의 다음 노드로 해준다.

		h->first->llink = NULL;			

		free(freeNode);
	}

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 invertList를 수행할 수 없습니다.\n");
		return -1;
	}


	int size = 0; // 리스트에 들어있는 노드의 수를 위한  변수
	listNode *searchNode = h->first;
	while (searchNode != NULL)
	{
		searchNode = searchNode->rlink;
		size++;
	}

	// 리스트에 들어있는 노드의 수가 2개 미만인 경우
	if (size < 2)
	{
		printf("Error! : list에 노드가 2개 미만이므로 invertList를 수행할 수 없습니다.\n");
		return -1;
	}

	else
	{
		searchNode = h->first;
		listNode *tempRlink = searchNode->rlink;
		listNode *tempLlink = searchNode->llink;

		while (searchNode->rlink != NULL)
		{
			searchNode->llink = tempRlink;
			searchNode->rlink = tempLlink;

			// searchNode->rlink를 searchNode->llink로 바꿨기 때문에
			// 다음 노드를 가기 위해선 searchNode->link를 해야 함
			searchNode = searchNode->llink; 
			tempRlink = searchNode->rlink;
			tempLlink = searchNode->llink;
		}

		searchNode->rlink = tempLlink;
		searchNode->llink = tempRlink;

		h->first = searchNode;
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 inseartNode를 수행할 수 없습니다.\n");
		return -1;
	}


	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // 메모리를 할당받지 못한 경우
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	newNode->key = key;
	newNode->rlink = NULL;
	newNode->llink = NULL;


	if (h->first == NULL)
		h->first = newNode;

	else
	{
		listNode *searchNode = h->first; 

		while (searchNode->rlink != NULL) // searchNode의 다음 노드가 NULL일 때까지 반복
		{
			if (searchNode->key >= key)   // 입력받은 key보다 큰 값이 나오는 경우 반복문 종료
				break;

			searchNode = searchNode->rlink;
		}
		
		if (searchNode == h->first && searchNode->key >= key) // 노드를 맨 앞에 삽입하는 경우
		{
			h->first->llink = newNode;
			newNode->rlink = h->first;
			h->first = newNode;
		}

		else if (searchNode->rlink == NULL) // 노드를 맨 뒤에 삽입하는 경우
		{
			searchNode->rlink = newNode;
			newNode->llink = searchNode;
		}

		else // 노드를 중간에 삽입하는 경우
		{
			newNode->rlink = searchNode;
			newNode->llink = searchNode->llink;

			searchNode->llink->rlink = newNode;
			searchNode->llink = newNode;
		}
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	// h에 메모리가 할당되어 있지 않은 경우
	if (h == NULL)
	{
		printf("Error! : 할당받은 메모리가 없어 deleteFirst를 수행할 수 없습니다.\n");
		return -1;
	}

	// list에 노드가 하나도 없다면
	if (h->first == NULL)
	{
		printf("Error! : list에 노드가 없어 deleteFirst를 수행할 수 없습니다.\n");
		return -1;
	}


	listNode *searchNode = h->first;
	while(searchNode != NULL) // searchNode가 NULL일 떄까지 반복
	{
		if(searchNode->key == key) // 삭제한 노드를 찾은 경우
			break;

		searchNode = searchNode->rlink;
	}

	if (searchNode == NULL) // 삭제할 노드를 찾지 못했을 경우
	{
		printf("Error! : list에서 삭제할 노드를 찾지 못했습니다.\n");
		return -1;
	}


	// 맨 앞의 노드를 삭제하는 경우
	if (searchNode->llink == NULL)
		searchNode->rlink->llink = NULL;

	// 맨 뒤의 노드를 삭제하는 경우
	else if (searchNode->rlink == NULL)
		searchNode->llink->rlink = NULL;

	// 중간의 노드를 삭제하는 경우
	else
	{
		searchNode->rlink->llink = searchNode->llink;
		searchNode->llink->rlink = searchNode->rlink;
	}

	free(searchNode);

	return 1;
}


