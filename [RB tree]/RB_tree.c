// ==============  [ ����#1 : Ʈ���� ����� ���� �˰��� ���� ]  ==============
//                 
// �������� : 2021-10-15                           �ۼ��� : 2020039004 �ֹ���
// ����ȯ�� : vscode���� gcc(version : 6.3.0) �����Ϸ� ȯ�濡�� �ڵ带 ®���ϴ�.
//
// �ڵ� �ۼ� �ð� : 2021-10-09  21:00 ~ 2021-10-10  06:15
// �ּ� �ۼ� �ð� : 2021-10-14  19:43 ~ 2021-10-14  21:30 
//
// ���� �䱸 ���� :
//   1. �����ؾ� �� Ű�� ����� ������ test.txt�� ����Ǿ� ����
//      - ���� ������ �����Ǿ� ����
//      - �ߺ��Ǵ� Ű ���� ����
//      - ���ڿ� ���� ���̴� ����(' ')���� ���еǾ� ����
//      - ������ ���������� -1�� ������ ���� �˸�
//    
//   2. ��� ������ �а� Ű���� ũ�⿡ ���� Tree �ڷᱸ���� �����ϴ� �Լ�(�˰���) ����
//      - �ڷᱸ�� ���� �� ���� �˰��� ����
//      - �����ð��� ��� �ƹ� �ڷᱸ���� ��� ������.
//      - �����Ϸ��� C��� gcc �����Ϸ��� ������ ��
//
//   3. ������ Tree �ڷᱸ���� ����� ������ ����ؼ� Ư�� key�� �˻��ϴ� �Լ�(�˰���) ����
//      - key���� �Է°����� �ָ� �˻������ �˷��ִ� �Լ� ����
// ===========================================================================

/********************************************************************
 * �����ڷ� :
 * 1. Red-Black tree : https://slidesplayer.org/slide/16581725/
 * 2. runtime �ӵ� ������Ű�� : https://modoocode.com/129
 * 3. recursive vs iterative : https://medium.com/backticks-tildes/iteration-vs-recursion-c2017a483890
 * 4. �ݺ��� vs ��͹� (3���̶� ����) : https://wonillism.tistory.com/17
********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ------------- [RB Ʈ���� ���� ����ü �� �Լ�] -------------
typedef struct _Node {

	struct _Node* parent;     // �θ� ����� �ּڰ��� ����Ű�� ������ ����
	struct _Node* leftChild;  // �� ��� ���� ���� �ڽ��� �ּڰ��� ����Ű�� ������ ����
	struct _Node* rightChild; // �� ��� ���� ������ �ڽ��� �ּڰ��� ����Ű�� ������ ����
	int key;    // key���� �����ϴ� ����
	bool color; // false = black,  true = red

} Node;

Node* NIL; // NIL = ���� ��� (black ���)


// RBƮ���� ���� ����� ���� �Լ�
void init(Node** initNode, int key); // key���� ���� ��带 ����
void inorder(Node* root); // iterator ������� inorder ������ ��ȸ�ϴ� �Լ�
void recurInorder(Node* node, FILE* fp); // recursive ������� inorder ������ ��ȸ�ϴ� �Լ�
void search(Node* search, int key);  // key���� ���� ��带 ã�� �Լ�
void insert(Node** root, int key);   // key���� ���� ��带 RB Ʈ���� ����
void findProblem(Node** root, Node* insertNode); // ���� �� ����� ������ case�� ã�� �Լ�
Node* LLB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : LLB
Node* LRB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : LRB
Node* RRB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : RRB
Node* RLB_Rotate(Node* xNode, Node* pNode, Node* ppNode); // case : RLB
Node* colorFlip(Node* xNode, Node* pNode, Node* ppNode);  // case : **R (s�� ������ ���)
// -------------------------------------------------------------


// ------------- [ stack�� ���� ����ü �� �Լ� ] -------------
typedef struct _sNode {

	Node* data;
	struct _sNode* next;

} sNode;


// stack�� ���� ����� ���� �Լ�
void push(sNode** top, Node* insertData); // stack�� push ������ �����ϴ� �Լ�
Node* pop(sNode** top); // stack�� pop������ �����ϴ� �Լ�
// --------------------------------------------------



int main(void)
{
	// ------ [ NIL(=�������)�� �ʱ⼳�� ] ------
	NIL = (Node*)malloc(sizeof(Node));

	if (NIL == NULL)
	{
		printf("�޸𸮸� �Ҵ���� ���Ͽ����ϴ�.\n");
		return 0;
	}

	NIL->parent = NULL;     // insert ������ ���� parent ���� ����� ����������, �⺻�����δ� NULL ���� ����Ű���� �Ѵ�.
	NIL->leftChild = NULL;  // NIL ���� ��������̹Ƿ� ���� �ڽ��� �������� �ʴ´�.
	NIL->rightChild = NULL; // NIL ���� ��������̹Ƿ� ������ �ڽ��� �������� �ʴ´�.
	NIL->key = -1;      // NIL ��忡�� key���� �������� �����Ƿ� -1�� ����
	NIL->color = false; // NIL ���� black ����̹Ƿ� false�� ����
	// ------------------------------------------

	Node* root = NULL; // root�� �ʱ� ������ NULL�� �����Ѵ�.
	init(&root, -1);   // init �Լ��� ���� root�� ��/������ �ڽ��� NIL ��带 ����Ű��, ���� �����͸� ���� �ʾ����Ƿ� key ���� -1�� �ʱ�ȭ�Ѵ�.

	FILE* pFile = fopen("test.txt", "r"); // read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}


	// ���� �б� ����
	while (true) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;

		// RB tree�� Ű ������ intTmep�� ������ ��带 �������ش�.
		insert(&root, intTemp);
	}
	printf("RB tree ������ ���������� ���ƽ��ϴ�.\n\n");

	fclose(pFile);          // close file


	// ������ Ʈ������ Ű �˻�
	int searchKey;
	printf("�˻��� Key�� �Է��� �ּ��� : \n");
	scanf("%d", &searchKey);
	search(root, searchKey);


	/* recursive ����� inorder ��ȸ (�ּ��� �����ϸ� ����Ͻ� �� �ֽ��ϴ�.) */
	FILE* pFile_output = fopen("sorting file.text", "w"); // ���� �̸��� sorting file�� ���·� ��ȯ
	recurInorder(root, pFile_output);
	fclose(pFile_output);

	/* iterator ����� inorder ��ȸ */
	// inorder(root);

	printf("\nsorting�� �����͸� \'sorting file.txt\'���Ͽ� ���������� �Ű���ϴ�.\n");


	return 0;
}


