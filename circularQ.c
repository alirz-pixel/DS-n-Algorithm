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
	printf("[----- [최문형] [2020039004] -----]");

	QueueType *cQ = createQueue(); // QueueType 구조체 변수 포인터 cQ를 선언한 후, 초기설정을 해준다.
	element data; 
	char command;

	do{
		// 메뉴 출력 화면
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': // Insert 작업 실행
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': // Delete 작업 실행
			deQueue(cQ, &data); 
			break;
		case 'p': case 'P': // PrintQ 작업 실행
			printQ(cQ);
			break;
		case 'b': case 'B': // Debug 작업 실행
			debugQ(cQ);
			break;
		case 'q': case 'Q': // Quit 작업 실행
   	        freeQueue(cQ);
			break;
		default: // 메뉴에 없는 command 입력 시, 실행
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); // QueueType의 사이즈 만큼 동적메모리 할당

	if (cQ == NULL) // 동적할당에서 문제가 발생한 경우
	{
		printf("Error! : Insufficient memory!\n");
		return NULL;
	}

	//Queue init
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) // 0 ~ MAX_QUEUE_SIZE 까지 반복
		cQ->queue[i] = '\0'; // debug 작업 실행 시, 쓰레기값이 출력되는 것을 막기 위해 NULL값을 대입해주는 코드

	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; // 큐가 메모리 할당을 제대로 받지 못한 경우, free를 실행하기 전에 함수를 종료한다.
    free(cQ); // cQ에 할당된 메모리를 해제시켜준다.
    return 1;
}

element getElement()
{
	element item; // char형 변수 item 을 선언한다.
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ == NULL) // 큐가 메모리 할당을 제대로 받지 못한 상태에서 함수를 실행한 경우
	{
		printf("Error! : 큐를 생성하는데 문제가 생겨 isEmpty 함수를 실행할 수 없습니다.\n");
		return 1;
	}

	// 큐가 비어있는 경우, front와 rear이 같은 곳에 있기 때문에
	// front == rear 로 큐가 비어있는지 판단한다.
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
	if (cQ == NULL) // 큐가 메모리 할당을 제대로 받지 못한 상태에서 함수를 실행한 경우
	{
		printf("Error! : 큐를 생성하는데 문제가 생겨 함수를 실행할 수 없습니다.\n");
		return 1;
	}

	// 큐가 가득찬 경우, front가 rear보다 한 칸 앞에 있기 때문에
	// (cQ->rear + 1) % MAX_QUEUE_SIZE 로 큐가 가득 찬 지 판단한다.
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
	if (!isFull(cQ)) // 큐가 가득찬 경우, 1을 리턴받기 때문에 not을 붙혀준다.
	{				 // 큐가 가득차지 않은 경우, Push 진행
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
		cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    if (!isEmpty(cQ)) // 큐가 비어있는 경우, 1을 리턴받기 때문에 not을 붙혀준다.
	{
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; 
		cQ->queue[cQ->front] = '\0'; // Pop을 하게 되었을 때, front 값을 다른 걸로 바꿔 debug에 이상한 값이 출력되지 않도록 한다.
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	// 실제 데이터가 들어있는 곳은 front보다 한 칸 앞이므로
	// 배열을 넘어가지 않도록 모듈로 연산과 함께 1을 front와 rear에 더해준다.
	first = (cQ->front + 1)%MAX_QUEUE_SIZE; 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]); //3칸을 확보한 후, 오른쪽 정렬하여 queue에 있는 값을 출력한다.
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // 0 ~ MAX_QUEUE_SIZE -1 까지 반복하면서 큐 안의 값들을 출력한다.
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); 
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); 

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // 현재 front와 rear이 위치한 곳을 출력한다.
}


