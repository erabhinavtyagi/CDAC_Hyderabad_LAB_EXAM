//02. Write a program to Sort a stack using a temporary stack.
Input :  8 5 7 1 9 12 10

#include<stdio.h>
#include<stdlib.h>
#define MAX 5

void push_main (int *, int);
void push_temp (int *, int);
int pop_main (int *);
int pop_temp (int *);
void sort (int *, int *);

int main_stack[MAX], temp_stack[MAX];
int top1 = 0, top2 = 0;

//-----------------MAIN FUNCTION------------------------------
int main ()
{
  int data, i, j;
  int *top1, *top2;
  top1 = main_stack;
  top2 = temp_stack;

//INPUT ELEMENTS IN MAIN STACK------------
  printf ("Enter Elements in Stack1:\n");
  for (i = 0; i < MAX; ++i)
    {
      scanf ("%d", &data);
      *(top1 + i) = data;
    }
  printf ("Top1: %d\n", *(top1 + i - 1));
  printf ("Main Stack is: \n");
  for (j = MAX - 1; j >= 0; j--)
    {
      printf ("Stack[%d] : %d\n", j, main_stack[j]);
    }
  //AFTER SORTING-----------------------------
  sort (top1 + i - 1, top2);
  return 0;
}

int pop_main (int *top1)
{
  int pop_value;
  pop_value = *top1;		// To check which value is popped from Stack.
 // printf ("Deleted %d\n", pop_value);
  top1--;
 // printf ("Top1 : %d\n", *top1);
  return pop_value;
}

//----------------- FUNCTION TO DELETE AN ELEMENT FROM TEMP_STACK---------------------
int pop_temp (int *top2)
{

  int pop_value;
  pop_value = *top2;		// To check which value is popped from Stack.
 // printf ("Deleted %d\n", pop_value);
  top2--;
 // printf ("Top2 : %d\n", *top2);
  return pop_value;
}


//---------------- FUNCTION TO SORT STACK----------------------------
void sort (int *top1, int *top2)
{
  int temp, x;

  printf ("INITIAL Top1: %d \t Top2: %d\n", *top1, *top2);

  while (top1 != NULL)		// Till Main Stack is not Empty
    {
      temp = pop_main (top1);	// delete item from Main Stack and save it in "temp"
      *top2++ = temp;		//else copy "temp" value in Temp_stack.
      // Check Till Temp_Stack is not Empty and if value of temp_stack is less than "temp" variable.
      while ((top2 != NULL) && (*top2 > temp))
	{
	  x = pop_temp (top2);	// Delete the Element from Temp_stack and save it in "x"
	  *top1++ = x;		// Copy value of "x" in Main Stack.
	}

      *top2++ = temp;		//else copy "temp" value in Temp_stack.
    }

  printf ("Sorted Array is: ");
  for (int i = 0; i < MAX; i++)
    {
      printf ("%d\t", temp_stack[i]);
    }
  printf ("\n");
}
