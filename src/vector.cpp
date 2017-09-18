#include "vector.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

using std::malloc;
using std::free;
using std::realloc;
using std::cerr;


Shared DLLExport void vectorInit(Vector *vector)
{
	vector->capacity = VECTOR_INITIAL_CAPACITY;
	vector->size = 0;
	vector->items = (void **)malloc(sizeof(void *) * vector->capacity);
}


Shared DLLExport void vectorResize(Vector *vector, int newCapacity)
{
	void **items = (void **)realloc(vector->items, sizeof(void *) * newCapacity);
	if (items) {
		vector->items = items;
		vector->capacity = newCapacity;
	}
}


Shared DLLExport void vectorAppend(Vector *vector, void *value)
{
	vectorIncreaseCapacityIfFull(vector);
	vector->items[vector->size++] = value;
}


Shared DLLExport void *vectorGet(Vector *vector, int index)
{
	if (index >= vector->size || index < 0) {
		cerr << "Index" << index << "out of bounds for vector of size" << vector->size <<"\n";
		return NULL;
	}
	return vector->items[index];
}


Shared DLLExport void vectorSet(Vector *vector, int index, void *value)
{
	if (index >= 0 && index < vector->size) {
		vector->items[index] = value;
	}
}


Shared DLLExport void vectorRemove(Vector *vector, int index)
{
	if (index < 0 || index >= vector->size) {
		return;
	}
	vector->items[index] = NULL;
	for (int i=index; i < vector->size - 1; ++i) {
		vector->items[i] = vector->items[i + 1];
		vector->items[i + 1] = NULL;
	}
	vector->size--;
	if (vector->size > 0 && vector->size == vector->capacity / 4) {
		vectorResize(vector, vector->capacity / 2);
	}
}


Shared DLLExport void vectorIncreaseCapacityIfFull(Vector *vector)
{
	if (vector->size >= vector->capacity) {
		// NOTE: (yliangsiew) This is wasteful but better than making several realloc()
		// calls, which is even slower.
		vector->capacity *= 2;
		vector->items = (void **)realloc(vector->items, sizeof(void *) * vector->capacity);
	}
}


Shared DLLExport void vectorFree(Vector *vector)
{
	free(vector->items);
	vector->size = 0;
}
