#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100 // Maximum number of tasks
#define DESCRIPTION_LENGTH 100 // Maximum length for task description

typedef struct {
    int id;
    char description[DESCRIPTION_LENGTH];
    int completed; // 0 for incomplete, 1 for completed
} Task;

typedef struct {
    Task tasks[MAX_TASKS];
    int front, rear; // Front and rear indices of the queue
    int count;       // Count of elements in the queue
} Queue;

void initializeQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count == MAX_TASKS;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

void enqueue(Queue *q, Task task) {
    if (!isFull(q)) {
        q->rear = (q->rear + 1) % MAX_TASKS;
        q->tasks[q->rear] = task;
        q->count++;
        printf("Task added successfully!\n");
    } else {
        printf("Task list is full!\n");
    }
}

void dequeue(Queue *q) {
    if (!isEmpty(q)) {
        q->front = (q->front + 1) % MAX_TASKS;
        q->count--;
        printf("Task removed successfully!\n");
    } else {
        printf("No task to remove - queue is empty!\n");
    }
}

void listTasks(Queue *q) {
    if (!isEmpty(q)) {
        printf("Tasks:\n");
        printf("ID\tDescription\t\tCompleted\n");
        int i = q->front;
        int count = 0;
        while (count < q->count) {
            printf("%d\t%s\t\t%s\n", q->tasks[i].id, q->tasks[i].description, q->tasks[i].completed ? "Yes" : "No");
            i = (i + 1) % MAX_TASKS;
            count++;
        }
    } else {
        printf("No tasks - queue is empty!\n");
    }
}

void markTaskCompleted(Queue *q, int taskId) {
    int i = q->front;
    int count = 0;
    while (count < q->count) {
        if (q->tasks[i].id == taskId) {
            q->tasks[i].completed = 1;
            printf("Task marked as completed!\n");
            return;
        }
        i = (i + 1) % MAX_TASKS;
        count++;
    }
    printf("Task not found!\n");
}

void getUserInput(char *description) {
    printf("Enter task description: ");
    fgets(description, DESCRIPTION_LENGTH, stdin);
    if (description[strlen(description) - 1] == '\n') {
        description[strlen(description) - 1] = '\0';
    }
}

int main() {
    Queue taskQueue;
    initializeQueue(&taskQueue);

    char description[DESCRIPTION_LENGTH];
    int taskId = 1;
    char choice;

    printf("Welcome to the To-Do List!\n");

    do {
        getUserInput(description);
        Task newTask = {taskId++, "", 0};
        strcpy(newTask.description, description);
        enqueue(&taskQueue, newTask);

        printf("Do you want to add another task? (y/n): ");
        scanf(" %c", &choice);
        getchar();

    } while (choice == 'y' || choice == 'Y');

    listTasks(&taskQueue);

    int markId;
    do {
        printf("Enter the ID of the task you want to mark as completed (or enter 0 to exit): ");
        scanf("%d", &markId);
        while (getchar() != '\n');

        if (markId != 0) {
            markTaskCompleted(&taskQueue, markId);
            listTasks(&taskQueue);

        }
    } while (markId != 0);

    return 0;
}
