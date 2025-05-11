#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#define HASH_TABLE_SIZE 101

static taskPtr taskHashTable[HASH_TABLE_SIZE] = {NULL};

unsigned int HashFunction(int id) {
    return id % HASH_TABLE_SIZE;
}

void AddTaskToHashTable(taskPtr taskNode, int id) {
    unsigned int index = HashFunction(id);
    taskNode->nextHash = taskHashTable[index];
    taskHashTable[index] = taskNode;
    taskNode->id = id;
}

taskPtr FindTaskByID(int id) { 
    unsigned int index = HashFunction(id);
    taskPtr current = taskHashTable[index];

    while (current != NULL) {
        if (current->id == id) {
            printf("ID: %d olan gorev bulundu: %s\n", id, current->task);
            return current;
        }
        current = current->nextHash;
    }

    printf("ID: %d olan gorev bulunamadı.\n", id);
    return NULL;
}

void DeleteTaskByID(int id, listPtr list) { 
    unsigned int index = HashFunction(id);
    taskPtr current = taskHashTable[index];
    taskPtr previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->nextHash;
    }

    if (current == NULL) {
        printf("ID %d olan gorev bulunamadı.\n", id);
        return;
    }

    if (previous == NULL) {
        taskHashTable[index] = current->nextHash;
    } else {
        previous->nextHash = current->nextHash;
    }

    DeleteTask(current, list);
    printf("ID %d olan gorev silindi.\n", id);
}




/* MainList çalışma mantığı: Açılan bir sessionda üzerinde değişiklik yapılan ve yeni oluşturulan listelerin adreslerini yerel bir dosyaya kaydeder.
 Gerekli fonksiyonlarla , yapılan değişiklikler yerel dosyalara kaydedilebilir veya son sessionda yapılmış ve kaydeilmemiş değişiklikler geri çevrilebilir.*/

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
    AddTaskToHashTable(node, list->listSize);
    SaveListToMainList(list);
}// Görev düğümünü listenin sonuna ekleyen fonksiyon*

void AddTaskWithoutMainList(char task[],listPtr list) {
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
}// Görev düğümünü listenin sonuna ekler ancak liste bilgilerini masterlist dosyasina işlemez.Bu durum fonksiyonun bir döngü icerisinde cagirilmasi durumunda gereksiz yere mainlistte log acmasini engeller.

void AddBeforeAfterTask(char task[],listPtr list,taskPtr neighbouringTask,int beforeOrAfter) {
    if (neighbouringTask==NULL) {
        printf("Trying to access deleted data");
        exit(-1);
    }
    SaveListToMainList(list);
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

listPtr CreateList() {
    listPtr taskList=(listPtr)malloc(sizeof(List));
    if (taskList==NULL) {// Allocation kontrolü
      printf("Memory Allocation Failed");
        return NULL ;
    }
    int counter=0;
    FILE *listCounter=fopen("listcounter/listcounter.txt","r");
    if (listCounter) {
        fscanf(listCounter,"%d",&counter);
        fclose(listCounter);
    }
    taskList->head=NULL;
    taskList->tail=NULL;
    taskList->listSize=0;
    taskList->iD=counter;
    listCounter=fopen("listcounter/listcounter.txt","w");
    if (listCounter) {
        fprintf(listCounter,"%d",counter+1);
        fclose(listCounter);
    }
    SaveListToMainList(taskList);

    return taskList;
}//Liste oluşturup dönen fonksiyon.*

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
        printf("Could not find the task you are looking for.\n");
        return 0;
    }

}// Listeden istenen görevı arayan fonksiyon

void DeleteTask(taskPtr node,listPtr list) {
    if (!FindTask(node->task,list)) {
        printf("Could not find the task.\n");
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
    SaveListToMainList(list);
}// Verilen listeden taski silen fonksiyon*

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
    SaveListToMainList(list);
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
}// Listenin dosyasını, bilgilerini siler ve freeler.*

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
    SaveListToMainList(listTheTaskIsFrom);
    SaveListToMainList(DestinationList);
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

