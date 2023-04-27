#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

//
vector<DWORD> GetPIDS();

//
uintptr_t GetModuleBaseAddress(DWORD dwProcID, char* szModuleName);

//
int SetNameplateMaxDistance(int dist);