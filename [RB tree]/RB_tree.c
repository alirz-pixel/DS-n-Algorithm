// ==============  [ 과제#1 : 트리를 사용한 정렬 알고리즘 구현 ]  ==============
//                 
// 제출일자 : 2021-10-15                           작성자 : 2020039004 최문형
// 개발환경 : vscode에서 gcc(version : 6.3.0) 컴파일러 환경에서 코드를 짰습니다.
//
// 코드 작성 시간 : 2021-10-09  21:00 ~ 2021-10-10  06:15
// 주석 작성 시간 : 2021-10-14  19:43 ~ 2021-10-14  21:30 
//
// 과제 요구 사항 :
//   1. 정렬해야 할 키가 저장된 파일은 test.txt에 저장되어 있음
//      - 양의 정수로 구성되어 있음
//      - 중복되는 키 값은 없음
//      - 숫자와 숫자 사이는 공백(' ')으로 구분되어 있음
//      - 파일의 마지막에는 -1로 파일의 끝을 알림
//    
//   2. 상기 파일을 읽고 키값의 크기에 따라 Tree 자료구조에 저장하는 함수(알고리즘) 구현
//      - 자료구조 구현 및 삽입 알고리즘 구현
//      - 수업시간에 배운 아무 자료구조나 사용 가능함.
//      - 컴파일러는 C언어 gcc 컴파일러로 구현할 것
//
//   3. 구현한 Tree 자료구조에 저장된 내용을 기반해서 특정 key를 검색하는 함수(알고리즘) 구현
//      - key값을 입력값으로 주면 검색결과를 알려주는 함수 구현
// ===========================================================================

/********************************************************************
 * 참고자료 :
 * 1. Red-Black tree : https://slidesplayer.org/slide/16581725/
 * 2. runtime 속도 증가시키기 : https://modoocode.com/129
 * 3. recursive vs iterative : https://medium.com/backticks-tildes/iteration-vs-recursion-c2017a483890
 * 4. 반복문 vs 재귀문 (3번이랑 동일) : https://wonillism.tistory.com/17
********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ------------- [RB 트리를 위한 구조체 및 함수] -------------
typedef struct _Node {

	struct _Node* parent;     // 부모 노드의 주솟값를 가리키는 포인터 변수
	struct _Node* leftChild;  // 현 노드 기준 왼쪽 자식의 주솟값를 가리키는 포인터 변수
	struct _Node* rightChild; // 현 노드 기준 오른쪽 자식의 주솟값를 가리키는 포인터 변수
	int key;    // key값을 저장하는 변수
	bool color; // false = black,  true = red

} Node;

Node* NIL; // NIL = 리프 노드 (black 노드)


// RB트리를 위한 사용자 정의 함수
void init(Node** initNode, int key); // key값을 가진 노드를 생성
void inorder(Node* root); // iterator 방식으로 inorder 순으로 순회하는 함수
void recurInorder(Node* node, FILE* fp); // recursive 방식으로 inorder 순으로 순회하는 함수
void search(Node* search, int key);  // key값을 가진 노드를 찾는 함수
void insert(Node** root, int key);   // key값을 가진 노드를 RB 트리에 삽입
void findProblem(Node** root, Node* insertNode); // 삽입 시 생기는 문제의 case를 찾는 함수
Node* LLB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : LLB
Node* LRB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : LRB
Node* RRB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : RRB
Node* RLB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : RLB
Node* colorFlip(Node* xNode, Node* pNode, Node* ppNode);  // case : **R (s가 레드인 경우)
// -------------------------------------------------------------


// ------------- [ stack을 위한 구조체 및 함수 ] -------------
typedef struct _sNode {

	Node* data;
	struct _sNode* next;

} sNode;


// stack을 위한 사용자 정의 함수
void push(sNode** top, Node* insertData); // stack의 push 연산을 수행하는 함수
Node* pop(sNode** top); // stack의 pop연산을 수행하는 함수
// --------------------------------------------------



int main(void)
{
	// ------ [ NIL(=리프노드)의 초기설정 ] ------
	NIL = (Node*)malloc(sizeof(Node));

	if (NIL == NULL)
	{
		printf("메모리를 할당받지 못하였습니다.\n");
		return 0;
	}

	NIL->parent = NULL;     // insert 연산을 통해 parent 값이 변경될 예정이지만, 기본값으로는 NULL 값을 가리키도록 한다.
	NIL->leftChild = NULL;  // NIL 노드는 리프노드이므로 왼쪽 자식이 존재하지 않는다.
	NIL->rightChild = NULL; // NIL 노드는 리프노드이므로 오른쪽 자식이 존재하지 않는다.
	NIL->key = -1;      // NIL 노드에는 key값을 저장하지 않으므로 -1로 설정
	NIL->color = false; // NIL 노드는 black 노드이므로 false로 설정
	// ------------------------------------------

	Node* root = NULL; // root의 초기 설정을 NULL로 지정한다.
	init(&root, -1);   // init 함수를 통해 root의 왼/오른쪽 자식은 NIL 노드를 가리키며, 아직 데이터를 넣지 않았으므로 key 값은 -1로 초기화한다.

	FILE* pFile = fopen("test.txt", "r"); // read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}


	// 파일 읽기 성공
	while (true) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;

		// RB tree에 키 값으로 intTmep를 가지는 노드를 삽입해준다.
		insert(&root, intTemp);
	}
	printf("RB tree 생성을 성공적으로 마쳤습니다.\n\n");

	fclose(pFile);          // close file


	// 생성된 트리에서 키 검색
	int searchKey;
	printf("검색할 Key를 입력해 주세요 : \n");
	scanf("%d", &searchKey);
	search(root, searchKey);


	/* recursive 방식의 inorder 순회 (주석을 제거하면 사용하실 수 있습니다.) */
	FILE* pFile_output = fopen("sorting file.text", "w"); // 파일 이름은 sorting file의 형태로 반환
	recurInorder(root, pFile_output);
	fclose(pFile_output);

	/* iterator 방식의 inorder 순회 */
	// inorder(root);

	printf("\nsorting된 데이터를 \'sorting file.txt\'파일에 성공적으로 옮겼습니다.\n");


	return 0;
}


