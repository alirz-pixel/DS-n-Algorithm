/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */



#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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
	printf("[----- [�ֹ���] [2020039004] -----]\n\n");

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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	if (temp == NULL)  // �޸𸮸� �Ҵ���� ���� ��� NULL �� ��ȯ
	{
		printf("�޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return NULL;
	}

	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) { // p�� NULL �� ������ �ݺ��ϸ�, prev�� �Ҵ�� �޸𸮸� �����Ѵ�.
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) // �޸𸮸� �Ҵ���� ������ ��� -1�� ��ȯ
	{
		printf("�޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	node->key = key;

	// �� �տ� ��带 �־�� �ϱ� ������ node->link�� h->first�� ���ش�.
	// �� ��, h->first�� node�� �����Ѵ�.
	node->link = h->first; 
	h->first = node;       

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}


	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) // �޸𸮸� �Ҵ���� ������ ��� -1�� ��ȯ
	{
		printf("�޸𸮸� �Ҵ���� ���߽��ϴ�.");
		return -1;
	}

	node->link = NULL;
	node->key = key;


	// ���Ḯ��Ʈ�� ���� �ϳ��� ���� ���
	if (h->first == NULL)
		h->first = node;

	// ���Ḯ��Ʈ�� ���� �ϳ��� �ִ� ���
	else
	{
		// �� �տ� �־�� �ϴ� ���
		if (h->first->key >= key)
		{
			// �� �տ� ��带 �־�� �ϱ� ������ node->link�� h->first�� ���ش�.
			// �� ��, h->first�� node�� �����Ѵ�.
			node->link = h->first;
			h->first = node;
		}

		// �ִ� ���� �� ���� �ƴ� ��� 
		else
		{
			listNode* searchNode = h->first->link;
			listNode* previousNode = h->first;

			while (searchNode != NULL) // searchNode �� NULL�� �� ������ �ݺ�
			{
				if (searchNode->key >= key) // �Է¹��� key ������ ū ���� ���°�� �ݺ��� Ż��
					break;

				// previousNode�� ���� searchNode�� �������ְ�
				// searchNode�� searchNode->link�� �����ϸ鼭
				// ����Ʈ�� �ϳ��� �˻��Ѵ�.
				previousNode = searchNode;
				searchNode = searchNode->link;
			}

			// while ���� ���� searchNode�� �����ϴ� �� ���� ������ ��ġ�ϸ�
			// previousNode�� �����ϴ� �� ���� ������ ��ġ�������Ƿ�
			// node->link�� searchNode�� ���ְ�, previousNode->link�� node�� ���ش�.
			node->link = searchNode;
			previousNode->link = node;
		}
	}


	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) // �޸𸮸� �Ҵ���� ������ ��� -1�� ��ȯ
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}

	node->link = NULL;
	node->key = key;

	// ���� ����Ʈ�� �ƹ� �����͵� ���ٸ�
	if (h->first == NULL)
		h->first = node;

	// ���� ����Ʈ�� ���� �ϳ��� �ִٸ�
	else
	{
		listNode* searchNode = h->first;

		while (searchNode->link != NULL) // searchNode�� ���� ��尡 NULL�� ������ �ݺ�
			searchNode = searchNode->link;
		
		// while ���� ���� searchNode�� ������ ��带 ����Ű�� ����
		searchNode->link = node;
	}

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	// ����Ʈ�� �ƹ� ���� ���� ��� ���� �߻�
	if (h->first == NULL)
	{
		printf("Error! : ����Ʈ�� ���� �����ϴ�.\n");
		return -1;
	}

	//�� ���� ��带 �����ϴ� ���, h->first �� �ϳ� ������ �̵��ؾ��Ѵ�.
	listNode* freeNode = h->first;
	h->first = freeNode->link; // h->first �� �ϳ� ������ �̵���Ű�� �ڵ�.

	free(freeNode);

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	// ����Ʈ�� �ƹ� ���� ���� ��� ���� �߻�
	if (h->first == NULL)
	{
		printf("Error! : ����Ʈ�� ���� �����ϴ�.\n");
		return -1;
	}

	// h->first->key �� key ���� ���� ���
	// ��, �Ǿ��� ��带 �����ϴ� ���
	if (h->first->key == key)
	{
		listNode* freeNode = h->first;
		h->first = freeNode->link;
	}

	// �� ���� ��带 �������� �ʱ� ������ ������ �����ؾ���.
	else
	{
		listNode* searchNode = h->first;
		listNode* previousNode = NULL;

		while (searchNode != NULL) // searchNode �� NULL�� �� ������ �ݺ�
		{
			if (searchNode->key == key) // �����ϰ��� �ϴ� Ű���� ã�� ���
			{
				previousNode->link = searchNode->link;

				free(searchNode);
				return 0;
			}

			// previousNode�� ���� searchNode�� �������ְ�
			// searchNode�� searchNode->link�� �����ϸ鼭
			// ����Ʈ�� �ϳ��� �˻��Ѵ�.
			previousNode = searchNode;
			searchNode = searchNode->link;
		}

		printf("����Ʈ���� �����ϰ��� �ϴ� key ���� ã�� ���߽��ϴ�.\n");			
		return -1;
	}

	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	// ����Ʈ�� �ƹ� ���� ���� ��� ���� �߻�
	if (h->first == NULL)
	{
		printf("Error! : ����Ʈ�� ���� �����ϴ�.\n");
		return -1;
	}

	listNode* freeNode = h->first;

	// ����, ���Ḯ��Ʈ�� ���� �ϳ����̶��
	if (h->first->link == NULL)
		h->first = NULL;

	// ����, ���Ḯ��Ʈ�� ���� �� �̻��̶��
	else
	{
		listNode* previousNode = NULL;

		// �� ���� ��带 �����ؾ� �Ǳ� ������ freeNode�� ���� ��尡 NULL �� ������ �ݺ��Ѵ�.
		while (freeNode->link != NULL) 
		{
			// previousNode�� ���� freeNode�� �������ְ�
			// freeNode�� freeNode->link�� �����ϸ鼭
			// ����Ʈ�� �ϳ��� �˻��Ѵ�.						
			previousNode = freeNode;
			freeNode = freeNode->link;
		}

		// previousNode�� ���� ��尡 �����Ǿ����Ƿ� NULL ���� �����Ѵ�.
		previousNode->link = NULL;
	}

	free(freeNode);

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	// h�� �Ҵ���� �޸𸮰� ���� ��� ���� �߻�
	if (h == NULL) {
		printf("Error! : headnode�� �Ҵ���� �޸𸮰� ���� ������ �߻��Ͽ����ϴ�.\n");
		return -1;
	}

	// �������� ���ġ �Ƿ���, ����Ʈ�� ����� 2�� �̻� �־�� �ȴ�.
	// ����Ʈ�� ����� ���ϱ� ���� ���� i ����
	int i = 0;  
	listNode* p = h->first; 

	while (p != NULL)
	{
		p = p->link;
		i++;
	}

	if (i < 2) // list�� ����� 2�� �̸��� ���, ���� �߻�
	{
		printf("Error! : ����Ʈ�� ����� 2�� �̸��Դϴ�!\n");
		return -1;
	}

	listNode* tail = h->first;
	listNode* middle = tail->link;
	listNode* lead = middle->link;

	while (lead != NULL) // lead�� ���� NULL�� ������ �ݺ��Ѵ�.
	{
		middle->link = tail;

		// tail, middle, lead�� ���� �������� ������.
		tail = middle;
		middle = lead;
		lead = lead->link;
	}
	middle->link = tail;

	h->first->link = NULL; // ���� ��ġ ���� h->first->link�� NULL�� �ٲ���� ��.
	h->first = middle; 

	return 0;
}


void printList(headNode* h) {
	int i = 0; // ����Ʈ�� ����� ���ϱ� ���� ���� i ����
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // p �� NULL�� ������ �ݺ��Ѵ�.
		// ����Ʈ�� �ϳ��� �˻��ϸ鼭 ���� ����ϰ� i�� 1�� �����ش�.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++; 
	}

	printf("  items = %d\n", i);
}

