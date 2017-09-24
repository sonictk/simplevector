#include "vector.h"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <strsafe.h>
#include <tchar.h>

#elif __linux__ || __APPLE__
#include <dlfcn.h>

#endif // PLATFORM LAYER

using std::cout;
using std::endl;
using std::cerr;


int main(int argc, char *argv[])
{
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


#ifdef _WIN32
static TCHAR szWindowClass[] = _T("Test vector application");
static TCHAR szTitle[] = _T("Title bar text");

HINSTANCE hInst;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}


int WINAPI WinMain(_In_ HINSTANCE hInstance,
				   _In_ HINSTANCE hPrevInstance,
				   _In_ LPSTR lpCmdLine,
				   _In_ int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}

	hInst = hInstance;
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd) {
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return main(__argc, __argv);
}
#endif // _WIN32