// key값을 가진 노드를 생성하는 함수
void init(Node** initNode, int key)
{

	(*initNode) = (Node*)malloc(sizeof(Node)); // 새로 만드려는 노드에 동적 메모리 할당.
	if (initNode == NULL)
	{
		printf("메모리를 할당받지 못하였습니다.\n");
		exit(0);
	}

	(*initNode)->rightChild = NIL; // 새로 삽입되는 노드는 리프노드로 NIL 노드를 가진다.
	(*initNode)->leftChild = NIL;  // 새로 삽입되는 노드는 리프노드로 NIL 노드를 가진다.
	(*initNode)->parent = NULL;    // parent는 insert함수에서 변경될 예정이므로 NULL값을 대입해둔다.
	(*initNode)->color = true;     // 새로 삽입되는 노드는 red노드 이므로 true로 설정한다.
	(*initNode)->key = key;        // 새로운 노드의 키값을 입력받은 키값으로 설정해준다.

}


// key값을 가진 노드를 찾는 함수
void search(Node* search, int key)
{
	FILE* F_searchKey = fopen("search file.text", "w"); // 파일 이름은 search file의 형태로 반환

	while (search != NIL) 
	{
		if (search->key == key) // 찾고자 하는 key값을 찾은 경우
		{
			// printf(" find key : [ %5d ]를 찾았습니다.\n", search->key); // 키의 값까지 출력할 경우, 시간이 좀 더 오래 걸려(평균 : 0.03 ~ 0.06) 조교님께서 답변해 주신 대로 키의 존재 여부만 알 수 있도록 하였음.
			printf(" 해당 키를 찾았습니다.\n"); 
			fprintf(F_searchKey, "해당 키를 찾았습니다.");

			fclose(F_searchKey); // file close
			return;
		}

		if (search->key < key)  // 찾고자 하는 키 값이 현재 방문중인 노드의 키값보다 큰 경우
			search = search->rightChild; // 현재 방문 중인 노드의 오른쪽 서브트리를 탐색
		else                    // 찾고자 하는 키 값이 현재 방문중인 노드의 키값보다 작은 경우
			search = search->leftChild;  // 현재 방문 중인 노드의 왼쪽 서브트리를 탐색
	}

	printf(" 해당 키를 찾지 못했습니다.\n");
	fprintf(F_searchKey, "해당 키를 찾지 못했습니다.");

	fclose(F_searchKey); // file close
}


