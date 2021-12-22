#include <stdio.h>
#include <stdlib.h>

//create node
typedef struct Node
{
    int data;
    struct Node * next;
    struct Node * prev;
} N;

//initially head points to nowhere
N* head = NULL;


N* link(int n, N* queue, N* head);
void execution(int n, int k, N* head);

int main(int argc, char const *argv)
{
//variables for input
int n, k;
head = ( N*)malloc(sizeof(N));
N* queue;
printf("Enter number of persons: \n");
scanf("%d",&n);
printf("Enter the person who goes first: \n ");
scanf("%d",&k);

//checks variables
if(n<2||k==0)
{
    printf("please retry input: ");
    exit (0);
}

//assigns address of temp variable to queue
queue=link(n,queue,head);
printf("Hurry before the Romans capture us!: \n");

//decides which prisoner is killed off in pattern
execution(n,k,head);

//deallocates queue
free(queue);
return 0;
}

N* link(int n, N* queue, N* head )
{
    int item = 1;
    //until item is equal to n+1, the following if conditions will check
    while(item!= n+1)
    {
        //the initial head becomes the queue when the it links to nowhere
        if(item==1)
        {
            head->data = item;
            head->next = NULL;
            head->prev = NULL;
            queue = head;
        }
        //when item equals to the number of prisoners, the head will link to the queue node, while
        //the previous queue node will link to the head
        else
        {
            //temp data takes the data from item, temp next links to queue
            //temp prev points to nowhere, temp becomes the queue.
            N* temp;
            temp = (N*)malloc(sizeof(N));
            temp->data = item;
            temp->next = queue;
            temp->prev = NULL;
            queue->prev = temp;
            queue = temp;
        }
         if(item==n)
        {
            head->next = queue;
            queue->prev = head;
        }
        item++;
    }
    return queue;
}

void execution(int n, int k, N*head)
{
 int temp;
 temp = n;


 //until temp becomes 1
while(temp!=1)
{
    int b;
    //until b equals k minus 1
    for(b = 0; b<k-1;b++)
    {
        head = head->prev;
    }

    int m = head->data;

    N *p1, *p2, *joint;

    //pointers point to previous and next node
    p1= head->prev;
    p2= head->next;

    //head-next of previous points to pointer 1, head-previous of next points to pointer 2
    (head->next)->prev = p1;
    (head->prev)->next = p2;

    //head becomes joint, and head p1s linked to head of previous
    joint = head;
    head = head->prev;

    //deallocates joint
    free(joint);

    //as long as temp is equal to the number of prisoners
    if(temp==n)
    {
        printf("Person %d  is sacrificed\n", m);
    }
    //as long as temp is equal to 2
    else if(temp==2)
    {
        printf("Lastly, Person %d is sacrificed\nPerson %d gets captured by the Romans", m,head->data);

    }

    else
    {
        printf("Person %d is sacrificed\n", m);
    }
    //temp decrements by one every loop
    temp--;

}
}
