//Implement string library functions strlen, strcpy, strcat, strcmp with same return values and all error handling features using pointers.


#include <stdio.h>

int len (char *);
void concat (char *, char *);
char copy (char *, char *);
int cmp (char *, char *);


void
main ()
{
  char str1[1000], str2[1000];
  int d;

  //Input by User
  printf ("Enter First String : ");
  scanf ("%[^\n]%*c", str1);
  printf ("Enter Second String : ");
  scanf ("%[^\n]%*c", str2);

  //Length of String
  printf ("\n\n01. Length of String1 is %d \t", len (str1));
  printf ("Length of String2 is %d \n", len (str2));

  //String Comparision
  printf ("02. After Comparision Value is : %d\n", cmp (str1, str2));

  // Concatenation of Strings.
  concat (str1, str2);
  printf ("03. Concatenated String is %s\n", str1);

  // Copy String2 to string1
  copy (str1, str2);
  printf ("04. After copying String2 to string1: %s\n\n", str1);

}

/*-------------------------FUNCTIONS----------------------------------*/

// FUNCTION 1:TO FIND LENGTH OF A STRING.
int
len (char *c)
{
  int i, len = 0;
  for (i = 0; c[i] != '\0'; i++)
    len++;
  return len;
}

// FUNCTION 2 : CONCATATENATION OF TWO STRINGS.
void
concat (char *c, char *d)
{
  int i, l;
  l = len (c);			//Calling length function to determine length of string.
  // Insert the second string in the first string
  for (i = 0; d[i] != '\0'; i++)
    {
      c[i + l] = d[i];
    }
  c[i + l] = '\0';
}

// FUNCTION 3 : COPY CONTENTS OF STR2 TO STR1.
char
copy (char *c, char *d)
{
  int i;
  for (i = 0; c[i] != '0'; i++)
    {
      c[i] = d[i];
    }
  c[i] = '\0';
}

// FUNCTION 4 : COMPARE BOTH STRINGS.
int
cmp (char *c, char *d)
{
  for (; (*c - *d) == 0; c++, d++);
  return (*c - *d);
}
