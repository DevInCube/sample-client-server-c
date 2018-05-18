#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <progbase/console.h>
#include <storage.h>
#include <main_menu.h>

int main(void) {
    Menu * mainMenu = MainMenu_new();
    Storage * storage = Storage_new();
    
    bool isRunning = true;
    while (isRunning) {
        AcceptStatus status = MENU_INVALID;
        while (status == MENU_INVALID) {
            Console_clear();
            Menu_show(mainMenu);
            char input = getUserInput("Choose option");
            Console_clear();
            status = Menu_acceptInput(mainMenu, input, storage);
            if (status == MENU_INVALID) {
                puts("> invalid input, try again");
            } else if (status == MENU_RETURN) {
                isRunning = false;
                continue;
            }
            printf("> Press any key to continue ...");
            Console_getChar();
        }
    }
    puts("");
    Storage_free(storage);
    Menu_free(mainMenu);
    return 0;
}