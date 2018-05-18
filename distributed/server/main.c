#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "storage.h"

void handler(Request * req, Response * res, Storage * storage) {
    switch (req->functionName) {
        case FN_GET_FILES: {
            // @todo
            break;
        }
        case FN_NEW_LIST: {
            Storage_clearList(storage);
            break;
        }
        case FN_LOAD_LIST: {
            // @todo
            break;
        }
        case FN_SAVE_LIST: {
            // @todo
            break;
        }
        case FN_GET_STUDENTS: {
            // @todo
            break;
        }
        case FN_INSERT_STUDENT: {
            // @todo
            break;
        }
        case FN_UPDATE_STUDENT: {
            // @todo
            break;
        }
        case FN_DELETE_STUDENT: {
            // @todo
            break;
        }
        default: {
            fprintf(stderr, "[Server]> Error function name");
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