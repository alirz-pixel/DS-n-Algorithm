/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [�ֹ���] [2020039004] -----]\n");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	if (*h == NULL) // �޸𸮸� �Ҵ���� ������ ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���Ͽ����ϴ�.\n");
		return -1;
	}

	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{   // ������ȸ�� ���� ���� Ʈ�� -> ��� �湮 -> ������ ���� Ʈ�� ������ ����ǹǷ�
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);  // ���� ���� Ʈ���� ���� ��ȸ �Ѵ�.
		printf("[ %d ] ", ptr->key);  // ��带 �湮�Ѵ�.
		inorderTraversal(ptr->right); // ������ ���� Ʈ���� ���� ��ȸ �Ѵ�.
	}
}

void preorderTraversal(Node* ptr)
{   // ������ȸ�� ��� �湮 -> ���� ���� Ʈ�� -> ������ ���� Ʈ�� ������ ����ǹǷ�
	if (ptr != NULL)
	{
		printf("[ %d ] ", ptr->key);   // ��带 �湮�Ѵ�.
		preorderTraversal(ptr->left);  // ���� ���� Ʈ���� ���� ��ȸ�Ѵ�.
		preorderTraversal(ptr->right); // ������ ���� Ʈ���� ���� ��ȸ�Ѵ�.
	}
}

void postorderTraversal(Node* ptr)
{   // ���� ��ȸ�� ���� ���� Ʈ�� -> ������ ���� Ʈ�� -> ��� �湮 ������ ����ǹǷ�
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);  // ���� ���� Ʈ���� ���� ��ȸ�Ѵ�.
		postorderTraversal(ptr->right); // ������ ���� Ʈ���� ���� ��ȸ�Ѵ�.
		printf("[ %d ] ", ptr->key);    // ��带 �湮�Ѵ�.
	}
}


int insert(Node* head, int key)
{

	// initializeBST�� ����� ������� �ʾ��� ���
	if (head == NULL)
	{
		printf("Error! : initializeBST�� ����� ����Ǿ����� Ȯ���� �ּ���.\n");
		return -1;
	}

	Node *newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) // �޸𸮸� �Ҵ���� ������ ���
	{
		printf("Error! : �޸𸮸� �Ҵ���� ���� insert�� ����� �������� ���Ͽ����ϴ�.\n");
		return -1;
	}

	newNode->key = key;
	newNode->left = newNode->right = NULL;

	// Ʈ���� �ƹ� �����͵� ���� ���, newNode�� ��Ʈ���� �����Ѵ�.
	if (head->left == NULL)
		head->left = newNode;
	
	else
	{
		Node *searchNode = head->left; // searchNode�� ��Ʈ ���� ������

		// searchNode�� ���� ����̰ų� searchNode�� key���� �Է¹��� key���� ���� ������ �ݺ�
		while ((searchNode->left != NULL || searchNode->right != NULL) && searchNode->key != key)
		{
			// searchNode�� key ������ �Է¹��� key ���� ū ���
			if (searchNode->key < key) 
			{
				if (searchNode->right == NULL)  // �� ��� �����ʿ� newNode�� �����ؾ� �ϹǷ� �ݺ��� ����
					break;

				searchNode = searchNode->right; // searchNode�� ���� ��尡 �ƴ� ���, searchNode�� ������ ���� Ʈ�� Ž��
			}

			// searchNode�� key ������ �Է¹��� key ���� ū ���
			else 
			{
				if (searchNode->left == NULL)  // �� ��� ���ʿ� newNode�� �����ؾ� �ϹǷ� �ݺ��� ����
					break;

				searchNode = searchNode->left; // searchNode�� ���� ��尡 �ƴ� ���, searchNode�� ���� ���� Ʈ�� Ž��
			}
		}

		
		// Ʈ���� �̹� �ִ� ���� �Է¹��� ���, ������ �������� �ʰ� �Լ��� �����Ѵ�.
		if (searchNode->key == key)
		{
			printf("Error! : Ʈ���� �̹� �߰��Ǿ� �ִ� key ���Դϴ�.\n");
			return -1;
		}

		// searchNode�� key�� ���� �Է¹��� key���� ũ�Ƿ� �����ʿ� ��带 �����Ѵ�.
		if (searchNode->key < key) 
			searchNode->right = newNode;

		// searchNode�� key�� ���� �Է¹��� key���� �����Ƿ� ���ʿ� ��带 �����Ѵ�.
		else 
			searchNode->left = newNode;
	}

	return 1;
}