void SaveListToMainList(listPtr list) {
    char fullPath[100];
    char line[256];
    snprintf(fullPath,sizeof(fullPath),"mainlist/mainlist.txt");
    FILE *file=fopen(fullPath,"r");
    while (fgets(line, sizeof(line), file)) {
        char lineTemp[256];
        strcpy(lineTemp,line);
        size_t len=strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        unsigned long long ulladres = strtoull(line, NULL, 16);

        if (list == (listPtr)ulladres) {
            return;
        }
    }
    fclose(file);
    file=fopen(fullPath,"a");
    if (file==NULL) {
        perror("Error while opening the file.");
        return;
    }
    fprintf(file,"%p\n",list);
    fclose(file);
}//Listeyi mainliste kaydeden fonksiyon

void SaveTheChangesInMainList() {
    char line[256];
    char fullPath[100];
    snprintf(fullPath,sizeof(fullPath),"mainlist/mainlist.txt");
    FILE *file=fopen(fullPath,"r");
    if (file==NULL) {
        perror("Error while opening the file.");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        size_t len=strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        unsigned long long ulladres = strtoull(line, NULL, 16);
        listPtr list = (listPtr)ulladres;
        SaveListToFile(list);
    }
    fclose(file);
    FlushMainList();

}//Mainliste kaydedilmis(yani uzerinde değişiklik yapilmis) listeleri dosyaya kaydeder.

void FlushMainList() {
    char fullPath[100];
    snprintf(fullPath,sizeof(fullPath),"mainlist/mainlist.txt");
    FILE *file=fopen(fullPath,"w");
    fclose(file);
}//Sessiondaki kaydedilmemiş tüm değişiklikleri geri alır.

void ClearAllLogs() {
    char fullPath[100];
    snprintf(fullPath,sizeof(fullPath),"mainlist/mainlist.txt");
    FILE *file=fopen(fullPath,"w");
    fclose(file);
    FILE *listCounter=fopen("listcounter/listcounter.txt","w");
    fclose(listCounter);

}//Programin tuttugu tum  loglarını temizler (listcounter ve mainlist).

listPtr ReadFromFileAndCreateList(int fileId) {
    listPtr List=CreateList();
    List->iD=fileId;
    int counter=0;
    FILE *listCounter=fopen("listcounter/listcounter.txt","r");
    if (listCounter) {
        fscanf(listCounter,"%d",&counter);
        fclose(listCounter);
    }
    listCounter=fopen("listcounter/listcounter.txt","w");
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
        AddTaskWithoutMainList(line,List);
    }

    fclose(file);
    printf("List is successfully loaded from log %d.\n", fileId);

    return List;

}//Dosyadan veri okuyup liste döner.

listPtr MergeLists(listPtr mergedList,listPtr listToMerge) {
    mergedList->tail->next=listToMerge->head;
    listToMerge->head->previous=mergedList->tail;
    mergedList->tail=listToMerge->tail;
    DeleteList(listToMerge);
    return mergedList;
}//İki liste alarak ikinciyi birincinin arkasına ekler. İkincinin dosyasını siler ve freeler.

typedef struct stackNode {
    char *task;
    struct stackNode *next;
} StackNode;

typedef struct stack {
    StackNode *top;
} TaskStack;

TaskStack undoStack = {NULL}; 

void AddDeletedTaskToStack(const char* task) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Memory Allocation Failed\n");
        exit(-1);
    }
    newNode->task = strdup(task);
    newNode->next = undoStack.top;
    undoStack.top = newNode;
}

char* PopDeletedTaskFromStack() {
    if (undoStack.top == NULL) {
        return NULL;
    }
    StackNode* temp = undoStack.top;
    char* task = temp->task;

    undoStack.top = undoStack.top->next;
    free(temp);

    return task;
}

void UndoLastDeleted(listPtr list) {
    char* lastDeletedTask = PopDeletedTaskFromStack();
    if (lastDeletedTask == NULL) {
        printf("Geri alinacak görev yok!\n");
        return;
    }

    AddTask(lastDeletedTask, list);
    printf("'%s' gorevi basariyla geri alindi!\n", lastDeletedTask);
    free(lastDeletedTask);
}

void SmartDeleteTask(const char* taskName, listPtr list) {
    taskPtr gorev = FindTask((char*)taskName, list);
    if (gorev != NULL) {
        AddDeletedTaskToStack(gorev->task);
        DeleteTask(gorev, list);
        printf("'%s' gorevi basariyla silindi ve stack'e eklendi!\n", taskName);
    } else {
        printf("'%s' gorevi bulunamadi!\n", taskName);
    }
}

