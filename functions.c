#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

taskPtr CreateTask(char task[]) {// Görev düğümü oluşturan fonksiyon
    taskPtr node=(taskPtr)malloc(sizeof(Task));
    if (node==NULL) {//Allocation kontrolü
        printf("Memory Allocation Failed");
        exit(-1);
    }
    node->next=NULL;
    node->previous=NULL;
    node->task=strdup(task);
    if (node->task==NULL) {//Strdup Allocation kontrolü
        printf("TMemory Allocation Failed");
        free(node);
        exit(-1);
    }
    return node;
}

listPtr CreateList() { //Liste oluşturup dönen fonksiyon.
    listPtr taskList=(listPtr)malloc(sizeof(List));
    if (taskList==NULL) {// Allocation kontrolü
      printf("Memory Allocation Failed");
        return NULL ;
    }
    taskList->head=NULL;
    taskList->tail=NULL;
    taskList->listSize=0;

    return taskList;
}


