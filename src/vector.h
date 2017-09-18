/**
 * @brief  	Simple vector implementation. Similar to ``std::vector``, but with
 *				less templates.
 */

#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INITIAL_CAPACITY 64

#include "vector_library.h"


struct Vector
{
	int size;			/// The num. of items in the vector.
	int capacity;		/// The maximum num. of items the vector can have.
	void **items;		/// The items to store.
};


/**
 * Initializes the given ``vector`` to default values. Should be called after
 * allocating memory for a new ``Vector`` object.
 *
 * @param vector		The vector to initialize;
 */
Shared DLLExport void vectorInit(Vector *vector);


/**
 * This function resizes the given ``vector``.
 *
 * @param vector			The vector to resize.
 * @param newCapacity		The new capacity to resize the vector to.
 */
Shared DLLExport void vectorResize(Vector *vector, int newCapacity);


/**
 * This function adds a new item to the vector.
 *
 * @param vector		The vector to add an item to.
 * @param value		The pointer to the item to add.
 */
Shared DLLExport void vectorAppend(Vector *vector, void *value);


/**
 * This function retrieves an item from the vector.
 *
 * @param vector		The vector to get the item from.
 * @param index		The index at which to retrieve the item.
 *
 * @return				A pointer to the item to retrieve.
 */
Shared DLLExport void *vectorGet(Vector *vector, int index);


/**
 * This function sets the value at the ``index`` to the new item in the given ``vector``.
 *
 * @param vector		The vector to set a new item for.
 * @param index		The index in the vector at which to set it.
 * @param value		The new item to set.
 */
Shared DLLExport void vectorSet(Vector *vector, int index, void *value);


/**
 * This function removes an item from the given ``vector``.
 *
 * @param vector		The vector to remove an item from.
 * @param index		The index at which the item to be removed resides at.
 */
Shared DLLExport void vectorRemove(Vector *vector, int index);


/**
 * This function checks if the ``vector`` has reached its allocation capacity and
 * increases the storage if necessary. No operation is performed if the ``vector``
 * has not reached its capacity.
 *
 * @param vector		The vector to increase the capacity for.
 */
Shared DLLExport void vectorIncreaseCapacityIfFull(Vector *vector);


/**
 * This function de-allocates the memory for the given ``vector``'s items.
 *
 * @param vector		The vector to deallocate the memory for its items.
 */
Shared DLLExport void vectorFree(Vector *vector);


#endif /* VECTOR_H */
