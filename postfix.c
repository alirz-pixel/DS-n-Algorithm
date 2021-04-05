/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	inlparen = 20, /* ( 스택 안에 있는 왼쪽 괄호*/
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	printf("[----- [최문형] [2020039004] -----]\n");

	char command;

	do{
		//메뉴창 출력
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		// 사용자가 입력한 command에 대응하는 함수 실행하게 해주는 코드
		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; // push 연산을 수행한다.
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';	// 스택이 비어있다면 '\0'을 반환한다.
    else {
    	x = postfixStack[postfixStackTop--]; // 스택이 비어있지 않다면 Pop 연산을 수행한ㄷ.ㅏ
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; // push 연산을 수행하는 코드
}

int evalPop()
{
    if(evalStackTop == -1)  // 스택이 비어있다면 -1을 리턴한다.
        return -1;
    else
        return evalStack[evalStackTop--]; // 스택이 비어있지 않다면, Pop연산을 수행한다.
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	if (postfixExp[0] != '\0') // postfix를 수행했을 경우, Reset을 한 후에 실행하도록 에러코드 출력
	{
		printf("Error! : Reset을 진행한 후에, Infix를 실행해주세요.\n");
		return;
	}

    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	if (infixExp[0] == '\0') // Infix을 수행하지 않고, 이 함수를 실행한 경우 에러코드 출력
	{
		printf("Error! : Infix가 제대로 수행되었는지 확인해주세요.\n");
		return;
	}

	else if (postfixExp[0] != '\0') // 이미 postFix를 수행했을 경우, 한 번 더 수행하게 되면 문제가 발생하므로 에러코드 출력
	{
		printf("Error! : 이미 Postfix를 수행하였습니다.\n");
		return;
	}

	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	precedence token;

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		token = getToken(*exp);
		// x = (*exp++);

		if (token == lparen)  // 스택 밖에 ( 왼쪽 괄호가 있을 때, 우선순위 20 부여
			token = inlparen; // inlparen = 20

		
		if (token == operand) // token이 피연산자 일 때,
			charCat(exp);	  // postfixExp에 현재 문자 추가

		else if (token == rparen) // token이 ) 오른쪽 괄호 일 때,
		{
			while (getToken(postfixStack[postfixStackTop]) != lparen) // postfixStack[postfixStackTop]의 값이 ( 왼쪽 괄호가 나올 때까지 반복한다.
			{
				x = postfixPop();
				charCat(&x); // 왼쪽 괄호가 나오기 '전'까지의 연산자들은 postfixExp에 저장한다.
			}
			postfixPop(); // 왼쪽 괄호를 버린다.
		}

		else
		{
			// 입력 연산자가 스택의 탑에 있는 연산자보다 우선순위가 낮은 경우, 
			// 스택 탑에서 Pop 하여 postfixExp에 넣어준다.
			
			while (getToken(postfixStack[postfixStackTop]) >= token) // 현재 토큰 값보다 postfixStack[postfixStackTop]의 우선순위가 높으면 반복한다.
			{
				if(postfixStackTop == -1)  // postfixStack is empty 라면, 반복문 종료
					break;

				x = postfixPop();
				charCat(&x); // 현재 토큰 값보다 우선순위가 낮은 연산자는 postfixExp에 저장한다.
			}

			postfixPush(*exp); // 현재 연산자를 postfixStack에 push한다.
		}

		exp++;
	}

	while((x = postfixPop()) != '\0')
	{
		charCat(&x);
	}

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{	
	if (postfixExp[0] == '\0') // Postfix을 수행하지 않고, 이 함수를 실행한 경우 에러코드 출력
	{
		printf("Error! : Postfix가 제대로 수행되었는지 확인해주세요.\n");
		return;
	}

	else if (evalResult != 0) // 이미 Eval를 수행했을 경우, 굳이 연산을 한 번 더 할 필요 없으므로 에러코드 출력
	{
		printf("Error! : 이미 Eval 함수를 수행하였습니다.\n");
		return;
	}

	/* postfixExp, evalStack을 이용한 계산 */
	precedence token;
	int op1, op2;	// evalStack에서 Pop 하여 나온 값들을 저장하는 변수
	char x; 		// postfixStack에서 가져온 값을 저장하는 변수

	for (int i = 0; postfixExp[i] != '\0'; i++)
	{
		x = postfixExp[i]; // postfixExp 의 값을 하나씩 가져온다.
		token = getToken(x); // x의 값을 token으로 

		if (token == operand) // token이 피연산자라면
			evalPush(x - '0'); // 현재 x는 char로 선언되어 있기 때문에 - '0'을 하여 int형으로 변환시켜준다.
		
		else // token이 연산자라면
		{
			// 계산을 하기 위해 두 개의 피연산자를 Pop하여 연산을 수행한 후, 다시 Stack에 삽입한다.
			op1 = evalPop();
			op2 = evalPop();

			switch(token) {
				case plus: evalPush(op1 + op2); break; // 토큰이 +라면 둘이 더한 후, 그 값을 스택에 삽입
				case minus: evalPush(op1 - op2); break;// 토큰이 -라면 둘이 뻰 후,   그 값을 스택에 삽입
				case times: evalPush(op1 * op2); break;// 토큰이 *라면 둘이 곱한 후, 그 값을 스택에 삽입
				case divide: evalPush(op2 / op1);	   // 토큰이 /라면 둘이 나눈 후, 그 값을 스택에 삽입
			}
		}
	}

	evalResult = evalPop();
}

