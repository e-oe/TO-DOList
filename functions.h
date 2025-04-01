

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

taskPtr CreateTask(char task[]);//Görev oluşturur
listPtr CreateList();//Görev listesi oluşturur


#endif //FUNCTIONS_H
