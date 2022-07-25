/* Basic C-Program to perform the functioning of Elevator.
*   1. Check Current Floor & Destination Floor. 
*   2. Is Button pressed from inside panel? Which button pressed?
*   3. Going Up or Down?
*   4. Is someone requested for lift?
*
*   AUTHOR      - Abhinav Tyagi
*   EMAIL ID    - erabhinavtyagi@gmail.com
*  
*/

#include <stdio.h>

#define num 5                  // Numbers of Floor

int destFloor = 0;
int currentFloor = 0;
int FL[num];                   // Floor Array 

int main()
{
    int i, req =0; 

    printf("To use the lift Press: 1 \n");
    scanf("%d", &req);

    while(req == 1)            // Lift Access is Required: "TRUE".
    {   
        printf("\nCurrent Floor : %d\n", currentFloor);
        printf("Press the Floor number you want to go.\n0: Ground Floor\n1: First Floor\n2: Second Floor\n3: Third Floor\n4: Fourth Floor\n5: Fifth Floor\n");
        scanf("%d", &destFloor);

    // Lift Going Upwards
        if (destFloor > currentFloor)           
        {   
            printf("\n");
            for (i= currentFloor; i < destFloor ; ++i)
            {
                printf("Passing Floor: %d\n", i);       // Passing the other Floors.
                FL[currentFloor++];
            }
            if (i == destFloor)
            FL[currentFloor] = i-1;
            printf("\nYou have reached at Floor: %d\nThankyou! Have a Nice Day.\n", destFloor);
        }

    // Lift Going Downwards
        else if(destFloor < currentFloor)      
        {
            printf("\n");
            for (i= currentFloor; i > destFloor ; --i)
            {
                printf("Passing Floor: %d\n", i);       // Passing the other Floors.
                FL[currentFloor--];
            }
            if (i == destFloor)                        // Reached Destination Floor     
            FL[currentFloor] = i+1;                     
            printf("\nYou have reached at Floor: %d \nThankyou! Have a Nice Day.\n", destFloor);
        } 
    }
    return 0;
}