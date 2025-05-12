#include <stdio.h>
#include "functions.h"
#include "menu.h"



int main(void) {

    listPtr Listem = CreateList();
    listPtr Listem2 = CreateList();


    AddTask("1",Listem);
    AddTask("2",Listem);
    AddTask("3",Listem);
    DisplayList(Listem);
    AddTask("4",Listem2);
    AddTask("5",Listem2);
    AddTask("6",Listem2);
    DisplayList(Listem2);
    Listem=MergeLists(Listem,Listem2);
    printf("After Merging\n");
    DisplayList(Listem);










    
}
