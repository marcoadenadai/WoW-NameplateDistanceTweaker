#pragma once
#include <iostream>

using namespace std;

//
std::vector<DWORD> GetPIDS();

//
uintptr_t GetModuleBaseAddress(DWORD dwProcID, char* szModuleName);

//
int SetNameplateMaxDistance(int dist);