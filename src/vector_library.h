#ifndef VECTOR_MAIN_H
#define VECTOR_MAIN_H

#ifdef __cplusplus

#define Shared extern "C"
#define Shared extern "C"

#endif // __cplusplus

#ifdef _WIN32

#include <Windows.h>

#define DLLExport __declspec(dllexport)
#define DLLImport __declspec(dllimport)

#elif __linux__ || __APPLE__

#include <dlfcn.h>

#define DLLExport
#define DLLImport

#endif // Platform layer

#endif /* VECTOR_MAIN_H */
