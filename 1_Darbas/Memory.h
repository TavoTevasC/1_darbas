#pragma once

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <fstream>
#endif

// Matoja atminties naudojimą (KB)
static size_t getProcessMemoryKB() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return static_cast<double>(pmc.WorkingSetSize) / 1024.0;
    }
    return 0;
#else
    std::ifstream f("/proc/self/status");
    if (!f.is_open()) return 0;
    std::string line;
    while (std::getline(f, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            std::istringstream iss(line);
            std::string key;
            size_t value;
            std::string unit;
            if (iss >> key >> value >> unit) {
                return static_cast<double>(value);
            }
        }
    }
    return 0;
#endif
} 