// key���� ���� ��带 �����ϴ� �Լ�
void init(Node** initNode, int key)
{

	(*initNode) = (Node*)malloc(sizeof(Node)); // ���� ������� ��忡 ���� �޸� �Ҵ�.
	if (initNode == NULL)
	{
		printf("�޸𸮸� �Ҵ���� ���Ͽ����ϴ�.\n");
		exit(0);
	}

	(*initNode)->rightChild = NIL; // ���� ���ԵǴ� ���� �������� NIL ��带 ������.
	(*initNode)->leftChild = NIL;  // ���� ���ԵǴ� ���� �������� NIL ��带 ������.
	(*initNode)->parent = NULL;    // parent�� insert�Լ����� ����� �����̹Ƿ� NULL���� �����صд�.
	(*initNode)->color = true;     // ���� ���ԵǴ� ���� red��� �̹Ƿ� true�� �����Ѵ�.
	(*initNode)->key = key;        // ���ο� ����� Ű���� �Է¹��� Ű������ �������ش�.

}


// key���� ���� ��带 ã�� �Լ�
void search(Node* search, int key)
{
	FILE* F_searchKey = fopen("search file.text", "w"); // ���� �̸��� search file�� ���·� ��ȯ

	while (search != NIL) 
	{
		if (search->key == key) // ã���� �ϴ� key���� ã�� ���
		{
			// printf(" find key : [ %5d ]�� ã�ҽ��ϴ�.\n", search->key); // Ű�� ������ ����� ���, �ð��� �� �� ���� �ɷ�(��� : 0.03 ~ 0.06) �����Բ��� �亯�� �ֽ� ��� Ű�� ���� ���θ� �� �� �ֵ��� �Ͽ���.
			printf(" �ش� Ű�� ã�ҽ��ϴ�.\n"); 
			fprintf(F_searchKey, "�ش� Ű�� ã�ҽ��ϴ�.");

			fclose(F_searchKey); // file close
			return;
		}

		if (search->key < key)  // ã���� �ϴ� Ű ���� ���� �湮���� ����� Ű������ ū ���
			search = search->rightChild; // ���� �湮 ���� ����� ������ ����Ʈ���� Ž��
		else                    // ã���� �ϴ� Ű ���� ���� �湮���� ����� Ű������ ���� ���
			search = search->leftChild;  // ���� �湮 ���� ����� ���� ����Ʈ���� Ž��
	}

	printf(" �ش� Ű�� ã�� ���߽��ϴ�.\n");
	fprintf(F_searchKey, "�ش� Ű�� ã�� ���߽��ϴ�.");

	fclose(F_searchKey); // file close
}


