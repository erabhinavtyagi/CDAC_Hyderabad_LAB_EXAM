// Program for insertion sort

#include<stdio.h>

int main()
{
    int a[10], n, temp, i, j;

    printf("\n Enter the number of items: ");
    scanf("%d", &n);
    printf("\n Enter the Elements: ");
    
    for(i=0; i<n; i++)
    {
        scanf("\n%d", &a[i]);
    }

    // Sorting Logic
    for(i=1; i<n; i++)
    {
        temp = a[i];
        j = i-1;
        while(temp < a[j] && j>=0)
        {
            a[j+1] = a[j];
            j = j-1;
        }
        a[j+1] = temp;
    }

    // Display Sorted Output
    printf("\n Sorted Array is: \n");
    for(i=0; i<n; i++)
    printf("\n %d", a[i]);
    return 0;
}
