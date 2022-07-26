/* ===================================================================== */
/* ===================================================================== */

#include "cbool.h"
#include "error.h"
#include "list.h"

/* ===================================================================== */

typedef struct ListNodeTAG ListNode;

struct ListNodeTAG
{
    ListNode* prev;
    ListNode* next;
    void* data;
};

typedef struct ListTAG
{
    ListNode* first;
    ListNode* last;
} List;

/* ===================================================================== */

RET_NOTNULL
List* new_list()
{
    return (List*)safe_alloc(sizeof(List));
}

void delete_list(List* this, node_delete dispose)
{
    if (!this)
        return;

    for (ListNode* node = this->first, *next; node && (next = node->next, true); node = next)
    {
        if (dispose)
            dispose(node->data);

        free(node);
    }

    free(this);
}

/* ===================================================================== */

void* list_walk(List* this, node_callback callback)
{
    if (!this)
        return NULL;

    for (ListNode* node = this->first, *next; node && (next = node->next, true); node = next)
    {
        if (!callback(node->data))
            return node->data;
    }

    return NULL;
}

/* ===================================================================== */

void list_insert(List* this, void* item)
{
    if (!this)
        return;

    ListNode* n = (ListNode*)safe_alloc(sizeof(ListNode));

    n->prev = NULL;
    n->next = this->first;
    n->data = item;

    if (this->first)
        this->first->prev = n;
    else
        this->last = n;

    this->first = n;
}

/* ===================================================================== */

void list_removeNode(List* this, ListNode* node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        this->first = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        this->last = node->prev;

    free(node);
}

/* ===================================================================== */

void list_remove(List* this, void* item)
{
    if (!this)
        return;

    for (ListNode* node = this->first, *next; node && (next = node->next, true); node = next)
    {
        if (node->data == item)
            list_removeNode(this, node);
    }
}

/* ===================================================================== */