void insert(Node** root, int key)
{
	if ((*root)->key == -1) // 트리에 아무 데이터도 없다면
	{
		(*root)->key = key;     // 루트 노드에 삽입하려는 키값 대입.
		(*root)->color = false; // 루트 노드는 black이여야 함 (특성 1번)
		return;                 // 실행시간 향상을 위해 불필요한 연산을 하지 않도록 함수 종료
	}

	Node* insertNode;
	init(&insertNode, key); // key값을 가진 삽입할 노드 생성

	Node* search = (*root);
	while (1)
	{
		if (search->key < key) // 삽입하려는 노드의 키값보다 현재 방문중인 키의 값이 더 작을 경우
		{                      // (현재 방문중인 노드 기준으로 오른쪽에 삽입)
			if (search->rightChild == NIL) // 삽입할 노드를 오른쪽 자식에 삽입해야 하는 경우엔, 
			{                              // 현재 방문중인 노드의 오른쪽 자식은 NIL값을 가지고 있다
				search->rightChild = insertNode; // 현재 방문중인 오른쪽 자식에 삽입하려는 노드를 넣어준다.
				insertNode->parent = search;     // 이렇게 삽입된 노드의 부모노드는 현재 방문중인 노드이다.
				break;
			}

			search = search->rightChild;  // 오른쪽 서브트리 탐색
		}

		else				   // 삽입하려는 노드의 키값보다 현재 탐색중인 키의 값이 더 클 경우
		{                      // (현재 방문중인 노드 기준으로 왼쪽에 삽입)
			if (search->leftChild == NIL) // 삽입할 노드를 왼쪽 자식에 삽입해야 하는 경우엔, 
			{                             // 현재 방문중인 노드의 왼쪽 자식은 NIL값을 가지고 있다.
				search->leftChild = insertNode; // 현재 방문중인 왼쪽 자식에 삽입하려는 노드를 넣어준다.
				insertNode->parent = search;    // 이렇게 삽입된 노드의 부모노드는 현재 방문중인 노드이다.
				break;
			}

			search = search->leftChild;  // 왼쪽 서브트리 탐색
		}
	}

	// 노드를 삽입한 후, 특성 3번이 깨졌는지 확인해주는 함수
	// 만약 특성 3번이 깨졌다면, 문제의 case를 찾은 후 해결까지 해주는 함수
	findProblem(root, insertNode);


	// findProblem에서 ColorFlip(**R 불균형)이 실행되었을 경우, root의 color 값이 red(=true)로 변경되었을 수도 있다.
	(*root)->color = false; // 따라서 특성 1번이 깨지지 않도록 root의 color 값을 false(=black)으로 설정한다.

	return;
}


