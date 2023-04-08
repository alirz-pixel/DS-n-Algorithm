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
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
	printf("[----- [�ֹ���] [2020039004] -----]\n");

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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	if(*h == NULL) // �޸𸮸� �Ҵ���� ������ ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� freeList�� ������ �� �����ϴ�.\n");
		return -1;
	}

	if (h->rlink != h) // ����Ʈ�� ������ ���� ��, �����尡 2�� ���� �Ǵ� ���� �����ϴ� �ڵ�
	{
		listNode *searchNode = h->rlink;
		listNode *freeNode;

		h->llink->rlink = NULL; // �ݺ����� ���ᰡ �Ǵ� ������ ����� �ֱ� ���� ������ ����� rlink�� NULL ������ ������ �ش�.

		while (searchNode != NULL) // searchNode�� NULL�� ������ �ݺ� 
		{
			freeNode = searchNode;
			searchNode = searchNode->rlink;

			free(freeNode); // ��� ������ ������ ��������� �޸𸮸� ���������ش�.
		}
	}
	
	free(h); // �������� �޸𸮸� ���������ش�.

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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� insertLast�� ������ �� �����ϴ�.\n");
		return -1;
	}

	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // �޸𸮸� �Ҵ���� ������ ���
	{
		printf("�޸𸮸� �Ҵ���� ���Ͽ� insertLast�� ������ �� �����ϴ�.\n");
		return -1;
	}

	newNode->llink = h->llink; // newNode�� ������ ��尡 �� �����̹Ƿ�, ������ ������ ��� (h->llink)�� newNode�� ���� ���� �����Ѵ�.
	newNode->rlink = h;		   // newNode�� ������ ��尡 �� �����̹Ƿ�, newNode�� ���� ��带 ��� ���� �����Ѵ�.
	newNode->key = key;		   

	
	h->llink->rlink = newNode; // ������ ����� rlink�� newNode�� �������ش�.
	h->llink = newNode;        // ��� ����� ������ ��带 newNode�� �������ش�.

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteLast�� ������ �� �����ϴ�.\n");
		return -1;
	}

	// list�� ��� ���� �� ���
	if (h->llink == h) 
	{
		printf("Error! : list�� ��� ��常 �ֱ� ������ deleteLast�� ������ �� �����ϴ�.\n");
		return -1;
	}


	listNode* lastNode = h->llink;

	lastNode->llink->rlink = h; // '������ ����� ���� ���'���� rlink�� ������� �����Ѵ�.
	h->llink = lastNode->llink; // �������� llink�� ���ο� ������ ���� �����Ѵ�.

	free(lastNode);

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� insertFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}


	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL) // �޸𸮸� �Ҵ���� ������ ���
	{
		printf("�޸𸮸� �Ҵ���� ���Ͽ� insertFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}

	newNode->key = key;
	newNode->llink = h;        // newNode�� ù ��° ��尡 �� �����̹Ƿ�, noewNode�� llink�� ��� ���� �����Ѵ�.
	newNode->rlink = h->rlink; // newNode�� ù ��° ��尡 �� �����̹Ƿ�, ������ ù��° ��带 newNode�� rlink�� �����Ѵ�.

	h->rlink->llink = newNode; // ������ ù ��° ����� llink�� newNode�� �����Ͽ� newNode�� ù ��° ���� ����
	h->rlink = newNode;		   // ù ��° ��尡 ����Ǿ����Ƿ� h->rlink�� newNode�� �����Ѵ�.

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}

	// list�� ��� ���� �� ���
	if (h->llink == h) 
	{
		printf("Error! : list�� ��� ��常 �ֱ� ������ deleteFirst�� ������ �� �����ϴ�.\n");
		return -1;
	}

	listNode *firstNode = h->rlink;
	firstNode->rlink->llink = h; // �ι�° ����� llink�� ��� ���� �����Ѵ�. 
	h->rlink = firstNode->rlink; // ��� ����� rlink�� �� ��° ���� �����Ѵ�.
	// ���� �ڵ带 ���� ������ �� ��° ��尡 ù ��° ���� �ǰ� �ȴ�. (��, list�� ��尡 2�� �̻��� ���)
	
	free(firstNode);

	return 1;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� invertList�� ������ �� �����ϴ�.\n");
		return -1;
	}


	listNode *searchNode = h->rlink;
	listNode *tempRlink;

	while (searchNode != h) // searchNode�� ��� ����� ������ �ݺ�
	{
		tempRlink = searchNode->rlink; // rlink�� llink�� �����ϱ� ����, searchNode->rlink�� tempRlink�� �����Ѵ�.

		searchNode->rlink = searchNode->llink;
		searchNode->llink = tempRlink;

		// ���� �ڵ带 ���� rlink�� llink�� �ٲ�����Ƿ� ���� ��带 �����ϱ� ���ؼ� llink�� �����ؾ� ��.
		searchNode = searchNode->llink; 
	}

	tempRlink = searchNode->rlink;

	searchNode->rlink = searchNode->llink;
	searchNode->llink = tempRlink;

	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� 
 **/
int insertNode(listNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteNode�� ������ �� �����ϴ�.\n");
		return -1;
	}

	
	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	if (newNode == NULL)
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	listNode *searchNode = h->rlink;
	while (searchNode->rlink != h)  // searchNode�� ���� ��尡 ��� ����� ������ �ݺ�
	{
		if (searchNode->key >= key) // �Է¹��� key���� ū ���� ������ ��� �ݺ��� ����
			break;

		searchNode = searchNode->rlink;
	} 
	
	newNode->key = key;
	if (searchNode->key < key) // ������ ��� ���Ŀ� newNode�� �ִ� ���
	{
		newNode->rlink = h;
		newNode->llink = searchNode;

		searchNode->rlink = newNode;
		h->llink = newNode;
	}

	else
	{
		newNode->rlink = searchNode;		// newNode�� rlink�� searchNode�� ������
		newNode->llink = searchNode->llink; // newNode�� llink�� searchNode�� ���� ���� ������

		searchNode->llink->rlink = newNode; // searchNode�� ���� ��忡�� rlink�� newNode�� ������
		searchNode->llink = newNode;        // searchNode�� llink�� newNode�� ������
	}

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	// h�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (h == NULL)
	{
		printf("Error! : �Ҵ���� �޸𸮰� ���� deleteNode�� ������ �� �����ϴ�.\n");
		return -1;
	}

	// list�� ��� ���� �� ���
	if (h->llink == h) 
	{
		printf("Error! : list�� ��� ��常 �ֱ� ������ deleteNode�� ������ �� �����ϴ�.\n");
		return -1;
	}


	listNode *searchNode = h->rlink;
	while (searchNode != h) // searchNode�� ��� ����� ������ �ݺ�
	{
		if (searchNode->key == key)  // �Է¹��� key���� ���� ���� ������ ��� �ݺ��� ����
			break;

		searchNode = searchNode->rlink;
	}

	if (searchNode == h) // searchNode�� ��� ����� ���� ã�� ���� ����̹Ƿ� -1�� �����Ѵ�.
	{
		printf("Error! : list���� ������ ��带 ã�� ���߽��ϴ�.\n");
		return -1;
	}


	searchNode->llink->rlink = searchNode->rlink;
	searchNode->rlink->llink = searchNode->llink;

	free(searchNode);

	return 0;
}