typedef struct queueNode {
    char *task;
    struct queueNode *next;
} QueueNode;

typedef struct queue {
    QueueNode *front;
    QueueNode *rear;
} TaskQueue;

TaskQueue taskQueue = {NULL, NULL};

void EnqueueTask(const char* task) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->task = strdup(task);
    newNode->next = NULL;

    if (taskQueue.rear == NULL) {
        taskQueue.front = taskQueue.rear = newNode;
    } else {
        taskQueue.rear->next = newNode;
        taskQueue.rear = newNode;
    }
}

void ProcessNextTask(listPtr list) {
    if (taskQueue.front == NULL) {
        printf("Islenecek gorev yok.\n");
        return;
    }

    char* taskToProcess = taskQueue.front->task;
    printf("Siradaki görev: %s\n", taskToProcess);

    taskPtr gorev = FindTask(taskToProcess, list);
    if (gorev != NULL) {
        DeleteTask(gorev, list);
        SaveListToFile(list);
    }

    QueueNode* temp = taskQueue.front;
    taskQueue.front = taskQueue.front->next;
    if (taskQueue.front == NULL) taskQueue.rear = NULL;
    free(temp->task);
    free(temp);
}

void AutoQueueList(listPtr list) {
    taskPtr temp = list->head;
    while (temp != NULL) {
        EnqueueTask(temp->task);
        temp = temp->next;
    }
    printf("Tum gorevler kuyruga alindi.\n");
}

// AVL 
typedef struct AVLNode {
    char* task;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

int Max(int a, int b) {
    return (a > b) ? a : b;
}

int Height(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

AVLNode* CreateAVLNode(const char* task) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->task = strdup(task);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* RightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = Max(Height(y->left), Height(y->right)) + 1;
    x->height = Max(Height(x->left), Height(x->right)) + 1;

    return x;
}

AVLNode* LeftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = Max(Height(x->left), Height(x->right)) + 1;
    y->height = Max(Height(y->left), Height(y->right)) + 1;

    return y;
}

int GetBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return Height(node->left) - Height(node->right);
}

AVLNode* InsertAVLNode(AVLNode* node, const char* task) {
    if (node == NULL)
        return CreateAVLNode(task);

    if (strcmp(task, node->task) < 0)
        node->left = InsertAVLNode(node->left, task);
    else if (strcmp(task, node->task) > 0)
        node->right = InsertAVLNode(node->right, task);
    else
        return node;

    node->height = 1 + Max(Height(node->left), Height(node->right));

    int balance = GetBalance(node);

    if (balance > 1 && strcmp(task, node->left->task) < 0)
        return RightRotate(node);

    if (balance < -1 && strcmp(task, node->right->task) > 0)
        return LeftRotate(node);

    if (balance > 1 && strcmp(task, node->left->task) > 0) {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    if (balance < -1 && strcmp(task, node->right->task) < 0) {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}

void AutoInsertToAVL(listPtr list, AVLNode** root) {
    taskPtr current = list->head;
    while (current != NULL) {
        *root = InsertAVLNode(*root, current->task);
        current = current->next;
    }
}

void InOrderTraversal(AVLNode* root) {
    if (root != NULL) {
        InOrderTraversal(root->left);
        printf("%s\n", root->task);
        InOrderTraversal(root->right);
    }
}

void FreeAVLTree(AVLNode* root) {
    if (root != NULL) {
        FreeAVLTree(root->left);
        FreeAVLTree(root->right);
        free(root->task);
        free(root);
    }
}

void DisplayAVLInOrder(listPtr list) {
    AVLNode* root = NULL;
    AutoInsertToAVL(list, &root);
    printf("\n--- Gorevler Alfabetik Sirada ---\n");
    InOrderTraversal(root);
    FreeAVLTree(root);
}




/*The functions that i could add in feature
void FindAndRevertChanges(listPtr list) {
char address[100]=list;
}//Verilen listenin mainlistteki logunu silerek son sessionda yapilmis degisikliklerin kaydedilmemesini saglar.
*/