int deleteLeafNode(Node* head, int key)
{

	// initializeBST�� ����� ������� �ʾ��� ���
	if (head == NULL)
	{
		printf("Error! : initializeBST�� ����� ����Ǿ����� Ȯ���� �ּ���.\n");
		return -1;
	}

	// Ʈ���� �ƹ� �����͵� ���� ���
	if (head->left == NULL)
	{
		printf("Error! : Ʈ���� �ƹ� �����͵� �����ϴ�.\n");
		return -1;
	}


	Node *previous = head;
	Node *searchNode = head->left; 

	// searchNode�� left node �� ������ �ݺ�
	while (searchNode->left != NULL || searchNode->right != NULL)
	{
		previous = searchNode;

		// ���� ����� key���� �Է¹��� key���� ���� ���, �ݺ��� ����
		if (searchNode->key == key) break;

		// searchNode�� key ������ �Է¹��� key ���� ū ���
		if (searchNode->key < key)
		{
			// ����, serahcNode�� ������ �ڽ� ��尡 ���� ���
			if (searchNode->right == NULL)
				break;
			
			// �ƴ� ���, searchNode�� ������ ���� Ʈ�� Ž��
			searchNode = searchNode->right;
		}

		// searchNode�� key���� �Է¹��� key������ ���� ���
		else 
		{
			// ����, serahcNode�� ���� �ڽ� ��尡 ���� ���
			if (searchNode->left == NULL)
				break;

			// �ƴ� ���, seasrchNode�� ���� ���� Ʈ�� Ž��
			searchNode = searchNode->left;
		}
	}

	// �����ϰ��� �ϴ� key���� ���� ���
	if (searchNode->key != key)
	{
		printf("�����ϰ��� �ϴ� ��尡 Ʈ���� �����ϴ�.\n");
		return -1;
	}

	// �Է¹��� key���� ������ key���� ������ ���� ã������, leaf node�� �ƴ� ���
	if (searchNode->left != NULL || searchNode->right != NULL)
	{
		printf("the node [%d] is not a leaf\n", searchNode->key);
		return -1;
	}

	
	free(searchNode);

	// ��Ʈ ����� ��
	if (previous == head)
		head->left = NULL;
	
	// ������ �ڽ� ����� �޸𸮸� ������ ��, �� �θ� ����� right�� NULL�� ������ش�.
	else if (previous->key < key)
		previous->right = NULL;

	// ���� �ڽ� ����� �޸𸮸� ������ ��, �� �θ� ����� left�� NULL�� ������ش�.
	else
		previous->left = NULL;

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL) return NULL; // Ʈ���� �ƹ� �����͵� ���ų� Ž���� ������ ���, NULL ��ȯ
	if (ptr->key > key) return searchRecursive(ptr->left, key);  // ���� ����� key������ �Է¹��� key���� ���� ���, ���� ���� Ʈ�� Ž��
	if (ptr->key < key) return searchRecursive(ptr->right, key); // ���� ����� key������ �Է¹��� key���� ū ���, ������ ���� Ʈ�� Ž��

	return ptr; // Ž���� ������ ���, ã�� ����� �ּҸ� ��ȯ�Ѵ�.
}

Node* searchIterative(Node* head, int key)
{

	// Ʈ���� �ƹ� �����Ͱ� ���ų� head�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (head == NULL) return NULL;
	if (head->left == NULL) return NULL;


	Node *searchNode = head->left; // saerchNode�� ��Ʈ ���� ����
	while (searchNode->left != NULL || searchNode->right != NULL) // searchNode�� leaf node�� ������ �ݺ�
	{
		// ���� ����� key���� �Է¹��� key���� ���� ���, �ݺ��� ����
		if (searchNode->key == key) break; 

		// searchNode�� key ������ �Է¹��� key ���� ū ���
		if (searchNode->key < key)
		{
			// ����, serahcNode�� ������ �ڽ� ��尡 ���� ���, Ž���� ���������Ƿ� NULL ��ȯ
			if (searchNode->right == NULL)
				return NULL;
			
			// �ƴ� ���, searchNode�� ������ ���� Ʈ�� Ž��
			searchNode = searchNode->right;
		} 
			
		else 
		{
			// ����, serahcNode�� ���� �ڽ� ��尡 ���� ���, Ž���� ���������Ƿ� NULL ��ȯ
			if (searchNode->left == NULL)
				return NULL;

			// �ƴ� ���, seasrchNode�� ���� ���� Ʈ�� Ž��
			searchNode = searchNode->left;
		}
	}

	// Ž���� ������ ���, ã�� ����� �ּҸ� ��ȯ�Ѵ�.
	if (searchNode->key == key) return searchNode;
	return NULL;
}


int freeBST(Node* head)
{

	// head�� �޸𸮰� �Ҵ�Ǿ� ���� ���� ���
	if (head == NULL)
	{
		printf("Error! : �Ҵ�� �޸𸮰� �������� �ʾ� freeBST�� �������� ���߽��ϴ�.\n");
		return -1;
	}

	
	Node *searchNode, *previous;
	int i = 0;
	
	// Postorder Traversal �� Ž���ϸ�, �޸𸮸� �����Ѵ�.
	while (head->left != NULL) // ��Ʈ ��尡 NULL�� ������ �ݺ�
	{
		previous = head;
		searchNode = head->left;

		// searchNode�� left node �� ������ �ݺ�
		while (searchNode->left != NULL || searchNode->right != NULL)
		{
			previous = searchNode;

			if (searchNode->left != NULL) // ���� ���� Ʈ������ Ž���� �����Ѵ�.
				searchNode = searchNode->left;

			else // ���� �ڽ� ��尡 NULL�� ���, ������ ���� Ʈ���� Ž���Ѵ�.
				searchNode = searchNode->right;
		}
		free(searchNode); // leaf node �޸� ���� �Ǵ� ��Ʈ ��� �޸� ����


		// ��Ʈ ����� �� �ݺ��� ���������� (��Ʈ ����� ��, previous�� head�� ����Ŵ)
		if (previous == head) 
			break;

		// ������ leaf node�� ���� �����ִ� ����
		// ���� �ڽ� ����� �޸𸮸� ������ ��, �� �θ� ����� left�� NULL�� ������ش�.
		else if (previous->left != NULL)
			previous->left = NULL;

		// ������ �ڽ� ����� �޸𸮸� ������ ��, �� �θ� ����� right�� NULL�� ������ش�.
		else if (previous->right != NULL)
			previous->right = NULL;
	}

	free(head); // head node �޸� ����
}





