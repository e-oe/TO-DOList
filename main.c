#include <stdio.h>
#include "functions.h"



int main(void) {
    printf("write a task to add the list\n");
    char task1[]="tak1";
    char task2[]="tak2";
    char task3[]="tak3";
    char task4[]="tak4";
    listPtr List=CreateList();


    AddTask(task3,List);
    AddTask(task1,List);
    AddTask(task2,List);
    AddTask(task4,List);
    DisplayList(List);
    printf("after the operation\n");
    ChangeTaskPriority(List->tail,List,List->head,List,0);
    DisplayList(List);













    return 0;
}