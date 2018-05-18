#include <storage.h>
#include <assert.h>
#include <fs.h>
#include <stdio.h>
#include <serialization.h>
#include <string.h>

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
    printf("[Storage]> All files in dir: %s\n", fullPath);
    return Fs_getDirFiles(fullPath);
}

static void clearStudents(Storage * self) {
    for (int i = 0; i < PbList_count(self->students); i++) {
        Student * s = PbList_at(self->students, i);
        Student_free(s);
    }
    PbList_clear(self->students);
}
void Storage_clearList(Storage * self) {
    clearStudents(self);
    printf("[Storage]> List cleared\n");
}
int Storage_loadListFromFile(Storage * self, const char * fileName) {
    const char * path = getDataFilePath(fileName);
    if (!Fs_fileExists(path)) { return 1; }
    int len = Fs_getFileSize(path);
    char * text = malloc(sizeof(char) * len);
    if (0 == Fs_readAllText(path, text, len)) {
        free(text);
        return 1;
    }
    PbList * students = Serialization_deserializeStudentsNew(text);
    free(text);
    clearStudents(self);
    PbList_free(self->students);
    self->students = students;
    printf("[Storage]> Students loaded from %s\n", path);
    return 0;
}
int Storage_saveListToFile(Storage * self, const char * fileName) {
    const char * path = getDataFilePath(fileName);
    char * text = Serialization_serializeStudentsNew(self->students);
    if (text == NULL) { return 1; }
    if (0 == Fs_writeAllText(path, text, strlen(text))) {
        free(text);
        return 1;
    }
    printf("[Storage]> Students saved to %s\n", path);
    return 0;
}

// CRUD operations
PbList * Storage_getAllStudentsNew(Storage * self) {
    PbList * l = PbList_new();
    for (int i = 0; i < PbList_count(self->students); i++) {
        PbList_add(l, Student_newCopy(PbList_at(self->students, i)));
    }
    return l;
}

static Student * getStudentById(PbList * list, int id) {
    for (int i = 0; i < PbList_count(list); i++) {
        Student * s = PbList_at(list, i);
        if (s->id == id) { return s; }
    }
    return NULL;
}

static int getNewId(Storage * self) {
    int id = 0;
    bool isOk = false;
    while (!isOk) {
        id++;
        if (NULL == getStudentById(self->students, id)) {
            isOk = true;
        }
    }
    return id;
}

int Storage_insertStudent(Storage * self, Student * student) {
    student->id = getNewId(self);
    PbList_add(self->students, Student_newCopy(student));
    return student->id;
}
int Storage_updateStudent(Storage * self, Student * student) {
    Student * s = getStudentById(self->students, student->id);
    if (s != NULL) {
        *s = *student;
        return 0;
    }
    return 1;
}
int Storage_deleteStudent(Storage * self, int id) {
    Student * s = getStudentById(self->students, id);
    if (s != NULL) {
        Student_free(s);
        PbList_remove(self->students, s);
        return 0;
    }
    return 1;
}
