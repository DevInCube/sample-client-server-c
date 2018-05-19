#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "storage.h"

void handler(Request * req, Response * res, Storage * storage) {
    switch (req->functionName) {
        case FN_GET_FILES: {
            res->files = Storage_getAllFilesNew(storage);
            break;
        }
        case FN_NEW_LIST: {
            Storage_clearList(storage);
            break;
        }
        case FN_LOAD_LIST: {
            res->status = Storage_loadListFromFile(storage, req->fileName);
            break;
        }
        case FN_SAVE_LIST: {
            res->status = Storage_saveListToFile(storage, req->fileName);
            break;
        }
        case FN_GET_STUDENTS: {
            res->students = Storage_getAllStudentsNew(storage);
            break;
        }
        case FN_INSERT_STUDENT: {
            res->id = Storage_insertStudent(storage, &req->student);
            break;
        }
        case FN_UPDATE_STUDENT: {
            res->status = Storage_updateStudent(storage, &req->student);
            break;
        }
        case FN_DELETE_STUDENT: {
            res->status = Storage_deleteStudent(storage, req->id);
            break;
        }
        default: {
            fprintf(stderr, "[Server]> Error function name\n");
            break;
        }
    }
}

int main(void) {
    Storage * storage = Storage_new();
    int status = Server_run(3030, (ServerRequestHandler)handler, storage);
    printf("Server run status %i\n", status);
    Storage_free(storage);
    return 0;
}