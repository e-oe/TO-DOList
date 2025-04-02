

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
typedef struct task { //Görevleri, dinamik olarak hafızadan yer alacak şekilde bir char dizisine kaydedecek düğüm yapısı.
    struct task* next;
    struct task* previous;
    char* task ;
}Task;
typedef Task* taskPtr;

typedef struct list { //Oluşturulan düğümlerin başını,sonunu ve toplam düğüm sayısını tutacak liste yapısı.
    taskPtr head;
    taskPtr tail;
    int listSize;
}List;
typedef List* listPtr;

//fonksiyon bildirimleri

void AddTask(char task[],listPtr list);//Görev ddüğümümnü oluşturup listenin sonuna ekler
listPtr CreateList();//Görev listesi oluşturur
void DisplayList(listPtr List);//Listedeki görevleri gösteren fonksiyon
taskPtr FindTask(char task[],listPtr list);//Listede görev arayıp bulunan nodu dönen fonksiyon
void DeleteTask(taskPtr node,listPtr list);// Verilen listeden verilen taski silen fonksiyon



#endif //FUNCTIONS_H
