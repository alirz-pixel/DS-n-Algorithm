/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */



#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("[----- [최문형] [2020039004] -----]\n\n");

	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	if (temp == NULL)  // 메모리를 할당받지 못한 경우 NULL 값 반환
	{
		printf("메모리를 할당받지 못했습니다.\n");
		return NULL;
	}

	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) { // p가 NULL 일 때까지 반복하며, prev에 할당된 메모리를 해제한다.
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) // 메모리를 할당받지 못했을 경우 -1을 반환
	{
		printf("메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	node->key = key;

	// 맨 앞에 노드를 넣어야 하기 때문에 node->link를 h->first로 해준다.
	// 그 후, h->first를 node로 지정한다.
	node->link = h->first; 
	h->first = node;       

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}


	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) // 메모리를 할당받지 못했을 경우 -1을 반환
	{
		printf("메모리를 할당받지 못했습니다.");
		return -1;
	}

	node->link = NULL;
	node->key = key;


	// 연결리스트에 값이 하나도 없는 경우
	if (h->first == NULL)
		h->first = node;

	// 연결리스트에 값이 하나라도 있는 경우
	else
	{
		// 맨 앞에 넣어야 하는 경우
		if (h->first->key >= key)
		{
			// 맨 앞에 노드를 넣어야 하기 때문에 node->link를 h->first로 해준다.
			// 그 후, h->first를 node로 지정한다.
			node->link = h->first;
			h->first = node;
		}

		// 넣는 곳이 맨 앞이 아닌 경우 
		else
		{
			listNode* searchNode = h->first->link;
			listNode* previousNode = h->first;

			while (searchNode != NULL) // searchNode 가 NULL이 될 때까지 반복
			{
				if (searchNode->key >= key) // 입력받은 key 값보다 큰 값이 나온경우 반복문 탈출
					break;

				// previousNode에 현재 searchNode를 대입해주고
				// searchNode는 searchNode->link를 대입하면서
				// 리스트를 하나씩 검색한다.
				previousNode = searchNode;
				searchNode = searchNode->link;
			}

			// while 문을 통해 searchNode는 삽입하는 곳 기준 다음에 위치하며
			// previousNode는 삽입하는 곳 기준 이전에 위치해있으므로
			// node->link를 searchNode로 해주고, previousNode->link를 node로 해준다.
			node->link = searchNode;
			previousNode->link = node;
		}
	}


	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) // 메모리를 할당받지 못했을 경우 -1을 반환
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
		return -1;
	}

	node->link = NULL;
	node->key = key;

	// 연결 리스트에 아무 데이터도 없다면
	if (h->first == NULL)
		h->first = node;

	// 연결 리스트에 값이 하나라도 있다면
	else
	{
		listNode* searchNode = h->first;

		while (searchNode->link != NULL) // searchNode의 다음 노드가 NULL일 때까지 반복
			searchNode = searchNode->link;
		
		// while 문을 통해 searchNode는 마지막 노드를 가리키고 있음
		searchNode->link = node;
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	// 리스트에 아무 값도 없는 경우 에러 발생
	if (h->first == NULL)
	{
		printf("Error! : 리스트에 값이 없습니다.\n");
		return -1;
	}

	//맨 앞의 노드를 삭제하는 경우, h->first 를 하나 앞으로 이동해야한다.
	listNode* freeNode = h->first;
	h->first = freeNode->link; // h->first 를 하나 앞으로 이동시키는 코드.

	free(freeNode);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	// 리스트에 아무 값도 없는 경우 에러 발생
	if (h->first == NULL)
	{
		printf("Error! : 리스트에 값이 없습니다.\n");
		return -1;
	}

	// h->first->key 와 key 값이 같은 경우
	// 즉, 맨앞의 노드를 삭제하는 경우
	if (h->first->key == key)
	{
		listNode* freeNode = h->first;
		h->first = freeNode->link;
	}

	// 맨 앞의 노드를 삭제하지 않기 때문에 일일이 조사해야함.
	else
	{
		listNode* searchNode = h->first;
		listNode* previousNode = NULL;

		while (searchNode != NULL) // searchNode 가 NULL이 될 때까지 반복
		{
			if (searchNode->key == key) // 삭제하고자 하는 키값을 찾은 경우
			{
				previousNode->link = searchNode->link;

				free(searchNode);
				return 0;
			}

			// previousNode에 현재 searchNode를 대입해주고
			// searchNode는 searchNode->link를 대입하면서
			// 리스트를 하나씩 검색한다.
			previousNode = searchNode;
			searchNode = searchNode->link;
		}

		printf("리스트에서 삭제하고자 하는 key 값을 찾지 못했습니다.\n");			
		return -1;
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	// 리스트에 아무 값도 없는 경우 에러 발생
	if (h->first == NULL)
	{
		printf("Error! : 리스트에 값이 없습니다.\n");
		return -1;
	}

	listNode* freeNode = h->first;

	// 만약, 연결리스트의 값이 하나뿐이라면
	if (h->first->link == NULL)
		h->first = NULL;

	// 만약, 연결리스트의 값이 둘 이상이라면
	else
	{
		listNode* previousNode = NULL;

		// 맨 뒤의 노드를 제거해야 되기 때문에 freeNode의 다음 노드가 NULL 일 때까지 반복한다.
		while (freeNode->link != NULL) 
		{
			// previousNode에 현재 freeNode를 대입해주고
			// freeNode는 freeNode->link를 대입하면서
			// 리스트를 하나씩 검색한다.						
			previousNode = freeNode;
			freeNode = freeNode->link;
		}

		// previousNode의 다음 노드가 삭제되었으므로 NULL 값을 대입한다.
		previousNode->link = NULL;
	}

	free(freeNode);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	// h에 할당받은 메모리가 없는 경우 에러 발생
	if (h == NULL) {
		printf("Error! : headnode에 할당받은 메모리가 없어 에러가 발생하였습니다.\n");
		return -1;
	}

	// 연순으로 재배치 되려면, 리스트의 사이즈가 2개 이상 있어야 된다.
	// 리스트의 사이즈를 구하기 위한 변수 i 선언
	int i = 0;  
	listNode* p = h->first; 

	while (p != NULL)
	{
		p = p->link;
		i++;
	}

	if (i < 2) // list의 사이즈가 2개 미만인 경우, 에러 발생
	{
		printf("Error! : 리스트의 사이즈가 2개 미만입니다!\n");
		return -1;
	}

	listNode* tail = h->first;
	listNode* middle = tail->link;
	listNode* lead = middle->link;

	while (lead != NULL) // lead의 값이 NULL일 때까지 반복한다.
	{
		middle->link = tail;

		// tail, middle, lead를 각각 다음으로 보낸다.
		tail = middle;
		middle = lead;
		lead = lead->link;
	}
	middle->link = tail;

	h->first->link = NULL; // 역순 배치 전의 h->first->link를 NULL로 바꿔줘야 함.
	h->first = middle; 

	return 0;
}


void printList(headNode* h) {
	int i = 0; // 리스트의 사이즈를 구하기 위한 변수 i 선언
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // p 가 NULL일 때까지 반복한다.
		// 리스트를 하나씩 검색하면서 값을 출력하고 i에 1을 더해준다.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++; 
	}

	printf("  items = %d\n", i);
}

