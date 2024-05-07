#include <stdio.h>
#include <windows.h>
#include <dbghelp.h>

#pragma comment(lib, "user32.lib")
#pragma comment (lib, "dbghelp.lib")

#define SIZE_OF_ORIGINAL_INSTRUCTION 14

BOOL HookAndPatch(FARPROC hookingFunc);

//-- pointer to original MessageBox
typedef int (WINAPI * OrigMessageBox_t)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
OrigMessageBox_t pOrigMessageBox = NULL;

//-- storage for original bytes from MessageBox
char OriginalBytes[SIZE_OF_ORIGINAL_INSTRUCTION] = { 0 };


//-- the modified MessageBox function
int ModifiedMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) {
	SIZE_T bytesOut = 0;
	
	printf("ModifiedMessageBox() called. No MessageBox popup on screen!\n");

	//-- restore the original function 
	//WriteProcessMemory(GetCurrentProcess(), (LPVOID)pOrigMessageBox, OriginalBytes, SIZE_OF_ORIGINAL_INSTRUCTION, &bytesOut);
	//pOrigMessageBox(hWnd, lpText, lpCaption, uType);
	//HookAndPatch((FARPROC) ModifiedMessageBox);
	
	return IDOK;
}


//-- Set a hook on the MessageBox function by patching code
BOOL HookAndPatch(FARPROC hookingFunc) {

	SIZE_T bytesIn = 0;
	SIZE_T bytesOut = 0;
	
	//-- save the original address of MessageBoxA
	pOrigMessageBox = (OrigMessageBox_t) GetProcAddress(GetModuleHandle("user32.dll"), "MessageBoxA");

	//-- copy SIZE_OF_ORIGINAL_INSTRUCTION bytes of original code from MessageBoxA
	ReadProcessMemory(GetCurrentProcess(), pOrigMessageBox, OriginalBytes, SIZE_OF_ORIGINAL_INSTRUCTION, &bytesIn);
	
	
	//-- 6 hex bytes for JUMP instruction: \xFF\x25\x00\x00\x00\x00
	//-- 8 hex bytes for the function address
	char patch[14] = { 0 };
	memcpy(patch, "\xFF\x25", 2);
	memcpy(patch + 6, &hookingFunc, 8);
	
	// patch the MessageBoxA
	WriteProcessMemory(GetCurrentProcess(), (LPVOID) pOrigMessageBox, patch, sizeof(patch), &bytesOut);
	
	printf("MessageBoxA() has been hooked!\n");
	printf("ModifiedMessageBox is at: %p ; OriginalBytes is at: %p\n", ModifiedMessageBox, OriginalBytes);
	
	return FALSE;
}


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

    switch (dwReason)  {
		case DLL_PROCESS_ATTACH:
			HookAndPatch((FARPROC) ModifiedMessageBox);
			break;
			
		case DLL_THREAD_ATTACH:
			break;
			
		case DLL_THREAD_DETACH:
			break;
			
		case DLL_PROCESS_DETACH:
			break;
	}
	
    return TRUE;
}

