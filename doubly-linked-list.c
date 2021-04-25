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
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
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

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


