#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void ShowMainMenu(listPtr list) {
    system("cls || clear");  // Ekranı temizler

    printf("===== TO-DO LIST UYGULAMASI =====\n");
    printf("1.  Gorev Ekle\n");
    printf("2.  Gorevleri Listele\n");
    printf("3.  Gorev Sil (Task Name Girerek)\n");
    printf("4.  Geri Al (Undo)\n");
    printf("5.  listeyi temizle\n");
    printf("6.  Siradaki Gorevi Isle (Process Next Task)\n");
    printf("7.  Gorevleri Alfabetik Listele\n");
    printf("8.  ID ile gorev bul\n");
    printf("9.  Listeyi Kaydet\n");
    printf("10. Kaydedilen listeyi sil\n");
    printf("11. Kayitli Liste Dosyasi Sil (savedlists)\n");
    printf("12. Cikis\n");
    printf("Seciminizi girin: ");

    int secim;
    char buffer[100];
    scanf("%d", &secim);
    getchar(); // \n temizliği

    if (secim == 1) {
        printf("Yeni gorev: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        AddTask(buffer, list);
    }

    else if (secim == 2) {
        system("cls || clear");
        printf("================================================\n");
        printf("|  ID/Tasks                        Address       \n");
        printf("================================================\n");

        taskPtr current = list->head;
        int index = 1;
        while (current != NULL) {
            printf("| %2d) %-20s | %p |\n", index, current->task, (void*)current);
            current = current->next;
            index++;
        }

        printf("================================================\n");
        printf("Pointer of List (head): %p\n", (void*)list);
        printf("Total Task Count: %d\n", list->listSize);
        printf("================================================\n");
    }

    else if (secim == 3) {
        printf("Silinecek gorevin adini girin: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        SmartDeleteTask(buffer, list);
    }

    else if (secim == 4) {
        UndoLastDeleted(list);
    }
    
    else if (secim == 5) {
       ClearList(list);
    }

    else if (secim == 6) {
        AutoQueueList(list);
        ProcessNextTask(list);
    }

    else if (secim == 7) {
    system("cls || clear");
    DisplayAVLInOrder(list);
    }
    
    else if (secim == 8) {
    printf("ID girin: ");
    int IdNo;
    scanf("%d", &IdNo);
    getchar();  // \n temizliği

    FindTaskByID(IdNo);
   }

    else if (secim == 9) {
        SaveListToFile(list);
    }

    else if (secim == 10) {
        DeleteList(list);
    }

    else if (secim == 11) {
    printf("Silinecek listenin nosunu girin: ");
    int listNo;
    scanf("%d", &listNo);
    getchar();  // \n temizliği

    DeleteFile(listNo);
   }
    
    else if (secim == 12) {
        printf("Cikis yapiliyor...\n");
        exit(0);
    }
    

    else {
        printf("Gecersiz secim!\n");
    }

    printf("\nDevam etmek icin ENTER'a basin...");
    getchar();
}
