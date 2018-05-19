#pragma once

#include "student.h"
#include <progbase/collections/pblist.h>

typedef enum {
    FN_NONE,
    FN_GET_FILES,
    FN_NEW_LIST,
    FN_LOAD_LIST,
    FN_SAVE_LIST,
    FN_GET_STUDENTS,
    FN_INSERT_STUDENT,
    FN_UPDATE_STUDENT,
    FN_DELETE_STUDENT
} FunctionName;

char * FunctionName_toString(FunctionName fn);

typedef struct {
    FunctionName functionName;
    int id;
    Student student;
    char fileName[100];
} Request;

void Request_clear(Request * req);

typedef struct {
    int status;
    int id;
    PbList * files;
    PbList * students;
} Response;

void Response_clear(Response * res);