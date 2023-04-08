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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	printf("[----- [�ֹ���] [2020039004] -----]\n");

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

	// singly-linked-list�� initialize �� �Ҵ���� �޸��� �ּҰ��� ��ȯ�ϱ� ������ �̱������͸� �Ű������� ������
	// doubly-linked-list�� initialize �� �Ű������� �Է¹��� ���� �Ҵ���� �޸��� �ּҰ��� ���� �־�� �Ǳ� ������ ���������͸� �Ű������� �޴´�.

	if (*h != NULL) // �̹� initialize�� �� ���, freeList�� �� �Ŀ� �ٽ� �޸𸮸� �Ҵ��Ѵ�.
		freeList(*h); // h�� headnode�� �ּҰ��� ����Ű�� �ֱ� ������ freeList�� ȣ���� ��, �������� �ѹ� ����� �ȴ�.

	(*h) = (headNode*)malloc(sizeof(headNode)); // h�� �Ҵ���� �޸��� �ּҰ� �������ش�.
	if (*h == NULL) // �޸𸮸� �Ҵ���� ���� ��� 
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h){

	// initialize�� �Ҵ���� �ּҰ��� headnode�� �����ؾ��ϱ� ������ ���������͸� �Ű������� �޾�����
	// freeList�� �Ҵ���� �ּҰ��� �����Ͽ� �������ֱ⸸ �ϸ� �Ǳ� ������(=���� ������ �ʿ䰡 ���� ������) �̱� �����͸� �Ű������� �޴´�.

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� freeList�� ������ �� �����ϴ�.\n");
		return -1;
	}
	
	// doubly-linked-list�� ����ִ� ���� �ϳ��� �湮�ϸ� �޸𸮸� �����Ѵ�.
	listNode *searchNode = h->first;
	listNode *freeNode;
	while (searchNode != NULL) // searchNode�� NULL���� �� ���� �ݺ�
	{ 
		freeNode = searchNode;
		searchNode = searchNode->rlink;
		free(freeNode);
	}


	free(h); // ���������� h�� �������ش�.

	return 0;
}


