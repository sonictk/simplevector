#include "vector.h"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <strsafe.h>

#elif __linux__ || __APPLE__
#include <dlfcn.h>

#endif // PLATFORM LAYER

using std::cout;
using std::endl;
using std::cerr;


int main(int argc, char *argv[])
{
	// TODO: (sonictk) Do example of load-time dynamic linking
	// NOTE: (sonictk) This is an example of Run-time dynamic linking
#ifdef _WIN32
	HMODULE vectorModule = LoadLibrary(TEXT("simpleVector.dll"));
	if (vectorModule == NULL) {
		LPVOID msg;
		LPVOID displayBuffer;
		DWORD errNo = GetLastError();
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					  FORMAT_MESSAGE_FROM_SYSTEM |
					  FORMAT_MESSAGE_IGNORE_INSERTS,
					  NULL,
					  errNo,
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					  (LPTSTR) &msg,
					  0, NULL );

		displayBuffer = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
										  (lstrlen((LPCTSTR)msg) + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)displayBuffer,
						LocalSize(displayBuffer) / sizeof(TCHAR),
						TEXT("Failed with error %d: %s"),
						errNo,
						msg);
		MessageBox(NULL, (LPCTSTR)displayBuffer, TEXT("Error"), MB_OK);
		LocalFree(msg);
		LocalFree(displayBuffer);
		cerr << "Failed to load library!";
		return 1;
	}
	FARPROC vectorInitAddress = GetProcAddress(vectorModule, "vectorInit");
	if (vectorInitAddress == NULL) {
		cerr << "Failed to get address of exported function!\n";
		return 1;
	}
	FARPROC vectorResizeAddress = GetProcAddress(vectorModule, "vectorResize");
	if (vectorResizeAddress == NULL) {
		cerr << "Failed to get address of exported function!\n";
		return 1;
	}
	FARPROC vectorAppendAddress = GetProcAddress(vectorModule, "vectorAppend");
	if (vectorAppendAddress == NULL) {
		cerr << "Failed to get address of exported function!\n";
		return 1;
	}
	FARPROC vectorGetAddress = GetProcAddress(vectorModule, "vectorGet");
	if (vectorGetAddress == NULL) {
		cerr << "Failed to get address of exported function!\n";
		return 1;
	}
	FARPROC vectorFreeAddress = GetProcAddress(vectorModule, "vectorFree");
	if (vectorFreeAddress == NULL) {
		cerr << "Failed to get address of exported function!\n";
		return 1;
	}
	void (*vectorInit)(Vector *) = 0;
	vectorInit = (void (__cdecl *)(Vector *))vectorInitAddress;
	void (*vectorResize)(Vector *, int) = 0;
	vectorResize = (void (__cdecl *)(Vector *, int))vectorResizeAddress;
	void (*vectorAppend)(Vector *, void *) = 0;
	vectorAppend = (void (__cdecl *)(Vector *, void *))vectorAppendAddress;
	void *(*vectorGet)(Vector *, int) = 0;
	vectorGet = (void *(__cdecl *)(Vector *, int))vectorGetAddress;
	void (*vectorFree)(Vector *) = 0;
	vectorFree = (void (__cdecl *)(Vector *))vectorFreeAddress;

	Vector testVector;
	vectorInit(&testVector);
	vectorAppend(&testVector, (void *)"The first test");
	vectorAppend(&testVector, (void *)"The second test");
	char *test = (char *)vectorGet(&testVector, 0);
	char *test2 = (char *)vectorGet(&testVector, 1);
	cout << test << endl;
	cout << test2 << endl;
	vectorFree(&testVector);

	FreeLibrary(vectorModule);

#endif // _WIN32

	return 0;
}
