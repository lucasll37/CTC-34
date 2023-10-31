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
        return std::make_pair(pid, pmc.PagefileUsage);
    }
    CloseHandle(processHandle);
    return std::make_pair(0, 0);

#elif __linux__

    pid_t pid = getpid();
    std::string filepath = "/proc/" + std::to_string(pid) + "/status";
    std::ifstream file(filepath);
    std::string line;
    unsigned long vmSize = 0;

    while (std::getline(file, line)) {
        if (line.substr(0, 7) == "VmSize:") {
            std::istringstream iss(line);
            std::string key, value, unit;
            iss >> key >> value >> unit;
            vmSize = std::stol(value) * 1024;
            break;
        }
    }
    file.close();
    
    if(vmSize > 0) return std::make_pair(pid, vmSize);
    else return std::make_pair(0, 0);

#else

    return std::make_pair(0, 0);
#endif
}



#include <iostream>
#include <fstream>
#include <string>

bool checarOrdenacao(std::string palavraAnterior, std::string palavraAtual) {
    return palavraAnterior <= palavraAtual;
}

bool checkOrdenated(std::string pathToFile) {

    std::ifstream arquivo(pathToFile);

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo!" << std::endl;
        return false;
    }

    std::string palavraAtual, palavraAnterior;
    bool ordenado = true;
    int linha = 1;

    while (std::getline(arquivo, palavraAtual)) {
        if (linha > 1 && !checarOrdenacao(palavraAnterior, palavraAtual)) {
            std::cout << "As palavras não estão ordenadas lexicograficamente na linha " << linha << "." << std::endl;
            ordenado = false;
            break;
        }
        palavraAnterior = palavraAtual;
        linha++;
    }

    if (ordenado) {
        std::cout << "As palavras estão ordenadas lexicograficamente." << std::endl;
    }

    arquivo.close();
    return true;
}
