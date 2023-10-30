#include "utils.h"

std::pair<int, unsigned long> getMemoryUsage() {
#ifdef _WIN32

    DWORD pid = GetCurrentProcessId();
    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!processHandle) {
        return std::make_pair(0, 0);
    }

    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(processHandle, &pmc, sizeof(pmc))) {
        CloseHandle(processHandle);
        return std::make_pair(pid, pmc.WorkingSetSize);
    }
    CloseHandle(processHandle);
    return std::make_pair(0, 0);


#elif __linux__

    pid_t pid = getpid();
    std::string filepath = "/proc/" + std::to_string(pid) + "/statm";
    std::ifstream file(filepath);
    unsigned long virt, rss;

    if (file >> virt >> rss) {
        file.close();

        return std::make_pair(pid, rss * sysconf(_SC_PAGESIZE));
    }
    file.close();
    return std::make_pair(0, 0);;

#else
    // Caso o sistema operacional não seja suportado
    return std::make_pair(0, 0);
#endif
}
