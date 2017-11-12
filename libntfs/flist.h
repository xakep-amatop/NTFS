/*In this file include main prototypes of functions to work with structure List, some function types and main list structure (List)*/
#ifndef __flist_h__
#define __flist_h__

#include "stdafx.h"

#ifdef LIBNTFS_EXPORTS
	#define LIBNTFS __declspec(dllexport)
#else
	#define LIBNTFS __declspec(dllimport)
#endif

/** Structure of list object*/
struct List {
	List* next;	/*pointer to next item in list*/
	void* data;	/*pointer to other data in list, such as another structures, arrays or simple data formats*/
};

/** Type of pointer to function for compare list objects */
typedef int(*comp_item)(void*, void*);

/**	Type of pointer to function for free heap memory allocated to data field
	if it was be allocated by means of group of this function: calloc, malloc, realloc
*/
typedef void(*free_data)(void*, ...);

/** Insert item in orderly list
	\param
		i		pointer to item, that will be inserted in list
		start	pointer to pointer to first item in list
		end		pointer to pointer to last	item in list
		Compare	pointer to function for compare items in list,
				we can choose what fields to compare and set rules of equals
				in this function
*/
#if defined(_WINDOWS_)
	LIBNTFS
#endif
	void AddItemList(struct List *i, struct List **start, struct List **last, int(*comp)(void*, void*));

/** Search item in list
	\param
		start	pointer to first item in list
		n		pointer to field, that will be found in list
		Compare	pointer to function for compare items in list,
				we can choose what fields to compare and set rules of equals
				in this function
	\return pointer to first disclosed item in list, if NULL item was not disclosed in list
*/
#if defined(_WINDOWS_)
	LIBNTFS
#endif 
	struct List *FindItemList(struct List *start, void * n, comp_item Compare);

/** Free list and all data in list allocated in heap
	\param
		start	pointer to pointer to first item in list
		fd		pointer to function for compare items in list,
		we can choose what fields to compare and set rules of equals
		in this function
	When function end working, then start parameter must be equal NULL 
*/
#if defined(_WINDOWS_)
	LIBNTFS
#endif 
	void FreeList(struct List **start, free_data fd);

#endif
