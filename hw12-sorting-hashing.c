/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	// 입력받은 배열(a)에 메모리가 할당되어있을 경우에만 메모리가 해제되도록함.
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // 정수형을 출력할 여백을 2자리 마련한 후, 빈자리가 있을 경우 0을 채우도록하여 화면에 출력함.
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);  // 정수형을 출력할 여백을 5자리 마련하여 화면에 출력함.
	printf("\n");
}


int selectionSort(int *a)
{
	int min;      // 최솟값을 저장하는 변수
	int minindex; // 최솟값의 위치를 저장하는 변수
	int i, j;     // 반복문에 사용될 변수

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	// 정렬되기 이전의 배열을 화면에 출력한다.
	printArray(a);

	/*
	  이 반복문은 a의 0번째 인덱스부터 a의 MAX_ARRAY_SIZE - 1 인덱스까지 반복하게 되는데,
	  반복문 한번의 수행당 기준 위치(i번쨰)와 i번째 이후에 있는 가장 작은 원소를 swap을 하게된다.
	  따라서 이 반복문이 종료되면, a의 배열은 정렬이 된다. (selectionSort)
	*/
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // minindex의 디폴트 값을 i번째로 해둔다.  (반복문을 돌면서 수정될 예정)
		min = a[i];   // min의 디폴트 값을 a[i]의 값으로 해둔다. (반복문을 돌면서 수정될 예정)

		// for문은 i + 1 부터 MAX_ARRAY_SIZE 까지 반복하면서 minindex와 min 값을 수정한다.
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])   // 만약, a의 j번째 값보다 min 값이 더 크다면 (최솟값 변경)
			{
				min = a[j];   // 최솟값(min)을 a의 j번째 값으로 수정한다.
				minindex = j; // 최솟값이 들어있는 위치(minindex)를 j번째로 수정한다.
			}
		}

		// a의 i 번째의 값과 minindex 번째의 값을 swap한다.
		a[minindex] = a[i]; 
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 후의 배열을 화면에 출력한다.
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬되기 이전의 배열을 화면에 출력한다.

	/*
	  이 반복문은 a의 1번째 인덱스부터 a의 MAX_ARRAY_SIZE - 1 인덱스까지 반복하게 되는데,
	  반복문 한번의 수행당 기준 위치(i번쨰)의 값을 i번째 이전의 값들 중 들어갈 자리에 넣어주게 된다.
	  (기준 위치의 값을 들어갈 자리에 넣어주기 위해서 [들어갈 자리 ~ i-1번쨰]의 값들을 오른쪽으로 한칸씩 옮겨준다.)
	  따라서 이 반복문이 종료되면, a의 배열은 정렬이 된다. (insertionSort)
	*/
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // t에 a[i]의 값을 저장해둔다.
		j = i;    // 그리고 j에 현재 i값을 대입한다.

		// j가 0보다 작거나 같아질 경우, 또는 a[j - 1] 값보다 t 값이 커질 때까지 반복
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; // 현재의 a[j] 값을 a[j - 1] 값으로 수정한다.
			j--;           // 그리고 j의 값을 1 만큼 줄여준다.
			// 즉, a[j - 1]의 값을 오른쪽으로 한칸 움직여준다.
		}
		a[j] = t; // a[j]에 t값을 대입해준다. (즉, 기준 위치(i번째)의 값을 a[j]에 넣어준다.)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 후의 배열을 화면에 출력한다.

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n"); 
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬되기 이전의 배열을 화면에 출력한다.

	/*
	  이 반복문은 a의 1번째 인덱스부터 a의 MAX_ARRAY_SIZE - 1 인덱스까지 반복하게 되는데,
	  반복문 한번의 수행당 a의 값들 중 가장 큰 값이 맨 뒤로 이동하게 된다.
	  따라서 이 반복문이 종료되면, a의 배열은 정렬이 된다. (bubbleSort)
	*/
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // 현재의 a[j]의 값이 a[j - 1]보다 작다면 swap (제일 큰 값을 맨 뒤로 보내기 위해서)
			{
				t = a[j-1];    // swap하기 위해 t에 a[j-1]의 값 대입
				a[j-1] = a[j]; // a[j - 1]의 값을 t에 대입했으므로, a[j - 1]에 a[j]값 대입
				a[j] = t;	   // a[j]에 t의 값을 대입함으로써 swap 완료
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 후의 배열을 화면에 출력한다.

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	// h만큼의 간격으로 떨어진 코드를 삽입 정렬하기 위해 
	// h의 초기값은 [배열의 개수 / 2]로 초기화되며, 반복문을 수행하고 난 후엔 h의 값이 절반으로 줄어들게 된다.
	// 그리고 이 반복문은 h가 1이 될 때까지 반복문이 돌아가게 된다.
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		// i는 0부터 h값만큼 반복하게 된다.
		for (i = 0; i < h; i++)
		{
			// j 값은 [i + h]부터 시작하여, j 값이 MAX_ARRAY_SIZE보다 작을 동안만 반복되게 되는데,
			// 이는 배열에서 h만큼 떨어진 곳들을 정렬하기 위함임.
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; // v에 a[j] 값을 저장
				k = j;    // k에 j 값을 저장

				// 이 반복문은 insertionSort과 유사하며,
				// a[j]의 값이 들어갈 위치를 찾을 떄 까지 반복하며
				// 반복문이 종료될 경우, k의 위치에 v 값을 대입하게 된다.
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h]; // a[k - h]의 값을 오른쪽으로 h 만큼 움직여준다.
					k -= h;        // 그리고 k의 값에 h 만큼 빼준다.
				}
				a[k] = v; // a[k]에 v의 값을 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



