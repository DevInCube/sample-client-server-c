#pragma once

#include <stdbool.h>
#include <progbase/collections/pblist.h>

PbList * Fs_getDirFiles(const char * dirPath);
bool Fs_fileExists(const char * fileName);
int Fs_getFileSize(const char * fileName);
int Fs_readAllText(const char * fileName, char * buffer, int bufferLen);
int Fs_writeAllText(const char * fileName, const char * buffer, int bufferLen);
char * Fs_getExecPath();
void Fs_pathJoin(char * buffer, const char * part);