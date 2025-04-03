#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddTask(char task[],listPtr list) {
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
    if (list->head==NULL) {
        list->head=node;
        list->tail=node;
        list->listSize++;
    }
    else {
        node->previous=list->tail;
        list->tail->next=node;
        list->tail=node;
        list->listSize++;
    }
}// Görev düğümünü listenin sonuna ekleyen fonksiyon
void AddBeforeAfterTask(char task[],listPtr List,taskPtr neighbouringTask,int beforeOrAfter) {
    
}//Tercihe göre bir görevi istenen herhangi bir görevden önce veya sonra oluşturur.

listPtr CreateList() {
    listPtr taskList=(listPtr)malloc(sizeof(List));
    if (taskList==NULL) {// Allocation kontrolü
      printf("Memory Allocation Failed");
        return NULL ;
    }
    taskList->head=NULL;
    taskList->tail=NULL;
    taskList->listSize=0;

    return taskList;
}//Liste oluşturup dönen fonksiyon.

void DisplayList(listPtr List) {
    if (List->listSize==0) {
        printf("Listeniz boş");
        return;
    }
    if (List->tail->next!=NULL) {
        printf("Listeniz Silinmiş");
        return;
    }

    taskPtr temp=List->head;
    while (temp!=NULL) {
        printf(temp->task);
        printf("\n");
        temp=temp->next;
    }
}//Listedeki görevleri gösteren fonksiyon

taskPtr FindTask(char task[],listPtr list) {
    if (list->listSize==0) {
        printf("Listeniz herhangi bir görev yok.");
        exit(-1);
    }
    else {
        taskPtr temp=list->head;
        for (int i=0;i<list->listSize;i++) {
            if (strcmp(temp->task, task) == 0) {
                return temp;
            }
            else {
                temp=temp->next;
            }
        }
        printf("Görev Bulunamadı");
        return 0;
    }

}// Listeden istenen görevı arayan fonksiyon

void DeleteTask(taskPtr node,listPtr list) {
    if (!FindTask(node->task,list)) {
        printf("Silinecek Görev Bulunamadı");
    }
    if (list->listSize==1) {
        free(node);
        list->listSize--;
        list->head=NULL;
        list->tail=NULL;
        return;
    }
    if (list->listSize>1&&node==list->head) {
        list->head=node->next;
        list->head->previous=NULL;
        free(node);
        list->listSize--;
        return;
    }
    if (list->listSize>1&&node==list->tail) {
        list->tail=node->previous;
        node->previous->next=NULL;
        free(node);
        list->listSize--;
        return;
    }
    else {
        node->previous->next=node->next;
        node->next->previous=node->previous;
        free(node);
        list->listSize--;
    }
}// Verilen listeden taski silen fonksiyon

void ClearList(listPtr List) {
    taskPtr temp=List->head;
    while (List->head!=NULL) {
        List->head=List->head->next;
        free(temp);
        temp=List->head;
    }
    List->tail=NULL;
    List->listSize=0;
}//Verilen listedeki tüm verileri silip freeler

void FreeList(listPtr List) {
        ClearList(List);
        free(List);
}// Listeyi önce silip ardından listeyi freeler

void ChangeTaskPriority(taskPtr taskToMove,listPtr ListTheTaskIsFrom,taskPtr newNeighbouringTask,listPtr DestinationList,int beforeOrAfter) {
    taskPtr temp=taskToMove;
    DeleteTask(taskToMove,ListTheTaskIsFrom);


}//Tercihe göre bir görevi istenen herhangi bir görevden sonraya veya önceye taşır.

void SaveListsToFiles();





