#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void ShowMainMenu(listPtr* list) {
    system("cls || clear");

    printf("===== TO-DO LIST UYGULAMASI =====\n");
    printf("1.  Gorev Ekle\n");
    printf("2.  Gorevleri Listele\n");
    printf("3.  Gorev Sil (Task Name Girerek)\n");
    printf("4.  Geri Al (Undo)\n");
    printf("5.  Listeyi Temizle\n");
    printf("6.  Siradaki Gorevi Isle (Process Next Task)\n");
    printf("7.  Gorevleri Alfabetik Listele\n");
    printf("8.  Gorev Onceligini Degistir (Ayni Liste icinde)\n");
    printf("9.  Gorevi baska listeye tasi\n");
    printf("10. iki Listeyi Birlestir (Merge)\n");
    printf("11. ID ile Gorev Bul\n");
    printf("12. Listeyi Kaydet\n");
    printf("13. Kaydedilen listeyi Sil\n");
    printf("14. Var Olan Listeyi Yukle (Numara ile)\n");
    printf("15. Var Olan Listeyi Sil (savedlists)\n");
    printf("16. Cikis\n");
    printf("Seciminizi girin: ");

    int secim;
    char buffer[100];
    scanf("%d", &secim);
    getchar();

    if (secim == 1) {
        printf("Yeni gorev: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        AddTask(buffer, *list);
    }

    else if (secim == 2) {
        system("cls || clear");
        printf("================================================\n");
        printf("|  ID/Tasks                        Address       \n");
        printf("================================================\n");

        taskPtr current = (*list)->head;
        int index = 1;
        while (current != NULL) {
            printf("| %2d) %-20s | %p |\n", index, current->task, (void*)current);
            current = current->next;
            index++;
        }

        printf("================================================\n");
        printf("Pointer of List (head): %p\n", (void*)*list);
        printf("Total Task Count: %d\n", (*list)->listSize);
        printf("================================================\n");
    }

    else if (secim == 3) {
        printf("Silinecek gorevin adini girin: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        SmartDeleteTask(buffer, *list);
    }

    else if (secim == 4) {
        UndoLastDeleted(*list);
    }

    else if (secim == 5) {
        ClearList(*list);
    }

    else if (secim == 6) {
        AutoQueueList(*list);
        ProcessNextTask(*list);
    }

    else if (secim == 7) {
        system("cls || clear");
        DisplayAVLInOrder(*list);
    }

    else if (secim == 8) { 
    printf("Tasinacak gorevin adini girin: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    taskPtr gorev = FindTask(buffer, *list);   
    if (!gorev) return;

    printf("Referans gorevin adini girin (onune/arkasina yerlestirilecek): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    taskPtr komsu = FindTask(buffer, *list);   
    if (!komsu) return;

    int secim;
    printf("1 - Once, 0 - Sonra eklensin: ");
    scanf("%d", &secim);
    getchar();  

    ChangeTaskPriority(gorev, *list, komsu, *list, secim);  
    }
    

    else if (secim == 9) {  // Görevi başka listeye taşı
    int hedefID;
    printf("Hedef liste numarasi: ");
    scanf("%d", &hedefID);
    getchar();

    listPtr hedefListe = ReadFromFileAndCreateList(hedefID);
    if (!hedefListe) {
        printf("Liste yuklenemedi.\n");
        return;
    }

    printf("Tasinacak gorevin adini girin: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    taskPtr gorev = FindTask(buffer, *list);
    if (!gorev) {
        printf("Gorev bulunamadi.\n");
        return;
    }

    char* kopya = strdup(gorev->task);  // Görev ismini kopyala
    DeleteTask(gorev, *list);           // Eski listeden sil

    printf("Hedef listedeki referans gorevin adini girin (yoksa ENTER): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    taskPtr komsu = NULL;
    if (strlen(buffer) > 0) {
        komsu = FindTask(buffer, hedefListe);
    }

    int konum = 0;
    if (komsu) {
        printf("1 - Once, 0 - Sonra eklensin: ");
        scanf("%d", &konum);
        getchar();
        AddBeforeAfterTask(kopya, hedefListe, komsu, konum);
    } else {
        printf("Referans gorev bulunamadi veya belirtilmedi. Liste sonuna eklenecek.\n");
        AddTask(kopya, hedefListe); 
    }

    free(kopya);
    SaveListToFile(hedefListe);
    printf("Gorev tasindi!\n");
    }
    
    else if (secim == 10) {  // İki listeyi birleştir (Merge)
    printf("Hedef (ana) liste numarasini girin: ");
    int hedefID;
    scanf("%d", &hedefID);
    getchar();

    printf("Birlesecek (kaynak) liste numarasini girin: ");
    int kaynakID;
    scanf("%d", &kaynakID);
    getchar();

    listPtr hedef = ReadFromFileAndCreateList(hedefID);
    listPtr kaynak = ReadFromFileAndCreateList(kaynakID);

    if (!hedef || !kaynak) {
        printf("Listeler yuklenemedi. ID'leri kontrol edin.\n");
        return;
    }

    hedef = MergeLists(hedef, kaynak);
    SaveListToFile(hedef);  // Hedef listeyi tekrar kaydediyoruz
    printf("Listeler basariyla birlestirildi!\n");
    }




    else if (secim == 11) {
        printf("ID girin: ");
        int IdNo;
        scanf("%d", &IdNo);
        getchar();
        FindTaskByID(IdNo);
    }

    else if (secim == 12) {
        SaveListToFile(*list);
    }

    else if (secim == 13) {
        DeleteList(*list);
        *list = NULL;
    }

    else if (secim == 14) {
        printf("Yuklenecek listenin numarasini girin: ");
        int id;
        scanf("%d", &id);
        getchar();

        listPtr loaded = ReadFromFileAndCreateList(id);
        if (loaded != NULL) {
            *list = loaded;
            printf("✔ Liste %d yuklendi!\n", id);
        } else {
            printf("❌ Liste yuklenemedi.\n");
        }
    }

    else if (secim == 15) {
        printf("Silinecek listenin numarasini girin: ");
        int listNo;
        scanf("%d", &listNo);
        getchar();
        DeleteFile(listNo);
    }

    else if (secim == 16) {
        printf("Cikis yapiliyor...\n");
        exit(0);
    }

    else {
        printf("Gecersiz secim!\n");
    }

    printf("\nDevam etmek icin ENTER'a basin...");
    getchar();
}
