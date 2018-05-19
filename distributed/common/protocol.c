#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>

char * FunctionName_toString(FunctionName fn) {
    switch (fn) {
        case FN_GET_FILES: return "GetFiles";
        case FN_NEW_LIST: return "NewList";
        case FN_LOAD_LIST: return "LoadList";
        case FN_SAVE_LIST: return "SaveList";
        case FN_GET_STUDENTS: return "GetStudents";
        case FN_INSERT_STUDENT: return "InsertStudent";
        case FN_UPDATE_STUDENT: return "UpdateStudent";
        case FN_DELETE_STUDENT: return "DeleteStudent";
        default: return "<error>";
    }
    return "";
}

void Request_clear(Request * req) {
    *req = (Request){0};
}

void Response_clear(Response * res) {
    if (res->files != NULL) {
        // @todo free strings
        PbList_free(res->files);
    }
    if (res->students != NULL) {
        // @todo free students
        PbList_free(res->students);
    }
    *res = (Response){0};
}