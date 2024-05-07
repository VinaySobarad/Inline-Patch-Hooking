#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "user32.lib")

int main(void){

	printf("Target For Hooker is Starting...\n");

	//-- ref:  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
	MessageBox(NULL, "This is the first message from THE FUTURE!", "1st MessageBox", MB_OK | MB_ICONINFORMATION);
	MessageBox(NULL, "This is the second message from THE FUTURE!", "2nd MessageBox", MB_OK | MB_ICONINFORMATION);
	MessageBox(NULL, "This is the third message from THE FUTURE!", "3rd MessageBox", MB_OK | MB_ICONINFORMATION);

	printf("Target For Hooker exiting...\n");

    return 0;
}