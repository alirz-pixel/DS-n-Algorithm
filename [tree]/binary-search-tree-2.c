/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	printf("[----- [�ֹ���] [2020039004] -----]\n");

	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	if (*h == NULL) // �����Ҵ��� ������ ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	top = -1;

	while(1) // Stack is not empty ���
	{
		// node�� ���� ���� Ʈ���� leaf node�� �� �� ���� �ݺ�
		for (; node != NULL; node = node->left) 
			push(node);

		node = pop();
		if (node == NULL) break;

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = rear = -1;    // ť �ʱ�ȭ�ϱ�
	enQueue(ptr);

	while (front != rear) // ť ���� �����Ͱ� ����� ������ �ݺ�
	{
		ptr = deQueue();  
		if (ptr == NULL) break; // ���� Ʈ�� �Ǵ� ��ȸ�� ���� ���, �ݺ��� ����

		// �������� ��ȸ�� ���� �ڽ� ������ Ž���ϹǷ� 
		if (ptr->left != NULL)
			enQueue(ptr->left);

		// ���� �ڽ� ��� Ȯ�� ��, ������ �ڽ� ��嵵 Ž���Ѵ�.
		if (ptr->right != NULL)
			enQueue(ptr->right);

		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	if (head == NULL) // initializeBST�� ����� ������� ���� ���
	{
		printf("Error! : initializeBST�� ����� ����Ǿ����� Ȯ���� �ּ���!\n");
		return -1;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) // �����Ҵ��� ������ ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���߽��ϴ�.\n");
		return -1;
	}
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) // initializeBST�� ����� ������� ���� ���
	{
		printf("Error! : initializeBST�� ����� ����Ǿ����� Ȯ���� �ּ���!\n");
		return -1;
	}

	if (head->left == NULL) // Ʈ���� �ƹ� �����͵� ���� ���
	{
		printf("Error! : Ʈ���� ����־� deleteNode�� ������ �� �����ϴ�.\n");
		return -1;
	}


	// �� ���Ŀ� ������ �θ����� ���Ǵ� �����ϰ��� �ϴ� ����� �θ����̴�.
	Node* previous = head;
	Node* searchNode = head->left;
	while (searchNode != NULL) // searchNode�� NULL�� ������ �ݺ�
	{
		// �����ϰ��� �ϴ� ��带 ã�� ���
		if (searchNode->key == key)
			break;

		previous = searchNode;

		// �����ϰ��� �ϴ� ����� ���� searchNode�� ������ ū ���
		if (searchNode->key < key)
			searchNode = searchNode->right;
		else
			searchNode = searchNode->left;
	}
	// �����ϰ��� �ϴ� ��带 ã�� ���� ���
	if (searchNode == NULL)
	{
		printf("Error! : �����ϰ��� �ϴ� ��带 ã�� ���߽��ϴ�.\n");
		return -1;
	}


	// �ڽ� ����� ������ �����ϱ� ���� ����
	int childNum = (searchNode->left != NULL) + (searchNode->right != NULL);

	// �����ϰ��� �ϴ� ��尡 �ܸ������ ���
	if (!childNum)
	{			
		// Ʈ���� ��Ʈ ��� �ۿ� ���ų�
		// �θ� ����� ���� ��带 �����ϰ��� �ϴ� ���
		if (previous == head || previous->key > key)	
			previous->left = NULL;

		// �θ� ����� ������ ��带 �����ϰ��� �ϴ� ���
		else
			previous->right = NULL;
	}

	// �����ϰ��� �ϴ� ��尡 �ϳ��� �ڽĸ��� ���� ��
	else if (childNum == 1)
	{
		// �����ϰ��� �ϴ� ����� �ڽĳ�带 �����ϴ� ����
		Node* childNode = (searchNode->left != NULL) ? searchNode->left : searchNode->right;

		// ��Ʈ��� �Ǵ� �θ� ����� ���� ��带 �����ϰ��� �ϴ� ���
		if (previous == head || previous->key > key)
			previous->left = childNode;
		
		else
			previous->right = childNode;
	}

	// �����ϰ��� �ϴ� ��尡 �ΰ��� �ڽ��� ���� ��
	else
	{
		// �����ϰ��� �ϴ� ����� ������ ����Ʈ�� �� ���� ���� ���� �� ���� ��带 �����ϱ� ���� ����
		Node* pre_minRNode = searchNode;
		Node* minRNode = searchNode->right;
		while (minRNode->left != NULL) // minRNode->left�� NULL�� ������ �ݺ�
		{
			pre_minRNode = minRNode;
			minRNode = minRNode->left;
		}
		minRNode->left = searchNode->left;
		
		// �����ϰ��� �ϴ� ����� ������ �ڽĳ�尡 ������尡 �ƴ� ���
		if (pre_minRNode != searchNode)
		{
			minRNode->right = searchNode->right;
			pre_minRNode->left = NULL;
		}

		// ��Ʈ��� �Ǵ� �θ� ����� ���� ��带 �����ϰ��� �ϴ� ���
		if (previous == head || previous->key > key)
			previous->left = minRNode;

		else
			previous->right = minRNode;
	}

	free(searchNode);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top == -1) // Stack is empty ���
		return NULL;

	Node* returnNode = stack[top--];
	return returnNode;
}

void push(Node* aNode)
{
	stack[++top] = aNode;
}



Node* deQueue()
{
	if (front == rear) // queue is empty ��� NULL ��ȯ
		return NULL;
	
	Node* returnNode = queue[++front]; 
	return returnNode;
}

void enQueue(Node* aNode)
{
	queue[++rear] = aNode;	
}

void printStack()
{
	if (top == -1)
		printf("stack is empty\n");

	for (int i = top; i >= 0; i--)
		printf(" [%d] ", stack[i]->key);
}



