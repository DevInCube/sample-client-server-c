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

typedef enum {
    MENU_INVALID,
    MENU_OK,
    MENU_RETURN
} AcceptStatus;

Menu * Menu_new(MenuItem items[], int itemsLen);
void Menu_free(Menu * self);
void Menu_show(Menu * self);
AcceptStatus Menu_acceptInput(Menu * self, char input, void * context);

int  getUserIntInput(const char * message);
float getUserFloatInput(const char * message);
void getUserStringInput(const char * message, char * buf, int bufLen);
char getUserInput(const char * message);