#include <fs.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

PbList * Fs_getDirFiles(const char * dirPath) {
    PbList * files = PbList_new();
    assert(0 && "Not impl");
    return files;
}
bool Fs_fileExists(const char * fileName) {
    assert(0 && "Not impl");
    return false;
}
int Fs_getFileSize(const char * fileName) {
    assert(0 && "Not impl");
    return 0;
}
int Fs_readAllText(const char * fileName, char * buffer, int bufferLen) {
    assert(0 && "Not impl");
    return 0;
}
int Fs_writeAllText(const char * fileName, const char * buffer, int bufferLen) {
    assert(0 && "Not impl");
    return 0;
}