void findProblem(Node** root, Node* xNode)
{
	// 재귀함수를 이용해서 문제가 생긴 부분을 다시 찾아도 되지만(recursive), 이 방식의 경우 실행시간에 영향을 주기 때문에 iterative 방식으로 구현하였다.
	while (xNode != NULL) // 프로그램에 문제가 생기지 않도록 xNode가 NULL일 경우, 반복문이 종료되도록 하였다.
	{
		// 노드가 삽입되거나 **R의 문제를 해결한 후, RB tree의 특성에는 영향이 없는 경우
		if (xNode->parent->color == false) // 즉, 3번 특성이 깨지지 않은 경우 (pNode가 블랙이어야 한다.)
		{
			// printf("아무 문제 없습니다 \n"); // 이 주석은 findProblem이 잘 동작하는지 확인하는 코드입니다. 현재 어떤 case의 문제가 발생했는지 알고 싶으시다면 주석을 제거하여 확인하시면 됩니다.
			return; // 이 함수를 종료시킨다.
		}


		// 노드 삽입으로 인해 RB tree의 특성을 만족하지 못하게 된 경우.
		Node* ppNode = xNode->parent->parent; // 강의자료의 그림처럼 ppNode를 설정한다.
		Node* pNode = xNode->parent;          // 강의자료의 그림처럼 pNode를 설정한다.


		// 이 아래는 case별로 해결 과정을 기술한 코드입니다.
		// 강의자료와는 다른 case로 나누어 해결하였습니다. 

		// 이 경우엔 L*B 문제
		if (!ppNode->rightChild->color) //즉, s Node의 컬러가 black인 경우
		{
			Node* change; // rotate 연산으로 인해 root가 변했을 경우, 변한 root의 주소를 담는 포인터 변수 선언

			// case: LLB
			if (pNode->leftChild == xNode)
			{
				// printf("LLB 문제 발생\n"); // 이 주석은 findProblem이 잘 동작하는지 확인하는 코드입니다. 현재 어떤 case의 문제가 발생했는지 알고 싶으시다면 주석을 제거하여 확인하시면 됩니다.
				change = LLB_Rotate(xNode, pNode, ppNode);
			}

			// case: LRB
			else
			{
				// printf("LRB 문제 발생\n"); // 이 주석은 findProblem이 잘 동작하는지 확인하는 코드입니다. 현재 어떤 case의 문제가 발생했는지 알고 싶으시다면 주석을 제거하여 확인하시면 됩니다.
				change = LRB_Rotate(xNode, pNode, ppNode);
			}


			if (change != NULL) 	// rotate연산으로 인해 root가 변하는 경우
				(*root) = change;   // root를 역참조하여 새로운 root(=change)로 교체한다.

			return;
		}

		// 이 경우엔 R*B 문제임
		else if (!ppNode->leftChild->color)
		{
			Node* change; // rotate 연산으로 인해 root가 변했을 경우, 변한 root의 주소를 담는 포인터 변수 선언

			// case: RRB
			if (pNode->rightChild == xNode)
			{
				// printf("RRB 문제 발생 [%d]\n", xNode->key); // 이 주석은 findProblem이 잘 동작하는지 확인하는 코드입니다. 현재 어떤 case의 문제가 발생했는지 알고 싶으시다면 주석을 제거하여 확인하시면 됩니다.
				change = RRB_Rotate(xNode, pNode, ppNode);
			}

			// case: RLB
			else
			{
				// printf("RLB 문제 발생\n"); // 이 주석은 findProblem이 잘 동작하는지 확인하는 코드입니다. 현재 어떤 case의 문제가 발생했는지 알고 싶으시다면 주석을 제거하여 확인하시면 됩니다.
				change = RLB_Rotate(xNode, pNode, ppNode);
			}


			if (change != NULL) 	// rotate연산으로 인해 root가 변하는 경우
				(*root) = change;   // root를 역참조하여 새로운 root(=change)로 교체한다.

			return;
		}

		// 이 경우엔 **R 문제임
		else
		{
			// printf("**R 문제 발생\n"); // 이 주석은 findProblem이 잘 동작하는지 확인하는 코드입니다. 현재 어떤 case의 문제가 발생했는지 알고 싶으시다면 주석을 제거하여 확인하시면 됩니다.
			xNode = colorFlip(xNode, pNode, ppNode);
		}
	}
}


Node* LLB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (pNode->rightChild != NIL) // pNode의 오른쪽 자식 노드가 NIL 노드가 아니라면 (= pNode의 오른쪽 자식이 리프노드가 아니라면)
	{                                          
		ppNode->leftChild = pNode->rightChild; // ppNode의 왼쪽자식으로 이동한 뒤
		pNode->rightChild->parent = ppNode;    // 이 자식노드의 부모 노드를 ppNode로 지정해줌.
	}
	else
		ppNode->leftChild = NIL;

	// ppNode가 있던 자리를 pNode가 차지하게 되었으므로
	pNode->parent = ppNode->parent; // 기존 ppNode의 parent를 pNode의 parent로 옮김.

	xNode->parent = pNode;      // xNode의 parent를 pNode로 새로 대입
	ppNode->parent = pNode;     // ppNode의 parent를 pNode로 새로 대입
	pNode->rightChild = ppNode; // pNode의 오른쪽 자식노드가 ppNode를 가리키도록 설정

	pNode->color = false; // 노드의 색을 바꾸어 특성 3번에 문제가 생기지 않도록 함.
	ppNode->color = true;

	if (pNode->parent != NULL) // pNode의 parent->child를 다시 설정해주기 위해 우선 NULL이 아닌지부터 체크한다. (= pNode가 root인지 확인한다.)
	{
		if (pNode->parent->key < pNode->key)   // pNode->key가 pNode의 parent->key보다 크다면, pNode는 부모의 오른쪽 자식임
			pNode->parent->rightChild = pNode; // pNode의 parent가 바뀌면서 pNode->parent->rightChild도 pNode를 가리키도록 함.

		else								  // pNode->key가 pNode의 parent->key보다 작다면, pNode는 부모의 왼쪽 자식임
			pNode->parent->leftChild = pNode; // pNode의 parent가 바뀌면서 pNode->parent->leftChild도 pNode를 가리키도록 함.

		return NULL; // NULL 값을 반환했다는 뜻은 회전이 일어났음에도 root의 변화는 없다는 것을 의미한다.
	}

	return pNode; // rotate 연산으로 인해 root의 값이 변경되었으므로 변경된 root의 주소값을 반환한다.
}

