#include <iostream>
#include <string>
#include<unistd.h>
#define READ  0
#define WRITE 1
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
        bool f = fork();
        if (!f){
            if (dup2(pipefd[WRITE], WRITE) < 0) { exit(1); }
            system(proc[i].c_str());
            std::exit(0);
        }
        if (dup2(pipefd[READ], READ) < 0) { std::exit(1);}
        close(pipefd[WRITE]);
        close(pipefd[READ]);
    }
    system(proc[3].c_str());
    return 0;
}