void insert(Node** root, int key)
{
	if ((*root)->key == -1) // Ʈ���� �ƹ� �����͵� ���ٸ�
	{
		(*root)->key = key;     // ��Ʈ ��忡 �����Ϸ��� Ű�� ����.
		(*root)->color = false; // ��Ʈ ���� black�̿��� �� (Ư�� 1��)
		return;                 // ����ð� ����� ���� ���ʿ��� ������ ���� �ʵ��� �Լ� ����
	}

	Node* insertNode;
	init(&insertNode, key); // key���� ���� ������ ��� ����

	Node* search = (*root);
	while (1)
	{
		if (search->key < key) // �����Ϸ��� ����� Ű������ ���� �湮���� Ű�� ���� �� ���� ���
		{                      // (���� �湮���� ��� �������� �����ʿ� ����)
			if (search->rightChild == NIL) // ������ ��带 ������ �ڽĿ� �����ؾ� �ϴ� ��쿣, 
			{                              // ���� �湮���� ����� ������ �ڽ��� NIL���� ������ �ִ�
				search->rightChild = insertNode; // ���� �湮���� ������ �ڽĿ� �����Ϸ��� ��带 �־��ش�.
				insertNode->parent = search;     // �̷��� ���Ե� ����� �θ���� ���� �湮���� ����̴�.
				break;
			}

			search = search->rightChild;  // ������ ����Ʈ�� Ž��
		}

		else				   // �����Ϸ��� ����� Ű������ ���� Ž������ Ű�� ���� �� Ŭ ���
		{                      // (���� �湮���� ��� �������� ���ʿ� ����)
			if (search->leftChild == NIL) // ������ ��带 ���� �ڽĿ� �����ؾ� �ϴ� ��쿣, 
			{                             // ���� �湮���� ����� ���� �ڽ��� NIL���� ������ �ִ�.
				search->leftChild = insertNode; // ���� �湮���� ���� �ڽĿ� �����Ϸ��� ��带 �־��ش�.
				insertNode->parent = search;    // �̷��� ���Ե� ����� �θ���� ���� �湮���� ����̴�.
				break;
			}

			search = search->leftChild;  // ���� ����Ʈ�� Ž��
		}
	}

	// ��带 ������ ��, Ư�� 3���� �������� Ȯ�����ִ� �Լ�
	// ���� Ư�� 3���� �����ٸ�, ������ case�� ã�� �� �ذ���� ���ִ� �Լ�
	findProblem(root, insertNode);


	// findProblem���� ColorFlip(**R �ұ���)�� ����Ǿ��� ���, root�� color ���� red(=true)�� ����Ǿ��� ���� �ִ�.
	(*root)->color = false; // ���� Ư�� 1���� ������ �ʵ��� root�� color ���� false(=black)���� �����Ѵ�.

	return;
}


