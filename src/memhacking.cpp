#include "memhacking.hpp"
#include <tlhelp32.h>
#include <psapi.h>

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
    DWORD pid, access = PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;

    vector<DWORD> pids = GetPIDS();
    if(pids.size() <= 0)
        return -4;

    for(int i=0;i<pids.size();i++){
        pid = pids[i];

        HANDLE proc_handle = OpenProcess(access, 0, pid);
        if(!proc_handle)
            return pid;

        //DWORD nameplateAddr = 0x00BA4B90;  //12209040; (INT)
        //float ptr;
        //ReadProcessMemory(proc_handle, (void*)nameplateAddr, &ptr, sizeof(ptr), NULL);
        
        float tmp = (float)dist * 20;
        DWORD nameplateAddr = 0x00BA4B90;  //12209040; (INT)
        WriteProcessMemory(proc_handle, (void*)(nameplateAddr), &tmp, sizeof(tmp), NULL);
    }

    return 0;
}