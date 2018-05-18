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
    Storage_clearList(storage);
}

void load(Storage * storage) {
    char file[100] = "";
    getUserStringInput("Enter filename", file, 100);
    int status = Storage_loadListFromFile(storage, file);
    if (status == 0) {
        puts("loaded");
    } else {
        puts("load error");
    }
}

void save(Storage * storage) {
    char file[100] = "";
    getUserStringInput("Enter filename", file, 100);
    int status = Storage_saveListToFile(storage, file);
    if (status == 0) {
        puts("saved");
    } else {
        puts("save error");
    }
}

void getAll(Storage * storage) {
    PbList * students = Storage_getAllStudentsNew(storage);
    int count = PbList_count(students);
    printf("Students (%i):\n--------------------------------------\n", count);
    for (int i = 0; i < count; i++) {
        Student * s = PbList_at(students, i);
        printf("%i. [%i] %s - %f\n", i, s->id, s->name, s->score);
        Student_free(s);
    }
    PbList_free(students);
    puts("--------------------------------------");
}

static Student * getUserNewStudentInput() {
    char name[100] = "";
    getUserStringInput("Enter student name", name, 100);
    float score = getUserFloatInput("Enter student score");
    return Student_new(0, name, score);
}

void insert(Storage * storage) {
    Student * student = getUserNewStudentInput();
    int id = Storage_insertStudent(storage, student);
    student->id = id;
}

void update(Storage * storage) {
    int id = getUserIntInput("Enter student id");
    Student * student = getUserNewStudentInput();
    student->id = id;
    int status = Storage_updateStudent(storage, student);
    if (status == 0) {
        puts("updated");
    } else {
        puts("update error");
    }
}

void delete(Storage * storage) {
    int id = getUserIntInput("Enter student id");
    int status = Storage_deleteStudent(storage, id);
    if (status == 0) {
        puts("deleted");
    } else {
        puts("delete error");
    }
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