void findProblem(Node** root, Node* xNode)
{
	// ����Լ��� �̿��ؼ� ������ ���� �κ��� �ٽ� ã�Ƶ� ������(recursive), �� ����� ��� ����ð��� ������ �ֱ� ������ iterative ������� �����Ͽ���.
	while (xNode != NULL) // ���α׷��� ������ ������ �ʵ��� xNode�� NULL�� ���, �ݺ����� ����ǵ��� �Ͽ���.
	{
		// ��尡 ���Եǰų� **R�� ������ �ذ��� ��, RB tree�� Ư������ ������ ���� ���
		if (xNode->parent->color == false) // ��, 3�� Ư���� ������ ���� ��� (pNode�� ���̾�� �Ѵ�.)
		{
			// printf("�ƹ� ���� �����ϴ� \n"); // �� �ּ��� findProblem�� �� �����ϴ��� Ȯ���ϴ� �ڵ��Դϴ�. ���� � case�� ������ �߻��ߴ��� �˰� �����ôٸ� �ּ��� �����Ͽ� Ȯ���Ͻø� �˴ϴ�.
			return; // �� �Լ��� �����Ų��.
		}


		// ��� �������� ���� RB tree�� Ư���� �������� ���ϰ� �� ���.
		Node* ppNode = xNode->parent->parent; // �����ڷ��� �׸�ó�� ppNode�� �����Ѵ�.
		Node* pNode = xNode->parent;          // �����ڷ��� �׸�ó�� pNode�� �����Ѵ�.


		// �� �Ʒ��� case���� �ذ� ������ ����� �ڵ��Դϴ�.
		// �����ڷ�ʹ� �ٸ� case�� ������ �ذ��Ͽ����ϴ�. 

		// �� ��쿣 L*B ����
		if (!ppNode->rightChild->color) //��, s Node�� �÷��� black�� ���
		{
			Node* change; // rotate �������� ���� root�� ������ ���, ���� root�� �ּҸ� ��� ������ ���� ����

			// case: LLB
			if (pNode->leftChild == xNode)
			{
				// printf("LLB ���� �߻�\n"); // �� �ּ��� findProblem�� �� �����ϴ��� Ȯ���ϴ� �ڵ��Դϴ�. ���� � case�� ������ �߻��ߴ��� �˰� �����ôٸ� �ּ��� �����Ͽ� Ȯ���Ͻø� �˴ϴ�.
				change = LLB_Rotate(xNode, pNode, ppNode);
			}

			// case: LRB
			else
			{
				// printf("LRB ���� �߻�\n"); // �� �ּ��� findProblem�� �� �����ϴ��� Ȯ���ϴ� �ڵ��Դϴ�. ���� � case�� ������ �߻��ߴ��� �˰� �����ôٸ� �ּ��� �����Ͽ� Ȯ���Ͻø� �˴ϴ�.
				change = LRB_Rotate(xNode, pNode, ppNode);
			}


			if (change != NULL) 	// rotate�������� ���� root�� ���ϴ� ���
				(*root) = change;   // root�� �������Ͽ� ���ο� root(=change)�� ��ü�Ѵ�.

			return;
		}

		// �� ��쿣 R*B ������
		else if (!ppNode->leftChild->color)
		{
			Node* change; // rotate �������� ���� root�� ������ ���, ���� root�� �ּҸ� ��� ������ ���� ����

			// case: RRB
			if (pNode->rightChild == xNode)
			{
				// printf("RRB ���� �߻� [%d]\n", xNode->key); // �� �ּ��� findProblem�� �� �����ϴ��� Ȯ���ϴ� �ڵ��Դϴ�. ���� � case�� ������ �߻��ߴ��� �˰� �����ôٸ� �ּ��� �����Ͽ� Ȯ���Ͻø� �˴ϴ�.
				change = RRB_Rotate(xNode, pNode, ppNode);
			}

			// case: RLB
			else
			{
				// printf("RLB ���� �߻�\n"); // �� �ּ��� findProblem�� �� �����ϴ��� Ȯ���ϴ� �ڵ��Դϴ�. ���� � case�� ������ �߻��ߴ��� �˰� �����ôٸ� �ּ��� �����Ͽ� Ȯ���Ͻø� �˴ϴ�.
				change = RLB_Rotate(xNode, pNode, ppNode);
			}


			if (change != NULL) 	// rotate�������� ���� root�� ���ϴ� ���
				(*root) = change;   // root�� �������Ͽ� ���ο� root(=change)�� ��ü�Ѵ�.

			return;
		}

		// �� ��쿣 **R ������
		else
		{
			// printf("**R ���� �߻�\n"); // �� �ּ��� findProblem�� �� �����ϴ��� Ȯ���ϴ� �ڵ��Դϴ�. ���� � case�� ������ �߻��ߴ��� �˰� �����ôٸ� �ּ��� �����Ͽ� Ȯ���Ͻø� �˴ϴ�.
			xNode = colorFlip(xNode, pNode, ppNode);
		}
	}
}


