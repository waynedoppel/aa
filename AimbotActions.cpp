#include "Actioncore.h"
#include "MemoryUtils.h"
#include <windows.h>
#include <string>
#include <iostream>

uintptr_t g_precisionPatchAddr = 0; // endereço salvo

void AimLegit() {
    std::wstring processName = L"HD-Player.exe";
    DWORD pid = GetProcessIdByName(processName);
    if (!pid) {
        std::cout << " Processo não encontrado!\n";
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        std::cout << " Erro ao abrir processo\n";
        return;
    }

    std::string patternStr = "FF FF 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FF FF FF FF FF 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 00 00 00 00 00 00 00 00 00 00 00 00 00 00 A5 43";

    std::vector<Byte_t> pattern;
    std::string mask;
    ParsePattern(patternStr, pattern, mask);

    auto matches = FindAllPatterns(hProcess, pattern, mask);

    for (auto baseAddr : matches) {
        uintptr_t readAddr = baseAddr + 0xD2;
        uintptr_t writeAddr = baseAddr + 0x9E;

        int value = 0;
        ReadProcessMemory(hProcess, (LPCVOID)readAddr, &value, sizeof(value), nullptr);
        WriteProcessMemory(hProcess, (LPVOID)writeAddr, &value, sizeof(value), nullptr);

        std::cout << " Valor copiado de 0x" << std::hex << readAddr << " para 0x" << writeAddr << "\n";
    }

    CloseHandle(hProcess);
}

void AimBot() {
    std::wstring processName = L"HD-Player.exe";
    DWORD pid = GetProcessIdByName(processName);
    if (!pid) {
        std::cout << " Processo não encontrado!\n";
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        std::cout << " Erro ao abrir processo\n";
        return;
    }

    std::string patternStr = "00 00 A5 43 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 80 BF";

    std::vector<Byte_t> pattern;
    std::string mask;
    ParsePattern(patternStr, pattern, mask);

    auto matches = FindAllPatterns(hProcess, pattern, mask);

    for (auto baseAddr : matches) {
        uintptr_t readAddr = baseAddr + 0x5c;
        uintptr_t writeAddr = baseAddr + 0x28;

        int value = 0;
        ReadProcessMemory(hProcess, (LPCVOID)readAddr, &value, sizeof(value), nullptr);
        WriteProcessMemory(hProcess, (LPVOID)writeAddr, &value, sizeof(value), nullptr);

        std::cout << " Valor copiado de 0x" << std::hex << readAddr << " para 0x" << writeAddr << "\n";
    }

    CloseHandle(hProcess);
}

void AimPrecision() {
    std::wstring processName = L"HD-Player.exe";
    DWORD pid = GetProcessIdByName(processName);
    if (!pid) {
        std::cout << " Processo não encontrado!\n";
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if (!hProcess) {
        std::cout << " Erro ao abrir processo\n";
        return;
    }

    const std::string originalStr = "19 3F 00 00 80 3F 03 00 00 00 00 00 70 41 00 00 0C 42 00 00 20 41 00 00 A0 41 CD CC 4C 3D 00 00 40 3F 66 66";
    const std::string patchedStr =  "19 3F 00 00 80 3F 03 00 00 00 00 00 75 41 00 00 00 00 00 00 79 41 00 00 66 46 CD CC 4C 3D 00 00 40 3F 66 66";

    std::vector<Byte_t> originalBytes, patchedBytes;
    std::string mask, dummy;

    ParsePattern(originalStr, originalBytes, mask);
    ParsePattern(patchedStr, patchedBytes, dummy);

    // se endereço ainda não foi salvo
    if (g_precisionPatchAddr == 0) {
        auto matches = FindAllPatterns(hProcess, originalBytes, mask);
        if (matches.empty()) {
            std::cout << " Padrão original não encontrado para patch.\n";
            CloseHandle(hProcess);
            return;
        }
        g_precisionPatchAddr = matches[0];
    }

    // aplica o patch, independentemente de estado anterior
    WriteProcessMemory(hProcess, (LPVOID)g_precisionPatchAddr, patchedBytes.data(), patchedBytes.size(), nullptr);
    std::cout << " Precision ATIVADO em 0x" << std::hex << g_precisionPatchAddr << "\n";

    CloseHandle(hProcess);
}



void DisablePrecision() {
    std::wstring processName = L"HD-Player.exe";
    DWORD pid = GetProcessIdByName(processName);
    if (!pid || g_precisionPatchAddr == 0) {
        std::cout << " Processo não encontrado ou endereço inválido!\n";
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if (!hProcess) {
        std::cout << " Erro ao abrir processo\n";
        return;
    }

    const std::string restoreStr = "19 3F 00 00 80 3F 03 00 00 00 00 00 70 41 00 00 0C 42 00 00 20 41 00 00 A0 41 CD CC 4C 3D 00 00 40 3F 66 66";

    std::vector<Byte_t> restorePattern;
    std::string dummy;
    ParsePattern(restoreStr, restorePattern, dummy);

    WriteProcessMemory(hProcess, (LPVOID)g_precisionPatchAddr, restorePattern.data(), restorePattern.size(), nullptr);
    std::cout << "Precision desativado em 0x" << std::hex << g_precisionPatchAddr << "\n";

    CloseHandle(hProcess);
}
