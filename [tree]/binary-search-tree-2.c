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
	printf("[----- [최문형] [2020039004] -----]\n");

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
	if (*h == NULL) // 동적할당을 실패한 경우
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
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

	while(1) // Stack is not empty 라면
	{
		// node가 왼쪽 서브 트리의 leaf node가 될 떄 까지 반복
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
	front = rear = -1;    // 큐 초기화하기
	enQueue(ptr);

	while (front != rear) // 큐 안의 데이터가 비었을 떄까지 반복
	{
		ptr = deQueue();  
		if (ptr == NULL) break; // 공백 트리 또는 순회를 끝낸 경우, 반복문 종료

		// 레벨순서 순회도 왼쪽 자식 노드부터 탐색하므로 
		if (ptr->left != NULL)
			enQueue(ptr->left);

		// 왼쪽 자식 노드 확인 후, 오른쪽 자식 노드도 탐색한다.
		if (ptr->right != NULL)
			enQueue(ptr->right);

		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	if (head == NULL) // initializeBST가 제대로 수행되지 않은 경우
	{
		printf("Error! : initializeBST가 제대로 수행되었는지 확인해 주세요!\n");
		return -1;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) // 동적할당을 실패한 경우
	{
		printf("Error! : 메모리를 할당받지 못했습니다.\n");
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
	if (head == NULL) // initializeBST가 제대로 수행되지 않은 경우
	{
		printf("Error! : initializeBST가 제대로 수행되었는지 확인해 주세요!\n");
		return -1;
	}

	if (head->left == NULL) // 트리에 아무 데이터도 없는 경우
	{
		printf("Error! : 트리가 비어있어 deleteNode를 수행할 수 없습니다.\n");
		return -1;
	}


	// 이 이후에 나오는 부모노드의 정의는 삭제하고자 하는 노드의 부모노드이다.
	Node* previous = head;
	Node* searchNode = head->left;
	while (searchNode != NULL) // searchNode가 NULL일 때까지 반복
	{
		// 삭제하고자 하는 노드를 찾은 경우
		if (searchNode->key == key)
			break;

		previous = searchNode;

		// 삭제하고자 하는 노드의 값이 searchNode의 값보다 큰 경우
		if (searchNode->key < key)
			searchNode = searchNode->right;
		else
			searchNode = searchNode->left;
	}
	// 삭제하고자 하는 노드를 찾지 못한 경우
	if (searchNode == NULL)
	{
		printf("Error! : 삭제하고자 하는 노드를 찾지 못했습니다.\n");
		return -1;
	}


	// 자식 노드의 개수를 저장하기 위한 변수
	int childNum = (searchNode->left != NULL) + (searchNode->right != NULL);

	// 삭제하고자 하는 노드가 단말노드일 경우
	if (!childNum)
	{			
		// 트리에 루트 노드 밖에 없거나
		// 부모 노드의 왼쪽 노드를 삭제하고자 하는 경우
		if (previous == head || previous->key > key)	
			previous->left = NULL;

		// 부모 노드의 오른쪽 노드를 삭제하고자 하는 경우
		else
			previous->right = NULL;
	}

	// 삭제하고자 하는 노드가 하나의 자식만을 가질 때
	else if (childNum == 1)
	{
		// 삭제하고자 하는 노드의 자식노드를 저장하는 변수
		Node* childNode = (searchNode->left != NULL) ? searchNode->left : searchNode->right;

		// 루트노드 또는 부모 노드의 왼쪽 노드를 삭제하고자 하는 경우
		if (previous == head || previous->key > key)
			previous->left = childNode;
		
		else
			previous->right = childNode;
	}

	// 삭제하고자 하는 노드가 두개의 자식을 가질 때
	else
	{
		// 삭제하고자 하는 노드의 오른쪽 서브트리 중 가장 작은 노드와 그 이전 노드를 저장하기 위한 변수
		Node* pre_minRNode = searchNode;
		Node* minRNode = searchNode->right;
		while (minRNode->left != NULL) // minRNode->left가 NULL일 때까지 반복
		{
			pre_minRNode = minRNode;
			minRNode = minRNode->left;
		}
		minRNode->left = searchNode->left;
		
		// 삭제하고자 하는 노드의 오른쪽 자식노드가 리프노드가 아닐 경우
		if (pre_minRNode != searchNode)
		{
			minRNode->right = searchNode->right;
			pre_minRNode->left = NULL;
		}

		// 루트노드 또는 부모 노드의 왼쪽 노드를 삭제하고자 하는 경우
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
	if (top == -1) // Stack is empty 라면
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
	if (front == rear) // queue is empty 라면 NULL 반환
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



