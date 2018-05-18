#include <stdlib.h>
#include <stdio.h>
#include <progbase/console.h>
#include <storage.h>

int main(void) {
    Storage * storage = Storage_new();
    Storage_getAllFilesNew(storage);
    Storage_free(storage);
    return 0;
}