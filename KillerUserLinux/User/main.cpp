#include<iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

typedef unsigned long long llong;

struct process {
    const size_t ID;
    const std::wstring NAME;
    process(size_t id, std::wstring name) : ID(id), NAME(name) {};
};

class ProcessHandler {
    const std::string killer_path = "~/Labs/OS-labs/KillerUserLinux/Killer/cmake-build-debug/Killer";
public:
    // I do not know how get a list of processes like in WinApi so...just printing
    void printProcesses() {
        std::cout << '\n';
        system("ps -e");
        std::cout << '\n';
    }

    void killerProcess(std::string name) {
        system((killer_path + " " + name).c_str());
    }
};



int main() {
    ProcessHandler handler;
    handler.printProcesses();
    setenv("PROC_TO_KILL", "bash,", 0);
    handler.killerProcess("");
    handler.printProcesses();
    unsetenv("PROC_TO_KILL");
    return 0;
}