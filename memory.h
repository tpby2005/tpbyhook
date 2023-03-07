//
// Created by tobyb on 3/7/2023.
//

#ifndef TPBY_HOOK_MEMORY_H
#define TPBY_HOOK_MEMORY_H

#include <Windows.h>
#include <iostream>

class Memory {
private:
    DWORD id = 0;
    HANDLE process = NULL;
public:
    Memory(const char* process_name);
    ~Memory();

    DWORD getProcessId();
    HANDLE getProcessHandle();

    uintptr_t getModuleAddress(const char* module_name);

    template <typename T>
    T read(uintptr_t address) {
        T value;
        ReadProcessMemory(this->process, (LPCVOID)address, &value, sizeof(T), NULL);

        return value;
    }

    template <typename T>
    bool write(uintptr_t address, T value) {
        return WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);
    }
};


#endif //TPBY_HOOK_MEMORY_H
