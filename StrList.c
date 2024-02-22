#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

typedef struct _node {
    char* _str;
    struct _node* _next;
} Node;

struct _StrList {
    Node* _head;
    size_t _size;
};

Node* Node_alloc(const char* str, Node* next) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) { 
        return NULL;
    }
    p->_str = strdup(str); 
    if (p->_str == NULL) { 
        free(p);
        return NULL;
    }
    p->_next = next;
    return p;
}

void Node_free(Node* node) {
    if (node == NULL) return;
    free(node->_str);
    free(node);
}

StrList* StrList_alloc() {
    StrList* p = (StrList*)malloc(sizeof(StrList));
    if (p == NULL) { 
        return NULL;
    }
    p->_head = NULL;
    p->_size = 0;
    return p;
}

void StrList_free(StrList* list) {
    if (list == NULL || list->_head == NULL) return;
    Node* p1 = list->_head;
    Node* p2;
    while (p1) {
        p2 = p1;
        p1 = p1->_next;
        Node_free(p2);
    }
    free(list);
}

size_t StrList_size(const StrList* StrList) {
    return StrList ? StrList->_size : 0;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if (StrList == NULL) return;
    Node* newNode = Node_alloc(data, NULL);
    if (newNode == NULL) return;
    if (StrList->_head == NULL) {
        StrList->_head = newNode;
    } else {
        Node* p = StrList->_head;
        while (p->_next) {
            p = p->_next;
        }
        p->_next = newNode;
    }
    ++(StrList->_size);
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL || index < 0 || index > StrList->_size) return;
    if (index == 0) {
        Node* newNode = Node_alloc(data, StrList->_head);
        if (newNode == NULL) return;
        StrList->_head = newNode;
        ++(StrList->_size);
        return;
    }
    Node* p = StrList->_head;
    for (int i = 0; i < index - 1; ++i) {
        p = p->_next;
    }
    Node* newNode = Node_alloc(data, p->_next);
    if (newNode == NULL) return;
    p->_next = newNode;
    ++(StrList->_size);
}

char* StrList_firstData(const StrList* StrList) {
    if (StrList == NULL || StrList->_head == NULL) return NULL;
    return StrList->_head->_str;
}

void StrList_print(const StrList* StrList) {
    if (StrList == NULL || StrList->_head == NULL) return;
    Node* p = StrList->_head;
    int isFirst=1;
    while (p) {
        if(!isFirst){
            printf(" %s", p->_str);
        } else{
            printf("%s", p->_str);
            isFirst=0;
        }
        p = p->_next;
    }
}

void StrList_printAt(const StrList* StrList, int index) {
    if (StrList == NULL || StrList->_head == NULL || index < 0 || index >= StrList->_size) return;
    Node* p = StrList->_head;
    for (int i = 0; i < index; ++i) {
        p = p->_next;
    }
    printf("%s", p->_str);
}

int StrList_printLen(const StrList* StrList) {
    if (StrList == NULL || StrList->_head == NULL) return 0;
    Node* p = StrList->_head;
    size_t num = 0;
    while (p) {
        num += strlen(p->_str);
        p = p->_next;
    }
    return num;
}

int StrList_count(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) return 0;
    Node* p = StrList->_head;
    size_t num = 0;
    while (p) {
        if (strcmp(p->_str, data) == 0) {
            num++;
        }
        p = p->_next;
    }
    return num;
}

void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || index >= StrList->_size) return;
    Node* p = StrList->_head;
    if (index == 0) {
        StrList->_head = p->_next;
        Node_free(p);
        --(StrList->_size);
        return;
    }
    for (int i = 0; i < index - 1; ++i) {
        p = p->_next;
    }
    Node* temp = p->_next;
    p->_next = temp->_next;
    Node_free(temp);
    --(StrList->_size);
}

void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) return;
    Node* p = StrList->_head;
    Node* prev = NULL;
    while (p) {
        if (strcmp(p->_str, data) == 0) {
            if (prev == NULL) {
                StrList->_head = p->_next;
                Node_free(p);
                p = StrList->_head;
            } else {
                prev->_next = p->_next;
                Node_free(p);
                p = prev->_next;
            }
            --(StrList->_size);
        } else {
            prev = p;
            p = p->_next;
        }
    }
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
    if (StrList1 == NULL && StrList2 == NULL) return 1;
    if (StrList1 == NULL || StrList2 == NULL) return 0;
    const Node* p1 = StrList1->_head;
    const Node* p2 = StrList2->_head;
    while (p1 && p2) {
        if (strcmp(p1->_str, p2->_str) != 0) return 0;
        p1 = p1->_next;
        p2 = p2->_next;
    }
    if (p1 != NULL || p2 != NULL) return 0;
    return 1;
}

StrList* StrList_clone(const StrList* StrList1) {
    if (StrList1 == NULL) return NULL;
    StrList* NewList = StrList_alloc();
    if (NewList == NULL) return NULL;
    Node* p = StrList1->_head;
    Node** copy = &(NewList->_head);
    NewList->_size = StrList1->_size;
    while (p) {
        *copy = Node_alloc(p->_str, NULL);
        if (*copy == NULL) {
            StrList_free(NewList);
            return NULL;
        }
        p = p->_next;
        copy = &((*copy)->_next);
    }
    return NewList;
}

void StrList_reverse(StrList* StrList) {
    if (StrList == NULL) return;
    Node* prev = NULL;
    Node* current = StrList->_head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }

    StrList->_head = prev;
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->_head == NULL) return;
    int s;
    Node* p;
    Node* q = NULL;
    do {
        s = 0;
        p = StrList->_head;
        while (p->_next != q) {
            if (strcmp(p->_str, p->_next->_str) > 0) {
                char* temp = p->_str;
                p->_str = p->_next->_str;
                p->_next->_str = temp;
                s = 1;
            }
            p = p->_next;
        }
        q = p;
    } while (s);
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->_head == NULL) return 1;
    Node* p = StrList->_head;
    while (p->_next) {
        if (strcmp(p->_str, p->_next->_str) > 0) {
            return 0;
        }
        p = p->_next;
    }
    return 1;
}