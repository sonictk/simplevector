#define SDL_MAIN_HANDLED
#include "SDL.h"

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
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		SDL_WINDOW_OPENGL
		);
	if (window == NULL) {
		return 1;
	}

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "test title", "test message", window);

	Vector testVector;
	vectorInit(&testVector);
	vectorAppend(&testVector, (void *)"The first test");
	vectorAppend(&testVector, (void *)"The second test");
	vectorAppend(&testVector, (void *)3);
	char *test = (char *)vectorGet(&testVector, 0);
	char *test2 = (char *)vectorGet(&testVector, 1);
	int *test3 = (int *)vectorGet(&testVector, 2);
	cout << "load-time dynamic linking test" << endl;
	cout << test << endl;
	cout << test2 << endl;
	cout << test3 << endl;
	vectorFree(&testVector);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
