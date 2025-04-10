#include <stdlib.h>
#include "linked_list.h"

struct node* insert_at_head(struct node* head, int value) {
    struct node* new_node = malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->value = value;
    new_node->next = head;
    return new_node;
}

struct node* insert_at_tail(struct node* head, int value) {
    struct node* new_node = malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->value = value;
    new_node->next = NULL;

    if (!head) {
        return new_node;
    }

    struct node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}

struct node* remove_from_head(struct node* head, int* value) {
    if (!head) return NULL;

    *value = head->value;
    struct node* temp = head->next;
    free(head);
    return temp;
}

struct node* remove_from_tail(struct node* head, int* value) {
    if (!head) return NULL;

    if (!head->next) {
        *value = head->value;
        free(head);
        return NULL;
    }

    struct node* temp = head;
    while (temp->next->next) {
        temp = temp->next;
    }

    *value = temp->next->value;
    free(temp->next);
    temp->next = NULL;
    return head;
}

void free_list(struct node* head) {
    while (head) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
}
