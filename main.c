#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

int addTask();
int showTask();
void main(void)
{
    int choice;

    printf("Starting the program...\n");
    Sleep(2000);

    printf("=========== Select Your Choice =========== \n1. Add A Task. \n2. Display All Tasks.\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addTask();
        break;
    case 2:
        showTask();
        break;


    default:
        printf("Unknown Error Occured!");
        break;
    }

    printf("Program finished!\n");
    Sleep(1000);
    printf("Clearing all the trash in 5 seconds...");
    Sleep(5000);
    system("cls");
    exit(0);
}

int addTask()
{
    printf("Checking all the functionalities...\n");
    Sleep(2000);
    system("cls");

    int task;

    FILE *fp;
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Enter the number of tasks: ");
    scanf("%d", &task);

    while (getchar() != '\n')
        ;

    if (task < 1)
    {
        printf("Less than 1 task isn't accepted!\nPlease start the program again.\n");
        return 1;
    }

    fp = fopen("task.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fp, "\n");
    fprintf(fp, "Date and Time of Storage: %s\U0001F447\n", asctime(tm_info));

    for (int i = 0; i < task; i++)
    {
        char ctx[100];

        printf("Enter task %d: ", i + 1);
        fgets(ctx, 100, stdin);
        fprintf(fp, "%d. %s\n", i + 1, ctx);
        printf("Task %d added!\n", i + 1);
    }

    printf("Successfully added all the tasks!\n");
    fprintf(fp, "===========================\n");
    fclose(fp);

    return 0;
}

int showTask()
{
    int time;
    FILE *fp;
    char line[200];
    fp = fopen("task.txt", "r+");

    if (fp == NULL)
    {
        printf("Unknown Error Occurred!\n");
    }

    printf("Getting the Data...\n");
    Sleep(2000);
    printf("Data Recieved Successfully \u2705.\n");
    Sleep(1000);

    system("cls");
    printf("How much seconds would you like to take to read all the data?\n");
    scanf("%d", &time);

    if(time < 1){
        printf("Woah! You're a quick reader!\n Slow Down Buddy");
        Sleep(5000);
    }



    system("cls");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    Sleep(time*1000);
    return 0;
}