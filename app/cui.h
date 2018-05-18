#pragma once

typedef void (*MenuItemHandler)(void * context);

typedef struct {
    char key;
    char name[100];
    MenuItemHandler handler;
} MenuItem;

typedef struct {
    MenuItem * items;
    int length;
} Menu;

Menu * Menu_new(MenuItem items[], int itemsLen);
void Menu_free(Menu * self);

int  getUserIntInput(const char * message);
void getUserStringInput(const char * message, char * buf, int bufLen);
char getUserInput(const char * message);