#pragma once

#include <progbase/collections/pblist.h>
#include <student.h>

typedef struct Storage Storage;

Storage * Storage_new();
void Storage_free(Storage * self);

PbList * Storage_getAllFilesNew(Storage * self);
void Storage_clearList(Storage * self);
int Storage_loadListFromFile(Storage * self, const char * fileName);
int Storage_saveListToFile(Storage * self, const char * fileName);

// CRUD operations

PbList * Storage_getAllStudentsNew(Storage * self);
int Storage_insertStudent(Storage * self, Student * student);
int Storage_updateStudent(Storage * self, Student * student);
int Storage_deleteStudent(Storage * self, int id);