Node* LLB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (pNode->rightChild != NIL) // pNode�� ������ �ڽ� ��尡 NIL ��尡 �ƴ϶�� (= pNode�� ������ �ڽ��� ������尡 �ƴ϶��)
	{                                          
		ppNode->leftChild = pNode->rightChild; // ppNode�� �����ڽ����� �̵��� ��
		pNode->rightChild->parent = ppNode;    // �� �ڽĳ���� �θ� ��带 ppNode�� ��������.
	}
	else
		ppNode->leftChild = NIL;

	// ppNode�� �ִ� �ڸ��� pNode�� �����ϰ� �Ǿ����Ƿ�
	pNode->parent = ppNode->parent; // ���� ppNode�� parent�� pNode�� parent�� �ű�.

	xNode->parent = pNode;      // xNode�� parent�� pNode�� ���� ����
	ppNode->parent = pNode;     // ppNode�� parent�� pNode�� ���� ����
	pNode->rightChild = ppNode; // pNode�� ������ �ڽĳ�尡 ppNode�� ����Ű���� ����

	pNode->color = false; // ����� ���� �ٲپ� Ư�� 3���� ������ ������ �ʵ��� ��.
	ppNode->color = true;

	if (pNode->parent != NULL) // pNode�� parent->child�� �ٽ� �������ֱ� ���� �켱 NULL�� �ƴ������� üũ�Ѵ�. (= pNode�� root���� Ȯ���Ѵ�.)
	{
		if (pNode->parent->key < pNode->key)   // pNode->key�� pNode�� parent->key���� ũ�ٸ�, pNode�� �θ��� ������ �ڽ���
			pNode->parent->rightChild = pNode; // pNode�� parent�� �ٲ�鼭 pNode->parent->rightChild�� pNode�� ����Ű���� ��.

		else								  // pNode->key�� pNode�� parent->key���� �۴ٸ�, pNode�� �θ��� ���� �ڽ���
			pNode->parent->leftChild = pNode; // pNode�� parent�� �ٲ�鼭 pNode->parent->leftChild�� pNode�� ����Ű���� ��.

		return NULL; // NULL ���� ��ȯ�ߴٴ� ���� ȸ���� �Ͼ������ root�� ��ȭ�� ���ٴ� ���� �ǹ��Ѵ�.
	}

	return pNode; // rotate �������� ���� root�� ���� ����Ǿ����Ƿ� ����� root�� �ּҰ��� ��ȯ�Ѵ�.
}

Node* LRB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (xNode->rightChild != NIL) // pNode�� ������ �ڽ� ��尡 NIL ��尡 �ƴ϶��
	{
		ppNode->leftChild = xNode->rightChild; // ppNode�� �����ڽ����� �̵��� ��
		xNode->rightChild->parent = ppNode;    // �� �ڽĳ���� �θ� ��带 ppNode�� ��������.
	}
	else
		ppNode->leftChild = NIL;

	if (xNode->leftChild != NIL) // xNode�� ���� �ڽ� ��尡 NIL ��尡 �ƴ϶��
	{
		pNode->rightChild = xNode->leftChild; // pNode�� ������ �ڽ����� �̵��� ��
		xNode->leftChild->parent = pNode;     // �� �ڽĳ���� �θ� ��带 pNode�� ��������.
	}
	else
		pNode->rightChild = NIL;


	// ppNode�� �ִ� �ڸ��� xNode�� �����ϰ� �Ǿ����Ƿ�
	xNode->parent = ppNode->parent; // ���� ppNode�� parent�� xNode�� parent�� �ű�.

	pNode->parent = xNode;      // pNode�� parent�� xNode�� ���� ����
	ppNode->parent = xNode;     // ppNode�� parent�� xNode�� ���� ����
	xNode->leftChild = pNode;   // xNode�� ���� �ڽĳ�尡 pNode�� ����Ű���� ��
	xNode->rightChild = ppNode; // xNode�� ������ �ڽĳ�尡 ppNode�� ����Ű���� ��

	xNode->color = false; // ����� ���� �ٲپ� Ư�� 3���� ������ ������ �ʵ��� ��.
	ppNode->color = true;

	if (xNode->parent != NULL) // xNode�� parent->child�� �ٽ� �������ֱ� ���� �켱 NULL�� �ƴ������� üũ�Ѵ�. (= xNode�� root���� Ȯ���Ѵ�.)
	{
		if (xNode->parent->key < xNode->key)   // xNode->key�� xNode�� parent->key���� ũ�ٸ�, xNode�� �θ��� ������ �ڽ���
			xNode->parent->rightChild = xNode; // xNode�� parent�� �ٲ�鼭 xNode->parent->rightChild�� xNode�� ����Ű���� ��.

		else								  // xNode->key�� xNode�� parent->key���� �۴ٸ�, xNode�� �θ��� ���� �ڽ���
			xNode->parent->leftChild = xNode; // xNode�� parent�� �ٲ�鼭 xNode->parent->leftChild�� xNode�� ����Ű���� ��.

		return NULL; // NULL ���� ��ȯ�ߴٴ� ���� ȸ���� �Ͼ������ root�� ��ȭ�� ���ٴ� ���� �ǹ��Ѵ�.
	}

	return xNode; // rotate �������� ���� root�� ���� ����Ǿ����Ƿ� ����� root�� �ּҰ��� ��ȯ�Ѵ�.
}

