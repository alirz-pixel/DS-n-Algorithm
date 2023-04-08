/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	printf("[----- [�ֹ���] [2020039004] -----]");

	QueueType *cQ = createQueue(); // QueueType ����ü ���� ������ cQ�� ������ ��, �ʱ⼳���� ���ش�.
	element data; 
	char command;

	do{
		// �޴� ��� ȭ��
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': // Insert �۾� ����
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': // Delete �۾� ����
			deQueue(cQ, &data); 
			break;
		case 'p': case 'P': // PrintQ �۾� ����
			printQ(cQ);
			break;
		case 'b': case 'B': // Debug �۾� ����
			debugQ(cQ);
			break;
		case 'q': case 'Q': // Quit �۾� ����
   	        freeQueue(cQ);
			break;
		default: // �޴��� ���� command �Է� ��, ����
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); // QueueType�� ������ ��ŭ �����޸� �Ҵ�

	if (cQ == NULL) // �����Ҵ翡�� ������ �߻��� ���
	{
		printf("Error! : Insufficient memory!\n");
		return NULL;
	}

	//Queue init
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) // 0 ~ MAX_QUEUE_SIZE ���� �ݺ�
		cQ->queue[i] = '\0'; // debug �۾� ���� ��, �����Ⱚ�� ��µǴ� ���� ���� ���� NULL���� �������ִ� �ڵ�

	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; // ť�� �޸� �Ҵ��� ����� ���� ���� ���, free�� �����ϱ� ���� �Լ��� �����Ѵ�.
    free(cQ); // cQ�� �Ҵ�� �޸𸮸� ���������ش�.
    return 1;
}

element getElement()
{
	element item; // char�� ���� item �� �����Ѵ�.
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ == NULL) // ť�� �޸� �Ҵ��� ����� ���� ���� ���¿��� �Լ��� ������ ���
	{
		printf("Error! : ť�� �����ϴµ� ������ ���� isEmpty �Լ��� ������ �� �����ϴ�.\n");
		return 1;
	}

	// ť�� ����ִ� ���, front�� rear�� ���� ���� �ֱ� ������
	// front == rear �� ť�� ����ִ��� �Ǵ��Ѵ�.
	if (cQ->front ==  cQ->rear) 
	{
		printf("Error! : Queue is empty\n");
		return 1;
	}

    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if (cQ == NULL) // ť�� �޸� �Ҵ��� ����� ���� ���� ���¿��� �Լ��� ������ ���
	{
		printf("Error! : ť�� �����ϴµ� ������ ���� �Լ��� ������ �� �����ϴ�.\n");
		return 1;
	}

	// ť�� ������ ���, front�� rear���� �� ĭ �տ� �ֱ� ������
	// (cQ->rear + 1) % MAX_QUEUE_SIZE �� ť�� ���� �� �� �Ǵ��Ѵ�.
	if (cQ->front == (cQ->rear + 1) % MAX_QUEUE_SIZE)
	{
		printf("Error! : Queue is full\n");
		return 1;
	}

   	return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{	
	if (!isFull(cQ)) // ť�� ������ ���, 1�� ���Ϲޱ� ������ not�� �����ش�.
	{				 // ť�� �������� ���� ���, Push ����
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
		cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    if (!isEmpty(cQ)) // ť�� ����ִ� ���, 1�� ���Ϲޱ� ������ not�� �����ش�.
	{
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; 
		cQ->queue[cQ->front] = '\0'; // Pop�� �ϰ� �Ǿ��� ��, front ���� �ٸ� �ɷ� �ٲ� debug�� �̻��� ���� ��µ��� �ʵ��� �Ѵ�.
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	// ���� �����Ͱ� ����ִ� ���� front���� �� ĭ ���̹Ƿ�
	// �迭�� �Ѿ�� �ʵ��� ���� ����� �Բ� 1�� front�� rear�� �����ش�.
	first = (cQ->front + 1)%MAX_QUEUE_SIZE; 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]); //3ĭ�� Ȯ���� ��, ������ �����Ͽ� queue�� �ִ� ���� ����Ѵ�.
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // 0 ~ MAX_QUEUE_SIZE -1 ���� �ݺ��ϸ鼭 ť ���� ������ ����Ѵ�.
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); 
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); 

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // ���� front�� rear�� ��ġ�� ���� ����Ѵ�.
}


