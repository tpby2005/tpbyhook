//
// Created by tobyb on 3/7/2023.
//

#include "memory.h"
#include <TlHelp32.h>
#include <comdef.h>

Memory::Memory(const char *process_name) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    while (Process32Next(snapshot, &entry)) {
        _bstr_t exe_file(entry.szExeFile);
        const char* exe_file_cstring = exe_file;

        if (!strcmp(process_name, exe_file_cstring)) {
            this->id = entry.th32ProcessID;
            this->process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->id);

            break;
        }
    }

    if (snapshot) {
        CloseHandle(snapshot);
    }
}

Memory::~Memory() {
    if (this->process) {
        CloseHandle(this->process);
    }
}

DWORD Memory::getProcessId() {
    return this->id;
}

HANDLE Memory::getProcessHandle() {
    return this->process;
}

uintptr_t Memory::getModuleAddress(const char *module_name) {
    MODULEENTRY32 entry;
    entry.dwSize = sizeof(MODULEENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->id);

    uintptr_t result = 0;

    while (Module32Next(snapshot, &entry)) {
        _bstr_t module(entry.szModule);
        const char* module_cstring = module;

        if (!strcmp(module_name, module_cstring)) {
            result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);

            break;
        }
    }

    if (snapshot) {
        CloseHandle(snapshot);
    }

    return result;
}