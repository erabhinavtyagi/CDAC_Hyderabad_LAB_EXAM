/*      Student record management System 
Write a C program to keep records and perform statistical analysis for a class of 5 students.  The information of each student contains: 
    • RollNumber
    • Name
    • Sex
    • Exam Score.  
Do following operations
1. Add student records
2. View all student records
3. Show student who gets the maximum score
4. Show student who gets the minimum score */

//---------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#define N 3			// To change number of students in class easily

struct student
{
  char name[20], gender;
  int roll;
  float marks;
} stud[N];			// records of N students

void
main ()
{				//struct student stud[n];       // Can be declare here also.
  int i;
  
printf("sizeof structure is %ld", sizeof(struct student));
  //-------Take Input from User----------------------
  printf ("Enter Details of Students.\n");
  printf ("----------------------------------\n");
  for (i = 0; i < N; i++)
    {
      printf ("Student [%d]------\n", i + 1);

      printf ("Name	:");
      scanf ("%s", stud[i].name);

      printf ("gender	:");
      scanf (" %c", &stud[i].gender);	//space is given before %c to avoid Buffer Error otherwise it will skip it.

      printf ("Roll num:");
      scanf ("%d", &stud[i].roll);

      printf ("Marks	:");
      scanf ("%f", &stud[i].marks);
    }

  //----------Print Record--------------------------
  printf ("\nDetails of Students are following.\n");
  for (i = 0; i < N; i++)

    {
      printf ("Student [%d]------\n", i + 1);

      printf ("Name		:%s\n", stud[i].name);
      printf ("gender		:%c\n", stud[i].gender);
      printf ("Roll num		:%d\n", stud[i].roll);
      printf ("Marks		:%.2f\n\n", stud[i].marks);
    }
//--------------MAXIMUM and MINIMUM SCORE----------------------
  char nm_h[20], nm_l[20];
  float max, min;
  max = stud[0].marks;
  min = stud[0].marks;


  for (i = 0; i < N; i++)
    {

      if (stud[i].marks > max)
	{
	  max = stud[i].marks;
	strcpy(nm_h, stud[i].name);
	}
      else if (stud[i].marks < min)
	{
	  min = stud[i].marks;
	 strcpy(nm_l, stud[i].name);
	}
    }

  printf ("%s got Highest Marks in class= %.2f\n", nm_h, max);
  printf ("%s got Lowest Marks in class = %.2f \n", nm_l, min);

}
