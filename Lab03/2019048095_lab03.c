#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char* ConvertExp(char exp[]);
int GetOperatorPriority(char op);
int CompareOperatorPriority(char op1, char op2);
int EvalExp(char exp[]);

typedef struct Node
{
    char data;
    struct Node* next;
}Node;

typedef struct
{
    Node* head;
}List;

void InitStack(List* stack);
int IsEmpty(List* stack);
void Push(List* stack, char data);
char Pop(List* stack);
char Peek(List* stack);

int main()
{
    char inp[100];
    memset(inp, 0, sizeof(inp));
    scanf("%s", inp);
    char* tmp = ConvertExp(inp);
    printf("%d", EvalExp(tmp) - '0');
}

char* ConvertExp(char exp[])
{
    List stack;
    InitStack(&stack);
    char pf[100];
    memset(pf, 0, sizeof(pf));

    int len = strlen(exp);
    int size = 0;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(exp[i])) pf[size++] = exp[i];
        else if (exp[i] == '(') Push(&stack, exp[i]);
        else if (exp[i] == ')')
        {
            while (Peek(&stack) != '(') pf[size++] = Pop(&stack);
            Pop(&stack);
        }
        else if (GetOperatorPriority(Peek(&stack)) >= GetOperatorPriority(exp[i]))
        {
            while (!IsEmpty(&stack))
            {
                if (Peek(&stack) == '(') break;
                else pf[size++] = Pop(&stack);
            }
            Push(&stack, exp[i]);
        }
        else 
        {
            Push(&stack, exp[i]);
        }
    }
    while (!IsEmpty(&stack))
    {
        if (Peek(&stack) == '(' || Peek(&stack) == ')') Pop(&stack);
        else pf[size++] = Pop(&stack);
    }

    printf("%s\n", pf);
    memcpy(exp, pf, strlen(pf) + 1);
    return exp;
}

int GetOperatorPriority(char op)
{
    if (op == '*' || op == '/') return 5;
    else if (op == '+' || op == '-') return 3;
    else if (op == '(') return 1;
    else return -1;
}

int CompareOperatorPriority(char op1, char op2)
{
    if (op1 > op2) return 1;
    else if (op1 < op2) return -1;
    else return 0;
}

int EvalExp(char exp[])
{
    List stack;
    InitStack(&stack);
    int len = strlen(exp);
    for (int i = 0; i < len; i++)
    {
        if (isdigit(exp[i]))
        {
            Push(&stack, exp[i]);
        }

        else
        {
            int num2 = Pop(&stack) - '0';
            int num1 = Pop(&stack) - '0';
            int sol = -1;

            if (exp[i] == '+')
            {
                sol = num1 + num2;
            }
            else if (exp[i] == '-')
            {
                sol = num1 - num2;
            }
            else if (exp[i] == '*')
            {
                sol = num1 * num2;
            }
            else if (exp[i] == '/')
            {
                sol = num1 / num2;
            }

            Push(&stack, sol + '0');
        }
    }

    return Pop(&stack);
}

//Linked List functions
void InitStack(List* stack) 
{
    stack->head = NULL;
}

int IsEmpty(List* stack)
{
    if (stack->head == NULL) return 1;
    else return 0;
}

void Push(List* stack, char data)
{
    Node* temp = (Node*)malloc(sizeof(Node));

    temp->data = data;
    temp->next = stack->head;
    stack->head = temp;
}

char Pop(List* stack)
{
    char tempData;
    Node* temp;

    if (IsEmpty(stack))
    {
        return;
    }

    tempData = stack->head->data;
    temp = stack->head;

    stack->head = stack->head->next;
    free(temp);
    return tempData;
}

char Peek(List* stack)
{
    if (IsEmpty(stack))
    {
        return;
    }
    return stack->head->data;
}