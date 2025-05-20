#include "MemoryUtils.h"
#include <TlHelp32.h>
#include <iostream>
#include "Globals.h"

DWORD GetProcessIdByName(const std::wstring& name) {
    PROCESSENTRY32W entry = { sizeof(entry) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (name == entry.szExeFile) {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}

void ParsePattern(const std::string& patternStr, std::vector<Byte_t>& pattern, std::string& mask) {
    pattern.clear();
    mask.clear();
    size_t i = 0;

    while (i < patternStr.size()) {
        if (patternStr[i] == ' ') {
            ++i;
            continue;
        }

        if (patternStr[i] == '?') {
            pattern.push_back(0x00);
            mask += '?';
            if (i + 1 < patternStr.size() && patternStr[i + 1] == '?') i++;
        }
        else {
            pattern.push_back(static_cast<Byte_t>(strtol(patternStr.substr(i, 2).c_str(), nullptr, 16)));
            mask += 'x';
            i++;
        }
        i++;
    }
}

bool MatchBytes(const Byte_t* data, const std::vector<Byte_t>& pattern, const std::string& mask) {
    for (size_t i = 0; i < pattern.size(); i++) {
        if (mask[i] == 'x' && data[i] != pattern[i])
            return false;
    }
    return true;
}

std::vector<uintptr_t> FindAllPatterns(HANDLE hProcess, const std::vector<Byte_t>& pattern, const std::string& mask) {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    uintptr_t start = reinterpret_cast<uintptr_t>(sysInfo.lpMinimumApplicationAddress);
    uintptr_t end = reinterpret_cast<uintptr_t>(sysInfo.lpMaximumApplicationAddress);

    MEMORY_BASIC_INFORMATION mbi;
    std::vector<uintptr_t> results;
    std::vector<Byte_t> buffer;

    for (uintptr_t addr = start; addr < end;) {
        if (VirtualQueryEx(hProcess, reinterpret_cast<LPCVOID>(addr), &mbi, sizeof(mbi))) {
            bool canRead = mbi.State == MEM_COMMIT &&
                !(mbi.Protect & PAGE_GUARD) &&
                (mbi.Protect & (PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_EXECUTE_READ));

            if (canRead) {
                SIZE_T regionSize = mbi.RegionSize;
                buffer.resize(regionSize);

                SIZE_T bytesRead = 0;
                if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(addr), buffer.data(), regionSize, &bytesRead)) {
                    for (size_t i = 0; i <= bytesRead - pattern.size(); ++i) {
                        bool found = true;
                        for (size_t j = 0; j < pattern.size(); ++j) {
                            if (mask[j] == 'x' && buffer[i + j] != pattern[j]) {
                                found = false;
                                break;
                            }
                        }
                        if (found) {
                            results.push_back(addr + i);
                        }
                    }
                }
            }
            addr += mbi.RegionSize;
        }
        else {
            addr += 0x1000;
        }
    }

    return results;
}

