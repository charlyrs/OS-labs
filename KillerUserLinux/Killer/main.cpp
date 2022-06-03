#include <iostream>
#include <string>
#include <sstream>


typedef unsigned long long llong;

class ProcessKiller {
public:
    bool killProcessById(llong id) {
        std::string command = "kill " + std::to_string(id);
        auto ret = system(command.c_str());
        return ret == 0;
    }

    bool killProcessByName(std::string name) {
        std::string command = "killall " + name;
        auto ret = system(command.c_str());
        return ret == 0;
    }

    void printState(bool killed, std::string name) {
        if (killed) {
            std::cout << "\n[Process " << name << " was successfuly terminated]";
        } else {
            std::cout << "\n[An error occured while trying to terminate process " << name << ']';
        }
    }
};

int main(int argc, char *argv[]) {
    ProcessKiller killer;
    auto var =getenv("PROC_TO_KILL");
    unsigned int count = 0;
    unsigned int all_processes = 0;
    if (var) {
        std::string str(var);
        std::stringstream ss(str);
        while (ss.getline(var, str.size(), ',')) {
            all_processes++;
            std::string name(var);
            auto killed = killer.killProcessByName(name);
            killer.printState(killed,name);
            count += killed;
        }
    }
    std::cout << "\n[" << count << " of " << all_processes << " PROC_TO_KILL processes were successfuly terminated]";
    return 0;
}
