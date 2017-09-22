#include "vector.h"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>

Import void vectorInit(Vector *vector);
Import void vectorResize(Vector *vector, int newCapacity);
Import void vectorAppend(Vector *vector, void *value);
Import void *vectorGet(Vector *vector, int index);
Import void vectorSet(Vector *vector, int index, void *value);
Import void vectorRemove(Vector *vector, int index);
Import void vectorIncreaseCapacityIfFull(Vector *vector);
Import void vectorFree(Vector *vector);

#endif // _WIN32

using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
	Vector testVector;
	vectorInit(&testVector);
	vectorAppend(&testVector, (void *)"The first test");
	vectorAppend(&testVector, (void *)"The second test");
	char *test = (char *)vectorGet(&testVector, 0);
	char *test2 = (char *)vectorGet(&testVector, 1);
	cout << "load-time dynamic linking test" << endl;
	cout << test << endl;
	cout << test2 << endl;
	vectorFree(&testVector);
	return 0;
}
