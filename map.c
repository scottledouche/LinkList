// Taylor Fry
// CS2240 1:00pm
// Assignment 1
// January 16, 2014

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

// Initializes size to 0.
void map_init(map_t* self) {
	assert(self != NULL);

	self->entry = NULL;
	self->size = 0;
}

// Places the entry into the a node and creates a new node .
int map_put(map_t* self, const char* key, const char* val) {
	assert(self != NULL);
	
	// search is used to go through the map to find a NULL node.
	map_entry_t* search;
	search = self->entry ;

	// Search moves through the link list comparing keys.
	// Matching keys return 1.
	// Keys that do not match moves search into the next node.
	// Completely traversing the link list returns 0.
	while(search != NULL) {
		if(strcmp(search->key, key) == 0)
			return 1;
		else
			search = (map_entry_t*)search->next;
	}
	
	// newNode will be placed in the link list if needed.
	// Allocating memory for it at this point in case it is not needed.
	map_entry_t* newNode;
	newNode = malloc(sizeof(map_entry_t));
	
	// Allocating memory for the key and value for newNode
	newNode->key = strncpy(malloc(strlen(key)+1), key, 20);
	newNode->value = strncpy(malloc(strlen(val)+1), val, 20);

	// Pointer returns to the beginning of the list
	newNode->next = self->entry; // not sure about warning
	self->entry = newNode;
	self->size++;

	return 0;
}

// Returns a requested value if it exists.
// If it does not exist, returns NULL.
const char* map_get(map_t* self, const char* key) {
	assert(self != NULL);

	map_entry_t* search;
	search = self->entry ;

	// search moves through the link list comparing keys.
	// If a key matches, it is returned.
	// If it does not match, search moves on to the next node.
	// If search moves completely through the link list, it returns NULL.
	while(search != NULL) {
		if(strncmp(search->key, key, 20) == 0)
			return search->value;		
		else	
			search = (map_entry_t*)search->next;
	}
	return "NULL";
}

// Returns the amount of nodes in the map.
// Prints the keys and values of each node.
int map_size(map_t* self) {
	assert(self != NULL);
	
	map_entry_t *search;
	search = self->entry ;
	
	// search moves through the link list,
	// printing out the key and value of each node as it goes.  
	while(search != NULL) {
		printf("Key: %s Value: %s\n", search->key, search->value);
		search = (map_entry_t*)search->next;
	}
	return self->size;
}

// Removes a requested node from the map.
// Frees the allocated memory the node was taking up.
// Returns 0 when successful and 1 if not.
int map_remove(map_t* self, const char* key) {
	assert(self != NULL);
	
	map_entry_t* nextNode;
	map_entry_t* search;
	nextNode = self->entry;
	search = self->entry;

	// search moves through the link list to find the requested key.
	// Upon match, it checks to see if the adresses match.
	// Matching moves the node next node up and frees the memory
	//  of the previous node.
	// Not matching moves nextNode forward, while freeing search.
	// Returns 0 if successful, 1 if not.
	while(search != NULL) {
		if(strncmp(search->key, key, 20) == 0) {
			if(&(*self->entry) == &(*search)) {
				self->entry = (map_entry_t*)search->next;
				free(search->key);
				free(search->value);
				free(search);
				self->size--;
			}
			else {
				nextNode->next = search->next;
				free(search->key);
				free(search->value);
				free(search);
				self->size--;
			}
			return 0;		
		}
		else {
			nextNode = search;
			search = (map_entry_t*)search->next;
		}
	}
	return 1;
}

// Removes entries into the map and frees up the memory
void map_destroy(map_t* self) {
	assert(self != NULL);

	map_entry_t* search; 
	search = self->entry;

	// search moves through the link list freeing the memory of key, 
	// value, and the node itself.  Then moves to the next node.
	while(self->entry != NULL) {
		self->entry = (map_entry_t*)self->entry->next;
		free(search->key);
		free(search->value);
		free(search);
		search = self->entry;
	}
}

int map_serialize(map_t* self, FILE* stream) {
	assert(self != NULL);
	
	map_entry_t* buff;
	
	buff = self->entry;
	
	fwrite(&buff, 1024, sizeof(buff), stream);
	
	return 0;
}

int map_deserialize(map_t* self, FILE* stream) {
	assert(self != NULL);
	
	return 0;
}
