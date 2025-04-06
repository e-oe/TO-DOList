#include <stdio.h>
#include "functions.h"



int main(void) {
    printf("write a task to add the list\n");
    char task1[]="tak1";
    char task2[]="tak2";
    char task3[]="tak3";
    char task4[]="tak4";
    listPtr Liste;

    
    Liste=ReadFromFileAndCreateList(50);
    AddTask("so",Liste);
    AddTask("is",Liste);
    AddTask("this even matter",Liste);
    DisplayList(Liste);
    SaveListToFile(Liste);

    return 0;
}