Node* LRB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (xNode->rightChild != NIL) // pNode의 오른쪽 자식 노드가 NIL 노드가 아니라면
	{
		ppNode->leftChild = xNode->rightChild; // ppNode의 왼쪽자식으로 이동한 뒤
		xNode->rightChild->parent = ppNode;    // 이 자식노드의 부모 노드를 ppNode로 지정해줌.
	}
	else
		ppNode->leftChild = NIL;

	if (xNode->leftChild != NIL) // xNode의 왼쪽 자식 노드가 NIL 노드가 아니라면
	{
		pNode->rightChild = xNode->leftChild; // pNode의 오른쪽 자식으로 이동한 뒤
		xNode->leftChild->parent = pNode;     // 이 자식노드의 부모 노드를 pNode로 지정해줌.
	}
	else
		pNode->rightChild = NIL;


	// ppNode가 있던 자리를 xNode가 차지하게 되었으므로
	xNode->parent = ppNode->parent; // 기존 ppNode의 parent를 xNode의 parent로 옮김.

	pNode->parent = xNode;      // pNode의 parent를 xNode로 새로 대입
	ppNode->parent = xNode;     // ppNode의 parent를 xNode로 새로 대입
	xNode->leftChild = pNode;   // xNode의 왼쪽 자식노드가 pNode를 가리키도록 함
	xNode->rightChild = ppNode; // xNode의 오른쪽 자식노드가 ppNode를 가리키도록 함

	xNode->color = false; // 노드의 색을 바꾸어 특성 3번에 문제가 생기지 않도록 함.
	ppNode->color = true;

	if (xNode->parent != NULL) // xNode의 parent->child를 다시 설정해주기 위해 우선 NULL이 아닌지부터 체크한다. (= xNode가 root인지 확인한다.)
	{
		if (xNode->parent->key < xNode->key)   // xNode->key가 xNode의 parent->key보다 크다면, xNode는 부모의 오른쪽 자식임
			xNode->parent->rightChild = xNode; // xNode의 parent가 바뀌면서 xNode->parent->rightChild도 xNode를 가리키도록 함.

		else								  // xNode->key가 xNode의 parent->key보다 작다면, xNode는 부모의 왼쪽 자식임
			xNode->parent->leftChild = xNode; // xNode의 parent가 바뀌면서 xNode->parent->leftChild도 xNode를 가리키도록 함.

		return NULL; // NULL 값을 반환했다는 뜻은 회전이 일어났음에도 root의 변화는 없다는 것을 의미한다.
	}

	return xNode; // rotate 연산으로 인해 root의 값이 변경되었으므로 변경된 root의 주소값을 반환한다.
}

Node* RRB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (pNode->leftChild != NIL) // pNode의 왼쪽 자식 노드가 NIL 노드가 아니라면
	{
		ppNode->rightChild = pNode->leftChild; // ppNode의 오른쪽자식으로 이동한 뒤
		pNode->leftChild->parent = ppNode;    // 이 자식노드의 부모 노드를 ppNode로 지정해줌.
	}
	else
		ppNode->rightChild = NIL;


	// ppNode가 있던 자리를 pNode가 차지하게 되었으므로
	pNode->parent = ppNode->parent; // 기존 ppNode의 parent를 pNode의 parent로 옮김.

	xNode->parent = pNode;      // xNode의 parent를 pNode로 새로 대입
	ppNode->parent = pNode;     // ppNode의 parent를 pNode로 새로 대입
	pNode->leftChild = ppNode; // pNode의 왼쪽 자식노드가 ppNode를 가리키도록 설정

	pNode->color = false; // 노드의 색을 바꾸어 특성 3번에 문제가 생기지 않도록 함.
	ppNode->color = true;

	if (pNode->parent != NULL) // pNode의 parent->child를 다시 설정해주기 위해 우선 NULL이 아닌지부터 체크한다. (= pNode가 root인지 확인한다.)
	{
		if (pNode->parent->key < pNode->key)   // pNode->key가 pNode의 parent->key보다 크다면, pNode는 부모의 오른쪽 자식임
			pNode->parent->rightChild = pNode; // pNode의 parent가 바뀌면서 pNode->parent->rightChild도 pNode를 가리키도록 함.

		else								  // pNode->key가 pNode의 parent->key보다 작다면, pNode는 부모의 왼쪽 자식임
			pNode->parent->leftChild = pNode; // pNode의 parent가 바뀌면서 pNode->parent->leftChild도 pNode를 가리키도록 함.

		return NULL; // NULL 값을 반환했다는 뜻은 회전이 일어났음에도 root의 변화는 없다는 것을 의미한다.
	}

	return pNode; // rotate 연산으로 인해 root의 값이 변경되었으므로 변경된 root의 주소값을 반환한다.
}

