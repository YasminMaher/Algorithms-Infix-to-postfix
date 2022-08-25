#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TYPE int

typedef struct
{
    TYPE* arr;
    int size;
    int top;
} Stack;

/*int parseInt(char input)
{
    return input-48;
}*/

void initialize(Stack *s, int size)
{
    s->arr=(TYPE*)malloc(size*sizeof(TYPE));
    s->size=size;
    s->top=-1;
}

void push(Stack *s, TYPE value)
{
    s->arr[++(s->top)]=value;
}

TYPE pop(Stack *s)
{
    return s->arr[s->top--];
}

TYPE peek(Stack *s)
{
    if(isEmpty(s))
    {
        return '\0';
    }
    return s->arr[s->top];
}

int isEmpty(Stack *s)
{
    if(s->top==-1)
    {
        return 1;
    }
    return 0;
}

int evaluate(char* postfix)
{
    Stack s;
    initialize(&s, 64);
   char *t;
    t = strtok(postfix, " ");
    while(t != NULL) {
       if(isdigit(*t)) {
        push(&s, atoi(t));
       }
        else {
            int n2 = pop(&s), n1 = pop(&s);
            switch(*t) {
                case '+': push(&s,n1+n2); break;
                case '-': push(&s,n1-n2); break;
                case '*': push(&s,n1*n2); break;
                case '/': push(&s,n1/n2); break;
            }
        }
        t = strtok(NULL, " ");
    }
    return pop(&s);
}

int getPrecedence(char input)
{
    if (input =='+' || input == '-') return 1;
    if (input=='*' || input=='/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix)
{
    Stack operators;
    initialize(&operators, 20);
    while(*infix!='\0' && *infix!='\n')
    {

        if(*infix>='0' && *infix <='9')    // An Operand is Found- put it in
        {
            while(*infix>='0' && *infix <='9' && *infix!='\0' && *infix!='\n') {
            *postfix=*infix;
            postfix++;
            infix++;
            }
            infix--;
            *postfix=' ';
            postfix++;
        }

        else if(*infix=='(')             // A Left Parenthesis is Found
        {
            push(&operators, *infix);
        }

        else if(*infix==')')             // A Right Parenthesis is Found
        {
            while(peek(&operators)!='(')
            {
                *postfix=pop(&operators);
                postfix++;
                *postfix=' ';
                postfix++;
            }
            pop(&operators);
        }
        else                             // An Operator is Found
        {
            while(getPrecedence(peek(&operators))>=getPrecedence(*infix))
            {

                *postfix=pop(&operators);
                 postfix++;
                 *postfix=' ';
                 postfix++;

            }
            push(&operators, *infix);

        }
        infix++;
    }
    while(!isEmpty(&operators))
    {
        *postfix=pop(&operators);
        postfix++;
        *postfix=' ';
        postfix++;
    }
    *(--postfix)='\0';
}


int main()
{
    while(1){
            printf("\nenter infix equation or q to exit\n");
    int i;

//    char *infix = (char)malloc(14*sizeof(char));
//    char *postfix = (char)malloc(14*sizeof(char));
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    scanf("%s", infixExpr);
    infixToPostfix(&infixExpr , &postfixExpr);

    printf("%s", postfixExpr);

    int x = evaluate(postfixExpr);
    //if(x<0) x=-x;
    printf("\n%d" , x);
    }
}
