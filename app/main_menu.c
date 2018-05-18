#include <main_menu.h>
#include <stdio.h>
#include <storage.h>

void listFiles(Storage * storage) {
    PbList * files = Storage_getAllFilesNew(storage);
    int count = PbList_count(files);
    printf("\nFiles (%i):\n-----------------------------\n", count);
    for (int i = 0; i < count; i++) {
        char * file = PbList_at(files, i);
        printf("> %s\n", file);
        free(file);
    }
    puts("-----------------------------");
    PbList_free(files);
}

void newList(Storage * storage) {

}

void load(Storage * storage) {

}

void save(Storage * storage) {

}

void getAll(Storage * storage) {

}

void insert(Storage * storage) {

}

void update(Storage * storage) {

}

void delete(Storage * storage) {

}

Menu * MainMenu_new() {
    return Menu_new((MenuItem[]){
        {'1', "Show files", (MenuItemHandler)listFiles},
        {'2', "Clear list", (MenuItemHandler)newList},
        {'3', "Load list from file ...", (MenuItemHandler)load},
        {'4', "Save list to file ...", (MenuItemHandler)save},
        {'5', "Show all students", (MenuItemHandler)getAll},
        {'6', "Insert new student ...", (MenuItemHandler)insert},
        {'7', "Update student ...", (MenuItemHandler)update},
        {'8', "Delete student ...", (MenuItemHandler)delete},
        {'0', "exit", NULL}
    }, 9);
}