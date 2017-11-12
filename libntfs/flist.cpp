/*In this file defined main functions to work with structure List*/

#include "stdafx.h"

void AddItemList(struct List *i, struct List **start, struct List **last, int(*Compare)(void*, void*)){
<<<<<<< HEAD
  struct List *old, *p;
  p = *start;
  if (!*last) { /* first object in list */
    i->next = NULL;
    *last = i;
    *start = i;
    return;
  }
  old = NULL;
  while (p) {
    if (Compare(p, i) < 0) {
      old = p;
      p = p->next;
    }
    else {
      if (old) { /* insert object in middle*/
        old->next = i;
        i->next = p;
      }
      else {
        i->next = p; /*insert object in begin of list*/
        *start = i;
      }
      return;
    }
  }
  (*last)->next = i; /*insert in end of list*/
  i->next = NULL;
  *last = i;
}

struct List *FindItemList(struct List *start, void * n, comp_item Compare) {
  while (start) { 
    if (!Compare(n, start))
      return start;
    start = start->next;
  }
  return NULL;  /* object was nod disclosed */
}

void FreeList(struct List **start, free_data fd) {
  struct List* tmp;
  while (*start) {
    tmp = *start;
    *start = (*start)->next;
    fd(&tmp);  /*/ free data of list object*/
    if(tmp) free(tmp);    /*/ free list object*/
  }
=======
	struct List *old, *p;
	p = *start;
	if (!*last) { /* first object in list */
		i->next = NULL;
		*last = i;
		*start = i;
		return;
	}
	old = NULL;
	while (p) {
		if (Compare(p, i) < 0) {
			old = p;
			p = p->next;
		}
		else {
			if (old) { /* insert object in middle*/
				old->next = i;
				i->next = p;
			}
			else {
				i->next = p; /*insert object in begin of list*/
				*start = i;
			}
			return;
		}
	}
	(*last)->next = i; /*insert in end of list*/
	i->next = NULL;
	*last = i;
}

struct List *FindItemList(struct List *start, void * n, comp_item Compare) {
	while (start) { 
		if (!Compare(n, start))
			return start;
		start = start->next;
	}
	return NULL;  /* object was nod disclosed */
}

void FreeList(struct List **start, free_data fd) {
	struct List* tmp;
	while (*start) {
		tmp = *start;
		*start = (*start)->next;
		fd(&tmp);	/*/ free data of list object*/
		if(tmp) free(tmp);		/*/ free list object*/
	}
>>>>>>> 04369cdac075e42751460c7ba74939ade78eb23a
}
