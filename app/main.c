#include <stdlib.h>
#include <stdio.h>
#include <progbase/console.h>
#include <storage.h>
#include <main_menu.h>

int main(void) {
    Menu * mainMenu = MainMenu_new();
    Storage * storage = Storage_new();
    
    Console_clear();
    Menu_show(mainMenu);
    char input = getUserInput("Choose option");
    AcceptStatus status = Menu_acceptInput(mainMenu, input, storage);
    printf("> Press any key to continue ...");
    Console_getChar();
    
    Storage_free(storage);
    Menu_free(mainMenu);
    return 0;
}