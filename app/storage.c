#include <storage.h>
#include <assert.h>
#include <fs.h>
#include <stdio.h>

struct Storage {
    PbList * students;
};

Storage * Storage_new() {
    Storage * self = malloc(sizeof(Storage));
    self->students = PbList_new();
    return self;
}
void Storage_free(Storage * self) {
    PbList_free(self->students);
    free(self);
}

enum { PATH_MAX = 256 };

static char * getDataFilePath(const char * fileName) {
    static char path[PATH_MAX] = "";
    path[0] = '\0';
    Fs_pathJoin(path, Fs_getExecPath());
    Fs_pathJoin(path, "data");
    Fs_pathJoin(path, fileName);
    return path;
}

PbList * Storage_getAllFilesNew(Storage * self) {
    char * fullPath = getDataFilePath("");
    printf("> All files in dir: %s\n", fullPath);
    return Fs_getDirFiles(fullPath);
}
void Storage_clearList(Storage * self) {
    assert(0 && "Not impl");
}
int Storage_loadListFromFile(Storage * self, const char * fileName) {
    assert(0 && "Not impl");
    return 0;
}
int Storage_saveListToFile(Storage * self, const char * fileName) {
    assert(0 && "Not impl");
    return 0;
}

// CRUD operations
PbList * Storage_getAllStudentsNew(Storage * self) {
    assert(0 && "Not impl");
    return NULL;
}
int Storage_insertStudent(Storage * self, Student * student) {
    assert(0 && "Not impl");
    return -1;
}
int Storage_updateStudent(Storage * self, Student * student) {
    assert(0 && "Not impl");
    return 0;
}
int Storage_deleteStudent(Storage * self, int id) {
    assert(0 && "Not impl");
    return 0;
}
