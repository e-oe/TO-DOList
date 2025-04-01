#include <stdio.h>
#include "functions.h"



int main(void) {
    printf("Hello, World!\n");
    char task[]="first taskolkjuhiyhgbhgvytffgfcgfctructdrturdcdtfgfc";
    taskPtr gorev=CreateTask(task);
    printf(gorev->task);

    return 0;
}