Node* RRB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (pNode->leftChild != NIL) // pNode�� ���� �ڽ� ��尡 NIL ��尡 �ƴ϶��
	{
		ppNode->rightChild = pNode->leftChild; // ppNode�� �������ڽ����� �̵��� ��
		pNode->leftChild->parent = ppNode;    // �� �ڽĳ���� �θ� ��带 ppNode�� ��������.
	}
	else
		ppNode->rightChild = NIL;


	// ppNode�� �ִ� �ڸ��� pNode�� �����ϰ� �Ǿ����Ƿ�
	pNode->parent = ppNode->parent; // ���� ppNode�� parent�� pNode�� parent�� �ű�.

	xNode->parent = pNode;      // xNode�� parent�� pNode�� ���� ����
	ppNode->parent = pNode;     // ppNode�� parent�� pNode�� ���� ����
	pNode->leftChild = ppNode; // pNode�� ���� �ڽĳ�尡 ppNode�� ����Ű���� ����

	pNode->color = false; // ����� ���� �ٲپ� Ư�� 3���� ������ ������ �ʵ��� ��.
	ppNode->color = true;

	if (pNode->parent != NULL) // pNode�� parent->child�� �ٽ� �������ֱ� ���� �켱 NULL�� �ƴ������� üũ�Ѵ�. (= pNode�� root���� Ȯ���Ѵ�.)
	{
		if (pNode->parent->key < pNode->key)   // pNode->key�� pNode�� parent->key���� ũ�ٸ�, pNode�� �θ��� ������ �ڽ���
			pNode->parent->rightChild = pNode; // pNode�� parent�� �ٲ�鼭 pNode->parent->rightChild�� pNode�� ����Ű���� ��.

		else								  // pNode->key�� pNode�� parent->key���� �۴ٸ�, pNode�� �θ��� ���� �ڽ���
			pNode->parent->leftChild = pNode; // pNode�� parent�� �ٲ�鼭 pNode->parent->leftChild�� pNode�� ����Ű���� ��.

		return NULL; // NULL ���� ��ȯ�ߴٴ� ���� ȸ���� �Ͼ������ root�� ��ȭ�� ���ٴ� ���� �ǹ��Ѵ�.
	}

	return pNode; // rotate �������� ���� root�� ���� ����Ǿ����Ƿ� ����� root�� �ּҰ��� ��ȯ�Ѵ�.
}

