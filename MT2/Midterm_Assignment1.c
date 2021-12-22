#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define SIZE 50

int top = -1;
char stack[SIZE];


char pop()
{
   char item;
      //subtracts the value of top by one, removing the value of an element.
      return stack[top--];
}

void push(char item)
{
    //adds the value of top by one, pushing an element into the stack.
    stack[++top]=item;
}


int operators(char op)
{
	  if(op=='(')
    {
        return 1;
    }
    else if(op=='+' || op=='-')
    {
        return 2;
    }
    //highest precedence
    else if(op=='%'|| op=='*' || op=='/')
    {
        return 3;
    }
    else
    //lowest precedence
    {
        return 0;
    }
}

int main()
{
    char infix[SIZE], postfix[SIZE], eV[SIZE], temp;
    int i=0,p=0,d , d1, d2, val;

    printf("enter expression:");
    scanf("%s",infix);
    printf("Infix Expression: %s\n", infix);

    //assigns the current character of infix to temporary variable.
    while((temp=infix[i])!='\0')
    {

        //checks if the character of infix is a digit.
        if(isalnum(temp))
        {
            //assigns character digit to postfix expression
            postfix[p++]=temp;

        }
        else if(temp=='(')
        {

            push(temp);
        }
        else if(temp==')')
        {
            while(stack[top]!='(')
            {
                //assigns popped value to postfix expression.
                postfix[p++]=pop();
            }
            top--;
        }
        else
        {   //if the infix character has higher precedence than stack, it'll push the character into it.
            if((operators(temp)>operators(stack[top])) || top==-1)
            {
                push(temp);
            }
            else
            {
                //if the infix is lower, than it'll pop the stack element values until it is higher
                while((operators(temp)<operators(stack[top])) && top!=-1)
                {

                    postfix[p++]=pop();
                }
                push(temp);
            }
        }
    i++;
    }
    while(top!=-1)
    {

        postfix[p++]=pop();
    }
    //assigns last element of p to null character
    postfix[p]='\0';

    printf("Postfix Expression: %s\n", postfix);
   // copies postfix expression to eV
    strcpy(eV, postfix);
    //resets top value to -1
    top = -1;
    //empties stack array
    memset(stack,0,strlen(stack));
    for( i = 0;eV[i]!='\0';i++)
    {
        if(isdigit(eV[i]))
        {
            //converts character digit to numerical digit
            d = eV[i]-'0';
            push(d);
        }
        else
        {
                        //returned pop function is assigned to new function
                        d1 = pop();
                        d2 = pop();

                        //when the next character is an operator, the popped values will return based on case.
                        switch(eV[i])
                        {
                                case '+':
                                {
                                        val = d1 + d2;
                                        break;
                                }
                                case '-':
                                {
                                        val = d2 - d1;
                                        break;
                                }
                                case '*':
                                {
                                        val = d1 * d2;
                                        break;
                                }
                                case '/':
                                {
                                        val = d2 / d1;
                                        break;
                                }
                        }
                        //pushes the value to stack
                        push(val);

        }
    }
    printf("Evaluated Expression: %d\n", pop());
    return 0;
}
