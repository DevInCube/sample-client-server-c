#include <fs.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static char *ft_strdup(char *src);

// code adapted from https://stackoverflow.com/a/4204758/6634744
PbList * Fs_getDirFiles(const char * dirPath) {
    PbList * files = PbList_new();
    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char * name = dir->d_name;
            if (name[0] != '.') {
                PbList_add(files, ft_strdup(name));
            }
        }
        closedir(d);
    }
    return files;
}
bool Fs_fileExists(const char * fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) return 0;  // false: not exists
    fclose(f);
    return 1;  // true: exists
}
int Fs_getFileSize(const char * fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) return -1;  // error opening file
    fseek(f, 0, SEEK_END);  // rewind cursor to the end of file
    long fsize = ftell(f);  // get file size in bytes
    fclose(f);
    return fsize;
}
int Fs_readAllText(const char * fileName, char * buffer, int bufferLen) {
    FILE *f = fopen(fileName, "rb");
    if (!f) return 0;  // read 0 bytes from file
    long readBytes = fread(buffer, 1, bufferLen, f);
    fclose(f);
    return readBytes;  // number of bytes read
}
int Fs_writeAllText(const char * fileName, const char * buffer, int bufferLen) {
    FILE *f = fopen(fileName, "wb");
    if (!f) return 0;  // read 0 bytes from file
    long nwrite = fwrite(buffer, 1, bufferLen, f);
    fclose(f);
    return nwrite;  // number of bytes read
}

// adapted from https://stackoverflow.com/a/37132824/6634744
static char *ft_strdup(char *src) {
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}