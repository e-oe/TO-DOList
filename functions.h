

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
    int iD;
}List;
typedef List* listPtr;

//fonksiyon bildirimleri

void AddTask(char task[],listPtr list);//Görev düğümümünü oluşturup listenin sonuna ekler

void AddBeforeAfterTask(char task[],listPtr list,taskPtr neighbouringTask,int beforeOrAfter);//Tercihe göre bir görevi istenen herhangi bir görevden önce veya sonra oluşturur. Int olarak 1 gönderirse komşu taskın önüne 0 gönderilirse arakasına yerleşir.

listPtr CreateList();//Görev listesi oluşturur

void DisplayList(listPtr list);//Listedeki görevleri gösteren fonksiyon

taskPtr FindTask(char task[],listPtr list);//Listede görev arayıp bulunan nodu dönen fonksiyon

void DeleteTask(taskPtr node,listPtr list);// Verilen listeden verilen taski silen fonksiyon

void ClearList(listPtr list);//Verilen listedeki tüm verileri silip freeler

void DeleteList(listPtr list);// Listeyi önce silip ardından listeyi freeler

void DeleteFile(int listnumber);// Liste numarası alarak listenın kayıt dosyasını siler.

void ChangeTaskPriority(taskPtr taskToMove,listPtr listTheTaskIsFrom,taskPtr newNeighbouringTask,listPtr DestinationList,int beforeOrAfter);//Tercihe göre bir görevi istenen herhangi bir görevden sonraya veya önceye taşır.

void SaveListToFile(listPtr list);//Listeyi dosyaya kaydeden fonksiyon

listPtr ReadFromFileAndCreateList(int fileId);//Dosyadaki verıler ile bir liste olultrup döner.



#endif //FUNCTIONS_H
