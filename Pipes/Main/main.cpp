#include <iostream>
#include <string>
#include<unistd.h>
#define READ  0
#define STDIN 0
#define WRITE 1
#define STDOUT 1
const std::string proc[]{
        "../../M/cmake-build-debug/M",
        "../../A/cmake-build-debug/A",
        "../../P/cmake-build-debug/P",
        "../../S/cmake-build-debug/S"
};
int pipefd[2];

int main() {
    for (int i = 0; i < 3; i++) {
        if (pipe(pipefd) < 0){ std::exit(1); }
        auto pid = fork();
        if (pid == 0){
            dup2(pipefd[WRITE], STDOUT);
            system(proc[i].c_str());
            std::exit(0);
        }
        dup2(pipefd[READ], STDIN);
        close(pipefd[WRITE]);
        close(pipefd[READ]);
    }
    system(proc[3].c_str());
    return 0;
}
