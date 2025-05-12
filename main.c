#include <stdio.h>
#include "functions.h"
#include "menu.h"



int main(void) {

listPtr Listem = CreateList();

       while (1) {
        ShowMainMenu(&Listem);
    }

    return 0;

}
