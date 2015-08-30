/*************************************
* Lab 1 Exercise 2
* Name: Eugene
* Matric No: A0116631N
* Lab Group: 8
*************************************/

#include <stdio.h>
#include <stdlib.h> //for malloc() and free()

//Declaration of a Linked List Node
typedef struct NODE{
    int data;
    struct NODE* next;
} node;

//Function Prototypes
node* insertAt(node*, int, int);
void printList(node*);
void destroyList(node*);


int main()
{
    node* myList = NULL;    //Empty List
    int pos, input;

    //Fill in code for input and processing
    while (scanf("%i %i", &pos, &input) == 2){
        myList = insertAt(myList, pos, input);
    }

    //Output code coded for you
    printf("My List:\n");
    printList(myList);
    
    destroyList(myList);
    myList = NULL;

    
    printf("My List After Destroy:\n");
    printList(myList);
 
    return 0;
}

//Actual Function Implementations
node* insertAt(node* head, int pos, int newData)
{
    int i;
    node* ptr = malloc(sizeof(node));
    ptr->data = newData;
    if (head == NULL){
        head = ptr;
    } else if (pos == 0){
        ptr->next = head;
        head = ptr;
    } else {
        node* cursor = head;
        for (i = 0; i < pos - 1; i++){
            if (cursor->next == NULL){
                break;
            }
            cursor = cursor->next;
        }
        ptr->next = cursor->next;
        cursor->next = ptr;
    }
    return head;
}
 
void printList(node* head)
//Purpose: Print out the linked list content
//Assumption: the list is properly null terminated
{
    //This function has been implemented for you
    node* ptr = head;

    while (ptr != NULL)  {    //or you can write while(ptr)
        printf("%i ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void destroyList(node* head)
{
    node* curr;
    while ((curr = head) != NULL){
        head = head->next;
        free(curr);
    }
}
