#include "list.h"
#include <stdio.h>
#include <stdlib.h>

Node *create(double key) // создание корня дерева
{
    Node *tmp = malloc(sizeof(Node));
    tmp -> key = key;
    tmp -> next = tmp -> prev = NULL;
    return tmp;
}

Node *add_left(Node *root, double key){
    Node *tmp = create(key);
    tmp->next = root;
    root->prev = tmp;
    root = tmp;
    return root;
}

Node *add_right(List *list, double key){
    Node *tmp = create(key);
    Node *last = list->tail;
    last->next = tmp;
    tmp->prev = last;
    list->tail = tmp;
    return list->tail;
}

void list_print(Node *root, List *list) {
    if (list->size == 0) {
        printf("Список пуст\n");
        return;
    }
    while (root) {
        printf("%lf ", root->key);
        root = root->next;
    }
    printf("\n");
}

Node *find_node(Node *root, double value){
    int i=1;
    while(i<value) {
        root = root->next;
        i++;
    }
    return root;
}

Node *add_node(Node *root, List *list, double key){
    Node *tmp = create(key);
    Node *root_next = root->next;

    root->next = tmp;
    tmp->prev = root;
    tmp->next = root_next;
    root_next->prev = tmp;
    return list->head;
}

Node *delete_node(Node *root_1, Node *root,  List *list){
    if(!root->prev && !root->next){
        Node *tmp;
        list->tail = NULL;
        free(root);
        return NULL;
    }
    else if(!root->prev){
        Node *tmp;
        tmp = root->next;
        tmp->prev = NULL;
        root->next = NULL;
        free(root);
        return tmp;
    }
    else if(!root->next) {
        Node *tmp;
        tmp = root->prev;
        root->prev = NULL;
        tmp->next = NULL;
        list->tail = tmp;
        free(root);
        return root_1;
    }
    else {
        Node *root_prev = root->prev;
        Node *root_next = root->next;
        root_prev->next = root_next;
        root_next->prev = root_prev;
        root->prev = root->next = NULL;
        free(root);
        return root_1;
    }
}

Node *variant(Node *root, List *list, double key){
    int step = 1;
    Node *tmp = root;

    int i;
    for(i=key; i <= list->size; i+=key-1){// key-1 шаг из за того что мы удаляем один элемент
        tmp = root;
        while (step < i) {
            tmp = tmp->next;
            step++;
        }
        root = delete_node(root, tmp, list);
        step = 1;// единицей мы считаем первый элемент. Мы двигаемся ->next потом прибавляем step
        list->size--;
    }
    return root ;
}

int main(){
    Node *tmp = NULL;
    Node *root = NULL;
    List *list;
    list->size = 0;
    int action;
    double key;


    printf("Меню:\n");
    printf("1) Создать список\n");
    printf("2) Добавить в начало\n");
    printf("3) Добавить в конец\n");
    printf("4) Печать списка\n");
    printf("5) Вставить элемент\n");
    printf("6) Удалить элемент\n");
    printf("7) Длина списка\n");
    printf("8) Задание\n");
    printf("9) Выход\n");

    while (1)
    {
        printf("Введите действие: ");
        scanf("%d", &action);

        switch (action)
        {
            case 1:
            {

                printf("Введите значение корня: ");
                scanf("%lf", &key);
                root = create(key);
                list->tail = root;
                list->head = root;
                list->size++;
                break;
            }

            case 2:
            {
                printf("Введите значение: ");
                scanf("%lf", &key);
                root = add_left(root, key);
                list->size++;
                list->head = root;
                break;
            }

            case 3:
            {
                printf("Введите значение: ");
                scanf("%lf", &key);
                list->tail = add_right(list, key);
                list->size++;
                break;
            }

            case 4:
            {
                list_print(root, list);
                break;
            }

            case 5:
            {
                double value;
                printf("Введите номер эл-та после которого надо вставить число: ");
                scanf("%lf", &value);// мы вставляем число
                if(value<list->size) {
                    printf("Введите значение которое надо вставить : ");
                    scanf("%lf", &key);
                    tmp = find_node(root, value);// еще придумать ошибку если не нашел
                    root = add_node(tmp, list, key);

                    list->size++;
                }
                else{
                    printf("Такого номера не существует\n");
                }
                break;
            }

            case 6:
            {
                double value;
                printf("Введите номер эл-та которое надо удалить: ");
                scanf("%lf", &value);// мы вставляем число
                if(value <= list->size && value>0) {
                    tmp = find_node(root, value);
                    root = delete_node(root, tmp, list);
                    list->size--;
                }
                else
                    printf("Такого номера не существует\n");

                break;
            }

            case 7:
            {
                printf("Длина списка равна: %d\n", list->size);
                break;
            }

            case 8:
            {
                printf("Удалить каждый k-ый элемент: \n");
                printf("Введите k: ");
                scanf("%lf", &key);
                if(key <= 0 || key > list->size) {
                    printf("Неверный k-элемент \n");
                    break;
                }
                root = variant(root, list, key);
                break;
            }

            case 9: break;

            default:
            {
                printf("Ошибка. Такого пункта меню не существует\n");

                break;
            }
        }

        if (action == 9)
            break;
    }

    return 0;
}
