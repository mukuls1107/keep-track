#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

int startApp();
int addTask();
int showTask();
int clearScreen();
int status();
int errorRaise();
int removeTask();
void removeStringFromFile(const char *filename, const char *stringToRemove);
int isFileEmpty(const char *filename);
int clearContent();

void main(void)
{
    startApp();
    int check;
    while (true)
    {
        check = status();
        if (check == 1)
        {
            break;
        }
    }
}

int startApp()
{
    int choice;

    printf("Starting the program...\n");
    Sleep(2000);
    system("cls");
    printf("=========== Select Your Choice =========== \n1. Add A Task. \n2. Display All Tasks.\n3. Remove Task.\n4. Clear Data.\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        addTask();
        clearScreen();
        return 0;
    }
    else if (choice == 2)
    {
        showTask();
        clearScreen();
        return 0;
    }
    else if (choice == 3)
    {
        removeTask();
        clearScreen();
        return 0;
    }
    else if (choice == 4)
    {
        clearContent();
        clearScreen();
        return 0;
    }
    else
    {
        system("cls");
        printf("Unknown Error Occured!");
        return 1;
    }
}

int errorRaise()
{
    printf("oops!\nAn Unknown Error Occured!\n");
    Sleep(2000);
    printf("Clearing the screen/trash...");
    system("cls");
    return 0;
}

void removeStringFromFile(const char *filename, const char *stringToRemove)
{
    FILE *inputFile, *outputFile;
    char line[256];

    inputFile = fopen(filename, "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        exit(1);
    }

    outputFile = fopen("temp.txt", "w+");
    if (outputFile == NULL)
    {
        perror("Error opening temporary file");
        fclose(inputFile);
        exit(1);
    }

    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        if (strstr(line, stringToRemove) == NULL)
        {
            if (fputs(line, outputFile) == EOF)
            {
                perror("Error writing to temporary file");
                fclose(inputFile);
                fclose(outputFile);
                exit(1);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    if (remove(filename) == 0)
    {
        if (rename("temp.txt", filename) != 0)
        {
            perror("Error renaming temporary file");
            exit(1);
        }
        printf("String removed successfully.\n");
    }
    else
    {
        perror("Error removing file");
        exit(1);
    }
}

int removeTask()
{
    char taskArr[100];

    while (getchar() != '\n')
        ;

    printf("Enter the task you wish to remove: ");
    fgets(taskArr, sizeof(taskArr), stdin);

    size_t len = strlen(taskArr);
    if (len > 0 && taskArr[len - 1] == '\n')
    {
        taskArr[len - 1] = '\0';
    }

    removeStringFromFile("task.txt", taskArr);

    return 0;
}

int status()
{
    char choice;
    printf("Restart The program Again? [Y/N]\n");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        startApp();
        return 0;
    }
    else if (choice == 'N' || choice == 'n')
    {
        printf("Closing the program...");
        Sleep(2000);
        clearScreen();
        return 1;
    }
}

int clearScreen()
{

    printf("Clearing all the trash in 5 seconds...");
    Sleep(5000);
    system("cls");
    return 0;
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
    fprintf(fp, "Date and Time of Storage: %s👇\n", asctime(tm_info));

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
        return 1;
    }

    printf("Getting the Data...\n");
    Sleep(2000);
    printf("Data Recieved Successfully .\n");
    Sleep(1000);

    system("cls");

    if (isFileEmpty("task.txt") == 1)
    {
        printf("Empty File...\n");
        Sleep(2000);
        return 0;
    }

    printf("How much seconds would you like to take to read all the data?\n");
    scanf("%d", &time);

    if (time < 1)
    {
        printf("Woah! You're a quick reader!\n Slow Down Buddy");
        Sleep(5000);
    }

    system("cls");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    Sleep(time * 1000);
    return 0;
}

int isFileEmpty(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    if (file_size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int clearContent()
{
    FILE *fp;
    char flag;
    printf("Are you sure you want to clear all the Data from the file? [Y/N]: ");

    scanf("%c", &flag);
    if (flag == 'Y' || flag == 'y')
    {
        fp = fopen("task.txt", "w");

        if (fp == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        fprintf(fp, "");

        fclose(fp);
        printf("Data Cleared [x].");
        return 0;
    }else{
        printf("Nothing Cleared!");
        return 0;
    }

    return 0;
}