void printList(headNode* h) {
	int i = 0; // doubly-linked-list�� ����ִ� item�� ������ ���� int�� ����
	listNode* p;

	printf("\n---PRINT\n");

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // p�� NULL�� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� insertLast ������ �� �����ϴ�.\n");
		return -1;
	}


	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // �޸𸮸� �Ҵ���� ���� ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;


	if (h->first == NULL)   // empty�� ���¶��
		h->first = newNode; // list�� ù ��带 newNode�� �Ѵ�.

	else // not empty ���
	{
		listNode *searchNode = h->first; // �� �������� ��带 �ֱ� ���� ����

		while(searchNode->rlink != NULL)  // searchNode�� ���� ��尡 NULL�� ������ �ݺ�
			searchNode = searchNode->rlink;
		
		// list�� ������ ��忡 newNode�� �߰��ϴ� �ڵ�
		searchNode->rlink = newNode;
		newNode->llink = searchNode;
	}

	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteLast�� ������ �� �����ϴ�.\n");
		return -1;
	}

	// list�� ��尡 �ϳ��� ���ٸ�
	if (h->first == NULL)
	{
		printf("Error! : list�� ��尡 ���� deleteLast�� ������ �� �����ϴ�.\n");
		return -1;
	}


	// list�� ��尡 �ϳ� ���̶��
	if (h->first->rlink == NULL)
	{
		free(h->first);
		h->first = NULL;
	}

	else
	{
		listNode *searchNode = h->first;  // ������ ��带 �����ϱ� ���� ����
		while (searchNode->rlink != NULL) // searchNode�� ���� ��尡 NULL�� ������ �ݺ�
			searchNode = searchNode->rlink;

		searchNode->llink->rlink = NULL;  // ������ ��带 free�ϱ� ��, �������� ���� ��带 ������ ���� �������ִ� �ڵ�
		free(searchNode);
	}

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	
	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� insertFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}

	
	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // �޸𸮸� �Ҵ���� ���� ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;


	if (h->first == NULL)   // empty�� ���¶��
		h->first = newNode; // list�� ù ��带 newNode�� �Ѵ�.

	else // not empty ���
	{
		newNode->rlink = h->first;
		h->first->llink = newNode;
		h->first = newNode;
	}

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}

	// list�� ��尡 �ϳ��� ���ٸ�
	if (h->first == NULL)
	{
		printf("Error! : list�� ��尡 ���� deleteFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}


	// list�� ��尡 �ϳ����̶��
	if (h->first->rlink == NULL)
	{
		free(h->first);
		h->first = NULL;
	}

	else
	{
		listNode *freeNode = h->first;
		h->first = h->first->rlink;		// h->frist�� ���� h->frist�� ���� ���� ���ش�.

		h->first->llink = NULL;			

		free(freeNode);
	}

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� invertList�� ������ �� �����ϴ�.\n");
		return -1;
	}


	int size = 0; // ����Ʈ�� ����ִ� ����� ���� ����  ����
	listNode *searchNode = h->first;
	while (searchNode != NULL)
	{
		searchNode = searchNode->rlink;
		size++;
	}

	// ����Ʈ�� ����ִ� ����� ���� 2�� �̸��� ���
	if (size < 2)
	{
		printf("Error! : list�� ��尡 2�� �̸��̹Ƿ� invertList�� ������ �� �����ϴ�.\n");
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

			// searchNode->rlink�� searchNode->llink�� �ٲ�� ������
			// ���� ��带 ���� ���ؼ� searchNode->link�� �ؾ� ��
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



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� inseartNode�� ������ �� �����ϴ�.\n");
		return -1;
	}


	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // �޸𸮸� �Ҵ���� ���� ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
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

		while (searchNode->rlink != NULL) // searchNode�� ���� ��尡 NULL�� ������ �ݺ�
		{
			if (searchNode->key >= key)   // �Է¹��� key���� ū ���� ������ ��� �ݺ��� ����
				break;

			searchNode = searchNode->rlink;
		}
		
		if (searchNode == h->first && searchNode->key >= key) // ��带 �� �տ� �����ϴ� ���
		{
			h->first->llink = newNode;
			newNode->rlink = h->first;
			h->first = newNode;
		}

		else if (searchNode->rlink == NULL && searchNode->key < key) // ��带 �� �ڿ� �����ϴ� ���
		{
			searchNode->rlink = newNode;
			newNode->llink = searchNode;
		}

		else // ��带 �߰��� �����ϴ� ���
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
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteNode�� ������ �� �����ϴ�.\n");
		return -1;
	}

	// list�� ��尡 �ϳ��� ���ٸ�
	if (h->first == NULL)
	{
		printf("Error! : list�� ��尡 ���� deleteNode�� ������ �� �����ϴ�.\n");
		return -1;
	}


	// list�� ��尡 �ϳ����̰�, �� ��尡 key���� ���ٸ�
	if ((h->first->rlink == NULL && h->first->llink == NULL) && h->first->key == key)
	{
		free(h->first);
		h->first = NULL;
	}

	// list�� ��尡 ���� �����
	else
	{
		listNode *searchNode = h->first;
		while(searchNode != NULL) // searchNode�� NULL�� ������ �ݺ�
		{
			if(searchNode->key == key) // ������ ��带 ã�� ���
				break;

			searchNode = searchNode->rlink;
		}

		if (searchNode == NULL) // ������ ��带 ã�� ������ ���
		{
			printf("Error! : list���� ������ ��带 ã�� ���߽��ϴ�.\n");
			return -1;
		}
		

		// �� ���� ��带 �����ϴ� ���
		if (searchNode->llink == NULL)
		{
			h->first = searchNode->rlink;
			searchNode->rlink->llink = NULL;
		}

		// �� ���� ��带 �����ϴ� ���
		else if (searchNode->rlink == NULL)
			searchNode->llink->rlink = NULL;

		// �߰��� ��带 �����ϴ� ���
		else
		{
			searchNode->rlink->llink = searchNode->llink;
			searchNode->llink->rlink = searchNode->rlink;
		}

		free(searchNode);
	}



	return 1;
}


