/*
*                   CDAC HYDERABAD LAB EXAM, AUG 2022
*           **************************************************
*
*1. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms.
*   Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.
*   Priorities of Tasks T1,T2,T3,T4,T5 are 5,6,7,8,9 respectively.
*
*   AUTHOR      - Abhinav Tyagi
*   EMAIL ID    - erabhinavtyagi@gmail.com
*  
*/


#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#define QueueLength 4       // 4 blocks
#define ItemSize 16         // 16 Kb

TaskHandle_t task1Handle,task2Handle,task3Handle,task4Handle,task5Handle;
QueueHandle_t q_t4_t5;

void task1(void *data)
{
    while(1)
    {
        printf("\n------------ IN TASK 1 -----------\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task2(void *data)
{
    while(1)
    {
        printf("\n------------ IN TASK 2 -----------\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task3(void *data)
{
    while(1)
    {
        printf("\n------------ IN TASK 3 -----------\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task4(void *data)
{
    BaseType_t send;
    int pdata = 100;

    while(1)
    {   
        pdata++;
        printf("\n------------ IN TASK 4 -----------\n");
        send = xQueueSend(q_t4_t5, &pdata, pdMS_TO_TICKS(1000));
        if (send == pdFALSE)
        {
            perror("Sending Failed\n");
        }
        else
        {
            printf("Pressure Data Sent to Task 5\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    vTaskDelete(NULL);
}

void task5(void *data)
{
    int buffer;
    BaseType_t rec =0;
    while(1)
    {   
        printf("\n------------ IN TASK 5 -----------\n");
        
        rec = xQueueReceive(q_t4_t5, &buffer, pdMS_TO_TICKS(1000));
        if (rec == pdTRUE)
        {
            printf("Data Received from Task 4: %d\n", buffer);
        }                       
        else
        {
            perror("Error in Receving Data From TASK 4.\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    BaseType_t res;

    printf("Starting Main Task\n\n");

    // Create Queue to Transfer Data from Task 4 to Task 5
       q_t4_t5 = xQueueCreate(QueueLength, ItemSize);

   // Create Task 1
   res = xTaskCreate(task1, "Task1", 2048, NULL, 5, &task1Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task1.\n");
   }
   else
   {
    printf("Task1 Created.\n");
   }

    // Create Task 2
   res = xTaskCreate(task2, "Task2", 2048, NULL, 6, &task2Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task2.\n");
   }
    else
   {
    printf("Task2 Created.\n");
   }

   // Create Task 3
   res = xTaskCreate(task3, "Task3", 2048, NULL, 7, &task3Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task3.\n");
   }
    else
   {
    printf("Task3 Created.\n");
   }

   // Create Task 4
   res = xTaskCreate(task4, "Task4", 2048, NULL, 8, &task4Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task4.\n");
   }
    else
   {
    printf("Task4 Created.\n");
   }

   // Create Task 5
   res = xTaskCreate(task5, "Task5", 2048, NULL, 9, &task5Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task5.\n");
   }
   else
   {
    printf("Task5 Created.\n");
   }
}