Node* RLB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (xNode->rightChild != NIL) // pNode의 오른쪽 자식 노드가 NIL 노드가 아니라면
	{
		pNode->leftChild = xNode->rightChild; // pNode의 왼쪽 자식으로 이동한 뒤
		xNode->rightChild->parent = pNode;     // 이 자식노드의 부모 노드를 pNode로 지정해줌.
	}
	else
		pNode->leftChild = NIL;

	if (xNode->leftChild != NIL) // xNode의 왼쪽 자식 노드가 NIL 노드가 아니라면
	{
		ppNode->rightChild = xNode->leftChild; // ppNode의 오른쪽 자식으로 이동한 뒤
		xNode->leftChild->parent = ppNode;    // 이 자식노드의 부모 노드를 ppNode로 지정해줌.
	}
	else
		ppNode->rightChild = NIL;


	// ppNode가 있던 자리를 xNode가 차지하게 되었으므로
	xNode->parent = ppNode->parent;    // 기존 ppNode의 parent를 xNode의 parent로 옮김.

	pNode->parent = xNode;      // pNode의 parent를 xNode로 새로 대입
	ppNode->parent = xNode;     // ppNode의 parent를 xNode로 새로 대입
	xNode->rightChild = pNode;  // xNode의 오른쪽 자식노드가 pNode를 가리키도록 함
	xNode->leftChild = ppNode;  // xNode의 왼쪽 자식노드가 ppNode를 가리키도록 함


	xNode->color = false; // 노드의 색을 바꾸어 특성 3번에 문제가 생기지 않도록 함.
	ppNode->color = true;


	if (xNode->parent != NULL) // xNode의 parent->child를 다시 설정해주기 위해 우선 NULL이 아닌지부터 체크한다. (= xNode가 root인지 확인한다.)
	{
		if (xNode->parent->key < xNode->key)   // xNode->key가 xNode의 parent->key보다 크다면, xNode는 부모의 오른쪽 자식임
			xNode->parent->rightChild = xNode; // xNode의 parent가 바뀌면서 xNode->parent->rightChild도 xNode를 가리키도록 함.

		else								  // xNode->key가 xNode의 parent->key보다 작다면, xNode는 부모의 왼쪽 자식임
			xNode->parent->leftChild = xNode; // xNode의 parent가 바뀌면서 xNode->parent->leftChild도 xNode를 가리키도록 함.

		return NULL; // NULL 값을 반환했다는 뜻은 회전이 일어났음에도 root의 변화는 없다는 것을 의미한다.
	}

	return xNode; // rotate 연산으로 인해 root의 값이 변경되었으므로 변경된 root의 주소값을 반환한다.
}

Node* colorFlip(Node* xNode, Node* pNode, Node* ppNode)
{
	ppNode->color = true;              // 삽입된 노드의 조부모 color값을 레드(=true)로 바꿔준다.
	ppNode->leftChild->color = false;  // 조부모의 왼쪽자식을 블랙(=false)로 바꿔준다.
	ppNode->rightChild->color = false; // 위와 마찬가지로 조부모의 오른쪽자식을 블랙(=false)로 바꿔준다.

	if (ppNode->parent == NULL) // ppNode가 root인 경우에는 더이상 문제를 찾을 필요가 없다. (=findProblem 함수를 실행할 필요가 없다.)
		return NULL;            // 따라서 NULL값을 반환해준다.


	return ppNode; // colorFlip을 하고나면 ppNode에서 같은 문제가 발생했을 수도 있다. 따라서 ppNode를 다시 xNode로 보고 문제가 있는지 확인하기 위해 ppNode를 반환한다.
}


