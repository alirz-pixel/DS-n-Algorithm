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
	printf("[----- [최문형] [2020039004] -----]\n");

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
	if (*h == NULL) // 메모리를 할당받지 못했을 경우
	{
		printf("Error! : 메모리를 할당받지 못하였습니다.\n");
		return -1;
	}

	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{   // 중위순회는 왼쪽 서브 트리 -> 노드 방문 -> 오른쪽 서브 트리 순으로 진행되므로
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);  // 왼쪽 서브 트리를 중위 순회 한다.
		printf("[ %d ] ", ptr->key);  // 노드를 방문한다.
		inorderTraversal(ptr->right); // 오른쪽 서브 트리를 중위 순회 한다.
	}
}

void preorderTraversal(Node* ptr)
{   // 전위순회는 노드 방문 -> 왼쪽 서브 트리 -> 오른쪽 서브 트리 순으로 진행되므로
	if (ptr != NULL)
	{
		printf("[ %d ] ", ptr->key);   // 노드를 방문한다.
		preorderTraversal(ptr->left);  // 왼쪽 서브 트리를 전위 순회한다.
		preorderTraversal(ptr->right); // 오른쪽 서브 트리를 전위 순회한다.
	}
}

void postorderTraversal(Node* ptr)
{   // 후위 순회는 왼쪽 서브 트리 -> 오른쪽 서브 트리 -> 노드 방문 순으로 진행되므로
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);  // 왼쪽 서브 트리를 후위 순회한다.
		postorderTraversal(ptr->right); // 오른쪽 서브 트리를 후위 순회한다.
		printf("[ %d ] ", ptr->key);    // 노드를 방문한다.
	}
}


int insert(Node* head, int key)
{

	// initializeBST가 제대로 수행되지 않았을 경우
	if (head == NULL)
	{
		printf("Error! : initializeBST가 제대로 수행되었는지 확인해 주세요.\n");
		return -1;
	}

	Node *newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) // 메모리를 할당받지 못했을 경우
	{
		printf("Error! : 메모리를 할당받지 못해 insert를 제대로 수행하지 못하였습니다.\n");
		return -1;
	}

	newNode->key = key;
	newNode->left = newNode->right = NULL;

	// 트리에 아무 데이터도 없을 경우, newNode를 루트노드로 설정한다.
	if (head->left == NULL)
		head->left = newNode;
	
	else
	{
		Node *searchNode = head->left; // searchNode를 루트 노드로 설정함

		// searchNode가 리프 노드이거나 searchNode의 key값과 입력받은 key값이 같을 때까지 반복
		while ((searchNode->left != NULL || searchNode->right != NULL) && searchNode->key != key)
		{
			// searchNode의 key 값보다 입력받은 key 값이 큰 경우
			if (searchNode->key < key) 
			{
				if (searchNode->right == NULL)  // 이 노드 오른쪽에 newNode를 삽입해야 하므로 반복문 종료
					break;

				searchNode = searchNode->right; // searchNode가 리프 노드가 아닐 경우, searchNode의 오른쪽 서브 트리 탐색
			}

			// searchNode의 key 값보다 입력받은 key 값이 큰 경우
			else 
			{
				if (searchNode->left == NULL)  // 이 노드 왼쪽에 newNode를 삽입해야 하므로 반복문 종료
					break;

				searchNode = searchNode->left; // searchNode가 리프 노드가 아닐 경우, searchNode의 왼쪽 서브 트리 탐색
			}
		}

		
		// 트리에 이미 있는 값을 입력받은 경우, 삽입을 진행하지 않고 함수를 종료한다.
		if (searchNode->key == key)
		{
			printf("Error! : 트리에 이미 추가되어 있는 key 값입니다.\n");
			return -1;
		}

		// searchNode의 key값 보다 입력받은 key값이 크므로 오른쪽에 노드를 삽입한다.
		if (searchNode->key < key) 
			searchNode->right = newNode;

		// searchNode의 key값 보다 입력받은 key값이 작으므로 왼쪽에 노드를 삽입한다.
		else 
			searchNode->left = newNode;
	}

	return 1;
}

