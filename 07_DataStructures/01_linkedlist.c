// Create a Linked List - 4,6,7,8,9 and add 11 at the end.

#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  struct node *next;
} *head;

void createlist (int n);
void display ();
void insertnodeatend (int data);

int main ()
{
  int n, data;
  printf ("Enter the Total Number of Nodes: ");
  scanf ("%d", &n);
  createlist (n);
  printf ("Enter the data to Enter at the end of list: \n");
  scanf ("%d", &data);
  insertnodeatend (data);
  printf ("Data in List\n");
  display ();
}

void insertnodeatend (int data)
{
  struct node *newnode, *temp;
  newnode = (struct node *) malloc (sizeof (struct node));
  if (newnode == NULL)
    {
      printf ("Unable to allocate memory\n");
    }
  else
    {
      newnode->data = data;
      newnode->next = NULL;

      temp = head;
      while (temp != NULL && temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = newnode;
      printf ("Data is inserted.\n:");
    }
}

void createlist (int n)
{
  struct node *newnode, *temp;
  int data, i;
  head = (struct node *) malloc (sizeof (struct node));
  if (head == NULL)
    {
      printf ("Unable to allocate Memory");
    }
  else
    {
      printf ("Enter the data of Node 1: ");
      scanf ("%d", &data);
      head->data = data;
      head->next = NULL;
      temp = head;

      for (i = 2; i <= n; i++)
	    {
	      newnode = (struct node *) malloc (sizeof (struct node));
        if (newnode == NULL)
          {
            printf ("Unable to allocate memory.\n");
            break;
          }
        else
          {
            printf ("Enter the data of Node %d: ", i);
            scanf ("%d", &data);
            newnode->data = data;
            newnode->next = NULL;

            temp->next = newnode;
            temp = temp->next;
          }
      }
      printf ("List is created.\n");
    }
}

void display ()
{
  struct node *temp;
  if (head == NULL)
    {
      printf ("List is Empty.\n");
    }
  else
    {
      temp = head;
      while (temp != NULL)
      {
        printf ("Data is %d.\n", temp->data);
        temp = temp->next;
      }
    }
}