#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct
{
    Node*head;
    Node*tail;
} DoublyLinkedList;

DoublyLinkedList*init()
{
    DoublyLinkedList *l=malloc(sizeof(DoublyLinkedList));
    l->head=NULL;
    l->tail=NULL;
    return l;
}

Node *newNode(int x)
{
    Node *n=malloc(sizeof(Node));
    n->data=x;
    n->next=NULL;
    n->prev=NULL;
    return n;
}

DoublyLinkedList* convertArrayToDoublyLinkedList(int array[], int size)
{
    DoublyLinkedList *list = init();
    Node *n =list->head;
    n=newNode(array[size-1]);
    int i;
    n->data=array[0];
    n->next=NULL;

    if (list->head==NULL)
        list->head=list->tail=NULL;

    for (i=1; i<size; i++)
    {
        n=list->head->next;
        n->data=array[i];
    }
    return list;
}

void printlnListForward(DoublyLinkedList * list)
{
    Node *n=list->head;
    while (n!=NULL)
    {
        printf("%d",n->data);
        n->next=list->head->next;
    }
    printf("\n");
}

void printlnListBackward(DoublyLinkedList * list)
{

    Node *n=list->tail;
    while (n!=NULL)
    {
        printf("%d",n->data);
        n->prev=list->tail->prev;
    }
    printf("\n");
}

DoublyLinkedList *copy (DoublyLinkedList *list)
{
    DoublyLinkedList *newList=init();
    while (newList->head!=NULL)
    {
        newList->head->data=list->head->data;
        newList->head->next=list->head->next;

    }
    return newList;
}

void concatenate(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    Node *l1=list1->head;
    Node *l2=list2->head;
    if (l1==NULL)
        l1->next=l2;
    while (l1!=NULL)
        l1=l1->next;
    l1->next=l2;
    if (l2==NULL)
        l1=l1->next;

}


int areEqual(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    while (list1->head!=NULL && list2->head!=NULL)
    {


        if  (list1->head==list2->head)
        {
            return 1;
            list1->head=list1->head->next;
            list2->head=list2->head->next;
        }
        else
            return 0;
    }
}

int isPalindrome(DoublyLinkedList * list)
{
    while (list->head!=NULL)
    {
        if (list->head==list->tail)
        {
            return 1;
            list->head=list->head->next;
            list->tail=list->tail->prev;
        }
        else
            return 0;
    }
}

size_t length(DoublyLinkedList*  list)
{
    size_t count = 0;
    if (list->head==NULL)
    {
        list->head=list->tail=NULL;
        return count;
    }
    while (list->head!=NULL)
    {
        count++;
        list->head=list->head->next;
    }
    return count;
}

void Destroy (DoublyLinkedList *list)
{
    while (list->head!=NULL)
    {
        Node *t=list->head;
        list->head=list->head->next;
        free(t);
    }
    list->tail=NULL;
}

DoublyLinkedList* getDifferenceBetweenLists(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    DoublyLinkedList *newlist = init();
    Node *l1=list1->head;
    Node *l2=list2->head;
    while (l1!=NULL && l2!=NULL)
    {
        if (l1->data==l2->data)
        {
            l1=l1->next;
            l2=l2->next;
        }
        else if (l1->data!=l2->data)
        {
            newlist->head->data =l1->data;
            newlist->head->next=l1->next;
        }
    }
    while (l1!=NULL)
    {
        newlist->head->data=l1->data;
        newlist->head->next=l1->next;
    }
    return newlist;
}

int checkSumofFirstHalfEqualSumOfSecondHalf(DoublyLinkedList*  list)
{
    Node *l=list->head;
    int sum1, sum2;
    while (l!=NULL)
    {

    }
}

int main()
{
    system("color f0");
    DoublyLinkedList *list=init();
    int array[]= {1,2,3};
    list=convertArrayToDoublyLinkedList(array,3);
    printlnListForward(list);
    return 0;
}
