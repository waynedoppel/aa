#pragma once
#include <Windows.h>
#include <vector>
#include <string>

using Byte_t = unsigned char;

DWORD GetProcessIdByName(const std::wstring& name);
void ParsePattern(const std::string& patternStr, std::vector<Byte_t>& pattern, std::string& mask);
std::vector<uintptr_t> FindAllPatterns(HANDLE hProcess, const std::vector<Byte_t>& pattern, const std::string& mask);
