#pragma once

#include "student.h"
#include <progbase/collections/pblist.h>

typedef enum {
    FN_GET_FILES,
    FN_NEW_LIST,
    FN_LOAD_LIST,
    FN_SAVE_LIST,
    FN_GET_STUDENTS,
    FN_INSERT_STUDENT,
    FN_UPDATE_STUDENT,
    FN_DELETE_STUDENT
} FunctionName;

typedef struct {
    FunctionName functionName;
    int id;
    Student student;
    char fileName[100];
} Request;

typedef struct {
    int status;
    int id;
    PbList * list;
} Response;