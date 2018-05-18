#include <stdlib.h>
#include <stdio.h>
#include "server.h"

Response handler(Request * req) {
    Response res;
    return res;
}

int main(void) {
    int status = Server_run(3030, handler);
    printf("Server run status %i\n", status);
    return 0;
}