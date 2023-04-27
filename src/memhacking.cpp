#include "memhacking.hpp"
#include <Windows.h>
//#include <string>
#include <tlhelp32.h>
#include <vector>
#include <psapi.h>
#include <fstream>
#include <string>

/*
*/
vector<DWORD> GetPIDS()
{
    std::vector<DWORD> pids;
    std::wstring targetProcessName = L"Wow.exe";

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes

    PROCESSENTRY32W entry; //current process
    entry.dwSize = sizeof entry;

    if (!Process32FirstW(snap, &entry))//start with the first in snapshot
        return pids;

    do {
        if (std::wstring(entry.szExeFile) == targetProcessName)
            pids.emplace_back(entry.th32ProcessID); //name matches; add to list
    } while (Process32NextW(snap, &entry)); //keep going until end of snapshot

    return pids;
}

/* 
*/
uintptr_t GetModuleBaseAddress(DWORD dwProcID, char* szModuleName)
{
    uintptr_t ModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, dwProcID);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 ModuleEntry32;
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &ModuleEntry32)) {
            do {
                if (strcmp(ModuleEntry32.szModule, szModuleName) == 0) {
                    ModuleBaseAddress = (uintptr_t)ModuleEntry32.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnapshot, &ModuleEntry32));
        }
        CloseHandle(hSnapshot);
    }
    return ModuleBaseAddress;
}


/*
*/
int SetNameplateMaxDistance(int dist)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tokenPrivileges;
    DWORD pid, access = PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;

    // Obtain a handle to the current process's access token
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return -1;

    // Lookup the privilege ID for the SE_DEBUG_NAME privilege
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tokenPrivileges.Privileges[0].Luid))
        return -2;

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Enable the SE_DEBUG_NAME privilege
    if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
        return -3;

    vector<DWORD> pids = GetPIDS();
    if(pids.size() <= 0)
        return -4;

    for(int i=0;i<pids.size();i++){
        pid = pids[i];

        HANDLE proc_handle = OpenProcess(access, 0, pid);
        if(!proc_handle)
            return pid;

        //float ptr;
        //ReadProcessMemory(proc_handle, (void*)nameplateAddr, &ptr, sizeof(ptr), NULL);
        
        float tmp = (float)dist * 100;
        DWORD nameplateAddr = 0x00BA4B90;  //12209040; (INT)
        WriteProcessMemory(proc_handle, (void*)(nameplateAddr), &tmp, sizeof(tmp), NULL);
    }

    return 0;
}