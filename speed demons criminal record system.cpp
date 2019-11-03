/*
& Coded By Speed Demons
1)Shams
2)Pias
3)Robin
4)Raz
5)Shanto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
     int criminal_id;
     char Name[256];
     char case_name[256];
     int Telephone;
     int age;
    struct node* next;
} node;
 
typedef void (*callback)(node* data);
node* create( int criminal_id,char Name[256],char case_name[256],int Telephone,int age,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->criminal_id=criminal_id;
    strcpy(new_node->Name,Name); 
    strcpy(new_node->case_name,case_name);
    new_node->Telephone=Telephone;
    new_node->age=age;
    new_node->next = next;
    return new_node;
}
node* prepend(node* head,int criminal_id,char Name[256],char case_name[256],int Telephone,int age)
{
    node* new_node = create(criminal_id,Name,case_name,Telephone,age,head);
    head = new_node;
    return head;
}
 
void traverse(node* head,callback f)
{
     printf("--- Criminal Detail List--- \n\n");
    node* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}
node* remove_front(node* head)
{
    if(head == NULL)
        return NULL;
    node *front = head;
    head = head->next;
    front->next = NULL;
    if(front == head)
        head = NULL;
    free(front);
    return head;
}
node* remove_back(node* head)
{
    if(head == NULL)
        return NULL;
 
    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
 
    if(back != NULL)
        back->next = NULL;
 
    if(cursor == head)
        head = NULL;
 
    free(cursor);
 
    return head;
}
 
node* remove_any(node* head,node* nd)
{
    if(nd == NULL)
        return NULL;
    
    if(nd == head)
        return remove_front(head);
 

    if(nd->next == NULL)
        return remove_back(head);
 
    
    node* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nd)
            break;
        cursor = cursor->next;
    }
 
    if(cursor != NULL)
    {
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;
 
}

void display(node* n)
{

    if(n != NULL)
        printf("Criminal Name:-%s \t Case_name:-%s \t Criminal ID:-%d \t Mobile:-%d \t Age:-%d \n\n", n->Name,n->case_name,n->criminal_id,n->Telephone,n->age);
}
 

node* search(node* head,int criminal_id)
{
    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->criminal_id == criminal_id)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}
 

void dispose(node *head)
{
    node *cursor, *tmp;
 
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}

int count(node *head)
{
    node *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}


void menu()
{
    printf("--- Criminal record system--- \n\n");
    printf("0.menu\n");
    printf("1.Register a criminal\n");
     printf("2.Search for a criminal\n");
    printf("3.Update criminal Information\n");
    printf("4.Delete criminal Information\n");
       printf("5.Display All criminals\n");
    printf("-1.quit\n");
 
}

void displayAll(node *head)
{
      printf("--- Criminal details--- \n\n");
      printf("-- Criminal Name -- \t --Case name-- \t -- Mobile -- \t --Criminal ID -- \t -- Age --  \n\n");
 node *cursor=head;
    while(cursor != NULL)
    {
        cursor = cursor->next;
        printf("-- %s -- \t -- %s -- \t -- %d -- \t --%d-- \t -- %d --",cursor->Name,cursor->case_name,cursor->Telephone,cursor->criminal_id,cursor->age);

    }
}
 
int main()
{
    int command = 0;
    int criminal_id;
    char Name[256];
    char case_name[256];
    int Telephone;
    int age;
 
    node* head = NULL;
    node* tmp = NULL;
    callback disp = display;
 
    menu();
    while(1)
    {
        printf("\nEnter a command(0-5,-1 to quit):");
        scanf("%d",&command);
 
        if(command == -1)
            break;
        switch(command)
        {
        case 0:
            menu();
            break;
        case 1:
            printf("Please enter the name of criminal:");
            scanf("%s",Name);
           printf("\n Please Enter case name of Criminal:");
            scanf("%s",case_name);
            printf("\n Please Enter criminal ID:");
            scanf("%d",&criminal_id);
            printf("\n Please Enter mobile number of criminal:");
            scanf("%d",&Telephone);
            printf("\n Please Enter age of criminal:");
            scanf("%d",&age);
            
            head = prepend(head,criminal_id,Name,case_name,Telephone,age);
            traverse(head,disp);
            break;
        case 2:
            printf("Please enter Criminal ID:");
            scanf("%d",&criminal_id);
              tmp = search(head,criminal_id);
            if(tmp != NULL)
            {
                display(tmp);
            }
            else
            {
                printf("Criminal not found for This id:- %d .",criminal_id);
            }
            break;
       
        case 3:
            printf("Enter Criminal ID to Update:");
            scanf("%d",&criminal_id);
            tmp = search(head,criminal_id);
            if(tmp != NULL)
            {
            printf("Please enter the New name of Criminal:");
            scanf("%s",&Name);
            printf("\n Please Enter New case name of Criminal:");
            scanf("%s",&case_name);
            strcpy(tmp->Name,Name);
            strcpy(tmp->case_name,case_name);
        
            display(tmp);
            }
            else
            {
                printf("Criminal not found for this ID:- %d .",criminal_id);
            }
            break;
       
        case 4:
            printf("Enter the Criminal ID to remove:");
            scanf("%d",&criminal_id);
            tmp = search(head,criminal_id);
            if(tmp != NULL)
            {
               head=remove_any(head,tmp);
                if(head != NULL)
                    traverse(head,disp);
            }
            else
            {
                 printf("Criminal not found for this ID:- %d .",criminal_id);
            }
            break;
        case 5:
           traverse(head,disp);
            break;
       
        }
 
    }
    dispose(head);
    return 0;
}