// RB 트리의 데이터들을 파일로 옮기는 함수이다. (inorder 방식으로 RB 트리를 탐색할 경우, 정렬된 형태로 반환이 가능하다.)
void recurInorder(Node* node, FILE* fp)
{
	// Inorder 순회를 recursive 방식으로 짜게될 경우,
	// iterator 방식과 실행시간의 차이는 크게 없지만 평균 '0.02 ~ 0.04'초 정도 더 걸리는 문제점이 발생하여
	// 기본으로는 iterator 방식으로 Inorder 순회를 돌도록 코드를 작성하였음.
	if (node != NIL) // 현재 방문 중인 노드가 리프 노드가 아닐 경우
	{
		recurInorder(node->leftChild, fp);  // 왼쪽 자식을 먼저 순회한 후에
		fprintf(fp, "%d ", node->key);      // 현재 방문 중인 노드의 key 값을 파일에 옮겨준다.
		recurInorder(node->rightChild, fp); // 그리고 오른쪽 자식을 순회한다.
	}
}

// RB 트리의 데이터들을 파일로 옮기는 함수이다. (inorder 방식으로 RB 트리를 탐색할 경우, 정렬된 형태로 반환이 가능하다.)
void inorder(Node* root)
{
	// 이 함수를 recursive 방식으로 짜게되면 되게 간단하게 코드를 짤 수 있다.
	// 하지만 참고자료 3, 4번과 같이 recursive 방식으로 짜게될 경우, 실행시간이 늘어난다는 단점이 존재한다.
	// 따라서 recursive 방식이 아닌 iterator 방식으로 코드를 짜게되었다.


	//파일 형태로 반환하기 위한 FILE 포인터 변수 선언
	FILE* pFile_output = fopen("sorting file.text", "w"); // 파일 이름은 sorting file의 형태로 반환


	Node* search = root; // RB tree에서 현재 방문중인 노드를 알기위한 RB tree의 Node 포인터 변수 선언
	sNode* top = NULL;   // stack을 위한 top 변수를 만든 뒤 NULL 값으로 초기 설정해준다.
	push(&top, NIL);     // 반복문이 종료될 수 있도록 하기 위해 stack에 NIL 노드를 맨 처음에 넣어준다.


	// Left -> visit -> Right 탐색을 할 예정 (= inorder)
	while (1)
	{
		for (; search != NIL; search = search->leftChild) // 더 이상 왼쪽 자식이 없을 떄까지 반복한다.
			push(&top, search);  // 반복하면서 방문한 노드들을 stack에 저장해준다.

		search = pop(&top); // 위의 반복문이 끝났다면 '가운데(visit)'를 방문하기 위해 stack의 값을 하나 가져온다 (=pop)
		if (search == NIL)  break; // stack에 아무 노드도 들어있지 않았다면 이대로 반복문을 종료한다.

		fprintf(pFile_output, "%d ", search->key); // 방문한 노드의 key값을 sorting fild에다가 적어준다.
		search = search->rightChild; // 그 후, 오른쪽 자식(=Right)을 탐색한다.
	}


	fclose(pFile_output); // close file
}

// stack의 push 연산을 수행하는 함수
void push(sNode** top, Node* insertData)
{
	sNode* newTop = (sNode*)malloc(sizeof(sNode)); // push 후 변경될 top을 가리키는 임시 변수
	if (newTop == NULL)
	{
		printf("메모리를 할당받지 못하였습니다.\n");
		exit(0);
	}

	newTop->data = insertData; // 새로 생길 (임시)top에 현재 방문 중인 노드를 넣어준다.
	newTop->next = (*top);     // 그 후, 기존의 top을 새로 생길 (임시)top의 next로 지정해준다.

	(*top) = newTop; // 새로 생긴 (임시)top을 stack의 top이 되도록 대입해준다.
}

// stack의 pop연산을 수행하는 함수
Node* pop(sNode** top)
{
	sNode* delNode = (*top);      // 메모리를 해제하기 위해 delNode에 기존의 top을 저장해둔다.
	Node* popNode = (*top)->data; // 반환할 노드를 popNode에 저장한다.

	(*top) = (*top)->next; // pop 연산을 수행했으므로 top을 기존 top의 next로 변경해준다.

	free(delNode);  // pop하기 전의 top에 할당된 메모리를 해제해준다.
	return popNode; // pop한 노드를 반환해준다.
}