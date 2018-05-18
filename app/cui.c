#include <cui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <progbase/console.h>

static void clearStdIn();

int  getUserIntInput(const char * message) {
    printf("> %s: ", message);
    int x = 0;
    scanf("%i", &x);
    clearStdIn();
    return x;
}
void getUserStringInput(const char * message, char * buf, int bufLen) {
    printf("> %s: ", message);
    fgets(buf, bufLen, stdin);
    buf[strlen(buf) - 1] = '\0';
}
char getUserInput(const char * message) {
    printf("> %s: ", message);
    char c = Console_getChar();
    puts("");
    return c;
}

static void clearStdIn() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
