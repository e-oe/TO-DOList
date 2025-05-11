#include <stdio.h>
#include "functions.h"
#include "menu.h"



int main(void) {
    /*printf("write a task to add the list\n");
    char task1[]="tak1";
    char task2[]="tak2";
    char task3[]="tak3";
    char task4[]="tak4";
    */

    listPtr Listem = CreateList();

       while (1) {
        ShowMainMenu(Listem);
    }

    return 0;

    /*
    listPtr Listem=CreateList();
    listPtr list=CreateList();
    ReadFromFileAndCreateList(50);
    AddTask(task1,Listem);
    AddTask(task2,Listem);
    AddTask(task1,list);
    AddTask(task3,Listem);
    AddTask(task2,list);
    AddTask(task4,Listem);
    AddTask(task3,Listem);
    AddTask(task3,Listem);
    DisplayList(Listem);
    DeleteTask(FindTask(task4,Listem),Listem);
    printf("after======\n");
    DisplayList(Listem);
    SaveTheChangesInMainList();
    FlushMainList();
    */


    
    // listPtr Liste=ReadFromFileAndCreateList(50);
    // DisplayList(Liste);
    // DeleteTask(task1,Liste);
    // DisplayList(Liste);
    // SaveListToFile(Liste);





    
}
