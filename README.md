# CDAC Hyderabad Lab Exams, Batch March 2022.

## C Programming

1. Prime Fibonacci numbers in given range using Recursion.

2. Implement string library functions strlen, strcpy, strcat, strcmp with same return values and all error handling features using pointers.

3. *Student record management System* 
Write a C program to keep records and perform statistical analysis for a class of 5 students. The information of each student contains: 
RollNumber, Name, Gender, Exam Score.

Do following operations :
- Add student records
- View all student records
- Show student who gets the maximum score
- Show student who gets the minimum score 


## ARM 

1. Implement a SVC Handler to cater for the following requirements:
    
    - Before calling the SVC exception ensure that the processor is driven in unprivileged mode of operation
      with PSP acting as Stack Pointer and initialize PSP with a valid address.
    
    - **SVC 0X01** : Should drive the processor in privilege mode of operation with the PSP as stack pointer  when it returns back to thread mode. Perfom 64 bit unsigned addition in SVC 0X01 handler by passing initialized values of parameters via registers in Thread Mode and storing results in registers.   

    - **SVC 0x02** : Should drive the processor in privilege mode of operation with MSP as stack pointer when it returns back to thread mode. Perfom 64 bit unsigned subtraction in SVC 0X02 handler by passing initialized values of parameters via registers in Thread Mode and storing results in registers.

    Note: You may choose appropriate registers for parameter passing and results.
       
2. Write an Embedded C Program to carry out a loopback operation using UART interface.
   Data should be received using "Interrupt mechanism" and transferred back using "Polling mechanism".    


## Embedded Operating System

1. Using PIPE
    - Open "usr/include/stdio.h" in parent process.
    - Create a child process and count number of "S" in it. 

2. Using Posix Message Queue
    - Send the file "usr/include/stdio.h" to receiver and Receiver will count number of "s" in the file.

## Embedded Linux Device Driver

1. LED OPERATION USING GPIO & TIMERS
    - Write a Character Driver using ioctl & Kernel Timer functionality.
    - Use GPIO_23 to interface LED on RaspberryPi and blink the LED Periodically using Kernel Timer.
    - Use ioctl functionality to change the periodicity of LED Blinking. 

2. KERNEL SYNCHRONIZATION MECHANISMS FOR MULTIPLE DEVICES

    - Write a Character Driver for Multiple Devices and create two device numbers. 
      Use Semaphore to protect the Critical section (write activity) and Use WaitQueue to avoid 
      consecutive write operations.
    - Maintain a Kernel Buffer of 50 bytes to Read and Write Data.  
    - Put write function to sleep using WaitQueue after successful write operation before releasing semaphore.
    - Wake-up sleep (waitqueues) operation only in Read function.
    - Write two separate programs for Read and Write for each device.

## Real Time Operating Systems

1. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms.
Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.
Priorities of Tasks T1,T2,T3,T4,T5 are 5,6,7,8,9 respectively.

2. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. 
Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.
Priorities of Tasks T1,T2,T3 are 5,6,7 respectively.

## IOT Hackathon 

Time limit: 48hours & using kits provided by CDAC only. No other components allowed.

1. To design and develop "Smart Weather Monitoring System"
2. To design and develop "Metal Detection System"
3. To design and develop "Smart Home"

## Data Structures & Algorithms

1. Create a Linked List with data "4,6,7,8,9" and add 11 at the end.
2. Program for insertion sort.
3. Sort a Stack having following values. 
    Input :  8 5 7 1 9 12 10
