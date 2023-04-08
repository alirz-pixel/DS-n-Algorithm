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

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	outlparen = 20, /* ( ���� �ۿ� �ִ� ���� ��ȣ*/
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

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
	printf("[----- [�ֹ���] [2020039004] -----]\n");

	char command;

	do{
		//�޴�â ���
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		// ����ڰ� �Է��� command�� �����ϴ� �Լ� �����ϰ� ���ִ� �ڵ�
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
    postfixStack[++postfixStackTop] = x; // push ������ �����Ѵ�.
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';	// ������ ����ִٸ� '\0'�� ��ȯ�Ѵ�.
    else {
    	x = postfixStack[postfixStackTop--]; // ������ ������� �ʴٸ� Pop ������ �����Ѥ�.��
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; // push ������ �����ϴ� �ڵ�
}

int evalPop()
{
    if(evalStackTop == -1)  // ������ ����ִٸ� -1�� �����Ѵ�.
        return -1;
    else
        return evalStack[evalStackTop--]; // ������ ������� �ʴٸ�, Pop������ �����Ѵ�.
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
	if (postfixExp[0] != '\0') // postfix�� �������� ���, Reset�� �� �Ŀ� �����ϵ��� �����ڵ� ���
	{
		printf("Error! : Reset�� ������ �Ŀ�, Infix�� �������ּ���.\n");
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	if (infixExp[0] == '\0') // Infix�� �������� �ʰ�, �� �Լ��� ������ ��� �����ڵ� ���
	{
		printf("Error! : Infix�� ����� ����Ǿ����� Ȯ�����ּ���.\n");
		return;
	}

	else if (postfixExp[0] != '\0') // �̹� postFix�� �������� ���, �� �� �� �����ϰ� �Ǹ� ������ �߻��ϹǷ� �����ڵ� ���
	{
		printf("Error! : �̹� Postfix�� �����Ͽ����ϴ�.\n");
		return;
	}

	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	precedence token;
	int lparen_Error; // ��ȣ�� ����� �Ǿ��ִ��� Ȯ���� �ִ� ����

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		lparen_Error = 1; // ��ȣ�� ����� �Ǿ��ִٸ� ���� 0���� ����
		token = getToken(*exp);
		// x = (*exp++);

		if (token == lparen)  // ���� �ۿ� ( ���� ��ȣ�� ���� ��, �켱���� 20 �ο�
			token = outlparen; // outlparen = 20
		
		if (token == operand) // token�� �ǿ����� �� ��,
			charCat(exp);	  // postfixExp�� ���� ���� �߰�

		else if (token == rparen) // token�� ) ������ ��ȣ �� ��,
		{
			while (postfixStackTop != -1) 
			{
				// postfixStack[postfixStackTop]�� ���� ( ���� ��ȣ�� ������ �ݺ��� ����
				if (getToken(postfixStack[postfixStackTop]) == lparen)
				{
					lparen_Error = 0;
					break;
				}

				x = postfixPop();
				charCat(&x); // ���� ��ȣ�� ������ '��'������ �����ڵ��� postfixExp�� �����Ѵ�.
			}

			if (lparen_Error) // �Է¹��� ���� ���� ��ȣ�� �����ٸ�
			{
				printf("Error! : ���� ��ȣ�� ã�� ���߽��ϴ�.\n"); // �ڵ����� reset ����
				printf("����� ��� ��, �ڵ����� reset�� ����˴ϴ�.\n");
				debug();
				reset();
				break;
			}

			postfixPop(); // ���� ��ȣ�� ������.
		}

		else
		{
			// �Է� �����ڰ� ������ ž�� �ִ� �����ں��� �켱������ ���� ���, 
			// ���� ž���� Pop �Ͽ� postfixExp�� �־��ش�.
			
			while (postfixStackTop != -1) // postfixStack is empty ���, �ݺ��� ���� 
			{
				// ���� ��ū ������ postfixStack[postfixStackTop]�� �켱������ �������� �ݺ��� ����
				if (getToken(postfixStack[postfixStackTop]) < token)
					break;

				x = postfixPop();
				charCat(&x); // ���� ��ū ������ �켱������ ���� �����ڴ� postfixExp�� �����Ѵ�.
			}

			postfixPush(*exp); // ���� �����ڸ� postfixStack�� push�Ѵ�.
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
	if (postfixExp[0] == '\0') // Postfix�� �������� �ʰ�, �� �Լ��� ������ ��� �����ڵ� ���
	{
		printf("Error! : Postfix�� ����� ����Ǿ����� Ȯ�����ּ���.\n");
		return;
	}

	else if (evalResult != 0) // �̹� Eval�� �������� ���, ���� ������ �� �� �� �� �ʿ� �����Ƿ� �����ڵ� ���
	{
		printf("Error! : �̹� Eval �Լ��� �����Ͽ����ϴ�.\n");
		return;
	}

	/* postfixExp, evalStack�� �̿��� ��� */
	precedence token;
	int op1, op2;	// evalStack���� Pop �Ͽ� ���� ������ �����ϴ� ����
	char x; 		// postfixStack���� ������ ���� �����ϴ� ����

	for (int i = 0; postfixExp[i] != '\0'; i++)
	{
		x = postfixExp[i]; // postfixExp �� ���� �ϳ��� �����´�.
		token = getToken(x); // x�� ���� token���� 

		if (token == operand) // token�� �ǿ����ڶ��
			evalPush(x - '0'); // ���� x�� char�� ����Ǿ� �ֱ� ������ - '0'�� �Ͽ� int������ ��ȯ�����ش�.
		
		else // token�� �����ڶ��
		{
			// ����� �ϱ� ���� �� ���� �ǿ����ڸ� Pop�Ͽ� ������ ������ ��, �ٽ� Stack�� �����Ѵ�.
			op1 = evalPop();
			op2 = evalPop();

			switch(token) {
				case plus: evalPush(op1 + op2); break; // ��ū�� +��� ���� ���� ��, �� ���� ���ÿ� ����
				case minus: evalPush(op1 - op2); break;// ��ū�� -��� ���� �u ��,   �� ���� ���ÿ� ����
				case times: evalPush(op1 * op2); break;// ��ū�� *��� ���� ���� ��, �� ���� ���ÿ� ����
				case divide: evalPush(op2 / op1);	   // ��ū�� /��� ���� ���� ��, �� ���� ���ÿ� ����
			}
		}
	}

	evalResult = evalPop();
}