int deleteLeafNode(Node* head, int key)
{

	// initializeBST가 제대로 수행되지 않았을 경우
	if (head == NULL)
	{
		printf("Error! : initializeBST가 제대로 수행되었는지 확인해 주세요.\n");
		return -1;
	}

	// 트리에 아무 데이터도 없을 경우
	if (head->left == NULL)
	{
		printf("Error! : 트리에 아무 데이터도 없습니다.\n");
		return -1;
	}


	Node *previous = head;
	Node *searchNode = head->left; 

	// searchNode가 left node 일 때까지 반복
	while (searchNode->left != NULL || searchNode->right != NULL)
	{
		previous = searchNode;

		// 현재 노드의 key값과 입력받은 key값이 같은 경우, 반복문 종료
		if (searchNode->key == key) break;

		// searchNode의 key 값보다 입력받은 key 값이 큰 경우
		if (searchNode->key < key)
		{
			// 만약, serahcNode의 오른쪽 자식 노드가 없는 경우
			if (searchNode->right == NULL)
				break;
			
			// 아닐 경우, searchNode의 오른쪽 서브 트리 탐색
			searchNode = searchNode->right;
		}

		// searchNode의 key값이 입력받은 key값보다 작은 경우
		else 
		{
			// 만약, serahcNode의 왼쪽 자식 노드가 없는 경우
			if (searchNode->left == NULL)
				break;

			// 아닐 경우, seasrchNode의 왼쪽 서브 트리 탐색
			searchNode = searchNode->left;
		}
	}

	// 삭제하고자 하는 key값이 없는 경우
	if (searchNode->key != key)
	{
		printf("삭제하고자 하는 노드가 트리에 없습니다.\n");
		return -1;
	}

	// 입력받은 key값과 동일한 key값을 가지는 노드는 찾았으나, leaf node가 아닌 경우
	if (searchNode->left != NULL || searchNode->right != NULL)
	{
		printf("the node [%d] is not a leaf\n", searchNode->key);
		return -1;
	}

	
	free(searchNode);

	// 루트 노드일 때
	if (previous == head)
		head->left = NULL;
	
	// 오른쪽 자식 노드의 메모리를 해제한 후, 이 부모 노드의 right를 NULL로 만들어준다.
	else if (previous->key < key)
		previous->right = NULL;

	// 왼쪽 자식 노드의 메모리를 해제한 후, 이 부모 노드의 left를 NULL로 만들어준다.
	else
		previous->left = NULL;

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL) return NULL; // 트리에 아무 데이터도 없거나 탐색에 실패할 경우, NULL 반환
	if (ptr->key > key) return searchRecursive(ptr->left, key);  // 현재 노드의 key값보다 입력받은 key값이 작은 경우, 왼쪽 서브 트리 탐색
	if (ptr->key < key) return searchRecursive(ptr->right, key); // 현재 노드의 key값보다 입력받은 key값이 큰 경우, 오른쪽 서브 트리 탐색

	return ptr; // 탐색에 성공한 경우, 찾은 노드의 주소를 반환한다.
}

Node* searchIterative(Node* head, int key)
{

	// 트리에 아무 데이터가 없거나 head의 메모리가 할당되어 있지 않은 경우
	if (head == NULL) return NULL;
	if (head->left == NULL) return NULL;


	Node *searchNode = head->left; // saerchNode를 루트 노드로 설정
	while (searchNode->left != NULL || searchNode->right != NULL) // searchNode가 leaf node일 때까지 반복
	{
		// 현재 노드의 key값과 입력받은 key값이 같은 경우, 반복문 종료
		if (searchNode->key == key) break; 

		// searchNode의 key 값보다 입력받은 key 값이 큰 경우
		if (searchNode->key < key)
		{
			// 만약, serahcNode의 오른쪽 자식 노드가 없는 경우, 탐색에 실패했으므로 NULL 반환
			if (searchNode->right == NULL)
				return NULL;
			
			// 아닐 경우, searchNode의 오른쪽 서브 트리 탐색
			searchNode = searchNode->right;
		} 
			
		else 
		{
			// 만약, serahcNode의 왼쪽 자식 노드가 없는 경우, 탐색에 실패했으므로 NULL 반환
			if (searchNode->left == NULL)
				return NULL;

			// 아닐 경우, seasrchNode의 왼쪽 서브 트리 탐색
			searchNode = searchNode->left;
		}
	}

	// 탐색에 성공한 경우, 찾은 노드의 주소를 반환한다.
	if (searchNode->key == key) return searchNode;
	return NULL;
}


int freeBST(Node* head)
{

	// head의 메모리가 할당되어 있지 않은 경우
	if (head == NULL)
	{
		printf("Error! : 할당된 메모리가 존재하지 않아 freeBST를 수행하지 못했습니다.\n");
		return -1;
	}

	
	Node *searchNode, *previous;
	int i = 0;
	
	// Postorder Traversal 로 탐색하며, 메모리를 해제한다.
	while (head->left != NULL) // 루트 노드가 NULL일 때까지 반복
	{
		previous = head;
		searchNode = head->left;

		// searchNode가 left node 일 때까지 반복
		while (searchNode->left != NULL || searchNode->right != NULL)
		{
			previous = searchNode;

			if (searchNode->left != NULL) // 왼쪽 서브 트리부터 탐색을 시작한다.
				searchNode = searchNode->left;

			else // 왼쪽 자식 노드가 NULL일 경우, 오른쪽 서브 트리를 탐색한다.
				searchNode = searchNode->right;
		}
		free(searchNode); // leaf node 메모리 해제 또는 루트 노드 메모리 해제


		// 루트 노드일 때 반복문 빠져나오기 (루트 노드일 때, previous는 head를 가리킴)
		if (previous == head) 
			break;

		// 삭제한 leaf node의 연결 끊어주는 역할
		// 왼쪽 자식 노드의 메모리를 해제한 후, 이 부모 노드의 left를 NULL로 만들어준다.
		else if (previous->left != NULL)
			previous->left = NULL;

		// 오른쪽 자식 노드의 메모리를 해제한 후, 이 부모 노드의 right를 NULL로 만들어준다.
		else if (previous->right != NULL)
			previous->right = NULL;
	}

	free(head); // head node 메모리 해제
}





