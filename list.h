#ifndef list_h
#define list_h
#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
    double key;
    struct Item* next;
    struct Item* prev;
}Node;

typedef struct {
    struct Item* tail;// два барьерный элемент
    struct Item* head;
    int size;
} List;


#endif
