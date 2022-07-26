/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include "cbool.h"
#include "comp.h"

/* ===================================================================== */

typedef struct ListTAG List;

typedef void (*node_delete)(void*);
typedef bool (*node_callback)(void*);

/* ===================================================================== */

RET_NOTNULL
List* new_list(void);
void delete_list(List*, node_delete);

/* ===================================================================== */

void* list_walk(List*, node_callback);

void list_insert(List*, void*);
void list_remove(List*, void*);

/* ===================================================================== */
