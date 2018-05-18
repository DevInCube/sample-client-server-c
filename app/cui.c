#include <cui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <progbase/console.h>

Menu * Menu_new(MenuItem items[], int itemsLen) {
    Menu * self = malloc(sizeof(Menu));
    self->items = malloc(sizeof(MenuItem) * itemsLen);
    for (int i = 0; i < itemsLen; i++) {
        self->items[i] = items[i];
    }
    self->length = itemsLen;
    return self;
}
void Menu_free(Menu * self) {
    free(self->items);
    free(self);
}

void Menu_show(Menu * self) {
    puts("----------------------------");
    for (int i = 0; i < self->length; i++) {
        MenuItem * item = &self->items[i];
        printf("%c | %s\n", item->key, item->name);
    }
    puts("----------------------------");
}
AcceptStatus Menu_acceptInput(Menu * self, char input, void * context) {
    for (int i = 0; i < self->length; i++) {
        MenuItem * item = &self->items[i];
        if (item->key == input) {
            if (item->handler == NULL) { return MENU_RETURN; }
            item->handler(context);
            return MENU_OK;
        }
    }
    return MENU_INVALID;
}

static void clearStdIn();

int  getUserIntInput(const char * message) {
    printf("> %s: ", message);
    int x = 0;
    scanf("%i", &x);
    clearStdIn();
    return x;
}

float  getUserFloatInput(const char * message) {
    printf("> %s: ", message);
    float x = 0;
    scanf("%f", &x);
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
