#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

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

void AddBeforeAfterTask(char task[],listPtr list,taskPtr neighbouringTask,int beforeOrAfter) {
    if (neighbouringTask==NULL) {
        printf("Trying to access deleted data");
        exit(-1);
    }
    taskPtr node=(taskPtr)malloc(sizeof(Task));
    if (node==NULL) {//Allocation kontrolü
        printf("Memory Allocation Failed");
        exit(-1);
    }
    node->task=strdup(task);
    list->listSize++;
    if (list->listSize==1) {
        node->previous=NULL;
        node->next=NULL;
        list->head=node;
        list->tail=node;
        return;
    }
    if (beforeOrAfter) {//beforeOrAfter değişkenine 1 verildiğinde neighbouring task ten once yerlestir
        if (list->head==neighbouringTask) {
            list->head=node;
            node->next=neighbouringTask;
            node->previous=NULL;
            neighbouringTask->previous=node;
            return;
        }
        else {
            node->previous=neighbouringTask->previous;
            neighbouringTask->previous->next=node;
            node->next=neighbouringTask;
            neighbouringTask->previous=node;
            return;
        }
    }
    else {//beforeOrAfter değişkenine 0 verildiğinde neighbouring task dan sonra yerlestir
        if (list->tail==neighbouringTask) {
            list->tail=node;
            node->previous=neighbouringTask;
            neighbouringTask->next=node;
            node->next=NULL;
            return;
        }
        else {
            node->next=neighbouringTask->next;
            neighbouringTask->next->previous=node;
            node->previous=neighbouringTask;
            neighbouringTask->next=node;
            return;
        }
    }
}//Tercihe göre bir görevi istenen herhangi bir görevden önce veya sonra oluşturur. Int olarak 1 gönderirse komşu taskın önüne 0 gönderilirse arakasına yerleşir.

masterListPtr CreateMasterList() {
    masterListPtr masterList=(masterListPtr)malloc(sizeof(MasterList));
    if (masterList==NULL) {
        printf("Memory Allocation Failed");
        exit(-1);
    }
    masterList->next=NULL;
    masterList->previous=NULL;
    masterList->List=NULL;
    masterList->howManyList=0;
    return masterList;
}//MasterList oluşturan fonksiyon.Her runtime başlangıcında çağrılırsa kaydedılecek olan lıstelerın hesabını tutmak kolaylasır.

listPtr CreateList() {
    listPtr taskList=(listPtr)malloc(sizeof(List));
    if (taskList==NULL) {// Allocation kontrolü
      printf("Memory Allocation Failed");
        return NULL ;
    }
    int counter=0;
    FILE *listCounter=fopen("listcounter.txt","r");
    if (listCounter) {
        fscanf(listCounter,"%d",&counter);
        fclose(listCounter);
    }
    taskList->head=NULL;
    taskList->tail=NULL;
    taskList->listSize=0;
    taskList->iD=counter;
    listCounter=fopen("listcounter.txt","w");
    if (listCounter) {
        fprintf(listCounter,"%d",counter+1);
        fclose(listCounter);
    }

    return taskList;
}//Liste oluşturup dönen fonksiyon.

void DisplayList(listPtr list) {
    if (list->listSize==0) {
        printf("Your list is empty");
        return;
    }
    if (list->tail->next!=NULL) {
        printf("Can not access your list is deleted.");
        return;
    }

    taskPtr temp=list->head;
    while (temp!=NULL) {
        printf(temp->task);
        printf("\n");
        temp=temp->next;
    }
}//Listedeki görevleri gösteren fonksiyon

taskPtr FindTask(char task[],listPtr list) {
    if (list->listSize==0) {
        printf("Your list is empty.");
        return NULL;
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
        printf("Could not find the task you are looking for.");
        return 0;
    }

}// Listeden istenen görevı arayan fonksiyon

