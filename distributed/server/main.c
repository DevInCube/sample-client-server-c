#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "storage.h"

Response handler(Request * req, Storage * storage) {
    switch (req->functionName) {
        case FN_NEW_LIST: {
            Storage_clearList(storage);
            break;
        }
    }
    Response res;
    return res;
}

int main(void) {
    Storage * storage = Storage_new();
    int status = Server_run(3030, (ServerRequestHandler)handler, storage);
    printf("Server run status %i\n", status);
    Storage_free(storage);
    return 0;
}