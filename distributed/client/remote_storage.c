#include <storage.h>
#include "../common/protocol.h"
#include <stdio.h>
#include <string.h>
#include "client.h"

struct Storage { int _; };

Storage * Storage_new() {
    Storage * self = malloc(sizeof(Storage));
    return self;
}

void Storage_free(Storage * self) {
    Storage_free(self);
}

PbList * Storage_getAllFilesNew(Storage * self) {
    Request req = {0};
    req.functionName = FN_GET_FILES;
    Response res = {0};
    int status = Client_sendRequest(&req, &res); // @todo where
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return NULL;
    }
    return res.files;
}

void Storage_clearList(Storage * self) {
    Request req = {0};
    req.functionName = FN_NEW_LIST;
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
    }
}

int Storage_loadListFromFile(Storage * self, const char * fileName) {
    Request req = {0};
    req.functionName = FN_LOAD_LIST;
    strcpy(req.fileName, fileName);
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return 1;
    }
    return res.status;
}

int Storage_saveListToFile(Storage * self, const char * fileName) {
    Request req = {0};
    req.functionName = FN_SAVE_LIST;
    strcpy(req.fileName, fileName);
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return 1;
    }
    Response_clear(&res);
    return res.status;
}

// CRUD operations

PbList * Storage_getAllStudentsNew(Storage * self) {
    Request req = {0};
    req.functionName = FN_GET_STUDENTS;
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return NULL;
    }
    return res.students;
}

int Storage_insertStudent(Storage * self, Student * student) {
    Request req = {0};
    req.functionName = FN_INSERT_STUDENT;
    req.student = *student;
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return -1;
    }
    return res.id;
}

int Storage_updateStudent(Storage * self, Student * student) {
    Request req = {0};
    req.functionName = FN_UPDATE_STUDENT;
    req.student = *student;
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return -1;
    }
    return res.status;
}

int Storage_deleteStudent(Storage * self, int id) {
    Request req = {0};
    req.functionName = FN_DELETE_STUDENT;
    req.id = id;
    Response res = {0};
    int status = Client_sendRequest(&req, &res);
    if (status != 0) {
        fprintf(stderr, "Send request error\n");
        return -1;
    }
    return res.status;
}