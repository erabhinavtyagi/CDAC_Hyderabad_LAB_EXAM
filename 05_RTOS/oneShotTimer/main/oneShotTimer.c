// CREATE TASK 1,2,3,4,5 ; DELAY = 1000,2000,5000 RESPECTIVELY.
// SEND INTEGER DATA FROM TASK 4 TO 5 USING MESSAGE QUEUE

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>


TaskHandle_t task1Handle,task2Handle,task3Handle;
TimerHandle_t oneShotTimer;


void callTimer(TimerHandle_t xTimer)
{
     printf("Timer Fired. Do ANY Functionality Here!!\n");
}

void task1(void *data)
{
    printf("Task 1 Started.\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task2(void *data)
{
    printf("Task 2 Started.\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task3(void *data)
{
    printf("Task 3 Started.\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    xTimerStart(oneShotTimer,0);
    vTaskDelete(NULL);
}


void app_main(void)
{
    BaseType_t res;

    printf("Starting Main Task\n\n");

    /*
    TimerHandle_t xTimerCreate
                 ( const char * const pcTimerName,
                   const TickType_t xTimerPeriod,
                   const UBaseType_t uxAutoReload,
                   void * const pvTimerID,
                   TimerCallbackFunction_t pxCallbackFunction );
    */

   oneShotTimer = xTimerCreate ("Timer", pdMS_TO_TICKS(10000), pdTRUE, 0, callTimer);
                   
    //**************** Create 5 Tasks **************************

   /* BaseType_t xTaskCreate(TaskFunction_t pvTaskCode,
                            const char * const pcName,
                            configSTACK_DEPTH_TYPE usStackDepth,
                            void *pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t *pxCreatedTask
                          );
    */
   
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
}
