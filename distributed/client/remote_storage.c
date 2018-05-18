#include <storage.h>

struct Storage {
    int _;
};

Storage * Storage_new() {
    Storage * self = malloc(sizeof(Storage));
    return self;
}
void Storage_free(Storage * self) {
    Storage_free(self);
}

PbList * Storage_getAllFilesNew(Storage * self) {
    return NULL;
}
void Storage_clearList(Storage * self) {

}
int Storage_loadListFromFile(Storage * self, const char * fileName) {
    return 1;
}
int Storage_saveListToFile(Storage * self, const char * fileName) {
    return 1;
}

// CRUD operations
PbList * Storage_getAllStudentsNew(Storage * self) {
    return NULL;
}
int Storage_insertStudent(Storage * self, Student * student) {
    return -1;
}
int Storage_updateStudent(Storage * self, Student * student) {
    return 1;
}
int Storage_deleteStudent(Storage * self, int id) {
    return 1;
}