void DeleteTask(taskPtr node,listPtr list) {
    if (!FindTask(node->task,list)) {
        printf("Could not find the task.");
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
        free(node->task);
        free(node);
        list->listSize--;
        return;
    }
    if (list->listSize>1&&node==list->tail) {
        list->tail=node->previous;
        node->previous->next=NULL;
        free(node->task);
        free(node);
        list->listSize--;
        return;
    }
    else {
        node->previous->next=node->next;
        node->next->previous=node->previous;
        free(node->task);
        free(node);
        list->listSize--;
    }
}// Verilen listeden taski silen fonksiyon

void ClearList(listPtr list) {
    taskPtr temp=list->head;
    while (list->head!=NULL) {
        list->head=list->head->next;
        free(temp->task);
        free(temp);
        temp=list->head;
    }
    list->tail=NULL;
    list->listSize=0;
}//Verilen listedeki tüm verileri silip freeler

void DeleteList(listPtr list) {
        int x= list->iD;
        char fullPath[100];
        snprintf(fullPath,sizeof(fullPath),"savedlists/tasks_%d.txt",x);
        if (remove(fullPath)==0) {
            printf("%s deleted successfully.",fullPath);
        }
        else {
            perror("Error while deleting the file.");
        }
        ClearList(list);
        free(list);
}// Listenin dosyasını, bilgilerini siler ve freeler.

void DeleteFile(int listnumber) {
    char fullPath[100];
    snprintf(fullPath,sizeof(fullPath),"savedlists/tasks_%d.txt",listnumber);
    if (remove(fullPath)==0) {
        printf("%s deleted successfully.",fullPath);
    }
    else {
        perror("Error while deleting the file.");
    }
}// Liste numarası alarak listenın kayıt dosyasını siler.

void ChangeTaskPriority(taskPtr taskToMove,listPtr listTheTaskIsFrom,taskPtr newNeighbouringTask,listPtr DestinationList,int beforeOrAfter) {
    if (taskToMove==newNeighbouringTask) {
        printf("Invalid Action");
        return;
    }
    char* temp=strdup(taskToMove->task);
    DeleteTask(taskToMove,listTheTaskIsFrom);
    if (newNeighbouringTask==NULL) {
        printf("Invalid Action");
        return;
    }
    AddBeforeAfterTask(temp,DestinationList,newNeighbouringTask,beforeOrAfter);
    free(temp);
}//Tercihe göre bir görevi istenen herhangi bir görevden sonraya veya önceye taşır.

void SaveListToFile(listPtr list) {
    char fullPath[100];
    snprintf(fullPath,sizeof(fullPath),"savedlists/tasks_%d.txt",list->iD);
    FILE *file=fopen(fullPath,"w");
    if (file==NULL) {
        perror("Error while opening the file.");
        return;
    }
    taskPtr temp=list->head;

    while (temp!=NULL) {
        fprintf(file,"%s\n",temp->task);
        temp=temp->next;
    }
    fclose(file);
    printf("List is saved in %s file.\n",fullPath);
}//Listeyi dosyaya kaydeden fonksiyon

listPtr ReadFromFileAndCreateList(int fileId) {
    listPtr List=CreateList();
    List->iD=fileId;
    int counter=0;
    FILE *listCounter=fopen("listcounter.txt","r");
    if (listCounter) {
        fscanf(listCounter,"%d",&counter);
        fclose(listCounter);
    }
    listCounter=fopen("listcounter.txt","w");
    if (listCounter) {
        fprintf(listCounter,"%d",counter-1);
        fclose(listCounter);
    }
    char fullPath[100];
    char line[256];
    snprintf(fullPath,sizeof(fullPath),"savedlists/tasks_%d.txt",fileId);
    FILE *file=fopen(fullPath,"r");
    if (file==NULL) {
        perror("Error while opening the file.");
        return NULL;
    }
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        AddTask(line,List);
    }

    fclose(file);
    printf("List is successfully loaded from %d .\n", fileId);
    return List;

}//Dosyadan okuyup liste döner.