Node* RLB_Rotate(Node* xNode, Node* pNode, Node* ppNode)
{
	if (xNode->rightChild != NIL) // pNode�� ������ �ڽ� ��尡 NIL ��尡 �ƴ϶��
	{
		pNode->leftChild = xNode->rightChild; // pNode�� ���� �ڽ����� �̵��� ��
		xNode->rightChild->parent = pNode;     // �� �ڽĳ���� �θ� ��带 pNode�� ��������.
	}
	else
		pNode->leftChild = NIL;

	if (xNode->leftChild != NIL) // xNode�� ���� �ڽ� ��尡 NIL ��尡 �ƴ϶��
	{
		ppNode->rightChild = xNode->leftChild; // ppNode�� ������ �ڽ����� �̵��� ��
		xNode->leftChild->parent = ppNode;    // �� �ڽĳ���� �θ� ��带 ppNode�� ��������.
	}
	else
		ppNode->rightChild = NIL;


	// ppNode�� �ִ� �ڸ��� xNode�� �����ϰ� �Ǿ����Ƿ�
	xNode->parent = ppNode->parent;    // ���� ppNode�� parent�� xNode�� parent�� �ű�.

	pNode->parent = xNode;      // pNode�� parent�� xNode�� ���� ����
	ppNode->parent = xNode;     // ppNode�� parent�� xNode�� ���� ����
	xNode->rightChild = pNode;  // xNode�� ������ �ڽĳ�尡 pNode�� ����Ű���� ��
	xNode->leftChild = ppNode;  // xNode�� ���� �ڽĳ�尡 ppNode�� ����Ű���� ��


	xNode->color = false; // ����� ���� �ٲپ� Ư�� 3���� ������ ������ �ʵ��� ��.
	ppNode->color = true;


	if (xNode->parent != NULL) // xNode�� parent->child�� �ٽ� �������ֱ� ���� �켱 NULL�� �ƴ������� üũ�Ѵ�. (= xNode�� root���� Ȯ���Ѵ�.)
	{
		if (xNode->parent->key < xNode->key)   // xNode->key�� xNode�� parent->key���� ũ�ٸ�, xNode�� �θ��� ������ �ڽ���
			xNode->parent->rightChild = xNode; // xNode�� parent�� �ٲ�鼭 xNode->parent->rightChild�� xNode�� ����Ű���� ��.

		else								  // xNode->key�� xNode�� parent->key���� �۴ٸ�, xNode�� �θ��� ���� �ڽ���
			xNode->parent->leftChild = xNode; // xNode�� parent�� �ٲ�鼭 xNode->parent->leftChild�� xNode�� ����Ű���� ��.

		return NULL; // NULL ���� ��ȯ�ߴٴ� ���� ȸ���� �Ͼ������ root�� ��ȭ�� ���ٴ� ���� �ǹ��Ѵ�.
	}

	return xNode; // rotate �������� ���� root�� ���� ����Ǿ����Ƿ� ����� root�� �ּҰ��� ��ȯ�Ѵ�.
}

Node* colorFlip(Node* xNode, Node* pNode, Node* ppNode)
{
	ppNode->color = true;              // ���Ե� ����� ���θ� color���� ����(=true)�� �ٲ��ش�.
	ppNode->leftChild->color = false;  // ���θ��� �����ڽ��� ��(=false)�� �ٲ��ش�.
	ppNode->rightChild->color = false; // ���� ���������� ���θ��� �������ڽ��� ��(=false)�� �ٲ��ش�.

	if (ppNode->parent == NULL) // ppNode�� root�� ��쿡�� ���̻� ������ ã�� �ʿ䰡 ����. (=findProblem �Լ��� ������ �ʿ䰡 ����.)
		return NULL;            // ���� NULL���� ��ȯ���ش�.


	return ppNode; // colorFlip�� �ϰ��� ppNode���� ���� ������ �߻����� ���� �ִ�. ���� ppNode�� �ٽ� xNode�� ���� ������ �ִ��� Ȯ���ϱ� ���� ppNode�� ��ȯ�Ѵ�.
}


// RB Ʈ���� �����͵��� ���Ϸ� �ű�� �Լ��̴�. (inorder ������� RB Ʈ���� Ž���� ���, ���ĵ� ���·� ��ȯ�� �����ϴ�.)
void recurInorder(Node* node, FILE* fp)
{
	// Inorder ��ȸ�� recursive ������� ¥�Ե� ���,
	// iterator ��İ� ����ð��� ���̴� ũ�� ������ ��� '0.02 ~ 0.04'�� ���� �� �ɸ��� �������� �߻��Ͽ�
	// �⺻���δ� iterator ������� Inorder ��ȸ�� ������ �ڵ带 �ۼ��Ͽ���.
	if (node != NIL) // ���� �湮 ���� ��尡 ���� ��尡 �ƴ� ���
	{
		recurInorder(node->leftChild, fp);  // ���� �ڽ��� ���� ��ȸ�� �Ŀ�
		fprintf(fp, "%d ", node->key);      // ���� �湮 ���� ����� key ���� ���Ͽ� �Ű��ش�.
		recurInorder(node->rightChild, fp); // �׸��� ������ �ڽ��� ��ȸ�Ѵ�.
	}
}

// RB Ʈ���� �����͵��� ���Ϸ� �ű�� �Լ��̴�. (inorder ������� RB Ʈ���� Ž���� ���, ���ĵ� ���·� ��ȯ�� �����ϴ�.)
void inorder(Node* root)
{
	// �� �Լ��� recursive ������� ¥�ԵǸ� �ǰ� �����ϰ� �ڵ带 © �� �ִ�.
	// ������ �����ڷ� 3, 4���� ���� recursive ������� ¥�Ե� ���, ����ð��� �þ�ٴ� ������ �����Ѵ�.
	// ���� recursive ����� �ƴ� iterator ������� �ڵ带 ¥�ԵǾ���.


	//���� ���·� ��ȯ�ϱ� ���� FILE ������ ���� ����
	FILE* pFile_output = fopen("sorting file.text", "w"); // ���� �̸��� sorting file�� ���·� ��ȯ


	Node* search = root; // RB tree���� ���� �湮���� ��带 �˱����� RB tree�� Node ������ ���� ����
	sNode* top = NULL;   // stack�� ���� top ������ ���� �� NULL ������ �ʱ� �������ش�.
	push(&top, NIL);     // �ݺ����� ����� �� �ֵ��� �ϱ� ���� stack�� NIL ��带 �� ó���� �־��ش�.


	// Left -> visit -> Right Ž���� �� ���� (= inorder)
	while (1)
	{
		for (; search != NIL; search = search->leftChild) // �� �̻� ���� �ڽ��� ���� ������ �ݺ��Ѵ�.
			push(&top, search);  // �ݺ��ϸ鼭 �湮�� ������ stack�� �������ش�.

		search = pop(&top); // ���� �ݺ����� �����ٸ� '���(visit)'�� �湮�ϱ� ���� stack�� ���� �ϳ� �����´� (=pop)
		if (search == NIL)  break; // stack�� �ƹ� ��嵵 ������� �ʾҴٸ� �̴�� �ݺ����� �����Ѵ�.

		fprintf(pFile_output, "%d ", search->key); // �湮�� ����� key���� sorting fild���ٰ� �����ش�.
		search = search->rightChild; // �� ��, ������ �ڽ�(=Right)�� Ž���Ѵ�.
	}


	fclose(pFile_output); // close file
}

// stack�� push ������ �����ϴ� �Լ�
void push(sNode** top, Node* insertData)
{
	sNode* newTop = (sNode*)malloc(sizeof(sNode)); // push �� ����� top�� ����Ű�� �ӽ� ����
	if (newTop == NULL)
	{
		printf("�޸𸮸� �Ҵ���� ���Ͽ����ϴ�.\n");
		exit(0);
	}

	newTop->data = insertData; // ���� ���� (�ӽ�)top�� ���� �湮 ���� ��带 �־��ش�.
	newTop->next = (*top);     // �� ��, ������ top�� ���� ���� (�ӽ�)top�� next�� �������ش�.

	(*top) = newTop; // ���� ���� (�ӽ�)top�� stack�� top�� �ǵ��� �������ش�.
}

// stack�� pop������ �����ϴ� �Լ�
Node* pop(sNode** top)
{
	sNode* delNode = (*top);      // �޸𸮸� �����ϱ� ���� delNode�� ������ top�� �����صд�.
	Node* popNode = (*top)->data; // ��ȯ�� ��带 popNode�� �����Ѵ�.

	(*top) = (*top)->next; // pop ������ ���������Ƿ� top�� ���� top�� next�� �������ش�.

	free(delNode);  // pop�ϱ� ���� top�� �Ҵ�� �޸𸮸� �������ش�.
	return popNode; // pop�� ��带 ��ȯ���ش�.
}